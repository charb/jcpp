#include "jcpp/io/JObjectInputStream.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/io/JSerializable.h"
#include "jcpp/io/JStreamCorruptedException.h"
#include "jcpp/io/JOptionalDataException.h"
#include "jcpp/io/JNotActiveException.h"
#include "jcpp/io/JInvalidClassException.h"
#include "jcpp/lang/JInternalError.h"
#include "jcpp/lang/JPrimitiveArray.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "jcpp/lang/JPrimitiveBoolean.h"
#include "jcpp/lang/JPrimitiveByte.h"
#include "jcpp/lang/JPrimitiveChar.h"
#include "jcpp/lang/JPrimitiveDouble.h"
#include "jcpp/lang/JPrimitiveFloat.h"
#include "jcpp/lang/JPrimitiveInt.h"
#include "jcpp/lang/JPrimitiveLong.h"
#include "jcpp/lang/JThread.h"
#include "jcpp/lang/JClassCastException.h"
#include "jcpp/lang/JPrimitiveShort.h"
#include "jcpp/io/JExternalizable.h"
#include "jcpp/lang/reflect/JProxy.h"
#include "jcpp/io/JBlockDataInputStream.h"
#include "jcpp/io/JInvalidObjectException.h"
#include "jcpp/lang/JString.h"
#include "jcpp/lang/JBoolean.h"
#include "jcpp/lang/JByte.h"
#include "jcpp/lang/JCharacter.h"
#include "jcpp/lang/JShort.h"
#include "jcpp/lang/JInteger.h"
#include "jcpp/lang/JFloat.h"
#include "jcpp/lang/JLong.h"
#include "jcpp/lang/JDouble.h"
#include "jcpp/lang/JIllegalArgumentException.h"
#include "jcpp/lang/reflect/JArray.h"
#include "jcpp/lang/JSystem.h"

using namespace jcpp::lang::reflect;
using namespace jcpp::lang;

namespace jcpp{
    namespace io{

        JObjectInputStream::JGetField::~JGetField(){
        }

        //@Class(canonicalName="java.io.ObjectInputStream$GetFieldImpl", simpleName="ObjectInputStream$GetFieldImpl");
        class JGetFieldImpl : public JObjectInputStream::JGetField{
        protected:
            JObjectInputStream* in;
            JObjectStreamClass* desc;
            JPrimitiveByteArray* primVals;
            JPrimitiveObjectArray* objVals;
            JPrimitiveIntArray* objHandles;

        public:
            JGetFieldImpl(JObjectInputStream* in,JObjectStreamClass* desc):JGetField(getClazz()){
                this->in=in;
                this->desc=desc;
                primVals=new JPrimitiveByteArray(desc->getPrimDataSize());
                objVals=new JPrimitiveObjectArray(JObject::getClazz(),desc->getNumObjFields());
                objHandles=new JPrimitiveIntArray(desc->getNumObjFields());
            }

            static jcpp::lang::JClass* getClazz(){
                if (getFieldImplClazz==null){
                    getFieldImplClazz=new JGetFieldImplClass();
                }
                return getFieldImplClazz;
            }

            virtual JObjectStreamClass* getObjectStreamClass(){
                return desc;
            }

            virtual jbool defaulted(JString* name){
                return (getFieldOffset(name, null) < 0);
            }

            virtual jbool get(JString* name, jbool val){
                jint off = getFieldOffset(name, JBoolean::TYPE);
                return ((off >= 0) ? JBits::getBoolean(primVals, off) : val);
            }

            virtual jbyte get(JString* name, jbyte val){
                jint off = getFieldOffset(name, JByte::TYPE);
                return (off >= 0) ? primVals->getByte(off) : val;
            }

            virtual jchar get(JString* name, jchar val){
                jint off = getFieldOffset(name, JCharacter::TYPE);
                return (off >= 0) ? JBits::getChar(primVals, off) : val;
            }

