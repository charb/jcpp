#ifndef ORG_XML_SAX_PARSER_H
#define ORG_XML_SAX_PARSER_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "org/xml/sax/JEntityResolver.h"
#include "org/xml/sax/JDTDHandler.h"
#include "org/xml/sax/JDocumentHandler.h"
#include "org/xml/sax/JErrorHandler.h"
#include "org/xml/sax/JInputSource.h"

namespace org{
    namespace xml{
        namespace sax{

        	// @Class(canonicalName="org.xml.sax.Parser", simpleName="Parser");
            class JCPP_EXPORT JParser : public JInterface{
            public:
                static JClass* getClazz();

                virtual void setEntityResolver(JEntityResolver* resolver)=0;

                virtual void setDTDHandler(JDTDHandler* handler)=0;

                virtual void setDocumentHandler(JDocumentHandler* handler)=0;

                virtual void setErrorHandler(JErrorHandler* handler)=0;

                virtual void parse(JInputSource* source)=0;
                
                virtual void parse(JString* systemId)=0;

                virtual ~JParser();
            };
        }
    }
}

#endif
