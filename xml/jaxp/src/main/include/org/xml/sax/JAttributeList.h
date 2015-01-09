#ifndef ORG_XML_SAX_ATTRIBUTE_LIST_H
#define ORG_XML_SAX_ATTRIBUTE_LIST_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"

namespace org{
    namespace xml{
        namespace sax{

        	// @Class(canonicalName="org.xml.sax.AttributeList", simpleName="AttributeList");
            class JCPP_EXPORT JAttributeList : public JInterface{
            public:
                static JClass* getClazz();

                virtual jint getLength()=0;

                virtual JString* getName(jint i)=0;

                virtual JString* getType(jint i)=0;
                
                virtual JString* getValue(jint i)=0;

                virtual JString* getType(JString* name)=0;

                virtual JString* getValue(JString* name)=0;

                virtual ~JAttributeList();
            };
        }
    }
}

#endif