            virtual jshort get(JString* name, jshort val){
                jint off = getFieldOffset(name, JShort::TYPE);
                return (off >= 0) ? JBits::getShort(primVals, off) : val;
            }

            virtual jint get(JString* name, jint val){
                jint off = getFieldOffset(name, JInteger::TYPE);
                return (off >= 0) ? JBits::getInt(primVals, off) : val;
            }

            virtual jfloat get(JString* name, jfloat val){
                jint off = getFieldOffset(name, JFloat::TYPE);
                return (off >= 0) ? JBits::getFloat(primVals, off) : val;
            }

            virtual jlong get(JString* name, jlong val){
                jint off = getFieldOffset(name, JLong::TYPE);
                return (off >= 0) ? JBits::getLong(primVals, off) : val;
            }

            virtual jdouble get(JString* name, jdouble val){
                jint off = getFieldOffset(name, JDouble::TYPE);
                return (off >= 0) ? JBits::getDouble(primVals, off) : val;
            }

            virtual JObject* get(JString* name, JObject* val){
                jint off = getFieldOffset(name, JObject::getClazz());
                if (off >= 0) {
                    jint objHandle = objHandles->getInt(off);
                    in->handles->markDependency(in->passHandle, objHandle);
                    return ((in->handles->lookupException(objHandle) == null) ? objVals->get(off) : null);
                } else {
                    return val;
                }
            }

            virtual void readFields(){
                in->bin->readFully(primVals, 0, primVals->size(), false);

                jint oldHandle = in->passHandle;
                JPrimitiveObjectArray* fields = desc->getFields();
                jint numPrimFields = fields->size()- objVals->size();
                for (jint i = 0; i < objVals->size(); i++) {
                    JObjectStreamField* f=dynamic_cast<JObjectStreamField*>(fields->get(numPrimFields + i));
                    objVals->set(i, in->readObject0(f->isUnshared()));
                    objHandles->setInt(i,in->passHandle);
                }
                in->passHandle = oldHandle;
            }

            virtual jint getFieldOffset(JString* name, jcpp::lang::JClass* type) {
                JObjectStreamField* field = desc->getField(name, type);
                if (field != null) {
                    return field->getOffset();
                } else if (desc->getLocalDesc()->getField(name, type) != null) {
                    return -1;
                } else {
                    JStringBuilder* builder=new JStringBuilder();
                    builder->append("no such field ")->append(name)->append(" with type ")->append(type->toString());
                    throw new JIllegalArgumentException(builder->toString());
                }
            }

            ~JGetFieldImpl(){
            }
        };


        static JObject* unsharedMarker = new JObject();

        JObjectInputStream::JObjectInputStream(JInputStream *in,jcpp::lang::JClass* _class):JInputStream(_class){
            init(in);
        }

        JObjectInputStream::JObjectInputStream(JInputStream *in):JInputStream(getClazz()){
            init(in);
        }

        void JObjectInputStream::init(JInputStream* in){
            enableOverride=false;
            closed=false;
            depth=0;
            passHandle = NULL_HANDLE;
            primVals = null;
            curContext=null;
            if (in!=null){
                bin = new JBlockDataInputStream(in);
                handles = new JInputHandleTable(10);
                enableResolve=false;
                readStreamHeader();
                bin->setBlockDataMode(true);
            }else{
                bin=null;
                handles=null;
                enableOverride=true;
            }
        }

        JObject* JObjectInputStream::readObject() {
            if (enableOverride) {
                return readObjectOverride();
            }

            jint outerHandle=passHandle;
            JObject* obj=readObject0(false);
            handles->markDependency(outerHandle,passHandle);
            JClassNotFoundException* ex=handles->lookupException(passHandle);
            if (ex!=null){
                throw ex;
            }
            passHandle=outerHandle;
            if (closed && depth == 0) {
                clear();
            }
            return obj;
        }

