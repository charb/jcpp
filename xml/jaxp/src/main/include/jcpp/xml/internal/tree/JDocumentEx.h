#ifndef JCPP_XML_INTERNAL_TREE_DOCUMENT_EX_H
#define JCPP_XML_INTERNAL_TREE_DOCUMENT_EX_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/xml/internal/tree/JXmlWritable.h"
#include "jcpp/xml/internal/tree/JElementFactory.h"
#include "org/w3c/dom/JDocument.h"

using namespace org::w3c::dom;

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace tree{            

            	// @Class(canonicalName="javax.xml.internal.tree.DocumentEx", simpleName="DocumentEx");
            	class JCPP_EXPORT JDocumentEx : public virtual JDocument, public virtual JXmlWritable, public virtual JElementFactory{
                public:
                    static JClass* getClazz();

                    virtual JString* getSystemId()=0;

                    virtual void setElementFactory(JElementFactory* factory)=0;

                    virtual JElementFactory* getElementFactory()=0;

                    virtual JElementEx* getElementExById(JString* id)=0;

                    virtual void changeNodeOwner(JNode* node)=0;

                    virtual ~JDocumentEx();
                };
            }
        }
    }
}

#endif
