#include "jcpp/io/JObjectOutputStream.h"
#include "jcpp/io/JBlockDataOutputStream.h"
#include "jcpp/lang/JClassLoader.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/io/JIOException.h"
#include "jcpp/io/JSerializable.h"
#include "jcpp/util/JArrayList.h"
#include "jcpp/util/JList.h"
#include "jcpp/io/JNotSerializableException.h"
#include "jcpp/io/JExternalizable.h"
#include "jcpp/io/JNotActiveException.h"
#include "jcpp/lang/JBoolean.h"
#include "jcpp/lang/JByte.h"
#include "jcpp/lang/JCharacter.h"
#include "jcpp/lang/JShort.h"
#include "jcpp/lang/JInteger.h"
#include "jcpp/lang/JFloat.h"
#include "jcpp/lang/JLong.h"
#include "jcpp/lang/JDouble.h"
#include "jcpp/lang/JIllegalArgumentException.h"
#include "jcpp/lang/JInternalError.h"
#include "jcpp/lang/JStringBuilder.h"
#include "jcpp/lang/JEnum.h"
#include "jcpp/lang/JSystem.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "jcpp/io/JOutputHandleTable.h"

using namespace jcpp::util;
using namespace jcpp::lang;

namespace jcpp{
    namespace io{

        JObjectOutputStream::JPutField::~JPutField(){
        }

        //@Class(canonicalName="java.io.ObjectOutputStream$PutFieldImpl", simpleName="ObjectOutputStream$PutFieldImpl");
        class JPutFieldImpl : public JObjectOutputStream::JPutField{
        protected:
            JObjectOutputStream* s;
            JObjectStreamClass* desc;
            JPrimitiveByteArray* primVals;
            JPrimitiveObjectArray* objVals;

        public:
            static jcpp::lang::JClass* getClazz();

            JPutFieldImpl(JObjectOutputStream* s,JObjectStreamClass* desc):JPutField(getClazz()){
                this->s=s;
                this->desc=desc;
                primVals=new JPrimitiveByteArray(desc->getPrimDataSize());
                objVals=new JPrimitiveObjectArray(JObject::getClazz(),desc->getNumObjFields());
            }

            virtual void put(JString* name, jbool val){
                JBits::putBoolean(primVals,getFieldOffset(name,JBoolean::TYPE),val);
            }

            virtual void put(JString* name, jbyte val){
                primVals->setByte(getFieldOffset(name,JByte::TYPE),val);
            }

            virtual void put(JString* name, jchar val){
                JBits::putChar(primVals,getFieldOffset(name,JCharacter::TYPE),val);
            }

            virtual void put(JString* name, jshort val){
                JBits::putShort(primVals,getFieldOffset(name,JShort::TYPE),val);
            }

            virtual void put(JString* name, jint val){
                JBits::putInt(primVals,getFieldOffset(name,JInteger::TYPE),val);
            }

            virtual void put(JString* name, jfloat val){
                JBits::putFloat(primVals,getFieldOffset(name,JFloat::TYPE),val);
            }

            virtual void put(JString* name, jlong val){
                JBits::putLong(primVals,getFieldOffset(name,JLong::TYPE),val);
            }

            virtual void put(JString* name, jdouble val){
                JBits::putDouble(primVals,getFieldOffset(name,JDouble::TYPE),val);
            }

            virtual void put(JString* name, JObject* val){
                objVals->set(getFieldOffset(name,JObject::getClazz()),val);
            }

            virtual void write(JObjectOutput *out){
                if (s!=out){
                    throw new JIllegalArgumentException(new JString("wrong stream"));
                }
                out->write(primVals,0,primVals->size());

                JPrimitiveObjectArray* fields=desc->getFields();
                jint numPrimFields=fields->size()-objVals->size();
                for (jint i=0;i<objVals->size();i++){
                    JObjectStreamField* f=dynamic_cast<JObjectStreamField*>(fields->get(numPrimFields+i));
                    if (f->isUnshared()){
                        throw new JIOException(new JString("cannot write unshared object"));
                    }
                    out->writeObject(objVals->get(i));
                }
            }

            virtual void writeFields(){
                s->bout->write(primVals, 0, primVals->size(), false);

                JPrimitiveObjectArray* fields = desc->getFields();
                jint numPrimFields=fields->size()-objVals->size();
                for (jint i = 0; i < objVals->size(); i++) {
                    JObjectStreamField* f=dynamic_cast<JObjectStreamField*>(fields->get(numPrimFields + i));
                    s->writeObject0(objVals->get(i),f->isUnshared());
                }
            }

