#include "jcpp/xml/internal/tree/JAttributeNode1.h"
#include "jcpp/xml/internal/tree/JTextNode.h"
#include "jcpp/xml/internal/tree/JXmlDocument.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JSystem.h"
#include "org/w3c/dom/JDOMException.h"

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace tree{

                JAttributeNode1::JAttributeNode1(JString* name,JString* value, jbool specified, JString* defaultValue):JAttributeNode(getClazz(),null, name, value, specified, defaultValue){
                    this->value=value;
                    this->specified=specified;
                    this->defaultValue=defaultValue;
                }

                JAttributeNode* JAttributeNode1::makeClone(){
                    JAttributeNode1* retval = new JAttributeNode1(qName, value,specified, defaultValue);
                    retval->ownerDocument = ownerDocument;
                    return retval;
                }

                JString* JAttributeNode1::getPrefix(){
                    return null;
                }

                JString* JAttributeNode1::getLocalName(){
                    return null;
                }

                JAttributeNode1::~JAttributeNode1(){
                }
            }
        }
    }
}
