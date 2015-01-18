#include "jcpp/io/JObjectStreamClass.h"
#include "jcpp/io/JObjectStreamConstants.h"
#include "jcpp/io/JObjectStreamField.h"
#include "jcpp/io/JObjectInputStream.h"
#include "jcpp/io/JObjectOutputStream.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/reflect/JField.h"
#include "jcpp/lang/JPrimitiveBoolean.h"
#include "jcpp/lang/JPrimitiveByte.h"
#include "jcpp/lang/JPrimitiveChar.h"
#include "jcpp/lang/JPrimitiveShort.h"
#include "jcpp/lang/JPrimitiveInt.h"
#include "jcpp/lang/JPrimitiveFloat.h"
#include "jcpp/lang/JPrimitiveLong.h"
#include "jcpp/lang/JPrimitiveDouble.h"
#include "jcpp/io/JInvalidClassException.h"
#include "jcpp/lang/JInternalError.h"
#include "jcpp/lang/JUnsupportedOperationException.h"
#include "jcpp/io/JBits.h"
#include "jcpp/io/JSerializable.h"
#include "jcpp/io/JExternalizable.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/JNullPointerException.h"
#include "jcpp/io/JNotSerializableException.h"
#include "jcpp/util/JMap.h"
#include "jcpp/util/JHashMap.h"
#include "jcpp/lang/JStringBuilder.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JNoSuchMethodException.h"
#include "jcpp/util/JCollections.h"
#include "jcpp/util/JArrays.h"
#include "jcpp/lang/JNoSuchFieldException.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "jcpp/lang/JSystem.h"

using namespace jcpp::lang;
using namespace jcpp::lang::reflect;
using namespace jcpp::util;

namespace jcpp{
    namespace io{

        JString* JObjectStreamClass::WRITE_OBJECT_STRING = new JString("writeObject");

        JString* JObjectStreamClass::READ_OBJECT_STRING = new JString("readObject");

        JString* JObjectStreamClass::READ_OBJECT_STRING_NO_DATA = new JString("readObjectNoData");

        JString* JObjectStreamClass::WRITE_REPLACE_STRING = new JString("writeReplace");

        JString* JObjectStreamClass::READ_RESOLVE_STRING = new JString("readResolve");

        JString* JObjectStreamClass::SERIAL_PF_STRING = new JString("getSerialPersistentFields");


        JObjectStreamClass* JObjectStreamClass::lookup(jcpp::lang::JClass* cl) {
            return lookup(cl, false);
        }

        JObjectStreamClass* JObjectStreamClass::lookupAny(jcpp::lang::JClass* cl) {
            return lookup(cl, true);
        }

        JString* JObjectStreamClass::getName(){
            return name;
        }

        jcpp::lang::JClass* JObjectStreamClass::forClass(){
            return jClass;
        }

        JPrimitiveObjectArray* JObjectStreamClass::getFields(){
            return fields;
        }

        jint JObjectStreamClass::getNumFields(){
            return (fields==null?0:fields->size());
        }

        JObjectStreamField* JObjectStreamClass::getField(JString* name){
            return getField(name,null);
        }

        JString* JObjectStreamClass::toString(){
            JStringBuilder* builder=new JStringBuilder();
            builder->append("Class description :\nClass name : ")->append(name);
            builder->append(", SUID = ")->append(suid)->append(JSystem::lineSeparator());
            builder->append("Fields description :\nNumber of serializable fields = ")->append(getNumFields())->append(JSystem::lineSeparator());
            for (jint i = 0; i < getNumFields(); ++i) {
                JObjectStreamField* field=dynamic_cast<JObjectStreamField*>(fields->get(i));
                builder->append("type code : ")->append(field->getTypeCode())->append(", name : ")->append(field->getName())->append(JSystem::lineSeparator());
            }
            builder->append("Super ");
            if (superDesc == null) {
                builder->append(": null")->append(JSystem::lineSeparator())->append(JSystem::lineSeparator());
            }else {
                builder->append(superDesc->toString());
            }
            return builder->toString();
        }

        static JMap* allObjectStreamClass=null;

        JObjectStreamClass* JObjectStreamClass::lookup(jcpp::lang::JClass* meta, jbool all){
            if (meta == null){
                return null;
            }
            if (!all && !JSerializable::getClazz()->isAssignableFrom(meta)){
                return null;
            }
            JObjectStreamClass* desc=null;
            if (allObjectStreamClass==null){
                allObjectStreamClass=new JHashMap();
            }
            desc=dynamic_cast<JObjectStreamClass*>(allObjectStreamClass->get(meta));
            if (desc==null){
                desc = new JObjectStreamClass(meta);
                allObjectStreamClass->put(meta, desc);
            }
            return desc;
        }