            virtual jint getFieldOffset(JString* name, jcpp::lang::JClass* type) {
                JObjectStreamField* field = desc->getField(name, type);
                if (field == null) {
                    JStringBuilder* builder=new JStringBuilder();
                    builder->append("no such field ")->append(name)->append(" with type ")->append(type->toString());
                    throw new JIllegalArgumentException(builder->toString());
                }
                return field->getOffset();
            }

            ~JPutFieldImpl(){
            }
        };


        JObjectOutputStream::JObjectOutputStream(JOutputStream* out):JOutputStream(getClazz()){
            init(out);
        }

        JObjectOutputStream::JObjectOutputStream(JOutputStream* out,jcpp::lang::JClass* _class):JOutputStream(_class){
            init(out);
        }

        JObjectOutputStream::JObjectOutputStream(jcpp::lang::JClass* _class):JOutputStream(_class){
            init(null);
        }

        void JObjectOutputStream::init(JOutputStream* out){
            this->lengthPrimVals=0;
            this->primVals=null;
            curContext=null;
            curPut=null;
            depth = 0;
            enableReplace=false;
            
            if (out!=null){
                this->bout = new JBlockDataOutputStream(out);
                handles=new JOutputHandleTable(10, (jfloat) 3.00);
                enableOverride = false;
                writeStreamHeader();
                bout->setBlockDataMode(true);
            }else{
                bout=null;
                handles=null;
                enableOverride = true;
            }
        }

        void JObjectOutputStream::writeObject(JObject *obj){
            if(enableOverride){
                writeObjectOverride(obj);
            }else{
                try{
                    writeObject0(obj,false);
                }catch(JIOException* e){
                    if (depth == 0) {
                        writeFatalException(e);
                    }
                    throw e;
                }
            }
        }

        void JObjectOutputStream::writeUnshared(JObject* object){
            try{
                writeObject0(object,true);
            }catch(JIOException* ex){
                if (depth==0){
                    writeFatalException(ex);
                }
                throw ex;
            }
        }

        void JObjectOutputStream::defaultWriteObject(){
            JObject* curObj = curContext->getObj();
            JObjectStreamClass* curDesc = curContext->getDesc();

            bout->setBlockDataMode(false);
            defaultWriteFields(curObj, curDesc);
            bout->setBlockDataMode(true);
        }

        JObjectOutputStream::JPutField* JObjectOutputStream::putFields(){
            if (curPut==null){
                if (curContext==null){
                    throw new JNotActiveException(new JString("not in call to writeObject"));
                }
                curContext->getObj();
                JObjectStreamClass* curDesc=curContext->getDesc();
                curPut=new JPutFieldImpl(this,curDesc);
            }
            return curPut;
        }

        void JObjectOutputStream::writeFields(){
            if (curPut==null){
                throw new JNotActiveException(new JString("no current PutField object"));
            }
            bout->setBlockDataMode(false);
            JPutFieldImpl* impl=dynamic_cast<JPutFieldImpl*>(curPut);
            impl->writeFields();
            bout->setBlockDataMode(true);
        }

        void JObjectOutputStream::reset(){
            if (depth != 0) {
                throw new JIOException(new JString("stream active"));
            }
            bout->setBlockDataMode(false);
            bout->writeByte(TC_RESET);
            clear();
            bout->setBlockDataMode(true);
        }

        JObject* JObjectOutputStream::replaceObject(JObject *obj) {
            return obj;
        }

        jbool JObjectOutputStream::enableReplaceObject(jbool enable) {
            if (enable == enableReplace) {
                return enable;
            }
            enableReplace = enable;
            return !enableReplace;
        }

        void JObjectOutputStream::writeStreamHeader(){
            bout->writeShort(STREAM_MAGIC);
            bout->writeShort(STREAM_VERSION);
        }

        void JObjectOutputStream::writeClassDescriptor(JObjectStreamClass* desc){
            desc->writeNonProxy(this);
        }

        void JObjectOutputStream::write(jint b){
            bout->write(b);
        }

        void JObjectOutputStream::write(JPrimitiveByteArray* b){
            bout->write(b,0,b->size(),false);
        }

        void JObjectOutputStream::write(JPrimitiveByteArray* b, jint off, jint len){
            bout->write(b,off,len,false);
        }

        void JObjectOutputStream::flush(){
            bout->flush();
        }

        void JObjectOutputStream::drain(){
            bout->drain();
        }

        void JObjectOutputStream::close(){
            bout->close();
        }

        void JObjectOutputStream::writeBoolean(jbool b){
            bout->writeBoolean(b);
        }