        JObject* JObjectInputStream::readObjectOverride(){
            return null;
        }

        JObject* JObjectInputStream::readUnshared(){
            jint outerHandle=passHandle;
            JObject* obj=readObject0(true);
            handles->markDependency(outerHandle,passHandle);
            JClassNotFoundException* ex=handles->lookupException(passHandle);
            passHandle=outerHandle;
            if (ex!=null){
                throw ex;
            }
            if (closed && depth == 0) {
                clear();
            }
            return obj;
        }

        void JObjectInputStream::defaultReadObject() {
            JObject* curObj = curContext->getObj();
            JObjectStreamClass* curDesc = curContext->getDesc();
            bin->setBlockDataMode(false);
            defaultReadFields(curObj, curDesc);
            bin->setBlockDataMode(true);
            if (!curDesc->hasWriteObjectData()) {
                bin->setDefaultDataEnd(true);
            }
            JClassNotFoundException* ex=handles->lookupException(passHandle);
            if (ex!=null){
                throw ex;
            }
        }

        JObjectInputStream::JGetField* JObjectInputStream::readFields(){
            if (curContext == null) {
                throw new JNotActiveException(new JString("not in call to readObject"));
            }
            JObject* curObj=curContext->getObj();
            JObjectStreamClass* curDesc = curContext->getDesc();
            bin->setBlockDataMode(false);
            JGetFieldImpl* getField = new JGetFieldImpl(this,curDesc);
            getField->readFields();
            bin->setBlockDataMode(true);
            if (!curDesc->hasWriteObjectData()) {
                bin->setDefaultDataEnd(true);
            }
            return getField;
        }

        jcpp::lang::JClass *JObjectInputStream::resolveClass(JObjectStreamClass* desc) {
            return JThread::currentThread()->getContextClassLoader()->loadClass(desc->getName());
        }

        jcpp::lang::JClass* JObjectInputStream::resolveProxyClass(JPrimitiveObjectArray* ifaces) {
            JList* interfaces=new JArrayList();
            for (jint i = 0; i < ifaces->size(); ++i) {
                JString* iname=dynamic_cast<JString*>(ifaces->get(i));
                jcpp::lang::JClass* c=JThread::currentThread()->getContextClassLoader()->loadClass(iname);
                interfaces->add(c);
            }
            return JProxy::getProxyClass(JThread::currentThread()->getContextClassLoader(),interfaces);
        }

        JObject* JObjectInputStream::resolveObject(JObject *obj) {
            return obj;
        }

        jbool JObjectInputStream::enableResolveObject(jbool enable) {
            if (enable == enableResolve) {
                return enable;
            }
            enableResolve = enable;
            return !enableResolve;
        }

        void JObjectInputStream::readStreamHeader(){
            jshort s0 = bin->readShort();
            jshort s1 = bin->readShort();
            if (s0 != STREAM_MAGIC || s1 != STREAM_VERSION) {
                throw new JStreamCorruptedException(new JString("invalid stream header"));
            }
        }

        JObjectStreamClass* JObjectInputStream::readClassDescriptor(){
            JObjectStreamClass* desc = new JObjectStreamClass();
            desc->readNonProxy(this);
            return desc;
        }

        jint JObjectInputStream::read() {
            return bin->read();
        }

        jint JObjectInputStream::read(JPrimitiveByteArray* b) {
            return bin->read(b,0,b->size());
        }

        jint JObjectInputStream::read(JPrimitiveByteArray* b, jint off, jint len) {
            return bin->read(b,off,len);
        }

        jlong JObjectInputStream::skip(jlong n){
            return JInputStream::skip(n);
        }

        jint JObjectInputStream::available() {
            return bin->available();
        }

        void JObjectInputStream::close(){
            closed = true;
            if (depth == 0) {
                clear();
            }
            this->bin->close();
        }