        JObjectStreamClass::JObjectStreamClass(jcpp::lang::JClass* _class):JObject(getClazz()){
            this->primDataSize = 0;
            this->numObjFields = 0;
            this->fieldRefl=null;
            this->jClass=_class;
            this->name = _class->getName();
            this->bIsProxy=_class->isProxy();
            this->bIsEnum = _class->isEnum();
            this->serializable=JSerializable::getClazz()->isAssignableFrom(_class);
            this->externalizable=JExternalizable::getClazz()->isAssignableFrom(_class);
            this->suid=0;
            this->writeObjectData=false;
            this->blockExternalData=true;
            this->resolveEx=null;
            this->readObjectMethod=null;
            this->writeReplaceMethod=null;
            this->writeObjectMethod=null;
            this->readObjectNoDataMethod=null;
            this->readResolveMethod=null;
            this->dataLayout=null;
            this->deserializeEx=null;
            this->serializeEx=null;
            this->defaultSerializeEx=null;
            this->fields=null;
            this->cons=null;

            jcpp::lang::JClass* superCl=_class->getSuperclass();
            superDesc=(superCl != null)? lookup(superCl,false) : null;
            localDesc=this;
            if (serializable){
                if (bIsEnum) {
                    suid = 0;
                    fields = null;
                    return;
                }
                if (_class->isArray()) {
                    fields = null;
                    return;
                }

                suid = _class->getSerialVersionUID();
                try{
                    fields = getSerialFields(_class);
                    computeFieldOffsets();
                }catch(JInvalidClassException* e){
                    serializeEx=new JExceptionInfo(e->getClassname(),e->getMessage());
                    deserializeEx=serializeEx;
                    fields=null;
                }

                if (externalizable) {
                    cons = getExternalizableConstructor(_class);

                }else{
                    cons = getSerializableConstructor(_class);

                    JList* par=new JArrayList();
                    par->add(JObjectOutputStream::getClazz());
                    if (_class->hasMethod(WRITE_OBJECT_STRING,par)){
                        this->writeObjectMethod=_class->getDeclaredMethod(WRITE_OBJECT_STRING,par);
                        writeObjectData=writeObjectMethod!=null;
                    }

                    par=new JArrayList();
                    par->add(JObjectInputStream::getClazz());
                    if (_class->hasMethod(READ_OBJECT_STRING,par)){
                        this->readObjectMethod=_class->getDeclaredMethod(READ_OBJECT_STRING,par);
                    }

                    if (_class->hasMethod(READ_OBJECT_STRING_NO_DATA,null)){
                        this->readObjectNoDataMethod=_class->getDeclaredMethod(READ_OBJECT_STRING_NO_DATA,null);
                    }
                }
                if (_class->hasMethod(WRITE_REPLACE_STRING,null)){
                    this->writeReplaceMethod=getInheritableMethod(_class, WRITE_REPLACE_STRING, null, JObject::getClazz());
                }
                if (_class->hasMethod(READ_RESOLVE_STRING,null)){
                    this->readResolveMethod=getInheritableMethod(_class, READ_RESOLVE_STRING, null, JObject::getClazz());
                }

            }else{
                suid=0;
                fields=null;
            }

            fieldRefl=getReflector(fields,this);

            if (deserializeEx == null) {
                if (bIsEnum) {
                    deserializeEx = new JExceptionInfo(name, new JString("enum type"));
                } else if (cons == null) {
                    deserializeEx = new JExceptionInfo(name, new JString("no valid constructor"));
                }
            }
            for (jint i = 0; i < getNumFields(); i++) {
                JObjectStreamField* field=dynamic_cast<JObjectStreamField*>(fields->get(i));
                if (fields == null) {
                    defaultSerializeEx = new JExceptionInfo(name, new JString("unmatched serializable field(s) declared"));
                }
            }
        }

        JObjectStreamClass::JObjectStreamClass():JObject(getClazz()){
            this->name=null;
            this->suid=-1;
            this->bIsProxy=false;
            this->bIsEnum=false;
            this->serializable=false;
            this->externalizable=false;
            this->writeObjectData=false;
            this->blockExternalData=true;
            this->primDataSize=0;
            this->numObjFields=0;
            this->fieldRefl=null;
            this->fields = null;
            this->localDesc=null;
            this->superDesc=null;
            this->resolveEx=null;
            this->jClass=null;
            this->readObjectMethod=null;
            this->writeReplaceMethod=null;
            this->dataLayout=null;
            this->deserializeEx=null;
            this->serializeEx=null;
            this->defaultSerializeEx=null;
            cons=null;
            writeObjectMethod=null;
            readObjectNoDataMethod=null;
            readResolveMethod=null;
        }

