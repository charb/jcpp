#ifndef JCPP_XML_INTERNAL_PARSER_JINPUT_ENTITY_H
#define JCPP_XML_INTERNAL_PARSER_JINPUT_ENTITY_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/io/JReader.h"
#include "jcpp/lang/JStringBuffer.h"
#include "jcpp/lang/JPrimitiveCharArray.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "org/xml/sax/JLocator.h"
#include "org/xml/sax/JInputSource.h"
#include "org/xml/sax/JErrorHandler.h"
#include "org/xml/sax/JContentHandler.h"
#include "jcpp/xml/internal/parser/JElementValidator.h"

using namespace org::xml::sax;
using namespace jcpp::io;

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace parser{            

            	// @Class(canonicalName="javax.xml.internal.parser.InputEntity", simpleName="InputEntity");
            	class JCPP_EXPORT JInputEntity : public JObject, public JLocator{
                protected:
                    jint start;
                    jint finish;
                    JPrimitiveCharArray* buf;
                    jint lineNumber;
                    jbool returnedFirstHalf;
                    jbool maybeInCRLF;
                    JString* name;
                    JInputEntity* next;
                    JInputSource* input;
                    JReader* reader;
                    jbool isClosed;
                    JErrorHandler* errHandler;
                    JStringBuffer* rememberedText;
                    jint startRemember;
                    jbool isPE;
                    static jint BUFFER_SIZE ;

                public:
                    JInputEntity();

                    static JClass* getClazz();

                    static JInputEntity* getInputEntity(JErrorHandler* h);

                    virtual jbool isInternal();

                    virtual jbool isDocument();

                    virtual jbool isParameterEntity();

                    virtual JString* getName();

                    virtual void init(JInputSource* in, JString* name, JInputEntity* stack,jbool isPE);

                    virtual void init(JPrimitiveCharArray* b, JString* name,JInputEntity* stack, jbool isPE);

                    virtual void checkRecursion(JInputEntity* stack);

                    virtual JInputEntity* pop();

                    virtual jbool isEOF();

                    virtual JString* getEncoding();

                    virtual jchar getNameChar();

                    virtual jchar getc();

                    virtual jbool peekc(jchar c);

                    virtual void ungetc();

                    virtual jbool maybeWhitespace();

                    virtual jbool parsedContent(JContentHandler* contentHandler,JElementValidator* validator);
                    
                    virtual void unparsedContent(JContentHandler* contentHandler,JElementValidator* validator,jbool ignorableWhitespace,JString* whitespaceInvalidMessage);

                    virtual jbool checkSurrogatePair(jint offset);

                    virtual jbool ignorableWhitespace(JContentHandler* handler);

                    virtual jbool peek(JString* next, JPrimitiveCharArray* chars);

                    virtual jbool isXmlDeclOrTextDeclPrefix();

                    virtual void startRemembering();

                    virtual JString* rememberText();

                    virtual JLocator* getLocator();

                    virtual JString* getPublicId();

                    virtual JString* getSystemId();

                    virtual jint getLineNumber();

                    virtual jint getColumnNumber();

                    virtual void fillbuf();

                    virtual void close();

                    virtual void fatal(JString* messageId);

                    virtual ~JInputEntity();
                };
            }
        }
    }
}

#endif