        jbool JObjectInputStream::readBoolean() {
            return bin->readBoolean();
        }

        jbyte JObjectInputStream::readByte() {
            return bin->readByte();
        }

        jint JObjectInputStream::readUnsignedByte(){
            return bin->readUnsignedByte();
        }

        jchar JObjectInputStream::readChar() {
            return bin->readChar();
        }

        jshort JObjectInputStream::readShort() {
            return bin->readShort();
        }

        jint JObjectInputStream::readUnsignedShort(){
            return bin->readUnsignedShort();
        }

        jint JObjectInputStream::readInt() {
            return bin->readInt();
        }

        jlong JObjectInputStream::readLong() {
            return bin->readLong();
        }

        jfloat JObjectInputStream::readFloat() {
            return bin->readFloat();
        }

        jdouble JObjectInputStream::readDouble() {
            return bin->readDouble();
        }

        void JObjectInputStream::readFully(JPrimitiveByteArray* b){
            bin->readFully(b,0,b->size(),false);
        }

        void JObjectInputStream::readFully(JPrimitiveByteArray* b, jint off, jint len){
            bin->readFully(b,off,len,false);
        }

        jint JObjectInputStream::skipBytes(jint n){
            return bin->skipBytes(n);
        }

        JString* JObjectInputStream::readUTF() {
            return bin->readUTF();
        }

        void JObjectInputStream::clear() {
            handles->clear();
        }

        JObject* JObjectInputStream::readObject0(jbool unshared) {
            jbool oldMode = bin->getBlockDataMode();
            if (oldMode) {
                jint remain = bin->currentBlockRemaining();
                if (remain > 0) {
                    throw new JOptionalDataException();
                }else if (bin->isDefaultDataEnd()) {
                    throw new JOptionalDataException();
                }
                bin->setBlockDataMode(false);
            }
            jbyte tc;
            while ((tc = bin->peekByte()) == TC_RESET) {
                tc = bin->readByte();
                handleReset();
            }

            depth++;
            JObject* obj = null;
            switch (tc) {
            case TC_NULL:
                obj = readNull();
                break;

            case TC_REFERENCE:
                obj = readHandle(unshared);
                break;

            case TC_CLASS:
                obj=readClass(unshared);
                break;

            case TC_CLASSDESC:
            case TC_PROXYCLASSDESC:
                obj=readClassDesc(unshared);
                break;

            case TC_STRING:
            case TC_LONGSTRING:
                obj = checkResolve(readString(unshared));
                break;

            case TC_ARRAY:
                obj = checkResolve(readArray(unshared));
                break;

            case TC_ENUM:
                obj = checkResolve(readEnum(unshared));
                break;

            case TC_OBJECT:
                obj = checkResolve(readOrdinaryObject(unshared));
                break;

            case TC_EXCEPTION:{
                    JIOException* ex1 = readFatalException();
                    throw ex1;
                }
                break;

            case TC_BLOCKDATA:
            case TC_BLOCKDATALONG:
                if (oldMode){
                    bin->setBlockDataMode(true);
                    bin->peek();
                    throw new JOptionalDataException();
                }else{
                    throw new JStreamCorruptedException(new JString("unexpected block data"));
                }

            case TC_ENDBLOCKDATA:
                if (oldMode) {
                    throw new JOptionalDataException(true);
                } else {
                    throw new JStreamCorruptedException(new JString("unexpected end of block data"));
                }
                break;

            default:
                bin->setBlockDataMode(oldMode);
                throw new JStreamCorruptedException(new JString("invalid type code:"));
            }
            depth--;
            bin->setBlockDataMode(oldMode);
            return obj;
        }

        JObject* JObjectInputStream::checkResolve(JObject *obj) {
            if (!enableResolve || handles->lookupException(passHandle)!=null) {
                return obj;
            }
            JObject* rep = resolveObject(obj);
            if (rep != obj) {
                handles->setObject(passHandle, rep);
            }
            return rep;
        }