        void JObjectStreamClass::initProxy(jcpp::lang::JClass* jClass,JClassNotFoundException* resolveEx,JObjectStreamClass* superDesc) {
            this->jClass= jClass;
            this->resolveEx=resolveEx;
            this->superDesc = superDesc;
            bIsProxy = true;
            serializable = true;
            suid = 0;
            fields = null;
            if (jClass!=null){
                localDesc=lookup(jClass,true);
                if (!localDesc->isProxy()){
                    throw new JInvalidClassException(new JString("cannot bind proxy descriptor to a non-proxy class"));
                }
                name = localDesc->getName();
                externalizable=localDesc->externalizable;
                writeReplaceMethod=localDesc->writeReplaceMethod;
                cons = localDesc->cons;
                readResolveMethod = localDesc->readResolveMethod;
                deserializeEx = localDesc->deserializeEx;
            }
            fieldRefl = getReflector(fields, localDesc);
        }

        void JObjectStreamClass::initNonProxy(JObjectStreamClass * model,jcpp::lang::JClass* jClass,JClassNotFoundException* resolveEx,JObjectStreamClass* superDesc){
            this->jClass = jClass;
            this->resolveEx=resolveEx;
            this->superDesc = superDesc;
            this->name = model->name;
            suid = model->suid;
            bIsProxy = false;
            bIsEnum = model->bIsEnum;
            serializable = model->serializable;
            externalizable = model->externalizable;
            blockExternalData= model->blockExternalData;
            writeObjectData = model->writeObjectData;
            if (model->fields!=null){
                fields = model->fields->clone();
            }else{
                fields=null;
            }
            primDataSize = model->primDataSize;
            numObjFields = model->numObjFields;

            if (jClass!=null){
                localDesc=lookup(jClass,true);
                if (localDesc->isProxy()) {
                    throw new JInvalidClassException(new JString("cannot bind non-proxy descriptor to a proxy class"));
                }
                if (bIsEnum != localDesc->isEnum()) {
                    throw new JInvalidClassException(new JString(isEnum() ? "cannot bind enum descriptor to a non-enum class" : "cannot bind non-enum descriptor to an enum class"));
                }
                this->cons = localDesc->cons;
                this->writeObjectMethod= localDesc->writeObjectMethod;
                this->readObjectMethod = localDesc->readObjectMethod;
                this->readObjectNoDataMethod = localDesc->readObjectNoDataMethod;
                this->writeReplaceMethod=localDesc->writeReplaceMethod;
                this->readResolveMethod = localDesc->readResolveMethod;
                if (deserializeEx == null) {
                    deserializeEx = localDesc->deserializeEx;
                }
            }
            fieldRefl = getReflector(fields, localDesc);
            fields = fieldRefl->getFields();
        }

        void JObjectStreamClass::readNonProxy(JObjectInputStream *in) {
            name = in->readUTF();
            suid = in->readLong();
            bIsProxy = false;

            jbyte flags = in->readByte();
            writeObjectData = ((flags & JObjectStreamConstants::SC_WRITE_METHOD) != 0);
            blockExternalData = ((flags & JObjectStreamConstants::SC_BLOCK_DATA) != 0);
            externalizable = ((flags & JObjectStreamConstants::SC_EXTERNALIZABLE) != 0);
            jbool sflag = ((flags & JObjectStreamConstants::SC_SERIALIZABLE) != 0);
            if (externalizable && sflag) {
                JStringBuilder* builder=new JStringBuilder();
                builder->append(name)->append(" : serializable and externalizable flags conflict");
                throw new JInvalidClassException(builder->toString());
            }

            bIsEnum = ((flags & JObjectStreamConstants::SC_ENUM) != 0);
            serializable = externalizable || sflag;
            if (bIsEnum && suid != 0) {
                JStringBuilder* builder=new JStringBuilder();
                builder->append("enum ")->append(name)->append(" descriptor has non-zero serialVersionUID: ")->append(suid);
                throw new JInvalidClassException(builder->toString());
            }

            jshort numFields = in->readShort();
            if (bIsEnum && numFields != 0) {
                JStringBuilder* builder=new JStringBuilder();
                builder->append("enum ")->append(name)->append(" descriptor has non-zero field count: ")->append(numFields);
                throw new JInvalidClassException(builder->toString());
            }

            if (numFields > 0) {
                fields = new JPrimitiveObjectArray(JObjectStreamField::getClazz(),(jint)numFields);
                for (jint i = 0; i < numFields; ++i) {
                    jchar tcode=(jchar) in->readByte();
                    JString* fname=in->readUTF();
                    JString* signature=null;
                    if ((tcode=='L' || (tcode=='['))){
                        signature=in->readTypeString();
                    }else{
                        signature=new JString(tcode);
                    }
                    fields->set(i,new JObjectStreamField(fname,signature,false));
                }
            }
            computeFieldOffsets();
        }

