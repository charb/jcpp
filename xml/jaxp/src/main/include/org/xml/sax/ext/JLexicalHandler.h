#ifndef ORG_XML_SAX_EXT_LEXICAL_HANDLER_H
#define ORG_XML_SAX_EXT_LEXICAL_HANDLER_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JPrimitiveCharArray.h"
#include "org/xml/sax/JAttributes.h"

using namespace org::xml::sax;

namespace org{
    namespace xml{
        namespace sax{
            namespace ext{

            	// @Class(canonicalName="org.xml.sax.ext.LexicalHandler", simpleName="LexicalHandler");
                class JCPP_EXPORT JLexicalHandler : public JInterface{
                public:
                    static JClass* getClazz();

                    virtual void startDTD(JString* name, JString* publicId,JString* systemId)=0;

                    virtual void endDTD()=0;

                    virtual void startEntity(JString* name)=0;
                    
                    virtual void endEntity(JString* name)=0;
        
                    virtual void startCDATA()=0;
                    
                    virtual void endCDATA()=0;

                    virtual void comment(JPrimitiveCharArray* ch, jint start, jint length)=0;

                    virtual ~JLexicalHandler();
                };
            }
        }
    }
}

#endif
