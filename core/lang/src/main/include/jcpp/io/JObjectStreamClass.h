#ifndef JCPP_IO_JOBJECTSTREAMCLASS_H
#define JCPP_IO_JOBJECTSTREAMCLASS_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JString.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "jcpp/lang/JPrimitiveLongArray.h"
#include "jcpp/lang/JPrimitiveIntArray.h"
#include "jcpp/lang/JPrimitiveCharArray.h"
#include "jcpp/lang/JPrimitiveByteArray.h"
#include "jcpp/io/JInputStream.h"
#include "jcpp/io/JObjectStreamConstants.h"
#include "jcpp/io/JObjectStreamField.h"
#include "jcpp/lang/JClassNotFoundException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/io/JObjectStreamField.h"
#include "jcpp/io/JSerializable.h"
#include "jcpp/io/JInvalidClassException.h"
#include "jcpp/util/JList.h"
#include "jcpp/util/JArrayList.h"

using namespace jcpp::lang;
using namespace jcpp::util;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace io{
        class JObjectInputStream;
        class JObjectOutputStream;
        class JObjectStreamClassClass;
        class JGetFieldImpl;
        class JPutFieldImpl;

        //@Class(canonicalName="java.io.ObjectStreamClass", simpleName="ObjectStreamClass");
        class JCPP_EXPORT JObjectStreamClass : public JObject, public JSerializable{
        private:
       				static const jlong serialVersionUID = -6120832682080437368LL;
       			 static JMap* allObjectStreamClass;
        protected:
            static JString* WRITE_OBJECT_STRING;
            static JString* READ_OBJECT_STRING;
            static JString* READ_OBJECT_STRING_NO_DATA;
            static JString* WRITE_REPLACE_STRING;
            static JString* READ_RESOLVE_STRING;
            static JString* SERIAL_PF_STRING;

            //@Class(canonicalName="java.io.ObjectStreamClass$ClassDataSlot", simpleName="ObjectStreamClass$ClassDataSlot");
            class JCPP_EXPORT JClassDataSlot : public JObject{
                public:
                    JObjectStreamClass* desc;
                    jbool hasData;

                    JClassDataSlot(JObjectStreamClass* desc, jbool hasData):JObject(getClazz()){
                        this->desc = desc;
                        this->hasData = hasData;
                    }

                    static jcpp::lang::JClass* getClazz();
            };

            //@Class(canonicalName="java.io.ObjectStreamClass$ExceptionInfo", simpleName="ObjectStreamClass$ExceptionInfo");
            class JCPP_EXPORT JExceptionInfo : public JObject {
                public:
                    JString* className;
                    JString* message;

                    JExceptionInfo(JString* cn, JString* msg) : JObject(getClazz()){
                        className = cn;
                        message = msg;
                    }

                    static jcpp::lang::JClass* getClazz();

                    JInvalidClassException* newInvalidClassException() {
                        return new JInvalidClassException(className, message);
                    }
            };

            //@Class(canonicalName="java.io.ObjectStreamClass$FieldReflector", simpleName="ObjectStreamClass$FieldReflector");
            class JCPP_EXPORT JFieldReflector : public JObject{
            private:
                JPrimitiveObjectArray* fields;
                jint numFields;
                jint numObjFields;
                jint numPrimFields;

            public:
                JFieldReflector(JPrimitiveObjectArray* fields,jint numFields, jint numObjFields);

                static jcpp::lang::JClass* getClazz();

                JPrimitiveObjectArray* getFields();
                
                void getPrimFieldValues(JObject* obj, JPrimitiveByteArray* buf);
                
                void setPrimFieldValues(JObject* obj, JPrimitiveByteArray* buf);
                
                void getObjFieldValues(JObject* obj, JPrimitiveObjectArray* vals);
                
                void setObjFieldValues(JObject* obj, JPrimitiveObjectArray* vals);
            };
            
            jcpp::lang::JClass* jClass;
            JString* name;
            jlong suid;
            jbool bIsProxy;
            jbool bIsEnum;
            jbool serializable;
            jbool externalizable;
            jbool writeObjectData;
            jbool blockExternalData;
            JClassNotFoundException* resolveEx;
            JExceptionInfo* deserializeEx;
            JExceptionInfo* serializeEx;
            JExceptionInfo* defaultSerializeEx;
            JPrimitiveObjectArray* fields;
            jint primDataSize;
            jint numObjFields;
            JFieldReflector* fieldRefl;
            JPrimitiveObjectArray* dataLayout;
            JConstructor* cons;
            JMethod* writeObjectMethod;
            JMethod* readObjectMethod;
            JMethod* readObjectNoDataMethod;
            JMethod* writeReplaceMethod;
            JMethod* readResolveMethod;
            JObjectStreamClass* localDesc;
            JObjectStreamClass* superDesc;

            static JObjectStreamClass* lookup(jcpp::lang::JClass* obj,jbool all);
            JObjectStreamClass();
            JObjectStreamClass(jcpp::lang::JClass* _class);
            void initProxy(jcpp::lang::JClass* jClass,JClassNotFoundException* resolveEx,JObjectStreamClass* jObjectStreamClass);
            void initNonProxy(JObjectStreamClass* objectStreamClass,jcpp::lang::JClass* jClass,JClassNotFoundException* resolveEx,JObjectStreamClass* jObjectStreamClass);
            void readNonProxy(JObjectInputStream* objectInputStream);
            void writeNonProxy(JObjectOutputStream* out);
            JClassNotFoundException* getResolveException();
            void checkSerialize();
            void checkDeserialize();
            void checkDefaultSerialize();
            JObjectStreamClass* getSuperDesc();
            JObjectStreamClass* getLocalDesc();
            jbool isProxy();
            jbool isEnum();
            jbool isExternalizable();
            jbool isSerializable();
            jbool hasBlockExternalData();
            jbool hasWriteObjectData();
            jbool isInstantiable();
            jbool hasWriteObjectMethod();
            jbool hasReadObjectMethod();
            jbool hasReadObjectNoDataMethod();
            jbool hasWriteReplaceMethod();
            jbool hasReadResolveMethod();
            JObject* newInstance();
            void invokeWriteObject(JObject* object, JObjectOutputStream* out);
            void invokeReadObject(JObject* objet, JObjectInputStream* in);
            void invokeReadObjectNoData(JObject* obj);
            JObject* invokeWriteReplace(JObject* obj);
            JObject* invokeReadResolve(JObject* obj);
            JPrimitiveObjectArray* getClassDataLayout();
            JPrimitiveObjectArray* getClassDataLayout0();
            jint getPrimDataSize();
            jint getNumObjFields();
            void getPrimFieldValues(JObject *obj,JPrimitiveByteArray *buf);
            void setPrimFieldValues(JObject *obj,JPrimitiveByteArray *buf);
            void getObjFieldValues(JObject* jobject, JPrimitiveObjectArray* values);
            void setObjFieldValues(JObject* jobject, JPrimitiveObjectArray* values);
            void computeFieldOffsets();
            JObjectStreamClass* getVariantFor(jcpp::lang::JClass* cl);
            static JConstructor* getExternalizableConstructor(jcpp::lang::JClass* cl);
            static JConstructor* getSerializableConstructor(jcpp::lang::JClass* cl);
            static JMethod* getInheritableMethod(JClass* cl, JString* name, JList* argTypes, JClass* returnType);
            static JPrimitiveObjectArray* getSerialFields(jcpp::lang::JClass* cl);
            static JPrimitiveObjectArray* getDeclaredSerialFields(jcpp::lang::JClass* cl);
            static JPrimitiveObjectArray* getDefaultSerialFields(jcpp::lang::JClass* cl);
            static JFieldReflector* getReflector(JPrimitiveObjectArray* fields,JObjectStreamClass* localDesc);
            friend class JObjectInputStream;
            friend class JObjectOutputStream;
            friend class JGetFieldImpl;
            friend class JPutFieldImpl;

        public:
            static jcpp::lang::JClass* getClazz();

            static JObjectStreamClass* lookup(jcpp::lang::JClass* obj);

            static JObjectStreamClass* lookupAny(jcpp::lang::JClass* obj);

            JString* getName();

            jcpp::lang::JClass* forClass();

            JPrimitiveObjectArray* getFields();

            jint getNumFields();

            JObjectStreamField* getField(JString* name);

            JObjectStreamField* getField(JString* name,jcpp::lang::JClass* type);

            JString* toString();

            virtual ~JObjectStreamClass();
        };
    }
}

#endif