        void JObjectStreamClass::writeNonProxy(JObjectOutputStream* out){
            out->writeUTF(name);
            out->writeLong(suid);

            jbyte flags = 0;
            if (externalizable) {
                flags |= JObjectStreamConstants::SC_EXTERNALIZABLE;
                flags |= JObjectStreamConstants::SC_BLOCK_DATA;
            } else if (serializable) {
                flags |= JObjectStreamConstants::SC_SERIALIZABLE;
            }
            if (hasWriteObjectData()) {
                flags |= JObjectStreamConstants::SC_WRITE_METHOD;
            }
            if (isEnum()) {
                flags |= JObjectStreamConstants::SC_ENUM;
            }
            out->writeByte(flags);

            out->writeShort(getNumFields());
            for (jint i = 0; i < getNumFields(); i++) {
                JObjectStreamField* f = dynamic_cast<JObjectStreamField*>(fields->get(i));
                out->writeByte(f->getTypeCode());
                out->writeUTF(f->getName());
                if (!f->isPrimitive()) {
                    out->writeTypeString(f->getTypeString());
                }
            }
        }

        JClassNotFoundException* JObjectStreamClass::getResolveException(){
            return resolveEx;
        }

        void JObjectStreamClass::checkDeserialize() {
            if (deserializeEx != null) {
                throw deserializeEx->newInvalidClassException();
            }
        }

        void JObjectStreamClass::checkSerialize(){
            if (serializeEx != null) {
                throw serializeEx->newInvalidClassException();
            }
        }

        void JObjectStreamClass::checkDefaultSerialize(){
            if (defaultSerializeEx != null) {
                throw defaultSerializeEx->newInvalidClassException();
            }
        }

        JObjectStreamClass *JObjectStreamClass::getSuperDesc(){
            return superDesc;
        }

        JObjectStreamClass* JObjectStreamClass::getLocalDesc(){
            return localDesc;
        }

        JObjectStreamField* JObjectStreamClass::getField(JString* name,jcpp::lang::JClass* type){
            for (jint i=0;i<getNumFields();i++){
                JObjectStreamField* f=dynamic_cast<JObjectStreamField*>(fields->get(i));
                if (f->getName()->equals(name)){
                    if (type==null || (type==JObject::getClazz() && !f->isPrimitive())){
                        return f;
                    }
                    jcpp::lang::JClass* ft=f->getType();
                    if (ft!=null && type->isAssignableFrom(ft)){
                        return f;
                    }
                }
            }
            return null;
        }

        jbool JObjectStreamClass::isProxy(){
            return bIsProxy;
        }
        
        jbool JObjectStreamClass::isEnum(){
            return bIsEnum;
        }

        jbool JObjectStreamClass::isExternalizable(){
            return this->externalizable;
        }

        jbool JObjectStreamClass::isSerializable() {
            return this->serializable;
        }

        jbool JObjectStreamClass::hasBlockExternalData(){
            return this->blockExternalData;
        }

        jbool JObjectStreamClass::hasWriteObjectData() {
            return writeObjectData;
        }

        jbool JObjectStreamClass::isInstantiable() {
            return (cons != null);
        }

        jbool JObjectStreamClass::hasWriteObjectMethod(){
            return writeObjectMethod!=null;
        }

        jbool JObjectStreamClass::hasReadObjectMethod() {
            return readObjectMethod!=null;
        }

        jbool JObjectStreamClass::hasReadObjectNoDataMethod() {
            return (readObjectNoDataMethod != null);
        }

        jbool JObjectStreamClass::hasWriteReplaceMethod(){
            return (writeReplaceMethod != null);
        }

        jbool JObjectStreamClass::hasReadResolveMethod() {
            return (readResolveMethod != null);
        }

        JObject *JObjectStreamClass::newInstance() {
            if (cons != null) {
                return cons->newInstance(null);
            } else {
                throw new JUnsupportedOperationException();
            }
        }

        void JObjectStreamClass::invokeWriteObject(JObject* object, JObjectOutputStream* out){
            if (writeObjectMethod!=null){
                JList* args=new JArrayList();
                args->add(out);
                writeObjectMethod->invoke(object,args);
            }else{
                throw new JUnsupportedOperationException();
            }
        }

