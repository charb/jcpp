#ifndef JCPP_XML_INTERNAL_TREE_ELEMENT_FACTORY_H
#define JCPP_XML_INTERNAL_TREE_ELEMENT_FACTORY_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/xml/internal/tree/JElementEx.h"

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace tree{            

            	// @Class(canonicalName="javax.xml.internal.tree.ElementFactory", simpleName="ElementFactory");
                class JCPP_EXPORT JElementFactory : public JInterface{
                public:
                    static JClass* getClazz();

                    virtual JElementEx* createElementEx(JString* tag)=0;

                    virtual JElementEx* createElementEx(JString* uri, JString* tag)=0;

                    virtual ~JElementFactory();
                };
            }
        }
    }
}

#endif
