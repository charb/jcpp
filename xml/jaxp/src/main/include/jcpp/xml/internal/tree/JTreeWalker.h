#ifndef JCPP_XML_INTERNAL_TREE_TREE_WALKER_H
#define JCPP_XML_INTERNAL_TREE_TREE_WALKER_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/xml/internal/tree/JXmlWritable.h"
#include "org/w3c/dom/JNode.h"
#include "org/w3c/dom/JElement.h"

using namespace org::w3c::dom;

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace tree{            

            	// @Class(canonicalName="javax.xml.internal.tree.TreeWalker", simpleName="TreeWalker");
            	class JCPP_EXPORT JTreeWalker : public JObject{
                protected:
                    JNode* startPoint;
                    JNode* current;

                public:
                    JTreeWalker(JNode* node);

                    static JClass* getClazz();

                    virtual JNode* getCurrent();

                    virtual JNode* getNext();

                    virtual JElement* getNextElement(JString* tag);

                    virtual JElement* getNextElement(JString* nsURI, JString* localName);

                    virtual void reset();

                    virtual JNode* removeCurrent();

                    virtual ~JTreeWalker();
                };
            }
        }
    }
}

#endif