        void JObjectStreamClass::invokeReadObject(JObject* object, JObjectInputStream* in){
            if (readObjectMethod!=null){
                JList* args=new JArrayList();
                args->add(in);
                readObjectMethod->invoke(object,args);
            }else{
                throw new JUnsupportedOperationException();
            }
        }

        void JObjectStreamClass::invokeReadObjectNoData(JObject* obj){
            if (readObjectNoDataMethod != null) {
                readObjectNoDataMethod->invoke(obj,null);
            } else {
                throw new JUnsupportedOperationException();
            }
        }

        JObject* JObjectStreamClass::invokeWriteReplace(JObject* obj){
            if (writeReplaceMethod != null) {
                return writeReplaceMethod->invoke(obj, null);
            } else {
                throw new JUnsupportedOperationException();
            }
        }

        JObject* JObjectStreamClass::invokeReadResolve(JObject* obj){
            if (readResolveMethod != null) {
                return readResolveMethod->invoke(obj,null);
            } else {
                throw new JUnsupportedOperationException();
            }
        }

        JPrimitiveObjectArray* JObjectStreamClass::getClassDataLayout(){
            if (dataLayout == null) {
                dataLayout = getClassDataLayout0();
            }
            return dataLayout;
        }

        JPrimitiveObjectArray* JObjectStreamClass::getClassDataLayout0(){
            JList* classDataSlots = new JArrayList();
            jcpp::lang::JClass* start = jClass;
            jcpp::lang::JClass* end = jClass;

            while (end != null && JSerializable::getClazz()->isAssignableFrom(end)) {
                end = end->getSuperclass();
            }

            for (JObjectStreamClass* d = this; d != null; d = d->superDesc) {
                JString* searchName = ((d->forClass() != null) ? d->forClass()->getName() : d->getName());
                jcpp::lang::JClass* match = null;
                for (jcpp::lang::JClass* c = start; c != end; c = c->getSuperclass()) {
                    if (searchName->equals(c->getName())) {
                        match = c;
                        break;
                    }
                }

                if (match != null) {
                    for (jcpp::lang::JClass* c = start; c != match; c = c->getSuperclass()) {
                        classDataSlots->add(new JClassDataSlot(JObjectStreamClass::lookup(c,true), false));
                    }
                    start = match->getSuperclass();
                }
                classDataSlots->add(new JClassDataSlot(d->getVariantFor(match), true));
            }            

            for (jcpp::lang::JClass* c = start; c != end; c = c->getSuperclass()) {
                classDataSlots->add(new JClassDataSlot(JObjectStreamClass::lookup(c,true), false));
            }

            JCollections::reverse(classDataSlots);
            return classDataSlots->toArray();
        }

        jint JObjectStreamClass::getPrimDataSize(){
            return primDataSize;
        }

        jint JObjectStreamClass::getNumObjFields(){
            return numObjFields;
        }

        void JObjectStreamClass::getPrimFieldValues(JObject* obj, JPrimitiveByteArray* buf) {
            fieldRefl->getPrimFieldValues(obj, buf);
        }

        void JObjectStreamClass::setPrimFieldValues(JObject* obj, JPrimitiveByteArray* buf) {
            fieldRefl->setPrimFieldValues(obj, buf);
        }

        void JObjectStreamClass::getObjFieldValues(JObject* obj, JPrimitiveObjectArray* vals) {
            fieldRefl->getObjFieldValues(obj, vals);
        }

        void JObjectStreamClass::setObjFieldValues(JObject* obj, JPrimitiveObjectArray* vals) {
            fieldRefl->setObjFieldValues(obj, vals);
        }

        void JObjectStreamClass::computeFieldOffsets() {
            primDataSize = 0;
            numObjFields = 0;
            jint firstObjIndex = -1;

            for (jint i = 0; i < getNumFields(); ++i) {
                JObjectStreamField* field=dynamic_cast<JObjectStreamField*>(fields->get(i));
                switch (field->getTypeCode()) {
                case 'Z':
                case 'B':
                    field->setOffset(primDataSize++);
                    break;

                case 'C':
                case 'S':
                    field->setOffset(primDataSize);
                    primDataSize += 2;
                    break;

                case 'I':
                case 'F':
                    field->setOffset(primDataSize);
                    primDataSize += 4;
                    break;

                case 'J':
                case 'D':
                    field->setOffset(primDataSize);
                    primDataSize += 8;
                    break;

                case '[':
                case 'L':
                    field->setOffset(numObjFields++);
                    if (firstObjIndex == -1) {
                        firstObjIndex = i;
                    }
                    break;

                default:
                    throw new JInternalError();
                }
            }
            if (firstObjIndex != -1 && (firstObjIndex + numObjFields != getNumFields())) {
                JStringBuilder* builder=new JStringBuilder();
                builder->append(name)->append(" : illegal field order");
                throw new JInvalidClassException(builder->toString());
            }
        }

