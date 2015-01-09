#include "org/xml/sax/helpers/JAttributeListImpl.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JArrayIndexOutOfBoundsException.h"

namespace org{
    namespace xml{
        namespace sax{
            namespace helpers{

                JAttributeListImpl::JAttributeListImpl(JClass* _class):JObject(_class){
                    names=new JVector();
                    types=new JVector();
                    values=new JVector();
                }

                JAttributeListImpl::JAttributeListImpl():JObject(getClazz()){
                    names=new JVector();
                    types=new JVector();
                    values=new JVector();
                }

                JAttributeListImpl::JAttributeListImpl(JAttributeList* atts):JObject(getClazz()){
                    names=new JVector();
                    types=new JVector();
                    values=new JVector();
                    setAttributeList(atts);
                }

                void JAttributeListImpl::setAttributeList(JAttributeList* atts){
                    jint count = atts->getLength();
                    clear();
                    for (jint i = 0; i < count; i++) {
                        addAttribute(atts->getName(i), atts->getType(i), atts->getValue(i));
                    }
                }

                void JAttributeListImpl::addAttribute(JString* name, JString* type, JString* value){
                    names->addElement(name);
                    types->addElement(type);
                    values->addElement(value);
                }

                void JAttributeListImpl::removeAttribute(JString* name){
                    jint i = names->indexOf(name);
                    if (i >= 0) {
                        names->removeElementAt(i);
                        types->removeElementAt(i);
                        values->removeElementAt(i);
                    }
                }

                void JAttributeListImpl::clear(){
                    names->removeAllElements();
                    types->removeAllElements();
                    values->removeAllElements();
                }

                jint JAttributeListImpl::getLength(){
                    return names->size();
                }

                JString* JAttributeListImpl::getName(jint i){
                    if (i < 0) {
                        return null;
                    }
                    try {
                        return dynamic_cast<JString*>(names->elementAt(i));
                    } catch (JArrayIndexOutOfBoundsException* e) {
                        return null;
                    }
                }

                JString* JAttributeListImpl::getType(jint i){
                    if (i < 0) {
                        return null;
                    }
                    try {
                        return dynamic_cast<JString*>(types->elementAt(i));
                    } catch (JArrayIndexOutOfBoundsException* e) {
                        return null;
                    }
                }
                
                JString* JAttributeListImpl::getValue(jint i){
                    if (i < 0) {
                        return null;
                    }
                    try {
                        return dynamic_cast<JString*>(values->elementAt(i));
                    } catch (JArrayIndexOutOfBoundsException* e) {
                        return null;
                    }
                }

                JString* JAttributeListImpl::getType(JString* name){
                    return getType(names->indexOf(name));
                }

                JString* JAttributeListImpl::getValue(JString* name){
                    return getValue(names->indexOf(name));
                }

                JAttributeListImpl::~JAttributeListImpl(){
                }
            }
        }
    }
}
