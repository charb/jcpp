#include "jcpp/xml/internal/tree/JDataNode.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JSystem.h"
#include "org/w3c/dom/JDOMException.h"

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace tree{

                JDataNode::JDataNode(JClass* _class):JNodeBase(_class){
                    data=null;
                }

                JDataNode::JDataNode(JClass* _class,JPrimitiveCharArray* buf, jint offset, jint len):JNodeBase(_class){
                    data = new JPrimitiveCharArray(len);
                    JSystem::arraycopy (buf, offset, data, 0, len);
                }

                JDataNode::JDataNode(JClass* _class,JString* s):JNodeBase(_class){
                    if (s != null) {
                        data = new JPrimitiveCharArray(s->length());
                        s->getChars (0, data->size(), data, 0);
                    } else{
                        data = new JPrimitiveCharArray(0);
                    }
                }

                JDataNode::JNodeListImpl::JNodeListImpl():JObject(getClazz()){
                }

                JNode* JDataNode::JNodeListImpl::item(jint i){
                    return null;
                }

                jint JDataNode::JNodeListImpl::getLength(){
                    return 0;
                }

                JDataNode::JNodeListImpl::~JNodeListImpl(){
                }

                JDataNode::JNodeListImpl* JDataNode::childNodes = new JNodeListImpl();

                JPrimitiveCharArray* JDataNode::getText(){
                    return data;
                }

                void JDataNode::setText(JPrimitiveCharArray* buf){
                    data=buf;
                }

                JString* JDataNode::toString(){
                    if (data != null) {
                        return new JString(data);
                    } else {
                        return null;
                    }
                }

                JString* JDataNode::getData(){
                    return toString();
                }

                void JDataNode::setData(JString* data){
                    if (isReadonly ()){
                        throw new JDOMException(JDOMException::NO_MODIFICATION_ALLOWED_ERR);
                    }

                    if (data == null) {
                        setText(new JPrimitiveCharArray(0));
                    } else {
                        setText(data->toCharArray()); 
                    }
                }

                jint JDataNode::getLength(){
                    return data == null ? 0 : data->size();
                }

                JString* JDataNode::substringData(jint offset, jint count){
                    if (offset < 0 || offset > data->size() || count < 0){
                        throw new JDOMException(JDOMException::INDEX_SIZE_ERR);
                    }

                    count = (count< data->size() - offset ? count : data->size() - offset);
                    return new JString(data, offset, count);
                }

                void JDataNode::appendData(JString* newData){
                    if (isReadonly()){
                        throw new JDOMException(JDOMException::NO_MODIFICATION_ALLOWED_ERR);
                    }
                    jint length = newData->length ();
                    JPrimitiveCharArray* tmp= new JPrimitiveCharArray(length + data->size());
                    JSystem::arraycopy (data, 0, tmp, 0, data->size());
                    newData->getChars (0, length, tmp, data->size());
                    data = tmp;
                }

                void JDataNode::insertData(jint offset, JString* newData){
                    if (isReadonly ()){
                        throw new JDOMException(JDOMException::NO_MODIFICATION_ALLOWED_ERR);
                    }

                    if (offset < 0 || offset > data->size()){
                        throw new JDOMException(JDOMException::INDEX_SIZE_ERR);
                    }

                    jint length = newData->length ();
                    JPrimitiveCharArray* tmp= new JPrimitiveCharArray(length + data->size());

                    JSystem::arraycopy(data, 0, tmp, 0, offset);
                    newData->getChars(0, length, tmp, offset);
                    JSystem::arraycopy(data, offset,tmp, offset + length,data->size() - offset);
                    data = tmp;
                }

                void JDataNode::deleteData(jint offset, jint count){
                    JPrimitiveCharArray* tmp=null;
                    if (isReadonly ()){
                        throw new JDOMException(JDOMException::NO_MODIFICATION_ALLOWED_ERR);
                    }

                    if (offset < 0 || offset >= data->size() || count < 0){
                        throw new JDOMException(JDOMException::INDEX_SIZE_ERR);
                    }
                    count = (count< data->size() - offset ? count : data->size() - offset);

                    tmp = new JPrimitiveCharArray(data->size() - count);
                    JSystem::arraycopy (data, 0, tmp, 0, offset);
                    JSystem::arraycopy (data, offset + count, tmp, offset,tmp->size() - offset);
                    data = tmp;
                }

                void JDataNode::replaceData(jint offset, jint count, JString* arg){
                    if (isReadonly ()){
                        throw new JDOMException(JDOMException::NO_MODIFICATION_ALLOWED_ERR);
                    }

                    if (offset < 0 || offset >= data->size() || count < 0){
                        throw new JDOMException(JDOMException::INDEX_SIZE_ERR);
                    }

                    if ((offset + count) >= data->size()) {
                        deleteData(offset, count);
                        appendData(arg);

                    } else if (arg->length () == count) {
                        arg->getChars(0, (arg->length()), data, offset);

                    } else {
                        JPrimitiveCharArray* tmp= new JPrimitiveCharArray(data->size() + (arg->length() - count));
                        JSystem::arraycopy(data, 0, tmp, 0, offset);
                        arg->getChars(0, (arg->length ()), tmp, offset);
                        JSystem::arraycopy(data, (offset + count), tmp, (offset +arg->length ()), data->size() -(offset + count));
                        data = tmp;
                    }
                }

                JNodeList* JDataNode::getChildNodes(){
                    return childNodes;
                }

                JString* JDataNode::getNodeValue(){
                    return getData();
                }

                void JDataNode::setNodeValue(JString* value){
                    setData(value);
                }

                JDataNode::~JDataNode(){
                }
            }
        }
    }
}