        JObjectStreamClass* JObjectStreamClass::getVariantFor(jcpp::lang::JClass* cl) {
            if (this->jClass== cl) {
                return this;
            }
            JObjectStreamClass* desc = new JObjectStreamClass();
            if (isProxy()) {
                desc->initProxy(cl, null, superDesc);
            } else {
                desc->initNonProxy(this, cl, null, superDesc);
            }
            return desc;
        }

        JConstructor* JObjectStreamClass::getExternalizableConstructor(jcpp::lang::JClass* cl) {
            try {
                JConstructor* cons = cl->getDeclaredConstructor(null);
                return ((cons->getModifiers() & JModifier::PUBLIC) != 0) ? cons : null;
            } catch (JNoSuchMethodException* ex) {
                return null;
            }
        }

        JConstructor* JObjectStreamClass::getSerializableConstructor(jcpp::lang::JClass* cl) {
            JClass* initCl = cl;
            try {
                JConstructor* cons = initCl->getDeclaredConstructor(null);
                jint mods = cons->getModifiers();
                if ((mods & JModifier::PRIVATE) != 0){
                    return null;
                }
                return cons;
            } catch (JNoSuchMethodException* ex) {
                return null;
            }
        }

        JMethod* JObjectStreamClass::getInheritableMethod(JClass* cl, JString* name, JList* argTypes, JClass* returnType){
            JMethod* meth = null;
            JClass* defCl = cl;
            while (defCl != null) {
                try {
                    meth = defCl->getDeclaredMethod(name, argTypes);
                    break;
                } catch (JNoSuchMethodException* ex) {
                    defCl = defCl->getSuperclass();
                }
            }

            if ((meth == null) || (meth->getReturnType() != returnType)) {
                return null;
            }
            jint mods = meth->getModifiers();
            if ((mods & (JModifier::STATIC | JModifier::ABSTRACT)) != 0) {
                return null;

            } else if ((mods & (JModifier::PUBLIC | JModifier::PROTECTED)) != 0) {
                return meth;

            } else if ((mods & JModifier::PRIVATE) != 0) {
                return (cl == defCl) ? meth : null;

            } else {
                return meth;
            }
        }

        JPrimitiveObjectArray* JObjectStreamClass::getSerialFields(jcpp::lang::JClass* cl){
            JPrimitiveObjectArray* fields=null;
            if (JSerializable::getClazz()->isAssignableFrom(cl) && !JExternalizable::getClazz()->isAssignableFrom(cl) && !cl->isInterface() && !cl->isProxy()){
                fields = getDeclaredSerialFields(cl);
                if (fields==null){
                    fields = getDefaultSerialFields(cl);
                }
                if (fields!=null){
                    JArrays::sort(fields);
                }
           }else{
                fields=null;
           }
           return fields;
        }

        JPrimitiveObjectArray* JObjectStreamClass::getDeclaredSerialFields(jcpp::lang::JClass* cl){
            JPrimitiveObjectArray* serialPersistentFields = null;
            if (cl->hasDeclaredMethod(SERIAL_PF_STRING,null)){
                JMethod* m = cl->getDeclaredMethod(SERIAL_PF_STRING,null);
                serialPersistentFields= dynamic_cast<JPrimitiveObjectArray*>(m->invoke(null,null));
            }
            if (serialPersistentFields == null) {
                return null;
            } else if (serialPersistentFields->size() == 0) {
                return null;
            }

            JPrimitiveObjectArray* boundFields=new JPrimitiveObjectArray(JObjectStreamField::getClazz(),serialPersistentFields->size());

            for (jint i = 0; i < serialPersistentFields->size(); i++) {
                JObjectStreamField* spf = dynamic_cast<JObjectStreamField*>(serialPersistentFields->get(i));
                
                JString* fname = spf->getName();
                try{
                    if (cl->hasDeclaredField(fname)){
                        JField* f = cl->getDeclaredField(fname);
                        if ((f->getType() == spf->getType()) && ((f->getModifiers() & JModifier::STATIC) == 0)){
                            boundFields->set(i,new JObjectStreamField(f, spf->isUnshared(), true));
                        }
                    }
                } catch (JNoSuchFieldException* ex) {
                }
                if (boundFields->get(i) == null) {
                    boundFields->set(i, new JObjectStreamField(fname, spf->getType(), spf->isUnshared()));
                }
            }
            return boundFields;
        }
        
