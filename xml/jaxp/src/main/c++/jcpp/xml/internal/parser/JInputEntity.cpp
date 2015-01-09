#include "jcpp/xml/internal/parser/JInputEntity.h"
#include "jcpp/xml/internal/util/JXmlChars.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JSystem.h"
#include "jcpp/lang/JInternalError.h"
#include "jcpp/io/JInputStreamReader.h"
#include "jcpp/io/JFileInputStream.h"

using namespace jcpp::io;
using namespace jcpp::xml::internal::util;

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace parser{

                JInputEntity::JInputEntity():JObject(getClazz()){
                    start=0;
                    finish=0;
                    buf=null;
                    lineNumber=1;
                    returnedFirstHalf=false;
                    maybeInCRLF=false;
                    name=null;
                    next=null;
                    input=null;
                    reader=null;
                    isClosed=false;
                    errHandler=null;
                    rememberedText=null;
                    startRemember=0;
                    isPE=false;
                }

                jint JInputEntity::BUFFER_SIZE = 8 * 1024 + 1;

                JInputEntity* JInputEntity::getInputEntity(JErrorHandler* h){
                    JInputEntity* retval = new JInputEntity();
                    retval->errHandler = h;
                    return retval;
                }

                jbool JInputEntity::isInternal(){
                    return reader == null;
                }

                jbool JInputEntity::isDocument(){
                    return next == null;
                }

                jbool JInputEntity::isParameterEntity(){
                    return isPE;
                }

                JString* JInputEntity::getName(){
                    return name;
                }

                void JInputEntity::init(JInputSource* in, JString* name, JInputEntity* stack,jbool isPE){
                    input = in;
                    this->isPE = isPE;
                    reader = in->getCharacterStream();

                    if (reader == null) {
                        JInputStream* bytes = in->getByteStream();

                        if (bytes == null) {
                            reader=new JInputStreamReader(new JFileInputStream(in->getSystemId()));

                        } else if (in->getEncoding() != null){
                            reader = new JInputStreamReader(in->getByteStream());//TODO ,in->getEncoding());
                        
                        }else{
                            reader = new JInputStreamReader(in->getByteStream());
                        }
                    }
                    next = stack;
                    buf = new JPrimitiveCharArray(BUFFER_SIZE);
                    this->name = name;
                    checkRecursion(stack);
                }

                void JInputEntity::init(JPrimitiveCharArray* b, JString* name,JInputEntity* stack, jbool isPE){
                    next = stack;
                    buf = b;
                    finish = b->size();
                    this->name = name;
                    this->isPE = isPE;
                    checkRecursion(stack);
                }

                void JInputEntity::checkRecursion(JInputEntity* stack){
                    if (stack == null){
                        return;
                    }
                    for (stack = stack->next; stack != null; stack = stack->next) {
                        if (stack->name != null && stack->name->equals(name)){
                            fatal(new JString("Error"));
                        }
                    }
                }

                JInputEntity* JInputEntity::pop(){
                    close();
                    return next;
                }

                jbool JInputEntity::isEOF(){
                    if (start >= finish) {
                        fillbuf ();
                        return start >= finish;
                    } else{
                        return false;
                    }
                }

                JString* JInputEntity::getEncoding(){
                    if (reader == null){
                        return null;
                    }
                
                    /*TODO
                    if (dynamic_cast<JObject*>(reader)->isInstanceOf(JInputStreamReader::getClazz())){
                        return (dynamic_cast<JInputStreamReader*>(reader))->getEncoding();
                    }*/
                    return null;
                }

                jchar JInputEntity::getNameChar(){
                    if (finish <= start){
                        fillbuf ();
                    }
                    if (finish > start) {
                        jchar c = buf->getChar(start++);
                        if (JXmlChars::isNameChar(c)){
                            return c;
                        }
                        start--;
                    }
                    return 0;
                }

                jchar JInputEntity::getc(){
                    if (finish <= start){
                        fillbuf ();
                    }
                    if (finish > start) {
                        jchar c = buf->getChar(start++);

                        if (returnedFirstHalf) {
                            if (c >= 0xdc00 && c <= 0xdfff) {
                                returnedFirstHalf = false;
                                return c;

                            } else{
                                fatal(new JString("Error"));
                            }
                        }

                        if ((c >= 0x0020 && c <= 0xD7FF) || c == 0x0009 || (c >= 0xE000 && c <= 0xFFFD)){
                            return c;

                        }else if (c == '\r' && !isInternal()) {
                            maybeInCRLF = true;
                            c =getc ();
                            if (c != '\n'){
                                ungetc ();
                            }
                            maybeInCRLF = false;
                            lineNumber++;
                            return '\n';

                        } else if (c == '\n' || c == '\r') {
                            if (!isInternal () && !maybeInCRLF){
                                lineNumber++;
                            }
                            return c;
                        }

                        if (c >= ((jchar)0xd800) && c < ((jchar)0xdc00)) {
                            returnedFirstHalf = true;
                            return c;
                        }
                        fatal(new JString("Error"));
                    }
                    throw new JIOException();
                }

                jbool JInputEntity::peekc(jchar c){
                    if (finish <= start){
                        fillbuf();
                    }
                    if (finish > start) {
                        if (buf->getChar(start) == c) {
                            start++;
                            return true;
                        } else{
                            return false;
                        }
                    }
                    return false;
                }

                void JInputEntity::ungetc(){
                    if (start == 0){
                        throw new JInternalError(new JString("ungetc"));
                    }
                    start--;

                    if (buf->getChar(start) == '\n' || buf->getChar(start) == '\r') {
                        if (!isInternal ()){
                            lineNumber--;
                        }

                    } else if (returnedFirstHalf){
                        returnedFirstHalf = false;
                    }
                }

                jbool JInputEntity::maybeWhitespace(){
                    jchar c=0;
                    jbool isSpace = false;
                    jbool sawCR = false;

                    for (;;) {
                        if (finish <= start){
                            fillbuf();
                        }

                        if (finish <= start){
                            return isSpace;
                        }

                        c = buf->getChar(start++);
                        if (c == 0x20 || c == 0x09 || c == '\n' || c == '\r') {
                            isSpace = true;

                            if ((c == '\n' || c == '\r') && !isInternal()) {
                                if (!(c == '\n' && sawCR)) {
                                    lineNumber++;
                                    sawCR = false;
                                }

                                if (c == '\r'){
                                    sawCR = true;
                                }
                            }

                        } else {
                            start--;
                            return isSpace;
                        }
                    }
                }

                jbool JInputEntity::parsedContent(JContentHandler* contentHandler,JElementValidator* validator){
                    jint first=0;
                    jint last=0;
                    jbool sawContent=false;
                    jchar c=0;

                    for (first = last = start, sawContent = false; ; last++) {
                        if (last >= finish) {
                            if (last > first) {
                                validator->text();
                                contentHandler->characters(buf, first, last - first);
                                sawContent = true;
                                start = last;
                            }

                            if (isEOF ()){
                                return sawContent;
                            }
                        
                            first = start;
                            last = first - 1;   // incremented in loop
                            continue;
                        }

                        c = buf->getChar(last);

                        if ((c >  0x005D && c <= 0xD7FF)
                            || (c <  0x0026 && c >= 0x0020)
                            || (c >  0x003C && c <  0x005D)
                            || (c >  0x0026 && c <  0x003C)
                            ||  c == 0x0009
                            || (c >= 0xE000 && c <= 0xFFFD)
                            ){
                            continue;
                        }

                        if (c == '<' || c == '&'){
                            break;
                        }

                        if (c == '\n') {
                            if (!isInternal()){
                                lineNumber++;
                            }
                            continue;
                        }

                        if (c == '\r') {
                            if (isInternal ()){
                                continue;
                            }

                            contentHandler->characters(buf, first, last - first);
                            contentHandler->characters(JSystem::lineSeparator()->toCharArray(), 0, 1);
                            sawContent = true;
                            lineNumber++;
                            if (finish > (last + 1)) {
                                if (buf->getChar(last + 1) == '\n'){
                                    last++;
                                }

                            } else {
                            }
                            start = last + 1;
                            first = start;
                            continue;
                        }

                        if (c == ']') {
                            switch (finish - last) {
                                case 2:
                                    if (buf->getChar(last + 1) != ']') {
                                        continue;
                                    }

                                case 1:
                                    if (reader == null || isClosed){
                                        continue;
                                    }
                                    if (last == first){
                                        throw new JInternalError(new JString("fillbuf"));
                                    }
                                    last--;
                                    if (last > first) {
                                        validator->text();
                                        contentHandler->characters(buf, first, last - first);
                                        sawContent = true;
                                        start = last;
                                    }
                                    fillbuf();
                                    last = start;
                                    first = last;
                                    continue;

                                default:
                                    if (buf->getChar(last + 1) == ']' && buf->getChar(last + 2) == '>'){
                                        fatal(new JString("Error"));
                                    }
                                    continue;
                            }
                        }

                        if (c >= 0xd800 && c <= 0xdfff) {
                            if ((last + 1) >= finish) {
                                if (last > first) {
                                    validator->text();
                                    contentHandler->characters(buf, first, last - first);
                                    sawContent = true;
                                    start = last + 1;
                                }
 
                                if (isEOF ()) {
                                    fatal(new JString("Error"));
                                }
                                first = start;
                                last = first ;
                                continue;
                            }

                            if (checkSurrogatePair(last)){
                                last++;
                            }else {
                                last--;
                                break;
                            }
                            continue;
                        } 
                        fatal(new JString("Error"));
                    }
                    if (last == first){
                        return sawContent;
                    }
                    validator->text();
                    contentHandler->characters(buf, first, last - first);
                    start = last;
                    return true;
                }
                
                void JInputEntity::unparsedContent(JContentHandler* contentHandler,JElementValidator* validator,jbool ignorableWhitespace,JString* whitespaceInvalidMessage){
                    jint last=0;

                    for (;;) {
                        jbool done = false;
                        jchar c=0;
                        jbool white = ignorableWhitespace;

                        for (last = start; last < finish; last++) {
                            c = buf->getChar(last);

                            if (!JXmlChars::isChar(c)) {
                                white = false;
                                if (c >= 0xd800 && c <= 0xdfff) {
                                    if (checkSurrogatePair(last)) {
                                        last++;
                                        continue;

                                    } else {
                                        last--;
                                        break;
                                    }
                                }
                                fatal(new JString("Error"));
                            }

                            if (c == '\n') {
                                if (!isInternal()){
                                    lineNumber++;
                                }
                                continue;
                            }

                            if (c == '\r') {
                                if (isInternal()){
                                    continue;
                                }

                                if (white) {
                                    if (whitespaceInvalidMessage != null){
                                        errHandler->error (new JSAXParseException (whitespaceInvalidMessage));
                                    }
                                    contentHandler->ignorableWhitespace (buf, start,last - start);
                                    contentHandler->ignorableWhitespace (JSystem::lineSeparator()->toCharArray(), 0, 1);
                                } else {
                                    validator->text();
                                    contentHandler->characters(buf, start, last - start);
                                    contentHandler->characters(JSystem::lineSeparator()->toCharArray(), 0, 1);
                                }
                                lineNumber++;

                                if (finish > (last + 1)) {
                                    if (buf->getChar(last + 1) == '\n'){
                                        last++;
                                    }

                                }
                                start = last + 1;
                                continue;
                            }

                            if (c != ']') {
                                if (c != ' ' && c != '\t'){
                                    white = false;
                                }
                                continue;
                            }

                            if ((last + 2) < finish) {
                                if (buf->getChar(last + 1) == ']' && buf->getChar(last + 2) == '>') {
                                    done = true;
                                    break;
                                }
                                white = false;
                                continue;
                            } else {
                                break;
                            }
                        }

                        if (white) {
                            if (whitespaceInvalidMessage != null){
                                errHandler->error(new JSAXParseException(whitespaceInvalidMessage));
                            }
                            contentHandler->ignorableWhitespace (buf, start, last - start);

                        } else {
                            validator->text();
                            contentHandler->characters (buf, start, last - start);
                        }

                        if (done) {
                            start = last + 3;
                            break;
                        }
                        start = last;
                        fillbuf();
                        if (isEOF ()){
                            fatal(new JString("Error"));
                        }
                    }
                }

                jbool JInputEntity::checkSurrogatePair(jint offset){
                    if ((offset + 1) >= finish){
                        return false;
                    }

                    jchar c1 = buf->getChar(offset++);
                    jchar c2 = buf->getChar(offset);

                    if ((c1 >= 0xd800 && c1 < 0xdc00) && (c2 >= 0xdc00 && c2 <= 0xdfff)){
                        return true;
                    }
                    fatal(new JString("Error"));
                    return false;
                }

                jbool JInputEntity::ignorableWhitespace(JContentHandler* handler){
                    jchar c=0;
                    jbool isSpace = false;
                    jint first=0;

                    for (first = start;;) {
                        if (finish <= start) {
                            if (isSpace){
                                handler->ignorableWhitespace(buf, first, start - first);
                            }
                            fillbuf();
                            first = start;
                        }

                        if (finish <= start){
                            return isSpace;
                        }

                        c = buf->getChar(start++);
                        switch (c) {
                            case '\n':
                                if (!isInternal()){
                                    lineNumber++;
                                }

                            case 0x09:
                            case 0x20:
                                isSpace = true;
                                continue;

                            case '\r':
                                isSpace = true;
                                if (!isInternal()){
                                    lineNumber++;
                                }
                                handler->ignorableWhitespace(buf, first,(start - 1) - first);
                                handler->ignorableWhitespace(JSystem::lineSeparator()->toCharArray(), 0, 1);
                                
                                if (start < finish && buf->getChar(start) == '\n'){
                                    ++start;
                                }
                                first = start;
                                continue;

                            default:
                                ungetc();
                                if (isSpace){
                                    handler->ignorableWhitespace (buf, first, start - first);
                                }
                                return isSpace;
                        }
                    }
                }

                jbool JInputEntity::peek(JString* next, JPrimitiveCharArray* chars){
                    jint len=0;
                    jint i=0;

                    if (chars != null){
                        len = chars->size();
                    }else{
                        len = next->length();
                    }

                    if (finish <= start || (finish - start) < len){
                        fillbuf();
                    }

                    if (finish <= start){
                        return false;
                    }

                    if (chars != null) {
                        for (i = 0; i < len && (start + i) < finish; i++) {
                            if (buf->getChar(start + i) != chars->getChar(i)) {
                                return false;
                            }
                        }

                    } else {
                        for (i = 0; i < len && (start + i) < finish; i++) {
                            if (buf->getChar(start + i) != next->charAt(i)){
                                return false;
                            }
                        }
                    }

                    if (i < len) {
                        if (reader == null || isClosed){
                            return false;
                        }
                        
                        if (len > buf->size()){
                            fatal(new JString("Error"));
                        }
                        fillbuf();
                        return peek(next, chars);
                    }
                    start += len;
                    return true;
                }

                jbool JInputEntity::isXmlDeclOrTextDeclPrefix(){
                    JString* match = new JString("<?xml");
                    jint matchLen = match->length();
                    jint prefixLen = matchLen + 1;

                    if (finish <= start || (finish - start) < prefixLen){
                        fillbuf ();
                    }

                    if (finish <= start){
                        return false;
                    }

                    jint i=0;
                    for (i = 0; i < matchLen && (start + i) < finish; i++) {
                        if (buf->getChar(start + i) != match->charAt(i)){
                            return false;
                        }
                    }

                    if (i < matchLen) {
                        if (reader == null || isClosed){
                            return false;
                        }
                        
                        fillbuf ();
                        return isXmlDeclOrTextDeclPrefix();
                    }

                    if (!JXmlChars::isSpace(buf->getChar(i))) {
                        return false;
                    }

                    return true;
                }

                void JInputEntity::startRemembering(){
                    if (startRemember != 0){
                        throw new JInternalError();
                    }
                    startRemember = start;
                }

                JString* JInputEntity::rememberText(){
                    JString* retval=null;

                    if (rememberedText != null) {
                        rememberedText->append(buf, startRemember,start - startRemember);
                        retval = rememberedText->toString();

                    } else{
                        retval = new JString(buf, startRemember,start - startRemember);
                    }

                    startRemember = 0;
                    rememberedText = null;
                    return retval;
                }

                JLocator* JInputEntity::getLocator(){
                    JInputEntity* current = this;
                    while (current != null && current->input == null){
                        current = current->next;
                    }
                    return current == null ? this : current;
                }

                JString* JInputEntity::getPublicId(){
                    JLocator* where = getLocator();
                    if (where == this){
                        return input->getPublicId();
                    }
                    return where->getPublicId();
                }

                JString* JInputEntity::getSystemId(){
                    JLocator* where = getLocator();
                    if (where == this){
                        return input->getSystemId();
                    }
                    return where->getSystemId();
                }

                jint JInputEntity::getLineNumber(){
                    JLocator* where = getLocator();
                    if (where == this){
                        return lineNumber;
                    }
                    return where->getLineNumber();
                }

                jint JInputEntity::getColumnNumber(){
                    return -1;
                }

                void JInputEntity::fillbuf(){
                    if (reader == null || isClosed){
                        return;
                    }
                    
                    if (startRemember != 0) {
                        if (rememberedText == null){
                            rememberedText = new JStringBuffer();
                        }
                        rememberedText->append(buf, startRemember,start - startRemember);
                    }
                    
                    jbool extra = (finish > 0) && (start > 0);
                    jint len=0;

                    if (extra){
                        start--;
                    }
                    len = finish - start;

                    JSystem::arraycopy(buf, start, buf, 0, len);
                    start = 0;
                    finish = len;

                    len = buf->size() - len;
                    len = reader->read(buf, finish, len);

                    if (len >= 0){
                        finish += len;
                    }else{
                        close();
                    }
                    if (extra){
                        start++;
                    }
                    if (startRemember != 0){
                        startRemember = 1;
                    }
                }

                void JInputEntity::close(){
                    try {
                        if (reader != null && !isClosed){
                            reader->close();
                        }
                        isClosed = true;
                    } catch(JIOException* e) {
                    }
                }

                void JInputEntity::fatal(JString* messageId){
                    JSAXParseException* x = new JSAXParseException(messageId);
                    close();
                    errHandler->fatalError(x);
                    throw x;
                }

                JInputEntity::~JInputEntity(){
                }
            }
        }
    }
}