        JString* JObjectInputStream::readTypeString() {
            JString* str=null;
            jint oldHandle=passHandle;
            jbyte tc = bin->peekByte();
            switch (tc) {
                case TC_STRING:
                case TC_LONGSTRING:
                    str=readString(false);
                    break;

                case TC_NULL:
                    str=dynamic_cast<JString*> (readNull());
                    break;

                case TC_REFERENCE:
                    str=dynamic_cast<JString*> (readHandle(false));
                    break;

                default:
                    passHandle=oldHandle;
                    throw new JStreamCorruptedException(new JString("stream corrupted: invalid typecode "));
            }
            passHandle=oldHandle;
            return str;
        }

        JObject* JObjectInputStream::readNull() {
            if (bin->readByte() != TC_NULL) {
                throw new JInternalError();
            }
            passHandle = NULL_HANDLE;
            return null;
        }

        JObject* JObjectInputStream::readHandle(jbool unshared) {
            if (bin->readByte() != TC_REFERENCE) {
                throw new JInternalError();
            }
            jint tmp=bin->readInt();
            passHandle = tmp - baseWireHandle;
            if (passHandle < 0 || passHandle >= handles->getSize()) {
                throw new JStreamCorruptedException(new JString("invalid handle value"));
            }
            if (unshared){
                throw new JInvalidObjectException(new JString("cannot read back reference as unshared"));
            }
            JObject* obj = handles->lookupObject(passHandle);
            if (obj==unsharedMarker){
                throw new JInvalidObjectException(new JString("cannot read back reference as unshared"));
            }
            return obj;
        }

        JObject* JObjectInputStream::readClass(jbool unshared){
            if (bin->readByte() != TC_CLASS){
                throw new JInternalError();
            }
            JObjectStreamClass* desc=readClassDesc(false);
            jcpp::lang::JClass* jClass=desc->forClass();
            passHandle=handles->assign((unshared ? unsharedMarker : jClass));

            JClassNotFoundException* resolveEx = desc->getResolveException();
            if (resolveEx!=null){
                handles->markException(passHandle,resolveEx);
            }

            handles->finish(passHandle);
            return jClass;
        }

        JObjectStreamClass* JObjectInputStream::readClassDesc(jbool unshared) {
            jbyte tc = bin->peekByte();

            switch (tc) {
            case TC_NULL:
                return (JObjectStreamClass*) (readNull());

            case TC_REFERENCE:
                return (JObjectStreamClass*) (readHandle(unshared));

            case TC_CLASSDESC:
                return readNonProxyDesc(unshared);

            case TC_PROXYCLASSDESC:
                return readProxyDesc(unshared);

            default:
                throw new JStreamCorruptedException(new JString("invalid type code: "));
            }
        }

        JObjectStreamClass* JObjectInputStream::readProxyDesc(jbool unshared) {
            if (bin->readByte() != TC_PROXYCLASSDESC) {
                throw new JInternalError();
            }
            JObjectStreamClass* desc = new JObjectStreamClass;
            jint descHandle = handles->assign((unshared ? unsharedMarker : desc));
            passHandle = NULL_HANDLE;

            jint numIfaces = bin->readInt();
            JPrimitiveObjectArray* ifaces = new JPrimitiveObjectArray(JString::getClazz(),numIfaces);
            for (jint i = 0; i < numIfaces; ++i) {
                ifaces->set(i, bin->readUTF());
            }

            jcpp::lang::JClass* metaObj=null;
            JClassNotFoundException* resolveEx=null;
            bin->setBlockDataMode(true);
            try{
                metaObj = resolveProxyClass(ifaces);
                if(metaObj==null){
                    resolveEx=new JClassNotFoundException(new JString("null class"));
                }
            }catch(JClassNotFoundException* ex){
                resolveEx=ex;
            }
            skipCustomData();

            desc->initProxy(metaObj, resolveEx,readClassDesc(false));

            handles->finish(descHandle);
            passHandle = descHandle;
            return desc;
        }