        JPrimitiveObjectArray* JObjectStreamClass::getDefaultSerialFields(jcpp::lang::JClass* cl) {
            JList* clFields = cl->getDeclaredFields();
            if (clFields!=null){
                JList* list=new JArrayList();
                jint mask = JModifier::STATIC | JModifier::TRANSIENT;

                for (jint i = 0; i < clFields->size(); i++) {
                    JField* f=dynamic_cast<JField*>(clFields->get(i));
                    if ((f->getModifiers() & mask) == 0) {
                        list->add(new JObjectStreamField(f, false, true));
                    }
                }
                jint size = list->size();
                return (size == 0) ? null : list->toArray();
            }
            return null;
        }

        JObjectStreamClass::JFieldReflector::JFieldReflector(JPrimitiveObjectArray* fields,jint numFields, jint numObjFields) : JObject(JFieldReflector::getClazz()){
            this->fields = fields;
            this->numFields=numFields;
            this->numObjFields=numObjFields;
            this->numPrimFields=numFields-numObjFields;
        }

        JPrimitiveObjectArray* JObjectStreamClass::JFieldReflector::getFields() {
            return fields;
        }

        void JObjectStreamClass::JFieldReflector::setPrimFieldValues(JObject* obj, JPrimitiveByteArray *buf) {
            if (obj == null) {
                throw new JNullPointerException();
            }

            jint pos = 0;
            for (jint i = 0; i < numPrimFields; ++i) {
                JObjectStreamField* f = dynamic_cast<JObjectStreamField*>(fields->get(i));
                JField* field=f->getField(obj);
                switch (f->getTypeCode()) {
                    case 'Z': {
                        JPrimitiveBoolean* jPrimitiveBoolean=new JPrimitiveBoolean(JBits::getBoolean(buf,pos++));
                        field->set(obj,jPrimitiveBoolean);
                        break;

                    }case 'B':{
                        JPrimitiveByte* jPrimitiveByte=new JPrimitiveByte((jbyte) (buf->getByte(pos++)));
                        field->set(obj,jPrimitiveByte);
                        break;

                    }case 'C':{
                        JPrimitiveChar* jPrimitiveChar=new JPrimitiveChar(JBits::getChar(buf,pos));
                        pos += 2;
                        field->set(obj,jPrimitiveChar);
                        break;

                    }case 'S':{
                        JPrimitiveShort* jPrimitiveShort=new JPrimitiveShort(JBits::getShort(buf,pos));
                        pos += 2;
                        field->set(obj,jPrimitiveShort);
                        break;

                    }case 'I':{
                        JPrimitiveInt* jPrimitiveInt=new JPrimitiveInt(JBits::getInt(buf,pos));
                        pos += 4;
                        field->set(obj,jPrimitiveInt);
                        break;

                    }case 'F':{
                        JPrimitiveFloat* jPrimitiveFloat=new JPrimitiveFloat(JBits::getFloat(buf,pos));
                        pos += 4;
                        field->set(obj,jPrimitiveFloat);
                        break;

                    }case 'J':{
                        JPrimitiveLong* jPrimitiveLong=new JPrimitiveLong(JBits::getLong(buf,pos));
                        pos += 8;
                        field->set(obj,jPrimitiveLong);
                        break;

                    }case 'D':{
                        JPrimitiveDouble* jPrimitiveDouble=new JPrimitiveDouble(JBits::getDouble(buf,pos));
                        pos += 8;
                        field->set(obj,jPrimitiveDouble);
                        break;

                    }default:{
                        throw new JInternalError();
                    }
                }
            }
        }

