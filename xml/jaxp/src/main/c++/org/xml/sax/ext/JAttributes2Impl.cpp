#include "org/xml/sax/ext/JAttributes2Impl.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JIllegalArgumentException.h"
#include "jcpp/lang/JArrayIndexOutOfBoundsException.h"
#include "jcpp/lang/JSystem.h"

namespace org{
    namespace xml{
        namespace sax{
            namespace ext{

                JAttributes2Impl::JAttributes2Impl(JClass* _class):JAttributesImpl(_class){
                    declared=null;
                    specified=null;
                }

                JAttributes2Impl::JAttributes2Impl():JAttributesImpl(getClazz()){
                    declared=null;
                    specified=null;
                }

                JAttributes2Impl::JAttributes2Impl(JAttributes* atts):JAttributesImpl(getClazz(),atts){
                    declared=null;
                    specified=null;
                }

                jbool JAttributes2Impl::isDeclared(jint index){
                    if (index < 0 || index >= getLength ()){
                        throw new JArrayIndexOutOfBoundsException (new JString("No attribute at index "));
                    }
                    return declared->getBoolean(index);
                }

                jbool JAttributes2Impl::isDeclared(JString* uri, JString* localName){
                    jint index = getIndex(uri, localName);
                    if (index < 0){
                        throw new JIllegalArgumentException (new JString("No such attribute"));
                    }
                    return declared->getBoolean(index);
                }

                jbool JAttributes2Impl::isDeclared(JString* qName){
                    jint index = getIndex(qName);
                    if (index < 0){
                        throw new JIllegalArgumentException(new JString("No such attribute: "));
                    }
                    return declared->getBoolean(index);
                }

                jbool JAttributes2Impl::isSpecified(jint index){
                    if (index < 0 || index >= getLength()){
                        throw new JArrayIndexOutOfBoundsException (new JString("No attribute at index: "));
                    }
                    return specified->getBoolean(index);
                }

                jbool JAttributes2Impl::isSpecified(JString* uri, JString* localName){
                    jint index = getIndex(uri, localName);
                    if (index < 0){
                        throw new JIllegalArgumentException (new JString("No such attribute="));
                    }
                    return specified->getBoolean(index);
                }

                jbool JAttributes2Impl::isSpecified(JString* qName){
                    jint index = getIndex(qName);
                    if (index < 0){
                        throw new JIllegalArgumentException (new JString("No such attribute: "));
                    }
                    return specified->getBoolean(index);
                }

                void JAttributes2Impl::setAttributes(JAttributes* atts){
                    jint length = atts->getLength();

                    JAttributesImpl::setAttributes(atts);
                    declared = new JPrimitiveBooleanArray(length);
                    specified = new JPrimitiveBooleanArray(length);

                    if ((dynamic_cast<JObject*>(atts))->isInstanceOf(JAttributes2::getClazz())) {
                        JAttributes2* a2 = dynamic_cast<JAttributes2*>(atts);
                        for (jint i = 0; i < length; i++) {
                            declared->setBoolean(i, a2->isDeclared(i));
                            specified->setBoolean(i, a2->isSpecified(i));
                        }
                    } else {
                        JString* cdata=new JString("CDATA");
                        for (jint i = 0; i < length; i++) {
                            declared->setBoolean(i, ! cdata->equals(atts->getType(i)));
                            specified->setBoolean(i,true);
                        }
                    }
                }

                void JAttributes2Impl::addAttribute(JString* uri, JString* localName, JString* qName,JString* type, JString* value){
                    JAttributesImpl::addAttribute(uri, localName, qName, type, value);


                    jint length = getLength();
                    if(specified==null){
                        specified = new JPrimitiveBooleanArray(length);
                        declared = new JPrimitiveBooleanArray(length);

                    } else if (length > specified->size()) {
                        JPrimitiveBooleanArray* newFlags= new JPrimitiveBooleanArray(length);
                        JSystem::arraycopy(declared, 0, newFlags, 0, declared->size());
                        declared = newFlags;

                        newFlags = new JPrimitiveBooleanArray(length);
                        JSystem::arraycopy(specified, 0, newFlags, 0, specified->size());
                        specified = newFlags;
                    }

                    specified->setBoolean(length - 1, true);
                    declared->setBoolean(length - 1, ! (new JString("CDATA"))->equals(type));
                }

                void JAttributes2Impl::removeAttribute(jint index){
                    jint origMax = getLength() - 1;
                    JAttributesImpl::removeAttribute(index);
                    if (index != origMax) {
                        JSystem::arraycopy(declared, index + 1, declared, index,origMax - index);
                        JSystem::arraycopy(specified, index + 1, specified, index,origMax - index);
                    }
                }

                void JAttributes2Impl::setDeclared(jint index, jbool value){
                    if (index < 0 || index >= getLength ()){
                        throw new JArrayIndexOutOfBoundsException (new JString("No attribute at index "));
                    }
                    declared->setBoolean(index, value);
                }

                void JAttributes2Impl::setSpecified(jint index, jbool value){
                    if (index < 0 || index >= getLength ()){
                        throw new JArrayIndexOutOfBoundsException (new JString("No attribute at index: "));
                    }
                    specified->setBoolean(index, value);
                }

                JAttributes2Impl::~JAttributes2Impl(){
                }
            }
        }
    }
}