        JObjectStreamClass* JObjectInputStream::readNonProxyDesc(jbool unshared) {
            if (bin->readByte() != TC_CLASSDESC) {
                throw new JInternalError();
            }
            JObjectStreamClass* desc = new JObjectStreamClass;
            jint descHandle = handles->assign((unshared ? unsharedMarker : desc));
            passHandle = NULL_HANDLE;

            JObjectStreamClass* readDesc = readClassDescriptor();

            jcpp::lang::JClass* metaObj=null;
            JClassNotFoundException* resolveEx=null;
            bin->setBlockDataMode(true);
            try{
                metaObj = resolveClass(readDesc);
                if (metaObj==null){
                    resolveEx=new JClassNotFoundException(new JString("null class"));
                }
            }catch(JClassNotFoundException* ex){
                resolveEx=ex;
            }
            skipCustomData();

            desc->initNonProxy(readDesc, metaObj, resolveEx,readClassDesc(false));

            handles->finish(descHandle);
            passHandle = descHandle;
            return desc;
        }

        JString* JObjectInputStream::readString(jbool unshared) {
            jbyte tc = bin->readByte();
            JString* str=null;
            switch (tc) {
                case TC_STRING:
                    str = bin->readUTF();
                    break;

                case TC_LONGSTRING:
                    str = bin->readLongUTF();
                    break;

                default:
                    throw new JStreamCorruptedException(new JString("invalid type code: "));
            }
            passHandle = handles->assign((unshared ? unsharedMarker : str));
            handles->finish(passHandle);
            return str;
        }

        JObject* JObjectInputStream::readArray(jbool unshared){
            if (bin->readByte() != TC_ARRAY) {
                throw new JInternalError();
            }

            JObjectStreamClass* desc = readClassDesc(false);
            jint len = bin->readInt();

            JPrimitiveArray* pArray = null;
            jcpp::lang::JClass* cl=desc->forClass();
            jcpp::lang::JClass* ccl=null;
            if (cl != null) {
                ccl = cl->getComponentType();
                pArray = dynamic_cast<JPrimitiveArray*>(JArray::newInstance(ccl,len));
            }

            jint arrayHandle = handles->assign((unshared ? unsharedMarker : pArray));
            JClassNotFoundException* resolveEx=desc->getResolveException();
            if (resolveEx!=null){
                handles->markException(arrayHandle,resolveEx);
            }

            if(ccl==null) {
                for (jint i = 0; i < len; i++) {
                    readObject0(false);
                }
            }else if (ccl->isPrimitive()){
                if (ccl == JPrimitiveByte::getClazz()) {
                    JPrimitiveByteArray* ar=dynamic_cast<JPrimitiveByteArray*>(pArray);
                    bin->read(ar,0,len);

                }else if (ccl==JPrimitiveChar::getClazz()) {
                    JPrimitiveCharArray* ar=dynamic_cast<JPrimitiveCharArray*>(pArray);
                    bin->readChars(ar,0,len);

                }else if (ccl==JPrimitiveDouble::getClazz()) {
                    JPrimitiveDoubleArray* ar=dynamic_cast<JPrimitiveDoubleArray*>(pArray);
                    bin->readDoubles(ar,0,len);

                }else if (ccl==JPrimitiveFloat::getClazz()) {
                    JPrimitiveFloatArray* ar=dynamic_cast<JPrimitiveFloatArray*>(pArray);
                    bin->readFloats(ar,0,len);

                }else if (ccl == JPrimitiveInt::getClazz()) {
                    JPrimitiveIntArray* ar=dynamic_cast<JPrimitiveIntArray*>(pArray);
                    bin->readInts(ar,0,len);

                }else if (ccl==JPrimitiveLong::getClazz()) {
                    JPrimitiveLongArray* ar=dynamic_cast<JPrimitiveLongArray*>(pArray);
                    bin->readLongs(ar,0,len);

                }else if (ccl==JPrimitiveShort::getClazz()) {
                    JPrimitiveShortArray* ar=dynamic_cast<JPrimitiveShortArray*>(pArray);
                    bin->readShorts(ar,0,len);

                }else if (ccl==JPrimitiveBoolean::getClazz()) {
                    JPrimitiveBooleanArray* ar=dynamic_cast<JPrimitiveBooleanArray*>(pArray);
                    bin->readBooleans(ar,0,len);

                }else {
                    throw new JInternalError();
                }
            }else{
                for (jint i = 0 ; i < len; ++i) {
                    pArray->set(i,readObject0(false));
                    handles->markDependency(arrayHandle,passHandle);
                }
            }

            handles->finish(arrayHandle);
            passHandle = arrayHandle;
            return pArray;
        }

