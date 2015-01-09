#include "org/xml/sax/helpers/JAttributesImpl.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JArrayIndexOutOfBoundsException.h"
#include "jcpp/lang/JSystem.h"

namespace org{
    namespace xml{
        namespace sax{
            namespace helpers{

                JAttributesImpl::JAttributesImpl(JClass* _class):JObject(_class){
                    length=0;
                    data=null;
                }

                JAttributesImpl::JAttributesImpl(JClass* _class, JAttributes* atts):JObject(_class){
                    length=0;
                    data=null;
                    setAttributes(atts);
                }

                JAttributesImpl::JAttributesImpl():JObject(getClazz()){
                    length=0;
                    data=null;
                }

                JAttributesImpl::JAttributesImpl(JAttributes* atts):JObject(getClazz()){
                    length=0;
                    data=null;
                    setAttributes(atts);
                }
                
                void JAttributesImpl::ensureCapacity(jint n){
                    if (n <= 0) {
                        return;
                    }
                    jint max;
                    if (data == null || data->size() == 0) {
                        max = 25;

                    }else if (data->size() >= n * 5) {
                        return;

                    }else {
                        max = data->size();
                    }
                    while (max < n * 5) {
                        max *= 2;
                    }

                    JPrimitiveObjectArray* newData = new JPrimitiveObjectArray(JString::getClazz(),max);
                    if (length > 0) {
                        JSystem::arraycopy(data, 0, newData, 0, length*5);
                    }
                    data = newData;
                }
                
                void JAttributesImpl::badIndex(jint index){
                    JStringBuilder* builder=new JStringBuilder();
                    builder->append(new JString("Attempt to modify attribute at illegal index: "))
                           ->append(index);
                    throw new JArrayIndexOutOfBoundsException(builder->toString());
                }

                jint JAttributesImpl::getLength(){
                    return length;
                }

                JString* JAttributesImpl::getURI(jint index){
                    if (index >= 0 && index < length) {
                        return dynamic_cast<JString*>(data->get(index*5));
                    } else {
                        return null;
                    }
                }

                JString* JAttributesImpl::getLocalName(jint index){
                    if (index >= 0 && index < length) {
                        return dynamic_cast<JString*>(data->get(index*5+1));
                    } else {
                        return null;
                    }
                }

                JString* JAttributesImpl::getQName(jint index){
                    if (index >= 0 && index < length) {
                        return dynamic_cast<JString*>(data->get(index*5+2));
                    } else {
                        return null;
                    }
                }

                JString* JAttributesImpl::getType(jint index){
                    if (index >= 0 && index < length) {
                        return dynamic_cast<JString*>(data->get(index*5+3));
                    } else {
                        return null;
                    }
                }

                JString* JAttributesImpl::getValue(jint index){
                    if (index >= 0 && index < length) {
                        return dynamic_cast<JString*>(data->get(index*5+4));
                    } else {
                        return null;
                    }
                }

                jint JAttributesImpl::getIndex(JString* uri, JString* localName){
                    jint max = length * 5;
                    for (jint i = 0; i < max; i += 5) {
                        if (dynamic_cast<JString*>(data->get(i))->equals(uri) && 
                            dynamic_cast<JString*>(data->get(i+1))->equals(localName)) {
                            return i / 5;
                        }
                    }
                    return -1;
                }

                jint JAttributesImpl::getIndex(JString* qName){
                    jint max = length * 5;
                    for (jint i = 0; i < max; i += 5) {
                        if (dynamic_cast<JString*>(data->get(i+2))->equals(qName)) {
                            return i / 5;
                        }
                    }
                    return -1;
                }

                JString* JAttributesImpl::getType(JString* uri, JString* localName){
                    jint max = length * 5;
                    for (jint i = 0; i < max; i += 5) {
                        if (dynamic_cast<JString*>(data->get(i))->equals(uri) && 
                            dynamic_cast<JString*>(data->get(i+1))->equals(localName)) {
                            return dynamic_cast<JString*>(data->get(i+3));
                        }
                    }
                    return null;
                }