        void JObjectOutputStream::writeByte(jint b){
            bout->writeByte(b);
        }

        void JObjectOutputStream::writeShort(jint v){
            bout->writeShort(v);
        }

        void JObjectOutputStream::writeChar(jint v){
            bout->writeChar(v);
        }

        void JObjectOutputStream::writeInt(jint v){
            bout->writeInt(v);
        }

        void JObjectOutputStream::writeLong(jlong v){
            bout->writeLong(v);
        }

        void JObjectOutputStream::writeFloat(jfloat v){
            bout->writeFloat(v);
        }

        void JObjectOutputStream::writeDouble(jdouble v){
            bout->writeDouble(v);
        }

        void JObjectOutputStream::writeBytes(JString* str){
            bout->writeBytes(str);
        }

        void JObjectOutputStream::writeChars(JString* str){
            bout->writeChars(str);
        }

        void JObjectOutputStream::writeUTF(JString* str){
            bout->writeUTF(str);
        }

        void JObjectOutputStream::writeTypeString(JString* str){
            jint handle;
            if(str==null){
                writeNull();
            } else if ((handle = handles->lookup(str)) != -1){
                writeHandle(handle);
            } else{
                writeString(str,false);
            }
        }

        void JObjectOutputStream::clear() {
            handles->clear();
        }

        void JObjectOutputStream::writeObject0(JObject* obj,jbool unshared){
            jbool oldMode = bout->setBlockDataMode(false);
            depth++;
            if(obj == null){
                writeNull();
            }else{
                jint handle=0;
                if(!unshared && ((handle = handles->lookup(obj)) != -1) ) {
                    writeHandle(handle);

                }else if (jcpp::lang::JClass::getClazz()->isAssignableFrom(obj->getClass())){
                    writeClass((jcpp::lang::JClass*)obj,unshared);

                }else if (JObjectStreamClass::getClazz()->isAssignableFrom(obj->getClass())){
                    writeClassDesc((JObjectStreamClass*)obj,unshared);

                }else{
                    JObject* orig = obj;
                    jcpp::lang::JClass* cl = obj->getClass();
                    JObjectStreamClass* desc=null;
                    
                    for (;;) {
                        jcpp::lang::JClass* repCl;
                        desc = JObjectStreamClass::lookup(cl,true);
                        if (desc==null || !desc->hasWriteReplaceMethod() ||
                            (obj = desc->invokeWriteReplace(obj)) == null|| (repCl = obj->getClass()) == cl){
                            break;
                        }
                        cl = repCl;
                    }
                    if (enableReplace) {
                        JObject* rep = replaceObject(obj);
                        if (rep != obj && rep != null) {
                            cl = rep->getClass();
                            desc = JObjectStreamClass::lookup(cl,true);
                        }
                        obj = rep;
                    }
                    
                    jbool avoid=false;
                    if (obj != orig) {
                        if (obj == null) {
                            writeNull();
                            avoid=true;

                        }else{
                            if(!unshared && (handle = handles->lookup(obj) != -1) ){
                                writeHandle(handle);
                                avoid=true;

                            }else if (jcpp::lang::JClass::getClazz()->isAssignableFrom(obj->getClass())){
                                writeClass((jcpp::lang::JClass*)obj,unshared);
                                avoid=true;

                            }else if (JObjectStreamClass::getClazz()->isAssignableFrom(obj->getClass())){
                                writeClassDesc((JObjectStreamClass*)obj,unshared);
                                avoid=true;
                            }
                        }
                    }
                    if (!avoid){
                        if (obj->getClass()==JString::getClazz()){
                            writeString((JString*)obj,unshared);

                        }else if(obj->getClass()->isArray()){
                            writeArray(obj,desc,unshared);

                        } else if (obj->getClass()->isEnum()){
                             writeEnum(obj, desc,unshared);

                        }else if (JSerializable::getClazz()->isAssignableFrom(obj->getClass())){
                            writeOrdinaryObject(obj,desc,unshared);

                        }else{
                            throw new JNotSerializableException(obj->getClass()->getName());
                        }
                    }
                }
            }
            depth--;
            bout->setBlockDataMode(oldMode);
        }

        void JObjectOutputStream::writeNull(){
            bout->writeByte(TC_NULL);
        }

        void JObjectOutputStream::writeHandle(jint handle){
            bout->writeByte(TC_REFERENCE);
            bout->writeInt(baseWireHandle + handle);
        }

        void JObjectOutputStream::writeClass(jcpp::lang::JClass* cl,jbool unshared){
            bout->writeByte(TC_CLASS);
            writeClassDesc(JObjectStreamClass::lookup(cl,true),false);
            handles->assign((unshared ? null : cl));
        }