        JObject* JObjectInputStream::readEnum(jbool unshared) {
            if (bin->readByte() != TC_ENUM) {
                throw new JInternalError();
            }

            JObjectStreamClass* desc = readClassDesc(false);
            if (!desc->isEnum()){
                throw new JInvalidClassException(new JString("non-enum class: "));
            }

            jint enumHandle = handles->assign((unshared ? unsharedMarker : null));
            JClassNotFoundException* resolveEx=desc->getResolveException();
            if (resolveEx!=null){
                handles->markException(enumHandle,resolveEx);
            }

            JString* mname = readString(false);
            JEnum* en = null;
            if (desc->forClass()!=null){
                en=desc->forClass()->valueOf(mname);
                if (!unshared){
                    handles->setObject(enumHandle,en);
                }
            }

            handles->finish(enumHandle);
            passHandle = enumHandle;
            return en;
        }

        JObject* JObjectInputStream::readOrdinaryObject(jbool unshared) {
            if (bin->readByte() != TC_OBJECT) {
                throw new JInternalError();
            }

            JObjectStreamClass* desc = readClassDesc(false);
            desc->checkDeserialize();

            jcpp::lang::JClass* cl = desc->forClass();
            JObject* obj = desc->isInstantiable() ? desc->newInstance() : null;

            passHandle = handles->assign((unshared ? unsharedMarker : obj));
            JClassNotFoundException* resolveEx=desc->getResolveException();
            if (resolveEx!=null){
                handles->markException(passHandle,resolveEx);
            }

            if (desc->isExternalizable()){
                readExternalData(obj,desc);
            }else{
                readSerialData(obj, desc);
            }

            handles->finish(passHandle);
            
            if (obj != null && handles->lookupException(passHandle) == null && desc->hasReadResolveMethod()){
                JObject* rep = desc->invokeReadResolve(obj);
                if (unshared && rep->getClass()->isArray()) {
                    rep = rep->clone();
                }
                if (rep != obj) {
                    handles->setObject(passHandle, obj = rep);
                }
            }
            return obj;
        }
        
        void JObjectInputStream::readExternalData(JObject* obj, JObjectStreamClass* desc){
            JSerialCallbackContext* oldContext=curContext;
            curContext=null;
            jbool blocked=desc->hasBlockExternalData();
            if (blocked){
                bin->setBlockDataMode(true);
            }
            if (obj!=null){
                try{
                    (dynamic_cast<JExternalizable*>(obj))->readExternal(this);
                } catch (JClassNotFoundException* ex) {
                    handles->markException(passHandle, ex);
                }
            }
            if (blocked){
                skipCustomData();
            }
            curContext=oldContext;
        }
       