        void JObjectStreamClass::JFieldReflector::getPrimFieldValues(JObject* obj,JPrimitiveByteArray* buf){
            if (obj==null){
                throw new JNullPointerException();
            }
            for (jint i=0 ; i< numPrimFields ; i++){
                JObjectStreamField* f=dynamic_cast<JObjectStreamField*>(fields->get(i));
                JField* field=f->getField(obj);
                jint off=f->getOffset();

                switch(f->getTypeCode()){
                    case 'Z':{
                        JPrimitiveBoolean* b=dynamic_cast<JPrimitiveBoolean*>(field->get(obj));
                        jbool v=b->get();
                        JBits::putBoolean(buf, off, v);
                        break;

                    }case 'B' :{
                        JPrimitiveByte* b=dynamic_cast<JPrimitiveByte*>(field->get(obj));
                        jbyte v=b->get();
                        buf->setByte(off, v);
                        break;

                    }case 'C':{
                        JPrimitiveChar* b=dynamic_cast<JPrimitiveChar*>(field->get(obj));
                        jchar v = b->get();
                        JBits::putChar(buf, off, v);
                        break;

                    } case 'S':{
                        JPrimitiveShort* b =dynamic_cast<JPrimitiveShort*>(field->get(obj));
                        jshort v = b->get();
                        JBits::putShort(buf, off, v);
                        break;

                    }case 'I' :{
                        JPrimitiveInt* b=dynamic_cast<JPrimitiveInt*>(field->get(obj));
                        jint v = b->get();
                        JBits::putInt(buf, off, v);
                        break;

                    }case 'F' :{
                        JPrimitiveFloat* b=dynamic_cast<JPrimitiveFloat*>(field->get(obj));
                        jfloat v = b->get();
                        JBits::putFloat(buf, off, v);
                        break;

                    }case 'J': {
                        JPrimitiveLong* b=dynamic_cast<JPrimitiveLong*>(field->get(obj));
                        jlong v = b->get();
                        JBits::putLong(buf, off, v);
                        break;

                    }case 'D': {
                        JPrimitiveDouble* b=dynamic_cast<JPrimitiveDouble*>(field->get(obj));
                        jdouble v = b->get();
                        JBits::putDouble(buf, off, v);
                    }
                }
            }
        }

        void JObjectStreamClass::JFieldReflector::getObjFieldValues(JObject* jobject, JPrimitiveObjectArray* values){
            if (jobject==null){
                throw new JNullPointerException();
            }
            for (jint i=numPrimFields;i<fields->size();i++){
                JObjectStreamField* f=dynamic_cast<JObjectStreamField*>(fields->get(i));
                JField* field=f->getField(jobject);
                switch (f->getTypeCode() ){
                    case 'L':
                    case '[':{
                        JObject* current=field->get(jobject);
                        values->set(i-numPrimFields,current);
                        break;
                    }default:
                        throw new JInternalError();
                }
            }
        }

        void JObjectStreamClass::JFieldReflector::setObjFieldValues(JObject* jObject,JPrimitiveObjectArray* values) {
            if (jObject == null) {
                throw new JNullPointerException();
            }
            for (jint i = numPrimFields; i < fields->size(); ++i) {
                JObjectStreamField* f=dynamic_cast<JObjectStreamField*>(fields->get(i));
                JField* field=f->getField(jObject);
                switch (f->getTypeCode() ){
                    case 'L':
                    case '[':{
                        JObject* current = values->get(i-numPrimFields);
                        field->set(jObject,current);
                        break;
                    }default:
                        throw new JInternalError();
                }
            }
        }

        JObjectStreamClass::JFieldReflector* JObjectStreamClass::getReflector(JPrimitiveObjectArray* fields, JObjectStreamClass* localDesc){
            JPrimitiveObjectArray* localFields = (localDesc != null) ? localDesc->fields : null;
            JPrimitiveObjectArray* matches = new JPrimitiveObjectArray(JObjectStreamField::getClazz(),(fields!=null ? fields->size() : 0));
            jint nbObjFields=0;
            
            for (jint i = 0; i < matches->size(); i++) {
                JObjectStreamField* f = dynamic_cast<JObjectStreamField*>(fields->get(i));
                JObjectStreamField* m = null;
                
                if (localFields!=null){
                    for (jint j = 0; j < localFields->size(); j++) {
                        JObjectStreamField* lf = dynamic_cast<JObjectStreamField*>(localFields->get(j));
                        
                        if (f->getName()->equals(lf->getName())) {
                            if ((f->isPrimitive() || lf->isPrimitive()) && f->getTypeCode() != lf->getTypeCode()){
                                JStringBuilder* builder=new JStringBuilder();
                                builder->append("incompatible types for field ")->append(f->getName());
                                throw new JInvalidClassException(lf->getName(),builder->toString());
                            }
                            
                            if (lf->getField() != null) {
                                m = new JObjectStreamField(lf->getField(), lf->isUnshared(), false);
                            } else {
                                m = new JObjectStreamField(lf->getName(), lf->getSignature(), lf->isUnshared());
                            }
                        }
                    }
                }

                if (m == null) {
                    m = new JObjectStreamField(f->getName(), f->getSignature(), false);
                }
                m->setOffset(f->getOffset());
                matches->set(i, m);
                if (!m->isPrimitive()){
                    nbObjFields++;
                }
            }

            return new JFieldReflector(matches,matches->size(), nbObjFields);
        }

        JObjectStreamClass::~JObjectStreamClass() {
        }
    }
}
