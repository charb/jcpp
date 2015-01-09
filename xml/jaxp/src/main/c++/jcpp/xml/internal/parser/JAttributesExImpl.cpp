#include "jcpp/xml/internal/parser/JAttributesExImpl.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JBoolean.h"
#include "jcpp/lang/JIndexOutOfBoundsException.h"

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace parser{

                JAttributesExImpl::JAttributesExImpl():JAttributesImpl(getClazz()){
                    specified=new JVector();
                    defaults=new JVector();
                    idAttributeName=null;
                }

                void JAttributesExImpl::clear(){
                    JAttributesImpl::clear();
                    specified->removeAllElements();
                    defaults->removeAllElements();
                    idAttributeName = null;
                }

                void JAttributesExImpl::addAttribute(JString* uri, JString* localName, JString* qName,JString* type, JString* value, JString* defaultValue,jbool isSpecified){
                    JAttributesImpl::addAttribute(uri, localName, qName, type, value);
                    defaults->addElement(defaultValue);
                    specified->addElement(isSpecified ? JBoolean::TRUE : null);
                }

                jbool JAttributesExImpl::isSpecified(jint i){
                    JObject* value = specified->elementAt(i);
                    return value == JBoolean::TRUE;
                }

                JString* JAttributesExImpl::getDefault(jint i){
                    try {
                        if (i < 0){
                            return null;
                        }
                        return dynamic_cast<JString*>(defaults->elementAt(i));
                    } catch (JIndexOutOfBoundsException* e) {
                        return null;
                    }
                }

                JString* JAttributesExImpl::getIdAttributeName(){
                    return idAttributeName;
                }

                void JAttributesExImpl::setIdAttributeName(JString* name){
                    idAttributeName = name;
                }

                JAttributesExImpl::~JAttributesExImpl(){
                }
            }
        }
    }
}
