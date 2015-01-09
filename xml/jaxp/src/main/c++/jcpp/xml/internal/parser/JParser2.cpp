#include "jcpp/xml/internal/parser/JParser2.h"
#include "jcpp/xml/internal/parser/JInternalEntity.h"
#include "jcpp/xml/internal/parser/JExternalEntity.h"
#include "jcpp/xml/internal/parser/JResolver.h"
#include "jcpp/xml/internal/util/JXmlChars.h"
#include "jcpp/xml/internal/util/JXmlNames.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JBoolean.h"
#include "jcpp/lang/JSystem.h"
#include "jcpp/lang/JException.h"
#include "jcpp/lang/JInternalError.h"
#include "org/xml/sax/JSAXException.h"
#include "org/xml/sax/JSAXParseException.h"

using namespace jcpp::xml::internal::util;

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace parser{

                JParser2::JParser2(JClass* _class):JObject(_class){
                    in=null;
                    attTmp=null;
                    strTmp=null;
                    nameTmp=null;
                    nameCache=null;
                    charTmp= new JPrimitiveCharArray(2);
                    namePartsTmp = new JPrimitiveObjectArray(JString::getClazz(),3);
                    seenNSDecl=false;
                    nsSupport=null;
                    nsAttTmp=null;
                    isValidating = false;
                    fastStandalone = false;
                    isInAttribute = false;
                    namespaces=null;
                    prefixes=false;
                    inExternalPE=false;
                    doLexicalPE=false;
                    donePrologue=false;
                    isStandalone=false;
                    rootElementName=null;
                    ignoreDeclarations=false;
                    elements = new JHashtable(47);
                    params = new JHashtable(7);
                    notations = new JHashtable(7);
                    entities = new JHashtable(17);
                    contentHandler=null;
                    dtdHandler=null;
                    resolver=null;
                    errHandler=null;
                    locator=null;
                    declHandler=null;
                    lexicalHandler=null;
                    locator=new JDocLocator(this);
                    setHandlers();
                }

                JParser2::JParser2():JObject(getClazz()){
                    in=null;
                    attTmp=null;
                    strTmp=null;
                    nameTmp=null;
                    nameCache=null;
                    charTmp= new JPrimitiveCharArray(2);
                    namePartsTmp = new JPrimitiveObjectArray(JString::getClazz(),3);
                    seenNSDecl=false;
                    nsSupport=null;
                    nsAttTmp=null;
                    isValidating = false;
                    fastStandalone = false;
                    isInAttribute = false;
                    namespaces=null;
                    prefixes=false;
                    inExternalPE=false;
                    doLexicalPE=false;
                    donePrologue=false;
                    isStandalone=false;
                    rootElementName=null;
                    ignoreDeclarations=false;
                    elements = new JHashtable(47);
                    params = new JHashtable(7);
                    notations = new JHashtable(7);
                    entities = new JHashtable(17);
                    contentHandler=null;
                    dtdHandler=null;
                    resolver=null;
                    errHandler=null;
                    declHandler=null;
                    lexicalHandler=null;
                    locator=new JDocLocator(this);
                    setHandlers();
                }
                
                JParser2::JDocLocator::JDocLocator(JParser2* parser2):JObject(getClazz()){
                    this->parser2=parser2;
                }

                JString* JParser2::JDocLocator::getPublicId(){
                    return (parser2->in == null) ? null : parser2->in->getPublicId();
                }

                JString* JParser2::JDocLocator::getSystemId(){
                    return (parser2->in == null) ? null : parser2->in->getSystemId();
                }

                jint JParser2::JDocLocator::getLineNumber(){
                    return (parser2->in == null) ? -1 : parser2->in->getLineNumber();
                }

                jint JParser2::JDocLocator::getColumnNumber(){
                    return (parser2->in == null) ? -1 : parser2->in->getColumnNumber();
                }

                JParser2::JDocLocator::~JDocLocator(){
                }

                JParser2::JNameCacheEntry::JNameCacheEntry():JObject(getClazz()){
                    name=null;
                    chars=null;
                    next=null;
                }

                jbool JParser2::JNameCacheEntry::matches(JPrimitiveCharArray* value, jint len){
                    if (chars->size() != len){
                        return false;
                    }
                    for (jint i = 0; i < len; i++){
                        if (value->getChar(i) != chars->getChar(i)){
                            return false;
                        }
                    }
                    return true;
                }

                JParser2::JNameCacheEntry::~JNameCacheEntry(){
                }

                JParser2::JNameCache::JNameCache():JObject(getClazz()){
                    hashtable=new JPrimitiveObjectArray(JParser2::JNameCacheEntry::getClazz(),541);
                }

                JString* JParser2::JNameCache::lookup(JPrimitiveCharArray* value, jint len){
                    return lookupEntry(value, len)->name;
                }

                JParser2::JNameCacheEntry* JParser2::JNameCache::lookupEntry(JPrimitiveCharArray* value, jint len){
                    jint index = 0;
                    JParser2::JNameCacheEntry* entry=null;

                    for (jint i = 0; i < len; i++){
                        index = index * 31 + value->getChar(i);
                    }
                    index &= 0x7fffffff;
                    index %= hashtable->size();

                    for (entry = dynamic_cast<JNameCacheEntry*>(hashtable->get(index));entry != null;entry = entry->next) {
                        if (entry->matches(value, len)){
                            return entry;
                        }
                    }

                    entry = new JNameCacheEntry();
                    entry->chars = new JPrimitiveCharArray(len);
                    JSystem::arraycopy(value, 0, entry->chars, 0, len);
                    entry->name = new JString(entry->chars);
                    entry->next = dynamic_cast<JNameCacheEntry*>(hashtable->get(index));
                    hashtable->set(index, entry);
                    return entry;
                }

                JParser2::JNameCache::~JNameCache(){
                }
    
                JParser2::JNullHandler::JNullHandler():JDefaultHandler(getClazz()){
                }

                void JParser2::JNullHandler::startDTD(JString* name, JString* publicId, JString* systemId){
                }

                void JParser2::JNullHandler::endDTD(){
                }

                void JParser2::JNullHandler::startEntity(JString* name){
                }

                void JParser2::JNullHandler::endEntity(JString* name){
                }

                void JParser2::JNullHandler::startCDATA(){
                }

                void JParser2::JNullHandler::endCDATA(){
                }

                void JParser2::JNullHandler::comment(JPrimitiveCharArray* ch, jint start, jint length){
                }

                void JParser2::JNullHandler::elementDecl(JString* name, JString* model){
                }

                void JParser2::JNullHandler::attributeDecl(JString* eName, JString* aName, JString* type,JString* valueDefault, JString* value){
                }

                void JParser2::JNullHandler::internalEntityDecl(JString* name, JString* value){
                }

                void JParser2::JNullHandler::externalEntityDecl(JString* name, JString* publicId,JString* systemId){
                }

                JParser2::JNullHandler::~JNullHandler(){
                }

                jbool JParser2::supportValidation = true;
                JString* JParser2::strANY = new JString("ANY");
                JString* JParser2::strEMPTY = new JString("EMPTY");
                JParser2::JNullHandler* JParser2::nullHandler = new JParser2::JNullHandler();
                JString* JParser2::XmlLang = new JString("xml:lang");

                void JParser2::setNamespaceFeatures(jbool namespaces, jbool prefixes){
                    this->namespaces = namespaces;
                    this->prefixes = prefixes;
                }

                void JParser2::setEntityResolver(JEntityResolver* resolver){
                    this->resolver = resolver;
                }

                void JParser2::setDTDHandler(JDTDHandler* handler){
                    dtdHandler = handler;
                }

                void JParser2::setContentHandler(JContentHandler* handler){
                    contentHandler = handler;
                }

                void JParser2::setErrorHandler(JErrorHandler* handler){
                    errHandler = handler;
                }

                void JParser2::setLexicalHandler(JLexicalHandler* handler){
                    lexicalHandler = handler;
                }

                void JParser2::setDeclHandler(JDeclHandler* handler) {
                    declHandler = handler;
                }

                void JParser2::parse(JInputSource* in){
                    init();
                    parseInternal(in);
                }

                void JParser2::setFastStandalone(jbool value){ 
                    fastStandalone = value && !isValidating; 
                }

                jbool JParser2::isFastStandalone(){ 
                    return fastStandalone; 
                }

                void JParser2::pushInputBuffer(JPrimitiveCharArray* buf, jint offset, jint len){
                    if (len <= 0){
                        return;
                    }

                    if (offset != 0 || len != buf->size()) {
                        JPrimitiveCharArray* tmp = new JPrimitiveCharArray(len);
                        JSystem::arraycopy(buf, offset, tmp, 0, len);
                        buf = tmp;
                    }
                    pushReader(buf, null, false);
                }

                void JParser2::setIsValidating(jbool value){
                    if (supportValidation){
                        isValidating = value;
                    }else{
                        throw new JRuntimeException(new JString("validation not supported"));
                    }
                    if (value){
                        fastStandalone = false;
                    }
                }

                void JParser2::init (){
                    in = null;

                    attTmp = new JAttributesExImpl();
                    strTmp = new JStringBuffer();
                    nameTmp = new JPrimitiveCharArray(20);
                    nameCache = new JNameCache();

                    if (namespaces) {
                        nsSupport = new JNamespaceSupport();
                        if (supportValidation && isValidating && !prefixes) {
                            nsAttTmp = new JVector();
                        }
                    }

                    isStandalone = false;
                    rootElementName = null;
                    isInAttribute = false;

                    inExternalPE = false;
                    doLexicalPE = false;
                    donePrologue = false;

                    entities->clear();
                    notations->clear();
                    params->clear();
                    elements->clear();
                    ignoreDeclarations = false;

                    builtin(new JString("amp"), new JString("&#38;"));
                    builtin(new JString("lt"), new JString("&#60;"));
                    builtin(new JString("gt"), new JString(">"));
                    builtin(new JString("quot"), new JString("\""));
                    builtin(new JString("apos"), new JString("'"));

                    if (resolver == null){
                        resolver = new JResolver ();
                    }
                    setHandlers ();
                }

                void JParser2::setHandlers(){
                    if (contentHandler == null) {
                        contentHandler = nullHandler;
                    }
                    if (errHandler == null) {
                        errHandler = nullHandler;
                    }
                    if (dtdHandler == null) {
                        dtdHandler = nullHandler;
                    }
                    if (lexicalHandler == null) {
                        lexicalHandler = nullHandler;
                    }
                    if (declHandler == null) {
                        declHandler = nullHandler;
                    }
                }

                void JParser2::builtin(JString* entityName, JString* entityValue){
                    JInternalEntity* entity = new JInternalEntity(entityName, entityValue->toCharArray());
                    entities->put(entityName, entity);
                }

                void JParser2::parseInternal(JInputSource* input){
                    if (input == null){
                        fatal(new JString("empty input source"));
                    }

                    JException* th=null;
                    try {
                        in = JInputEntity::getInputEntity(errHandler);
                        in->init(input, null, null, false);


                        contentHandler->setDocumentLocator(locator);
                        contentHandler->startDocument();

                        maybeXmlDecl();
                        maybeMisc(false);
                        
                        if (!maybeDoctypeDecl ()) {
                            if (supportValidation && isValidating){
                                warning(new JString("Error"));
                            }
                        }
                        
                        maybeMisc(false);
                        donePrologue = true;
                        
                        if (!in->peekc('<') || !maybeElement(null)){
                            fatal(new JString("Should be start of an element."));
                        }

                        afterRoot();
                        maybeMisc(true);
                        if (!in->isEOF()){
                            fatal(new JString("The stream should be emtpy."));
                        }
                        contentHandler->endDocument();

                    } catch(JException* e) {
                        e->printStackTrace();
                        th=e;
                    } 
                    strTmp = null;
                    attTmp = null;
                    nameTmp = null;
                    nameCache = null;
                    nsAttTmp = null;

                    if (in != null) {
                        in->close();
                        in = null;
                    }
                    params->clear();
                    entities->clear();
                    notations->clear();
                    elements->clear();

                    afterDocument();
                    if (th!=null){
                        fatal(new JString("Error while parsing the file"), th);
                    }
                }

                void JParser2::afterRoot(){
                }

                void JParser2::afterDocument(){
                }

                void JParser2::whitespace(JString* roleId){
                    if (!maybeWhitespace()){
                        fatal(new JString("whitespace expected"));
                    }
                }

                jbool JParser2::maybeWhitespace(){
                     if (!(inExternalPE && doLexicalPE)){
                        return in->maybeWhitespace();
                    }

                    jchar c = getc();
                    jbool saw = false;

                    while (c == ' ' || c == '\t' || c == '\n' || c == '\r') {
                        saw = true;
                        if (in->isEOF() && !in->isInternal()){
                            return saw;
                        }
                        c = getc();
                    }
                    ungetc();
                    return saw;
                }

                JString* JParser2::maybeGetName(){
                    JNameCacheEntry*  entry = maybeGetNameCacheEntry();
                    return (entry == null) ? null : entry->name;
                }

                JParser2::JNameCacheEntry* JParser2::maybeGetNameCacheEntry(){
                    jchar c = getc();
                    if (!JXmlChars::isLetter(c) && c != ':' && c != '_') {
                        ungetc();
                        return null;
                    }
                    return nameCharString(c);
                }

                JString* JParser2::getNmtoken(){
                    jchar c = getc();
                    if (!JXmlChars::isNameChar(c)){
                        fatal (new JString("Should be a character name"));
                    }
                    return nameCharString(c)->name;
                }

                JParser2::JNameCacheEntry* JParser2::nameCharString(jchar c){
                    jint i = 1;
                    nameTmp->setChar(0, c);
                    for (;;) {
                        if ((c = in->getNameChar()) == 0){
                            break;
                        }
                        if (i >= nameTmp->size()) {
                            JPrimitiveCharArray* tmp = new JPrimitiveCharArray(nameTmp->size() + 10);
                            JSystem::arraycopy (nameTmp, 0, tmp, 0, nameTmp->size());
                            nameTmp = tmp;
                        }
                        nameTmp->setChar(i++, c);
                    }
                    return nameCache->lookupEntry(nameTmp, i);
                }

                void JParser2::parseLiteral(jbool isEntityValue){
                    jbool savedLexicalPE = doLexicalPE;
                    jchar quote = getc();
                    jchar c=0;
                    JInputEntity* source = in;

                    if (quote != '\'' && quote != '"'){
                        fatal(new JString("Error"));
                    }
                    isInAttribute = !isEntityValue;
                    strTmp = new JStringBuffer();

                    for (;;) {
                        if (in != source && in->isEOF()) {
                            in = in->pop();
                            continue;
                        }
                        if ((c =getc()) == quote && in == source){
                            break;
                        }

                        if (c == '&') {
                            JString* entityName =maybeGetName();

                            if (entityName != null) {
                                nextChar(';', new JString("Error"), entityName);
                                if (isEntityValue) {
                                    strTmp->append('&');
                                    strTmp->append(entityName);
                                    strTmp->append(';');
                                    continue;
                                }
                                expandEntityInLiteral(entityName, entities, isEntityValue);

                            } else if ((c = getc()) == '#') {
                                jint tmp=parseCharNumber();

                                if (tmp > 0xffff) {
                                    tmp = surrogatesToCharTmp(tmp);
                                    strTmp->append(charTmp->getChar(0));
                                    if (tmp == 2){
                                        strTmp->append(charTmp->getChar(1));
                                    }
                                } else{
                                    strTmp->append((jchar)tmp);
                                }
                            } else{
                                fatal(new JString("Error"));
                            }
                            continue;
                        }

                        if (c == '%' && isEntityValue) {
                            JString* entityName=maybeGetName();

                            if (entityName != null){
                                nextChar(';', new JString("Error"), entityName);
                                if (inExternalPE){
                                    expandEntityInLiteral(entityName,params, isEntityValue);

                                }else{
                                    fatal(new JString("Error"));
                                }
                                continue;
                            } else{
                                fatal(new JString("Error"));
                            }
                        }

                        if (!isEntityValue) {
                            if (c == ' ' || c == '\t' || c == '\n' || c == '\r') {
                                strTmp->append(' ');
                                continue;
                            }
                            if (c == '<'){
                                fatal(new JString("Error"));
                            }
                        }
                        strTmp->append(c);
                    }
                    isInAttribute = false;
                }

                void JParser2::expandEntityInLiteral(JString* name,JHashtable* table,jbool isEntityValue){
                    JObject* entity = table->get(name);

                    if (entity->isInstanceOf(JInternalEntity::getClazz())) {
                        JInternalEntity* value = dynamic_cast<JInternalEntity*>(entity);
                        if (supportValidation && isValidating && isStandalone && !value->isFromInternalSubset){
                            error(new JString("Error"));
                        }
                        pushReader(value->buf, name, !value->isPE);

                    } else if (entity->isInstanceOf(JExternalEntity::getClazz())) {
                        if (!isEntityValue){
                            fatal(new JString("Error"));
                        }
                        pushReader(dynamic_cast<JExternalEntity*>(entity));

                    } else if (entity == null) {
                        fatal(new JString("Error"));
                    }
                }

                JString* JParser2::getQuotedString(JString* type, JString* extra){
                    jchar quote = in->getc();

                    if (quote != '\'' && quote != '"'){
                        fatal(new JString("Error"));
                    }
                    jchar c=0;

                    strTmp = new JStringBuffer();
                    while ((c = in->getc()) != quote){
                        strTmp->append((jchar)c);
                    }
                    return strTmp->toString();
                }

                JString* JParser2::parsePublicId(){
                    JString* retval = getQuotedString(new JString("Error"), null);
                    for (jint i = 0; i < retval->length(); i++) {
                        jchar c = retval->charAt(i);
                        if ((new JString(" \r\n-'()+,./:=?;!*#@$_%0123456789"))->indexOf(c) == -1 && !(c >= 'A' && c <= 'Z') && !(c >= 'a' && c <= 'z')){
                            fatal(new JString("Error"));
                        }
                    }
                    strTmp = new JStringBuffer();
                    strTmp->append(retval);
                    return normalize(false);
                }

                jbool JParser2::maybeComment(jbool skipStart){
                    if (!in->peek(skipStart ? new JString("!--") : new JString("<!--"), null)){
                        return false;
                    }
                    jbool savedLexicalPE = doLexicalPE;
                    doLexicalPE = false;
                    jbool saveCommentText = lexicalHandler != nullHandler;
                    if (saveCommentText) {
                        strTmp = new JStringBuffer();
                    }

                    jbool stop=false;
                    for (;!stop;) {
                        try {
                            for (;!stop;) {
                                jint c = getc();
                                if (c == '-') {
                                    c = getc();
                                    if (c !='-') {
                                        if (saveCommentText){
                                            strTmp->append('-');
                                        }
                                        ungetc();
                                        continue;
                                    }
                                    nextChar('>', new JString("Error"), null);
                                    stop=true;
                                    break;
                                }
                                if (saveCommentText){
                                    strTmp->append((jchar)c);
                                }
                            }
                        } catch(JIOException* e) {
                            if (inExternalPE || (!donePrologue && in->isInternal())) {
                                if (supportValidation && isValidating){
                                    error(new JString("Error"),e);
                                }
                                in=in->pop();
                                continue;
                            }
                            fatal(new JString("Error"));
                        }
                    }
                    doLexicalPE = savedLexicalPE;
                    if (saveCommentText) {
                        jint length = strTmp->length();
                        JPrimitiveCharArray* charArray = new JPrimitiveCharArray(length);
                        if (length != 0) {
                            strTmp->getChars(0, length, charArray, 0);
                        }
                        lexicalHandler->comment(charArray, 0, length);
                    }
                    return true;
                }

                jbool JParser2::maybePI(jbool skipStart){
                    jbool savedLexicalPE = doLexicalPE;
                    if (!in->peek(skipStart ? new JString("?") : new JString("<?"), null)){
                        return false;
                    }
                    doLexicalPE = false;
                    JString* target = maybeGetName();

                    if (target == null){
                        fatal(new JString("Error"));
                    }
                    if ((new JString("xml"))->equals(target)){
                        fatal(new JString("Error"));
                    }
                    if ((new JString("xml"))->equalsIgnoreCase(target)){
                        fatal(new JString("Error"));
                    }
                    if (maybeWhitespace()){
                        strTmp = new JStringBuffer();
                        try {
                            for (;;){
                                jchar c = in->getc();
                                if (c == '?' && in->peekc('>')){
                                    break;
                                }
                                strTmp->append(c);
                            }
                        } catch(JIOException* e) {
                            fatal(new JString("Error"));
                        }
                        contentHandler->processingInstruction(target, strTmp->toString());
                    } else {
                        if (!in->peek(new JString("?>"), null)){
                            fatal(new JString("Error"));
                        }
                        contentHandler->processingInstruction(target, new JString(""));
                    }
                    doLexicalPE = savedLexicalPE;
                    return true;
                }

                void JParser2::maybeXmlDecl(){
                    if (!in->isXmlDeclOrTextDeclPrefix()) {
                        return;
                    }
                    peek(new JString("<?xml"));
                    readVersion(true, new JString("1.0"));
                    readEncoding(false);
                    readStandalone();
                    maybeWhitespace();
                    if (!peek(new JString("?>"))) {
                        jchar c = getc();
                        fatal(new JString("Error"));
                    }
                }

                JString* JParser2::maybeReadAttribute(JString* name, jbool must){
                    if (!maybeWhitespace()) {
                        if (!must){
                            return null;
                        }
                        fatal(new JString("Error"));
                    }

                    if (!peek(name)){
                        if (must){
                            fatal(new JString("Error"));
                        }else {
                            ungetc();
                            return null;
                        }
                    }

                    maybeWhitespace();
                    nextChar('=', new JString("Error"),null);
                    maybeWhitespace();
                    return getQuotedString(new JString("Error"), name);
                }

                void JParser2::readVersion(jbool must, JString* versionNum){
                    JString*  value = maybeReadAttribute(new JString("version"), must);
                    if (must && value == null){
                        fatal(new JString("Error"));
                    }
                    if (value != null) {
                        jint length = value->length();
                        for (jint i = 0; i < length; i++) {
                            jchar c = value->charAt (i);
                            if (!(    (c >= '0' && c <= '9')
                                    || c == '_' || c == '.'
                                    || (c >= 'a' && c <= 'z')
                                    || (c >= 'A' && c <= 'Z')
                                    || c == ':' || c == '-')
                                    ){
                                fatal(new JString("Error"));
                            }
                        }
                    }
                    if (value != null && !value->equals(versionNum)){
                        error(new JString("Error"));
                    }
                }

                void JParser2::maybeMisc(jbool eofOK){
                    while (!eofOK || !in->isEOF()) {
                        if (maybeComment(false) || maybePI(false) || maybeWhitespace()){
                            continue;
                        }else{
                            break;
                        }
                    }
                }

                JString* JParser2::getMarkupDeclname(JString* roleId, jbool qname){
                    JString*  name=null;
                    whitespace(roleId);
                    name = maybeGetName();
                    if (name == null){
                        fatal(new JString("Error"));
                    }
                    return name;
                }

                jbool JParser2::maybeDoctypeDecl(){
                    if (!peek(new JString("<!DOCTYPE"))){
                        return false;
                    }
                    JExternalEntity*  externalSubset = null;
                    rootElementName = getMarkupDeclname(new JString("Error"),true);
                    if (maybeWhitespace () && (externalSubset = maybeExternalID ()) != null) {
                        lexicalHandler->startDTD(rootElementName, externalSubset->publicId, externalSubset->verbatimSystemId);
                        maybeWhitespace ();
                    } else {
                        lexicalHandler->startDTD(rootElementName, null, null);
                    }
                    if (in->peekc('[')) {
                        for (;;) {
                            if (in->isEOF () && !in->isDocument()) {
                                in = in->pop();
                                continue;
                            }
                            if (maybeMarkupDecl () || maybePEReference () || maybeWhitespace ()){
                                continue;
                            }else if (peek(new JString("<!["))){
                                fatal(new JString("Error"));
                            }else{
                                break;
                            }
                        }
                        nextChar(']', new JString("Error"), null);
                        maybeWhitespace();
                    }
                    nextChar ('>', new JString("Error"), null);

                    if (externalSubset != null) {
                        externalSubset->name = new JString("[dtd]");
                        externalSubset->isPE = true;
                        externalParameterEntity(externalSubset);
                    }
                    params->clear();
                    lexicalHandler->endDTD();
                    JVector*  v = new JVector();

                    for (JEnumeration* e = notations->keys(); e->hasMoreElements();) {
                        JString* name = dynamic_cast<JString*>(e->nextElement());
                        JObject* value = notations->get(name);

                        if (value == JBoolean::TRUE){
                            if (supportValidation && isValidating){
                                error(new JString("Error"));
                            }
                            v->addElement(name);

                        } else if (value->isInstanceOf(JString::getClazz())) {
                            if (supportValidation && isValidating){
                                error(new JString("Error"));
                            }
                            v->addElement(name);
                        }
                    }
                    while (!v->isEmpty()) {
                        JObject* name = v->firstElement();
                        v->removeElement(name);
                        notations->remove(name);
                    }
                    return true;
                }

                jbool JParser2::maybeMarkupDecl(){
                    return maybeElementDecl()
                        || maybeAttlistDecl()
                        || maybeEntityDecl()
                        || maybeNotationDecl()
                        || maybePI(false)
                        || maybeComment(false);
                }

                void JParser2::readStandalone(){
                    JString*  value = maybeReadAttribute(new JString("standalone"), false);
                    if (value == null || (new JString("no"))->equals(value)){
                        return;
                    }
                    if ((new JString("yes"))->equals(value)) {
                        isStandalone = true;
                        return;
                    }
                    fatal(new JString("Error"));
                }

                jbool JParser2::isXmlLang(JString* value){
                    jint nextSuffix=0;
                    jchar c=0;
                    if (value->length() < 2){
                        return false;
                    }

                    c = value->charAt(1);
                    if (c == '-') {
                        c = value->charAt(0);
                        if (!(c == 'i' || c == 'I' || c == 'x' || c == 'X')){
                            return false;
                        }
                        nextSuffix = 1;

                    } else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
                        c = value->charAt(0);
                        if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))){
                            return false;
                        }
                        nextSuffix = 2;

                    } else{
                        return false;
                    }
                    
                    while (nextSuffix < value->length()) {
                        c = value->charAt(nextSuffix);
                        if (c != '-'){
                            break;
                        }
                        while (++nextSuffix < value->length()){
                            c = value->charAt(nextSuffix);
                            if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))){
                                break;
                            }
                        }
                    }
                    return value->length() == nextSuffix && c != '-';
                }

                jbool JParser2::maybeElement(JElementValidator* validator){
                    JParser2::JNameCacheEntry* name=null;
                    JElementDecl* element=null;
                    jbool haveAttributes = false;
                    jbool hasContent = true;
                    jint startLine=0;

                    name = maybeGetNameCacheEntry();
                    if (name == null){
                        return false;
                    }

                    if (validator != null){
                        validator->consume(name->name);
                    }

                    element = dynamic_cast<JElementDecl*>(elements->get(name->name));
                    if (supportValidation && isValidating) {
                        if (element == null || element->contentType == null) {
                            error(new JString("Error"));
                            element = new JElementDecl(name->name);
                            element->contentType = strANY;
                            elements->put(name->name, element);
                        }

                        if (validator == null && rootElementName != null && !rootElementName->equals(name->name)){
                            error(new JString("Error"));
                        }
                    }

                    startLine = in->getLineNumber ();
                    jbool sawWhite = in->maybeWhitespace();
                    JVector* exceptions = null;

                    if (namespaces){
                        nsSupport->pushContext();
                        seenNSDecl = false;
                    }

                    for (;;) {
                        if (in->peekc('>')){
                            break;
                        }

                        if (in->peekc('/')){
                            hasContent = false;
                            break;
                        }

                        if (!sawWhite){
                            fatal(new JString("Error"));
                        }

                        JString* attQName=null;
                        JAttributeDecl* info=null;
                        JString* value=null;

                        attQName = maybeGetName();
                        if (attQName == null){
                            fatal(new JString("Error"));
                        }

                        if (attTmp->getValue(attQName) != null){
                            fatal(new JString("Error"));
                        }

                        in->maybeWhitespace();
                        nextChar('=', new JString("Error"), attQName);
                        in->maybeWhitespace();
                        doLexicalPE = false;
                        parseLiteral(false);
                        sawWhite = in->maybeWhitespace();

                        info = (element == null) ? null : dynamic_cast<JAttributeDecl*>(element->attributes->get(attQName));
                        if (info == null) {
                            if (supportValidation && isValidating){
                                error(new JString("Error"));
                            }
                            value = strTmp->toString();

                        } else {
                            if (!JAttributeDecl::CDATA->equals(info->type)) {
                                value = normalize(!info->isFromInternalSubset);

                                if (supportValidation && isValidating){
                                    validateAttributeSyntax(info, value);
                                }

                            } else{
                                value = strTmp->toString();
                            }

                            if (supportValidation && isValidating && info->isFixed && !value->equals(info->defaultValue)){
                                error(new JString("Error"));
                            }
                        }

                        if (XmlLang->equals(attQName) && !isXmlLang(value)){
                            error(new JString("Error"));
                        }

                        JString* type = (info == null) ? JAttributeDecl::CDATA : info->type;
                        JString* defaultValue = (info == null) ? null : info->defaultValue;

                        if (namespaces) {
                            exceptions = processAttributeNS(attQName, type, value, defaultValue, true, false,exceptions);
                        } else {
                            attTmp->addAttribute(new JString(""), new JString(""), attQName, type, value,defaultValue, true);
                        }

                        haveAttributes = true;
                    }
                    if (element != null){
                        attTmp->setIdAttributeName(element->id);
                    }

                    if (element != null && element->attributes->size() != 0) {
                        haveAttributes = defaultAttributes(element) || haveAttributes;
                    }

                    if (seenNSDecl) {
                        jint length = attTmp->getLength();
                        for (jint i = 0; i < length; i++) {
                            JString* attQName = attTmp->getQName(i);
                            if (attQName->startsWith(new JString("xmlns"))) {
                                if (attQName->length() == 5 || attQName->charAt(5) == ':') {
                                    continue;
                                }
                            }
                            JPrimitiveObjectArray* attName= processName(attQName, true, false);
                            attTmp->setURI(i, dynamic_cast<JString*>(attName->get(0)));
                            attTmp->setLocalName(i, dynamic_cast<JString*>(attName->get(1)));
                        }

                    } else if (exceptions != null && errHandler != null) {
                        for (jint i = 0; i < exceptions->size(); i++) {
                            errHandler->error(dynamic_cast<JSAXParseException*>(exceptions->elementAt(i)));
                        }
                    }

                    if (namespaces) {
                        JPrimitiveObjectArray* parts = processName(name->name, false, false);
                        contentHandler->startElement(dynamic_cast<JString*>(parts->get(0)), 
                                                     dynamic_cast<JString*>(parts->get(1)),
                                                     dynamic_cast<JString*>(parts->get(2)), attTmp);

                    } else {
                        contentHandler->startElement(new JString(""), new JString(""), name->name, attTmp);
                    }

                    if (haveAttributes) {
                        attTmp->clear();
                        if (supportValidation && isValidating && namespaces && !prefixes) {
                            nsAttTmp->removeAllElements();
                        }
                    }

                    validator = newValidator(element);
                    
                    if (hasContent) {
                        content(element, false, validator);

                        if (!in->peek(name->name, name->chars)){
                            fatal(new JString("Error"));
                        }
                        in->maybeWhitespace();
                    }

                    nextChar('>', new JString("Error"), name->name);
                    validator->done();

                    if (namespaces) {
                        JPrimitiveObjectArray* parts = processName(name->name, false, false);

                        contentHandler->endElement(dynamic_cast<JString*>(parts->get(0)),
                                                   dynamic_cast<JString*>(parts->get(1)),
                                                   dynamic_cast<JString*>(parts->get(2)));
                        
                        JEnumeration* prefixes = nsSupport->getDeclaredPrefixes();
                        while (prefixes->hasMoreElements()) {
                            JString* prefix = dynamic_cast<JString*>(prefixes->nextElement());
                            contentHandler->endPrefixMapping(prefix);
                        }
                        nsSupport->popContext();

                    } else {
                        contentHandler->endElement(new JString(""), new JString(""), name->name);
                    }
                    return true;
                }

                JVector* JParser2::processAttributeNS(JString* attQName, JString* type,JString* value, JString* defaultValue,jbool isSpecified, jbool isDefaulting,JVector* exceptions){
                    jbool stop=false;
                    if (attQName->startsWith(new JString("xmlns"))) {
                        jbool defaultNSDecl = attQName->length() == 5;
                        if (!defaultNSDecl && attQName->charAt(5) != ':') {
                            stop=true;
                        }

                        if (!stop){
                            JString* prefix=null;
                            if (defaultNSDecl) {
                                prefix = new JString("");
                            } else {
                                prefix = attQName->substring(6);
                            }

                            if (!nsSupport->declarePrefix(prefix, value)) {
                                error(new JString("Error"));
                            }
                            contentHandler->startPrefixMapping(prefix, value);

                            if (prefixes) {
                                attTmp->addAttribute(new JString(""), prefix, attQName,type, value, defaultValue, isSpecified);

                            } else if (supportValidation && isValidating && !isDefaulting) {
                                nsAttTmp->addElement(attQName);
                            }
                            seenNSDecl = true;
                            return exceptions;
                        }
                    }

                    try {
                        JPrimitiveObjectArray* attName= processName(attQName, true, true);
                        attTmp->addAttribute(dynamic_cast<JString*>(attName->get(0)),
                                             dynamic_cast<JString*>(attName->get(1)),
                                             dynamic_cast<JString*>(attName->get(2)), type,
                                            value, defaultValue, isSpecified);
                    } catch (JSAXException* e) {
                        if (exceptions == null) {
                            exceptions = new JVector();
                        }
                        exceptions->addElement(e);
                        attTmp->addAttribute(new JString(""), attQName, attQName, type, value,defaultValue, isSpecified);
                    }
                    return exceptions;
                }

                JPrimitiveObjectArray* JParser2::processName(JString* qName, jbool isAttribute,jbool useException){
                    JPrimitiveObjectArray* parts= nsSupport->processName(qName, namePartsTmp,isAttribute);
                    if (parts == null) {
                        parts = new JPrimitiveObjectArray(JString::getClazz(),3);
                        parts->set(0, new JString(""));
                        JString* localName = JXmlNames::getLocalPart(qName);
                        parts->set(1, localName != null ? localName : new JString(""));
                        parts->set(2, qName);

                        if (useException) {
                            throw new JSAXParseException(new JString("Error"));
                        }
                        error(new JString("Error"));
                    }
                    return parts;
                }

                JElementValidator* JParser2::newValidator(JElementDecl* element){
                    return JElementValidator::ANY;     
                }

                void JParser2::validateAttributeSyntax(JAttributeDecl* attr, JString* value){
                }

                jbool JParser2::defaultAttributes(JElementDecl* element){
                    jbool didDefault = false;

                    for (JEnumeration* e = element->attributes->keys(); e->hasMoreElements(); ) {
                        JString* declAttName = dynamic_cast<JString*>(e->nextElement());
                        if (attTmp->getValue(declAttName) != null) {
                            continue;
                        }
                        JAttributeDecl* info = dynamic_cast<JAttributeDecl*>(element->attributes->get(declAttName));
                        if (supportValidation && isValidating && info->isRequired) {
                            if (namespaces && !prefixes) {
                                if (nsAttTmp->contains(declAttName)) {
                                    continue;
                                }
                            }
                            error(new JString("Error"));
                        }

                        JString* defaultValue = info->defaultValue;
                        if (defaultValue != null) {
                            if (supportValidation && isValidating && isStandalone && !info->isFromInternalSubset){
                                error(new JString("Error"));
                            }

                            if (namespaces) {
                                processAttributeNS(declAttName, info->type, defaultValue,defaultValue, false, true, null);

                            } else {
                                attTmp->addAttribute(new JString(""), new JString(""), declAttName, info->type,defaultValue, defaultValue, false);
                            }
                            didDefault = true;
                        }
                    }
                    return didDefault;
                }

                void JParser2::content(JElementDecl* element,jbool allowEOF,JElementValidator* validator){
                    for (;;) {
                        if (in->peekc('<')) {
                            if (maybeElement(validator)){
                                continue;
                            }
                            if (in->peekc('/')){
                                return;
                            }
                            if (maybeComment(true) || maybePI(true)){
                                continue;
                            }

                            if (in->peek(new JString("![CDATA["), null)) {
                                lexicalHandler->startCDATA();
                                in->unparsedContent(contentHandler, validator, (element != null) && element->ignoreWhitespace, (isStandalone && supportValidation && isValidating && !element->isFromInternalSubset) ? new JString("Error") : null);
                                lexicalHandler->endCDATA();
                                continue;
                            }
                            jchar c = getc();
                            fatal(new JString("Error"));
                        }

                        if (element != null && element->ignoreWhitespace && in->ignorableWhitespace(contentHandler)) {
                            if (supportValidation && isValidating && isStandalone && !element->isFromInternalSubset){
                                error(new JString("Error"));
                            }
                            continue;
                        }
                        if (in->parsedContent(contentHandler, validator)){
                            continue;
                        }
                        if (in->isEOF()){
                            break;
                        }
                        if (!maybeReferenceInContent(element, validator)){
                            throw new JInternalError();
                        }
                    }
                    if (!allowEOF){
                        fatal(new JString("Error"));
                    }
                }

                jbool JParser2::maybeElementDecl(){
                    JInputEntity* start = peekDeclaration(new JString("!ELEMENT"));
                    if (start == null){
                        return false;
                    }
                    JString* name = getMarkupDeclname(new JString("Error"), true);
                    JElementDecl* element = dynamic_cast<JElementDecl*>(elements->get(name));
                    jbool declEffective = false;
                    if (element != null) {
                        if (element->contentType != null) {
                            if (supportValidation && isValidating && element->contentType != null){
                                error(new JString("Error"));
                            }
                            element = new JElementDecl(name);
                        }

                    } else {
                        element = new JElementDecl(name);
                        if (!ignoreDeclarations) {
                            elements->put(element->name, element);
                            declEffective = true;
                        }
                    }
                    element->isFromInternalSubset = !inExternalPE;

                    whitespace(new JString("Error"));
                    if (peek(strEMPTY)) {
                        element->contentType = strEMPTY;
                        element->ignoreWhitespace = true;
                    
                    } else if (peek(strANY)) {
                        element->contentType = strANY;
                        element->ignoreWhitespace = false;
                    
                    } else{
                        element->contentType = getMixedOrChildren (element);
                    }

                    maybeWhitespace();
                    jchar c = getc();
                    if (c != '>'){
                        fatal(new JString("Error"));
                    }
                    if (supportValidation && isValidating && start != in){
                        error(new JString("Error"));
                    }
                    if (declEffective) {
                        declHandler->elementDecl(element->name, element->contentType);
                    }
                    return true;
                }

                JString* JParser2::getMixedOrChildren(JElementDecl* element){
                    JInputEntity* start=null;
                    strTmp = new JStringBuffer();
                    nextChar('(', new JString("Error"), element->name);
                    start = in;
                    maybeWhitespace();
                    strTmp->append('(');

                    if (peek(new JString("#PCDATA"))) {
                        strTmp->append("#PCDATA");
                        getMixed(element->name, start);
                        element->ignoreWhitespace = false;

                    } else {
                        element->model = getcps(element->name, start);
                        element->ignoreWhitespace = true;
                    }
                    return strTmp->toString();
                }

                JContentModel* JParser2::newContentModel(JString* tag){
                    return null;
                }

                JContentModel* JParser2::newContentModel(jchar type, JContentModel* next){
                    return null;
                }

                JContentModel* JParser2::getcps(JString* element,JInputEntity* start){
                    jbool decided = false;
                    jchar type = 0;
                    JContentModel* retval=null;
                    JContentModel* current=null;
                    JContentModel* temp=null;
                    do {
                        JString* tag=maybeGetName();
                        if (tag != null) {
                            strTmp->append(tag);
                            temp = getFrequency(newContentModel(tag));
                        
                        } else if (peek(new JString("("))){
                            JInputEntity* next = in;
                            strTmp->append('(');
                            maybeWhitespace();
                            temp = getFrequency(getcps(element, next));

                        } else{
                            fatal(new JString("Error"));
                        }

                        maybeWhitespace();
                        if (decided) {
                            jchar c = getc();
                            if (current != null) {
                                current->next = newContentModel(type, temp);
                                current = current->next;
                            }
                            if (c == type) {
                                strTmp->append(type);
                                maybeWhitespace();
                                continue;

                            } else if (c == ')') {
                                ungetc();
                                continue;
                            
                            } else {
                                fatal(new JString("Error"));
                            }

                        } else {
                            type = getc();
                            if (type == '|' || type == ',') {
                                decided = true;
                                retval = current = newContentModel(type, temp);

                            } else {
                                retval = current = temp;
                                ungetc();
                                continue;
                            }
                            strTmp->append(type);
                        }
                        maybeWhitespace ();

                    } while (!peek(new JString(")")));
                    if (supportValidation && isValidating && in != start){
                        error(new JString("Error"));
                    }
                    strTmp->append(')');
                    return getFrequency(retval);
                }

                JContentModel* JParser2::getFrequency(JContentModel* original){
                    jchar c = getc();
                    if (c == '?' || c == '+' || c == '*') {
                        strTmp->append(c);
                        if (original == null){
                            return null;
                        }
                        if (original->type == 0) {
                            original->type = c;
                            return original;
                        }
                        return newContentModel(c, original);
                    } else{
                        ungetc();
                        return original;
                    }
                }

                void JParser2::getMixed(JString* element, JInputEntity* start){
                    maybeWhitespace();
                    if (peek(new JString(")*")) || peek(new JString(")"))) {
                        if (supportValidation && isValidating && in != start){
                            error(new JString("Error"));
                        }
                        strTmp->append(')');
                        return;
                    }
                    JVector*  v = null;

                    if (supportValidation && isValidating){
                        v = new JVector();
                    }

                    while (peek(new JString("|"))) {
                        JString* name=null;
                        strTmp->append('|');
                        maybeWhitespace();
                        name = maybeGetName();
                        if (name == null){
                            fatal(new JString("Error"));
                        }
                        if (supportValidation && isValidating) {
                            if (v->contains(name)){
                                error(new JString("Error"));
                            }else{
                                v->addElement(name);
                            }
                        }
                        strTmp->append(name);
                        maybeWhitespace();
                    }
                    
                    if (!peek(new JString(")*"))){
                        fatal(new JString("Error"));
                    }
                    if (supportValidation && isValidating && in != start){
                        error(new JString("Error"));
                    }
                    strTmp->append(')');
                }

                jbool JParser2::maybeAttlistDecl(){
                    JInputEntity* start = peekDeclaration(new JString("!ATTLIST"));
                    if (start == null){
                        return false;
                    }
                    JString* name = getMarkupDeclname(new JString("Error"), true);
                    JElementDecl* element = dynamic_cast<JElementDecl*>(elements->get(name));
                    if (element == null) {
                        element = new JElementDecl(name);
                        if (!ignoreDeclarations){
                            elements->put(name, element);
                        }
                    }
                    maybeWhitespace();
                    while (!peek(new JString(">"))) {
                        name = maybeGetName();
                        if (name == null){
                            fatal(new JString("Error"));
                        }
                        whitespace(new JString("Error"));
                        JAttributeDecl* a = new JAttributeDecl(name);
                        a->isFromInternalSubset = !inExternalPE;
                        if (peek(JAttributeDecl::CDATA)){
                            a->type = JAttributeDecl::CDATA;

                        }else if (peek(JAttributeDecl::IDREFS)){
                            a->type = JAttributeDecl::IDREFS;

                        }else if (peek(JAttributeDecl::IDREF)){
                            a->type = JAttributeDecl::IDREF;

                        }else if (peek(JAttributeDecl::ID)) {
                            a->type = JAttributeDecl::ID;
                            if (element->id != null) {
                                if (supportValidation && isValidating){
                                    error(new JString("Error"));
                                }
                            } else{
                                element->id = name;
                            }

                        } else if (peek(JAttributeDecl::ENTITY)){
                            a->type = JAttributeDecl::ENTITY;
                        
                        }else if (peek(JAttributeDecl::ENTITIES)){
                            a->type = JAttributeDecl::ENTITIES;
                        
                        }else if (peek(JAttributeDecl::NMTOKENS)){
                            a->type = JAttributeDecl::NMTOKENS;
                        
                        }else if (peek(JAttributeDecl::NMTOKEN)){
                            a->type = JAttributeDecl::NMTOKEN;

                        }else if (peek(JAttributeDecl::NOTATION)) {
                            a->type = JAttributeDecl::NOTATION;
                            whitespace(new JString("Error"));
                            nextChar('(', new JString("Error"), null);
                            maybeWhitespace();
                            JVector* v = new JVector();
                            do {
                                if ((name = maybeGetName ()) == null){
                                    fatal(new JString("Error"));
                                }
                                if (supportValidation && isValidating && notations->get(name) == null){
                                    notations->put(name, name);
                                }
                                v->addElement(name);
                                maybeWhitespace();
                                if (peek(new JString("|"))){
                                    maybeWhitespace();
                                }
                            } while (!peek(new JString(")")));

                            a->values = new JPrimitiveObjectArray(JString::getClazz(),v->size());
                            for (jint i = 0; i < v->size(); i++){
                                a->values->set(i, v->elementAt(i));
                            }

                        } else if (peek(new JString("("))) {
                            a->type = JAttributeDecl::ENUMERATION;
                            maybeWhitespace();

                            JVector* v = new JVector();
                            do {
                                name = getNmtoken();
                                v->addElement(name);
                                maybeWhitespace();
                                if (peek(new JString("|"))){
                                    maybeWhitespace();
                                }
                            } while (!peek(new JString(")")));

                            a->values = new JPrimitiveObjectArray(JString::getClazz(),v->size());
                            for (jint i = 0; i < v->size(); i++){
                                a->values->set(i,v->elementAt(i));
                            }
                        } else{
                            fatal(new JString("Error"));
                        }
                        whitespace(new JString("Error"));
                        if (peek(new JString("#REQUIRED"))) {
                            a->valueDefault = JAttributeDecl::REQUIRED;
                            a->isRequired = true;

                        } else if (peek(new JString("#FIXED"))) {
                            if (supportValidation && isValidating && a->type == JAttributeDecl::ID){
                                error(new JString("Error"));
                            }
                            a->valueDefault = JAttributeDecl::FIXED;
                            a->isFixed = true;
                            whitespace(new JString("Error"));
                            doLexicalPE=false;
                            parseLiteral(false);
                            doLexicalPE = true;

                            if (a->type != JAttributeDecl::CDATA){
                                a->defaultValue = normalize(false);
                            }else{
                                a->defaultValue = strTmp->toString();
                            }
                            if (a->type != JAttributeDecl::CDATA){
                                validateAttributeSyntax(a, a->defaultValue);
                            }

                        } else if (peek(new JString("#IMPLIED"))) {
                            a->valueDefault = JAttributeDecl::IMPLIED;

                        } else {
                            if (supportValidation && isValidating && a->type == JAttributeDecl::ID){
                                error(new JString("Error"));
                            }

                            doLexicalPE = false;
                            parseLiteral(false);
                            doLexicalPE = true;

                            if (a->type != JAttributeDecl::CDATA){
                                a->defaultValue = normalize (false);
                            
                            }else{
                                a->defaultValue = strTmp->toString();
                            }
                            if (a->type != JAttributeDecl::CDATA){
                                validateAttributeSyntax (a, a->defaultValue);
                            }
                        }

                        if (XmlLang->equals(a->name) && a->defaultValue != null && !isXmlLang(a->defaultValue)){
                            error(new JString("Error"));
                        }

                        if (!ignoreDeclarations && element->attributes->get(a->name) == null) {
                            element->attributes->put(a->name, a);

                            JString* saxType=null;
                            if (a->type == JAttributeDecl::ENUMERATION || a->type == JAttributeDecl::NOTATION) {
                                JStringBuffer* fullType = new JStringBuffer();

                                if (a->type == JAttributeDecl::NOTATION) {
                                    fullType->append(a->type);
                                    fullType->append(' ');
                                }
                                if (a->values->size() > 1) {
                                    fullType->append('(');
                                }
                                for (jint i = 0; i < a->values->size(); i++) {
                                    fullType->append(a->values->get(i));
                                    if (i + 1 < a->values->size()) {
                                        fullType->append('|');
                                    }
                                }
                                if (a->values->size() > 1) {
                                    fullType->append(')');
                                }
                                saxType = fullType->toString();

                            } else {
                                saxType = a->type;
                            }
                            declHandler->attributeDecl(element->name, a->name, saxType, a->valueDefault, a->defaultValue);
                        }
                        maybeWhitespace();
                    }
                    if (supportValidation && isValidating && start != in){
                        error(new JString("Error"));
                    }
                    return true;
                }

                JString* JParser2::normalize(jbool invalidIfNeeded){
                    JString* s = strTmp->toString();
                    JString* s2 = s->trim();
                    jbool didStrip = false;

                    if (s != s2) {
                        s = s2;
                        s2 = null;
                        didStrip = true;
                    }
                    strTmp = new JStringBuffer();
                    for (jint i = 0; i < s->length(); i++) {
                        jchar c = s->charAt(i);
                        if (!JXmlChars::isSpace(c)) {
                            strTmp->append(c);
                            continue;
                        }
                        strTmp->append(' ');
                        while (++i < s->length () && JXmlChars::isSpace(s->charAt(i))){
                            didStrip = true;
                        }
                        i--;
                    }
                    if (supportValidation && isValidating && isStandalone) {
                        if (invalidIfNeeded && (s2 == null || didStrip)){
                            error(new JString("Error"));
                        }
                    }
                    if (didStrip){
                        return strTmp->toString();
                    }else{
                        return s;
                    }
                }

                jbool JParser2::maybeConditionalSect(){
                    if (!peek(new JString("<!["))){
                        return false;
                    }
                    JString* keyword=null;
                    JInputEntity* start = in;
                    maybeWhitespace();
                    if ((keyword = maybeGetName ()) == null){
                        fatal(new JString("Error"));
                    }
                    maybeWhitespace();
                    nextChar('[', new JString("Error"), null);

                    if ((new JString("INCLUDE"))->equals(keyword)) {
                        for (;;) {
                            while (in->isEOF() && in != start){
                                in = in->pop();
                            }
                            if (in->isEOF()){
                                if (supportValidation && isValidating){
                                    error(new JString("Error"));
                                }
                                in = in->pop();
                            }
                            if (peek(new JString("]]>"))){
                                break;
                            }

                            doLexicalPE = false;
                            if (maybeWhitespace()){
                                continue;
                            }
                            if (maybePEReference()){
                                continue;
                            }
                            doLexicalPE = true;
                            if (maybeMarkupDecl() || maybeConditionalSect()){
                                continue;
                            }
                            fatal(new JString("Error"));
                        }

                    } else if ((new JString("IGNORE"))->equals(keyword)) {
                        jint nestlevel = 1;
                        doLexicalPE = false;
                        while (nestlevel > 0) {
                            jchar c = getc();
                            if (c == '<') {
                                if (peek(new JString("!["))){
                                    nestlevel++;
                                }
                            } else if (c == ']') {
                                if (peek(new JString("]>"))){
                                    nestlevel--;
                                }
                            } else{
                                continue;
                            }
                        }
                    } else{
                        fatal(new JString("Error"));
                    }
                    return true;
                }

                jbool JParser2::maybeReferenceInContent(JElementDecl* element,JElementValidator* validator){
                    if (!in->peekc('&')){
                        return false;
                    }

                    if (!in->peekc('#')) {
                        JString* name = maybeGetName();
                        if (name == null){
                            fatal(new JString("Error"));
                        }
                        nextChar(';', new JString("Error"), name);
                        expandEntityInContent(element, name, validator);
                        return true;
                    }

                    validator->text();
                    contentHandler->characters(charTmp, 0,surrogatesToCharTmp(parseCharNumber()));
                    return true;
                }

                jint JParser2::parseCharNumber(){
                    jchar c=0;
                    jint retval = 0;

                    if (getc() != 'x') {
                        ungetc();
                        for (;;) {
                            c = getc();
                            if (c >= '0' && c <= '9') {
                                retval *= 10;
                                retval += (c - '0');
                                continue;
                            }
                            if (c == ';'){
                                return retval;
                            }
                            fatal(new JString("Error"));
                        }

                    } else for (;;) {
                        c = getc();
                        if (c >= '0' && c <= '9') {
                            retval <<= 4;
                            retval += (c - '0');
                            continue;
                        }
                        if (c >= 'a' && c <= 'f') {
                            retval <<= 4;
                            retval += 10 + (c - 'a');
                            continue;
                        }
                        if (c >= 'A' && c <= 'F') {
                            retval <<= 4;
                            retval += 10 + (c - 'A');
                            continue;
                        }
                        if (c == ';'){
                            return retval;
                        }
                        fatal(new JString("Error"));
                    }
                }

                jint JParser2::surrogatesToCharTmp(jint ucs4){
                    if (ucs4 <= 0xffff) {
                        if (JXmlChars::isChar(ucs4)) {
                            charTmp->setChar(0, (jchar) ucs4);
                            return 1;
                        } 

                    } else if (ucs4 <= 0x0010ffff) {
                        ucs4 -= 0x10000;
                        charTmp->setChar(0, (jchar) (0xd800 | ((ucs4 >> 10) & 0x03ff)));
                        charTmp->setChar(1, (jchar) (0xdc00 | (ucs4 & 0x03ff)));
                        return 2;
                    }
                    fatal(new JString("Error"));
                    return -1;
                }

                void JParser2::expandEntityInContent(JElementDecl* element,JString* name,JElementValidator* validator){
                    JObject* entity = entities->get(name);
                    JInputEntity* last = in;
                    if (entity == null) {
                        fatal(new JString("Error"));
                    }
                    if (entity->isInstanceOf(JInternalEntity::getClazz())) {
                        JInternalEntity* e = dynamic_cast<JInternalEntity*>(entity);
                        if (supportValidation && isValidating && isStandalone && !e->isFromInternalSubset){
                            error(new JString("Error"));
                        }

                        pushReader(e->buf, name, true);
                        content(element, true, validator);

                        if (in != last && !in->isEOF()) {
                            while (in->isInternal()){
                                in = in->pop();
                            }
                            fatal(new JString("Error"));
                        }

                        lexicalHandler->endEntity(name);
                        in = in->pop();

                    } else if (entity->isInstanceOf(JExternalEntity::getClazz())) {
                        JExternalEntity* e = dynamic_cast<JExternalEntity*>(entity);
                        if (e->notation != null){
                            fatal(new JString("Error"));
                        }

                        if (supportValidation && isValidating && isStandalone && !e->isFromInternalSubset){
                            error(new JString("Error"));
                        }

                        externalParsedEntity(element, e, validator);
                    } else
                        throw new JInternalError(name);
                }

                jbool JParser2::maybePEReference(){
                    if (!in->peekc('%')){
                        return false;
                    }
                    JString*  name = maybeGetName();
                    JObject*  entity=null;

                    if (name == null){
                        fatal(new JString("Error"));
                    }
                    nextChar(';', new JString("Error"), name);
                    entity = params->get(name);

                    if (entity->isInstanceOf(JInternalEntity::getClazz())) {
                        JInternalEntity* value = dynamic_cast<JInternalEntity*>(entity);
                        pushReader(value->buf, name, false);

                    } else if (entity->isInstanceOf(JExternalEntity::getClazz())) {
                        externalParameterEntity(dynamic_cast<JExternalEntity*>(entity));

                    } else if (entity == null) {
                        ignoreDeclarations = true;
                        if (supportValidation && isValidating){
                            error(new JString("Error"));
                        }else{
                            warning(new JString("Error"));
                        }
                    }
                    return true;
                }

                jbool JParser2::maybeEntityDecl(){
                    JInputEntity* start = peekDeclaration(new JString("!ENTITY"));
                    if (start == null){
                        return false;
                    }

                    JString* entityName=null;
                    JHashtable* defns=null;
                    JExternalEntity*  externalId=null;
                    jbool doStore=false;

                    doLexicalPE = false;
                    whitespace(new JString("Error"));
                    if (in->peekc('%')) {
                        whitespace(new JString("Error"));
                        defns = params;

                    } else{
                        defns = entities;
                    }

                    ungetc();
                    doLexicalPE = true;
                    entityName = getMarkupDeclname(new JString("Error"), false);
                    whitespace(new JString("Error"));
                    externalId = maybeExternalID();

                    doStore = (defns->get(entityName) == null);
                    if (!doStore && defns == entities){
                        warning(new JString("Error"));
                    }                    
                    doStore &= !ignoreDeclarations;

                    if (externalId == null) {
                        JPrimitiveCharArray* value=null;
                        JInternalEntity* entity=null;

                        doLexicalPE = false;
                        parseLiteral(true);
                        doLexicalPE = true;
                        
                        if (doStore) {
                            value = new JPrimitiveCharArray(strTmp->length());
                            if (value->size() != 0){
                                strTmp->getChars(0, value->size(), value, 0);
                            }
                            entity = new JInternalEntity (entityName, value);
                            entity->isPE = (defns == params);
                            entity->isFromInternalSubset = !inExternalPE;
                            defns->put(entityName, entity);

                            if (defns == params) {
                                JStringBuffer* buffer=new JStringBuffer();
                                buffer->append('%')->append(entityName);
                                entityName = buffer->toString();
                            }
                            declHandler->internalEntityDecl(entityName, new JString(value));
                        }

                    } else {
                        if (defns == entities && maybeWhitespace () && peek(new JString("NDATA"))) {
                            externalId->notation = getMarkupDeclname(new JString("Error"), false);

                            if (supportValidation && isValidating && notations->get(externalId->notation) == null){
                                notations->put(externalId->notation, JBoolean::TRUE);
                            }
                        }
                        externalId->name = entityName;
                        externalId->isPE = (defns == params);
                        externalId->isFromInternalSubset = !inExternalPE;
                        if (doStore) {
                            defns->put(entityName, externalId);
                            if (externalId->notation != null) {
                                dtdHandler->unparsedEntityDecl(entityName, externalId->publicId, externalId->systemId, externalId->notation);

                            } else {
                                if (defns == params) {
                                    JStringBuffer* buffer=new JStringBuffer();
                                    buffer->append('%')->append(entityName);
                                    entityName = buffer->toString();
                                }
                                declHandler->externalEntityDecl(entityName,externalId->publicId, externalId->systemId);
                            }
                        }
                    }
                    maybeWhitespace();
                    nextChar('>', new JString("Error"), entityName);
                    if (supportValidation && isValidating && start != in){
                        error(new JString("Error"));
                    }
                    return true;
                }

                JExternalEntity* JParser2::maybeExternalID(){
                    JString* temp = null;
                    JExternalEntity* retval=null;

                    if (peek(new JString("PUBLIC"))) {
                        whitespace(new JString("Error"));
                        temp = parsePublicId();

                    } else if (!peek(new JString("SYSTEM"))){
                        return null;
                    }

                    retval = new JExternalEntity(in);
                    retval->publicId = temp;
                    whitespace(new JString("Error"));
                    retval->verbatimSystemId = getQuotedString(new JString(""), null);
                    retval->systemId = resolveURI(retval->verbatimSystemId);
                    return retval;
                }

                JString* JParser2::parseSystemId(){
                    JString* uri = getQuotedString(new JString("systemId error"), null);
                    return resolveURI(uri);
                }

                JString* JParser2::resolveURI(JString* uri){
                    jint temp = uri->indexOf(':');
                    if (temp == -1 || uri->indexOf('/') < temp) {
                        JString* baseURI= in->getSystemId();
                        if (baseURI == null){
                            fatal(new JString("Error"));
                        }
                        if (uri->length() == 0){
                            uri = new JString(".");
                        }
                        baseURI = baseURI->substring(0, baseURI->lastIndexOf('/') + 1);
                        if (uri->charAt (0) != '/'){
                            JStringBuffer* buf=new JStringBuffer();
                            buf->append(baseURI)->append(uri);
                            uri = buf->toString();

                        }else {
                            JString* baseURIScheme=null;
                            jint colonIndex = baseURI->indexOf(':');
                            if (colonIndex == -1) {
                                baseURIScheme = new JString("file:");
                            } else {
                                baseURIScheme = baseURI->substring(0, colonIndex + 1);
                            }
                            JStringBuffer* buf=new JStringBuffer();
                            buf->append(baseURIScheme)->append(uri);
                            uri = buf->toString();
                        }
                    }
                    if (uri->indexOf('#') != -1){
                        error(new JString("URI containing #"));
                    }
                    return uri;
                }

                void JParser2::maybeTextDecl(){
                    if (!in->isXmlDeclOrTextDeclPrefix()) {
                        return;
                    }
                    peek(new JString("<?xml"));
                    readVersion(false, new JString("1.0"));
                    readEncoding(true);
                    maybeWhitespace();
                    if (!peek(new JString("?>"))){
                        fatal(new JString("error"));
                    }
                }

                jbool JParser2::externalParsedEntity(JElementDecl* element,JExternalEntity* next,JElementValidator* validator){
                    if (!pushReader(next)){
                        if (!isInAttribute){
                            lexicalHandler->endEntity(next->name);
                        }
                        return false;
                    }
                    maybeTextDecl();
                    content(element, true, validator);
                    if (!in->isEOF()){
                        fatal(new JString("error"));
                    }
                    in = in->pop();
                    if (!isInAttribute) {
                        lexicalHandler->endEntity(next->name);
                    }
                    return true;
                }

                void JParser2::externalParameterEntity(JExternalEntity* next){
                    if (isStandalone && fastStandalone){
                        return;
                    }
                    JInputEntity* pe=null;
                    inExternalPE = true;
                    try {
                        pushReader(next);
                    } catch (JException* e) {
                        fatal(new JString("Error"),e);
                    }
                    pe = in;
                    try {
                        maybeTextDecl ();
                    } catch (JException* e) {
                        fatal(new JString("Error"), e);
                    }
                    while (!pe->isEOF()) {
                        if (in->isEOF()) {
                            in = in->pop();
                            continue;
                        }
                        doLexicalPE = false;
                        if (maybeWhitespace()){
                            continue;
                        }
                        if (maybePEReference()){
                            continue;
                        }
                        doLexicalPE = true;
                        if (maybeMarkupDecl () || maybeConditionalSect ()){
                            continue;
                        }
                        break;
                    }
                    if (!pe->isEOF()){
                        fatal(new JString("Error"));
                    }
                    in = in->pop();
                    inExternalPE = !in->isDocument();
                    doLexicalPE = false;
                }

                void JParser2::readEncoding(jbool must){
                    JString* name = maybeReadAttribute(new JString("encoding"), must);

                    if (name == null){
                        return;
                    }
                    for (jint i = 0; i < name->length (); i++) {
                        jchar c = name->charAt(i);
                        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')){
                            continue;
                        }
                        if (i != 0 && ((c >= '0' && c <= '9')
                                        || c == '-'
                                        || c == '_'
                                        || c == '.'
                                        )){
                            continue;
                        }
                        fatal(new JString("Error in encoding"));
                    }

                    JString*  currentEncoding = in->getEncoding();

                    if (currentEncoding != null && !name->equalsIgnoreCase(currentEncoding)){
                        warning(new JString("Error in encoding"));
                    }
                }

                jbool JParser2::maybeNotationDecl(){
                    JInputEntity* start = peekDeclaration(new JString("!NOTATION"));
                    if (start == null){
                        return false;
                    }
                    JString* name = getMarkupDeclname(new JString("Error"), false);
                    JExternalEntity*  entity = new JExternalEntity(in);

                    whitespace(new JString("Error"));
                    if (peek( new JString("PUBLIC"))) {
                        whitespace(new JString("Error"));
                        entity->publicId = parsePublicId ();
                        
                        if (maybeWhitespace ()) {
                            if (!peek(new JString(">"))){
                                entity->systemId = parseSystemId ();
                            }else{ 
                                ungetc ();
                            }
                        }

                    } else if (peek (new JString("SYSTEM"))) {
                        whitespace(new JString("Error"));
                        entity->systemId = parseSystemId ();

                    } else{
                        fatal(new JString("Error"));
                    }

                    maybeWhitespace();
                    nextChar('>', new JString("Error"), name);

                    if (supportValidation && isValidating && start != in){
                        error(new JString("Error"));
                    }

                    if (entity->systemId != null && entity->systemId->indexOf('#') != -1){
                        error(new JString("Error"));
                    }

                    JObject*  value = notations->get(name);
                    if (value != null && value->isInstanceOf(JExternalEntity::getClazz())){
                        warning(new JString("Error"));

                    }else if (!ignoreDeclarations) {
                        notations->put(name, entity);
                        dtdHandler->notationDecl (name, entity->publicId,entity->systemId);
                    }
                    return true;
                }

                jchar JParser2::getc(){
                    if (!(inExternalPE && doLexicalPE)) {
                        jchar c = in->getc();
                        if (c == '%' && doLexicalPE){
                            fatal(new JString("Error"));
                        }
                        return c;
                    }
                    jchar c=0;

                    while (in->isEOF()) {
                        if (in->isInternal () || (doLexicalPE && !in->isDocument())){
                            in = in->pop();
                        
                        }else {
                            fatal(new JString("Error"));
                        }
                    }
                    if ((c = in->getc()) == '%' && doLexicalPE) {
                        JString* name = maybeGetName();
                        JObject* entity=null;


                        if (name == null){
                            fatal(new JString("Error"));
                        }
                        nextChar(';', new JString("Error"), name);
                        entity = params->get(name);

                        pushReader ((new JString(" "))->toCharArray(), null, false);

                        if (entity->isInstanceOf(JInternalEntity::getClazz())) {
                            pushReader((dynamic_cast<JInternalEntity*>(entity))->buf, name, false);

                        }else if (entity->isInstanceOf(JExternalEntity::getClazz())){
                            pushReader(dynamic_cast<JExternalEntity*>(entity));

                        }else if (entity == null){
                            fatal(new JString("Error"));
                        
                        }else{
                            throw new JInternalError ();
                        }

                        pushReader((new JString(" "))->toCharArray (), null, false);
                        return in->getc();
                    }
                    return c;
                }

                void JParser2::ungetc(){
                    in->ungetc();
                }

                jbool JParser2::peek(JString* s){
                    return in->peek(s, null);
                }

                JInputEntity* JParser2::peekDeclaration(JString* s){
                    JInputEntity* start=null;
                    if (!in->peekc('<')){
                        return null;
                    }
                    start = in;
                    if (in->peek(s, null)){
                        return start;
                    }
                    in->ungetc();
                    return null;
                }

                void JParser2::nextChar(jchar c, JString* location, JString* near){
                    while (in->isEOF () && !in->isDocument()){
                        in = in->pop();
                    }
                    if (!in->peekc(c)){
                        fatal (new JString("EOF reached"));
                    }
                }

                void JParser2::pushReader(JPrimitiveCharArray* buf, JString* name, jbool isGeneral){
                    if (isGeneral && !isInAttribute) {
                        lexicalHandler->startEntity(name);
                    }
                    JInputEntity* r = JInputEntity::getInputEntity(errHandler);
                    r->init(buf, name, in, !isGeneral);
                    in = r;
                }

                jbool JParser2::pushReader(JExternalEntity* next){
                    if (!next->isPE && !isInAttribute) {
                        lexicalHandler->startEntity(next->name);
                    }
                    JInputEntity* r = JInputEntity::getInputEntity(errHandler);
                    JInputSource* s = next->getInputSource(resolver);
                    r->init(s, next->name, in, next->isPE);
                    in = r;
                    return true;
                }

                void JParser2::warning(JString* messageId){
                    JSAXParseException* x = new JSAXParseException (messageId);
                    errHandler->warning (x);
                }

                void JParser2::error(JString* messageId){
                    JSAXParseException* x = new JSAXParseException(messageId);
                    errHandler->error (x);
                }

                void JParser2::error(JString* messageId, JException* e){
                    JSAXParseException* x = new JSAXParseException(messageId,e);
                    errHandler->error (x);
                }

                void JParser2::fatal(JString* message){
                    fatal(message, null);
                }

                void JParser2::fatal(JString* messageId, JException* e){
                    JSAXParseException* x = new JSAXParseException(messageId,e);
                    errHandler->fatalError(x);
                    throw x;
                }

                JParser2::~JParser2(){
                }
            }
        }
    }
}
