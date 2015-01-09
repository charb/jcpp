#ifndef ORG_W3C_DOM_TYPE_INFO_H
#define ORG_W3C_DOM_TYPE_INFO_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "org/w3c/dom/JNode.h"

namespace org{
    namespace w3c{
        namespace dom{

        	// @Class(canonicalName="org.w3c.dom.TypeInfo", simpleName="TypeInfo");
            class JCPP_EXPORT JTypeInfo : public JInterface{
            public:
                static JClass* getClazz();

                static jint DERIVATION_RESTRICTION ;
                
                static jint DERIVATION_EXTENSION;
                
                static jint DERIVATION_UNION;

                static jint DERIVATION_LIST;

                virtual JString* getTypeName()=0;

                virtual JString* getTypeNamespace()=0;

                virtual jbool isDerivedFrom(JString* typeNamespaceArg,JString* typeNameArg,jint derivationMethod)=0;

                virtual ~JTypeInfo();
            };
        }
    }
}

#endif