        void JObjectOutputStream::writeClassDesc(JObjectStreamClass* desc,jbool unshared){
            jint handle;
            if(desc == null){
                writeNull();
            } else if(!unshared && (handle = handles->lookup(desc)) != -1) {
                writeHandle(handle);
            } else if(desc->isProxy()){
                writeProxyDesc(desc,unshared);
            } else{
                writeNonProxyDesc(desc,unshared);
            }
        }

        void JObjectOutputStream::writeProxyDesc(JObjectStreamClass *desc,jbool unshared){
            bout->writeByte(TC_PROXYCLASSDESC);
            handles->assign((unshared?null :desc));

            jcpp::lang::JClass* cl=desc->forClass();
            JList* interfaces=cl->getInterfaces();
            bout->writeInt(interfaces->size());
            for(jint i = 0; i < interfaces->size(); ++i){
                jcpp::lang::JClass* clazz=dynamic_cast<jcpp::lang::JClass*>(interfaces->get(i));
                JString* s=clazz->getName();
                bout->writeUTF(s);
            }

            bout->setBlockDataMode(true);
            bout->setBlockDataMode(false);
            bout->writeByte(TC_ENDBLOCKDATA);
            writeClassDesc(desc->getSuperDesc(),false);
        }

        void JObjectOutputStream::writeNonProxyDesc(JObjectStreamClass* desc,jbool unshared){
            bout->writeByte(TC_CLASSDESC);
            handles->assign((unshared?null : desc));
            writeClassDescriptor(desc);
            bout->setBlockDataMode(true);
            //TODO annotateClass
            bout->setBlockDataMode(false);
            bout->writeByte(TC_ENDBLOCKDATA);
            writeClassDesc(desc->getSuperDesc(),false);
        }

        void JObjectOutputStream::writeString(JString* str,jbool unshared){
            handles->assign((unshared?null : str));
            jlong utflen = bout->getUTFLength(str);
            if(utflen <= 0xFFFF){
                bout->writeByte(TC_STRING);
                bout->writeUTF(str, utflen);
            }else{
                bout->writeByte(TC_LONGSTRING);
                bout->writeLongUTF(str, utflen);
            }
        }

        void JObjectOutputStream::writeArray(JObject *obj, JObjectStreamClass* desc,jbool unshared){
            bout->writeByte(TC_ARRAY);
            writeClassDesc(desc,false);
            handles->assign((unshared?null : obj));

            writeArrayProperties(obj);
        }

        void JObjectOutputStream::writeArrayProperties(JObject* array){
            JPrimitiveArray* primitiveArray=dynamic_cast<JPrimitiveArray*>(array);
            jcpp::lang::JClass* ccl=array->getClass()->getComponentType();
            bout->writeInt(primitiveArray->size());

            if (ccl->isPrimitive()){
                if (primitiveArray->getClass()==JPrimitiveIntArray::getClazz()){
                    JPrimitiveIntArray* ia=dynamic_cast<JPrimitiveIntArray*>(primitiveArray);
                    bout->writeInts(ia,0,ia->size());

                }else if (primitiveArray->getClass()==JPrimitiveByteArray::getClazz()){
                    JPrimitiveByteArray* ia=dynamic_cast<JPrimitiveByteArray*>(primitiveArray);
                    bout->write(ia,0,ia->size());

                }else if (primitiveArray->getClass()==JPrimitiveLongArray::getClazz()){
                    JPrimitiveLongArray* ia=dynamic_cast<JPrimitiveLongArray*>(primitiveArray);
                    bout->writeLongs(ia,0,ia->size());

                }else if (primitiveArray->getClass()==JPrimitiveFloatArray::getClazz()){
                    JPrimitiveFloatArray* ia=dynamic_cast<JPrimitiveFloatArray*>(primitiveArray);
                    bout->writeFloats(ia,0,ia->size());

                }else if (primitiveArray->getClass()==JPrimitiveDoubleArray::getClazz()){
                    JPrimitiveDoubleArray* ia=dynamic_cast<JPrimitiveDoubleArray*>(primitiveArray);
                    bout->writeDoubles(ia,0,ia->size());

                }else if (primitiveArray->getClass()==JPrimitiveShortArray::getClazz()){
                    JPrimitiveShortArray* ia=dynamic_cast<JPrimitiveShortArray*>(primitiveArray);
                    bout->writeShorts(ia,0,ia->size());

                }else if (primitiveArray->getClass()==JPrimitiveCharArray::getClazz()){
                    JPrimitiveCharArray* ia=dynamic_cast<JPrimitiveCharArray*>(primitiveArray);
                    bout->writeChars(ia,0,ia->size());

                }else if (primitiveArray->getClass()==JPrimitiveBooleanArray::getClazz()){
                    JPrimitiveBooleanArray* ia=dynamic_cast<JPrimitiveBooleanArray*>(primitiveArray);
                    bout->writeBooleans(ia,0,ia->size());

                }else{
                    throw new JInternalError();
                }
            }else{
                for (jint i=0;i<primitiveArray->size();i++){
                    writeObject0(primitiveArray->get(i),false);
                }
            }
        }