        void JObjectInputStream::readSerialData(JObject *obj, JObjectStreamClass *desc) {
            if (obj==null){
                return;
            }
            JPrimitiveObjectArray* dataSlots=desc->getClassDataLayout();

            for (jint i=0;i<dataSlots->size();i++){
                JObjectStreamClass::JClassDataSlot* dataSlot=dynamic_cast<JObjectStreamClass::JClassDataSlot*>(dataSlots->get(i));
                JObjectStreamClass* slotDesc=dataSlot->desc;
                
                if (dataSlot->hasData){
                    if (obj!=null && slotDesc->hasReadObjectMethod() && handles->lookupException(passHandle)==null){
                        JSerialCallbackContext* oldContext = curContext;
                        try{
                            curContext=new JSerialCallbackContext(obj,slotDesc);
                            bin->setBlockDataMode(true);
                            slotDesc->invokeReadObject(obj,this);
                        }catch(JClassNotFoundException* ex){
                            handles->markException(passHandle,ex);
                        }
                        curContext=oldContext;
                        bin->setDefaultDataEnd(false);

                    }else {
                        defaultReadFields(obj,slotDesc);
                    }
                    if (slotDesc->hasWriteObjectData()) {
                        skipCustomData();
                    }else {
                        bin->setBlockDataMode(false);
                    }
                }else{
                    if (obj != null && slotDesc->hasReadObjectNoDataMethod() && handles->lookupException(passHandle) == null){
                        slotDesc->invokeReadObjectNoData(obj);
                    }
                }
            }
        }

        void JObjectInputStream::skipCustomData() {
            jint oldHandle = passHandle;
            for (;;) {
                if (bin->getBlockDataMode()) {
                    bin->skipBlockData();
                    bin->setBlockDataMode(false);
                }
                switch (bin->peekByte()) {
                    case TC_BLOCKDATA:
                    case TC_BLOCKDATALONG:
                        bin->setBlockDataMode(true);
                        break;

                    case TC_ENDBLOCKDATA:
                        bin->readByte();
                        passHandle = oldHandle;
                        return;

                    default:
                        readObject0(false);
                        break;
                }
            }
        }

        void JObjectInputStream::defaultReadFields(JObject *obj, JObjectStreamClass *desc) {
            jcpp::lang::JClass* cl=desc->forClass();
            if (cl!=null && obj!=null && !cl->isInstance(obj)){
                throw new JClassCastException();
            }

            jint primDataSize = desc->getPrimDataSize();
            if (primVals == null || primVals->size() < primDataSize) {
                primVals = new JPrimitiveByteArray(primDataSize);
            }
            bin->readFully(primVals,0,primDataSize,false);
            if (obj != null) {
                desc->setPrimFieldValues(obj, primVals);
            }

            jint objHandle = passHandle;
            JPrimitiveObjectArray* fields=desc->getFields();
            jint numObjFields = desc->getNumObjFields();
            JPrimitiveObjectArray* objVals = new JPrimitiveObjectArray(JObject::getClazz(),numObjFields);
            jint numPrimFields=(fields!=null ? fields->size():0) -objVals->size();
            for (jint i = 0; i < objVals->size(); ++i) {
                JObjectStreamField* f=dynamic_cast<JObjectStreamField*>(fields->get(numPrimFields+i));
                JObject* readObj = readObject0(f->isUnshared());
                objVals->set(i,readObj);
                if (f->getField()!=null){
                    handles->markDependency(objHandle,passHandle);
                }
            }
            if (obj != null) {
                desc->setObjFieldValues(obj,objVals);
            }
            passHandle = objHandle;
        }

        JIOException* JObjectInputStream::readFatalException(){
            if (bin->readByte()!=TC_EXCEPTION){
                throw new JInternalError();
            }
            clear();
            return dynamic_cast<JIOException*>(readObject0(false));
        }

        void JObjectInputStream::handleReset(){
            if (depth > 0) {
                throw new JStreamCorruptedException(new JString("unexpected reset; recursion depth: "));
            }
            clear();
        }

        JObjectInputStream::~JObjectInputStream() {
        }
    }
}
