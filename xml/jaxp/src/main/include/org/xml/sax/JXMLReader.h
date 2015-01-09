#ifndef ORG_XML_SAX_XML_READER_H
#define ORG_XML_SAX_XML_READER_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "org/xml/sax/JEntityResolver.h"
#include "org/xml/sax/JDTDHandler.h"
#include "org/xml/sax/JContentHandler.h"
#include "org/xml/sax/JErrorHandler.h"
#include "org/xml/sax/JInputSource.h"

namespace org{
    namespace xml{
        namespace sax{

        	// @Class(canonicalName="org.xml.sax.XMLReader", simpleName="XMLReader");
            class JCPP_EXPORT JXMLReader : public JInterface{
            public:
                static JClass* getClazz();

                virtual jbool getFeature(JString* name)=0;

                virtual void setFeature(JString* name,jbool value)=0;

                virtual JObject* getProperty(JString* name)=0;

                virtual void setProperty(JString* name, JObject* value)=0;

                virtual void setEntityResolver(JEntityResolver* resolver)=0;

                virtual JEntityResolver* getEntityResolver()=0;

                virtual void setDTDHandler(JDTDHandler* handler)=0;

                virtual JDTDHandler* getDTDHandler()=0;

                virtual void setContentHandler(JContentHandler* handler)=0;

                virtual JContentHandler* getContentHandler()=0;

                virtual void setErrorHandler(JErrorHandler* handler)=0;

                virtual JErrorHandler* getErrorHandler()=0;

                virtual void parse(JInputSource* input)=0;

                virtual void parse(JString* systemId)=0;

                virtual ~JXMLReader();
            };
        }
    }
}

#endif