                JString* JAttributesImpl::getType(JString* qName){
                    jint max = length * 5;
                    for (jint i = 0; i < max; i += 5) {
                        if (dynamic_cast<JString*>(data->get(i+2))->equals(qName)) {
                            return dynamic_cast<JString*>(data->get(i+3));
                        }
                    }
                    return null;
                }

                JString* JAttributesImpl::getValue(JString* uri, JString* localName){
                    jint max = length * 5;
                    for (jint i = 0; i < max; i += 5) {
                        if (dynamic_cast<JString*>(data->get(i))->equals(uri) && 
                            dynamic_cast<JString*>(data->get(i+1))->equals(localName)) {
                            return dynamic_cast<JString*>(data->get(i+4));
                        }
                    }
                    return null;
                }

                JString* JAttributesImpl::getValue(JString* qName){
                    jint max = length * 5;
                    for (jint i = 0; i < max; i += 5) {
                        if (dynamic_cast<JString*>(data->get(i+2))->equals(qName)) {
                            return dynamic_cast<JString*>(data->get(i+4));
                        }
                    }
                    return null;
                }

                void JAttributesImpl::clear(){
                    if (data != null) {
                        for (jint i = 0; i < (length * 5); i++)
                            data->set(i, null);
                    }
                    length = 0;
                }

                void JAttributesImpl::setAttributes(JAttributes* atts){
                    clear();
                    length = atts->getLength();
                    if (length > 0) {
                        data = new JPrimitiveObjectArray(JString::getClazz(),length*5);
                        for (jint i = 0; i < length; i++) {
                            data->set(i*5, atts->getURI(i));
                            data->set(i*5+1, atts->getLocalName(i));
                            data->set(i*5+2, atts->getQName(i));
                            data->set(i*5+3, atts->getType(i));
                            data->set(i*5+4, atts->getValue(i));
                        }
                    }
                }

                void JAttributesImpl::addAttribute(JString* uri, JString* localName, JString* qName,JString* type, JString* value){
                    ensureCapacity(length+1);
                    data->set(length*5, uri);
                    data->set(length*5+1, localName);
                    data->set(length*5+2, qName);
                    data->set(length*5+3, type);
                    data->set(length*5+4, value);
                    length++;
                }

                void JAttributesImpl::setAttribute(jint index, JString* uri, JString* localName,JString* qName, JString* type, JString* value){
                    if (index >= 0 && index < length) {
                        data->set(index*5, uri);
                        data->set(index*5+1, localName);
                        data->set(index*5+2, qName);
                        data->set(index*5+3, type);
                        data->set(index*5+4, value);
                    } else {
                        badIndex(index);
                    }
                }

                void JAttributesImpl::removeAttribute(jint index){
                    if (index >= 0 && index < length) {
                        if (index < length - 1) {
                            JSystem::arraycopy(data, (index+1)*5, data, index*5,(length-index-1)*5);
                        }
                        index = (length - 1) * 5;
                        data->set(index++, null);
                        data->set(index++, null);
                        data->set(index++, null);
                        data->set(index++, null);
                        data->set(index, null);
                        length--;
                    } else {
                        badIndex(index);
                    }
                }

                void JAttributesImpl::setURI(jint index, JString* uri){
                    if (index >= 0 && index < length) {
                        data->set(index*5, uri);
                    } else {
                        badIndex(index);
                    }
                }

                void JAttributesImpl::setLocalName(jint index, JString* localName){
                    if (index >= 0 && index < length) {
                        data->set(index*5+1, localName);
                    } else {
                        badIndex(index);
                    }
                }

                void JAttributesImpl::setQName(jint index, JString* qName){
                    if (index >= 0 && index < length) {
                        data->set(index*5+2, qName);
                    } else {
                        badIndex(index);
                    }
                }

                void JAttributesImpl::setType(jint index, JString* type){
                    if (index >= 0 && index < length) {
                        data->set(index*5+3, type);
                    } else {
                        badIndex(index);
                    }
                }

                void JAttributesImpl::setValue(jint index, JString* value){
                    if (index >= 0 && index < length) {
                        data->set(index*5+4, value);
                    } else {
                        badIndex(index);
                    }
                }

                JAttributesImpl::~JAttributesImpl(){
                }
            }
        }
    }
}