        void JObjectOutputStream::writeEnum(JObject *obj, JObjectStreamClass* desc,jbool unshared){
            bout->writeByte(TC_ENUM);
            JObjectStreamClass* sdesc=desc->getSuperDesc();
            writeClassDesc((sdesc->forClass()==JEnum::getClazz()?desc:sdesc),false);
            handles->assign((unshared?null : obj));
            writeString( ((JEnum*)obj)->getName(),false);
        }

        void JObjectOutputStream::writeOrdinaryObject(JObject* obj, JObjectStreamClass* desc,jbool unshared){
            desc->checkSerialize();
            writeByte(TC_OBJECT);
            writeClassDesc(desc,false);
            handles->assign((unshared?null : obj));

            if (desc->isExternalizable() && !desc->isProxy()){
                writeExternalData(obj);
            }else{
                writeSerialData(obj,desc);
            }
        }
        
        void JObjectOutputStream::writeExternalData(JObject* obj){
            JPutField* oldPut=curPut;
            curPut=null;

            JSerialCallbackContext* oldContext=curContext;
            curContext=null;
            bout->setBlockDataMode(true);
            (dynamic_cast<JExternalizable*>(obj))->writeExternal(this);
            bout->setBlockDataMode(false);
            bout->writeByte(TC_ENDBLOCKDATA);
            curContext=oldContext;
            curPut=oldPut;
        }

        void JObjectOutputStream::writeSerialData(JObject *obj, JObjectStreamClass* desc){
            JPrimitiveObjectArray* classDataSlots=desc->getClassDataLayout();

            for (jint i=0;i<classDataSlots->size();i++){
                JObjectStreamClass::JClassDataSlot* dataSlot=dynamic_cast<JObjectStreamClass::JClassDataSlot*>(classDataSlots->get(i));
                JObjectStreamClass* slotDesc=dataSlot->desc;

                if (slotDesc->hasWriteObjectMethod()) {
                    JPutField* oldPut=curPut;
                    curPut=null;
                    JSerialCallbackContext* oldContext = curContext;
                    curContext = new JSerialCallbackContext(obj, slotDesc);
                    bout->setBlockDataMode(true);
                    slotDesc->invokeWriteObject(obj, this);
                    bout->setBlockDataMode(false);
                    bout->writeByte(TC_ENDBLOCKDATA);
                    curContext = oldContext;
                    curPut=oldPut;
                } else {
                    defaultWriteFields(obj, slotDesc);
                }
            }
        }

        void JObjectOutputStream::defaultWriteFields(JObject *obj, JObjectStreamClass* desc){
            desc->checkDefaultSerialize();

            jint primDataSize = desc->getPrimDataSize();
            if (primVals == null || primVals->size() < primDataSize) {
                primVals = new JPrimitiveByteArray(primDataSize);
            }
            desc->getPrimFieldValues(obj, primVals);
            bout->write(primVals, 0, primDataSize, false);
            
            JPrimitiveObjectArray* fields = desc->getFields();
            if (fields!=null){
                JPrimitiveObjectArray* objVals = new JPrimitiveObjectArray(JObject::getClazz(),desc->getNumObjFields());
                jint numPrimFields = fields->size() - objVals->size();
                desc->getObjFieldValues(obj, objVals);
            
                for (jint i = 0; i < objVals->size(); i++) {
                    JObjectStreamField* field=dynamic_cast<JObjectStreamField*>(fields->get(numPrimFields + i));
                    writeObject0(objVals->get(i),field->isUnshared());
                }
            }
        }

        void JObjectOutputStream::writeFatalException(JIOException* ex){
            clear();
            jbool oldMode=bout->setBlockDataMode(false);
            bout->writeByte(TC_EXCEPTION);
            writeObject0(ex,false);
            clear();
            bout->setBlockDataMode(oldMode);
        }

        JObjectOutputStream::~JObjectOutputStream(){
        }
    }
}
