#ifndef ORG_XML_SAX_ATTRIBUTES_H
#define ORG_XML_SAX_ATTRIBUTES_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"

namespace org{
    namespace xml{
        namespace sax{

        	// @Class(canonicalName="org.xml.sax.Attributes", simpleName="Attributes");
            class JCPP_EXPORT JAttributes : public JInterface{
            public:
                static JClass* getClazz();

                virtual jint getLength()=0;

                virtual JString* getURI(jint index)=0;

                virtual JString* getLocalName(jint index)=0;

                virtual JString* getQName(jint index)=0;

                virtual JString* getType(jint index)=0;

                virtual JString* getValue(jint index)=0;
                
                virtual jint getIndex(JString* uri, JString* localName)=0;

                virtual jint getIndex(JString* qName)=0;

                virtual JString* getType(JString* uri, JString* localName)=0;

                virtual JString* getType(JString* qName)=0;

                virtual JString* getValue(JString* uri, JString* localName)=0;

                virtual JString* getValue(JString* qName)=0;

                virtual ~JAttributes();
            };
        }
    }
}

#endif
