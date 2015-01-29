#ifndef JCPP_IO_JOBJECTOUTPUTSTREAM_H
#define JCPP_IO_JOBJECTOUTPUTSTREAM_H

#include "jcpp/io/JObjectStreamClass.h"
#include "jcpp/io/JObjectStreamConstants.h"
#include "jcpp/io/JBlockDataOutputStream.h"
#include "jcpp/lang/JClassLoader.h"
#include "jcpp/io/JDataOutputStream.h"
#include "jcpp/io/JSerialCallbackContext.h"
#include "jcpp/io/JOutputHandleTable.h"
#include "jcpp/io/JObjectOutput.h"
#include "jcpp/io/JIOException.h"
#include "jcpp/lang/JPrimitiveByteArray.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{
    	class JPutFieldImpl;
    	class JObjectStreamClass;

    	//@Class(canonicalName="java.io.ObjectOutputStream", simpleName="ObjectOutputStream");
        class JCPP_EXPORT JObjectOutputStream : public JOutputStream, public JObjectOutput, public JObjectStreamConstants{
        public:
    		//@Class(canonicalName="java.io.ObjectOutputStream$PutField", simpleName="ObjectOutputStream$PutField");
            class JCPP_EXPORT JPutField : public JObject{
            protected:
                JPutField(jcpp::lang::JClass* _class):JObject(_class){
                }
            public:
                static jcpp::lang::JClass* getClazz();
                virtual void put(JString* name,jbool val)=0;
                virtual void put(JString* name,jbyte val)=0;
                virtual void put(JString* name,jchar val)=0;
                virtual void put(JString* name,jshort val)=0;
                virtual void put(JString* name,jint val)=0;
                virtual void put(JString* name,jlong val)=0;
                virtual void put(JString* name,jfloat val)=0;
                virtual void put(JString* name,jdouble val)=0;
                virtual void put(JString* name,JObject* val)=0;
                virtual void write(JObjectOutput* out)=0;
                virtual ~JPutField();
            };

        protected:
            JBlockDataOutputStream* bout;
            JOutputHandleTable* handles;
            jint depth;
            JPrimitiveByteArray* primVals;
            jint lengthPrimVals;
            jbool enableOverride;
            jbool enableReplace;
            JSerialCallbackContext* curContext;
            JPutField* curPut;

            JObjectOutputStream(JOutputStream* out,jcpp::lang::JClass* _class);
            JObjectOutputStream(jcpp::lang::JClass* _class);
            virtual void init(JOutputStream* out);
            virtual void writeObjectOverride(JObject* obj);
            virtual JObject* replaceObject(JObject *obj);
            virtual jbool enableReplaceObject(jbool enable);
            virtual void writeStreamHeader();
            virtual void writeClassDescriptor(JObjectStreamClass* desc);
            virtual void drain();
            virtual void writeTypeString(JString* str);
            virtual void clear();
            virtual void writeObject0(JObject* object,jbool unshared);
            virtual void writeNull();
            virtual void writeHandle(jint handle);
            virtual void writeClass(jcpp::lang::JClass* cl,jbool unshared);
            virtual void writeClassDesc(JObjectStreamClass* desc,jbool unshared);
            virtual void writeProxyDesc(JObjectStreamClass* desc,jbool unshared);
            virtual void writeNonProxyDesc(JObjectStreamClass* desc,jbool unshared);
            virtual void writeString(JString* str,jbool unshared);
            virtual void writeArray(JObject* obj,JObjectStreamClass* desc,jbool unshared);
            virtual void writeArrayProperties(JObject* array);
            virtual void writeEnum(JObject* obj, JObjectStreamClass* desc,jbool unshared);
            virtual void writeOrdinaryObject(JObject* object, JObjectStreamClass* desc,jbool unshared);
            virtual void writeExternalData(JObject* obj);
            virtual void writeSerialData(JObject* obj, JObjectStreamClass* desc);
            virtual void defaultWriteFields(JObject* obj, JObjectStreamClass* desc);
            virtual void writeFatalException(JIOException* ex);
            friend class JPutFieldImpl;
            friend class JObjectStreamClass;

        public:
            JObjectOutputStream(JOutputStream* out);

            static jcpp::lang::JClass* getClazz();

            virtual void writeObject(JObject* object);

            virtual void writeUnshared(JObject* object);

            virtual void defaultWriteObject();

            virtual JPutField* putFields();

            virtual void writeFields();

            virtual void reset();

            virtual void write(jint b);

            virtual void write(JPrimitiveByteArray* b);

            virtual void write(JPrimitiveByteArray* b, jint off, jint len);

            virtual void flush();

            virtual void close();

            virtual void writeBoolean(jbool b);

            virtual void writeByte(jint b);

            virtual void writeShort(jint v);

            virtual void writeChar(jint v);

            virtual void writeInt(jint v);

            virtual void writeLong(jlong v);

            virtual void writeFloat(jfloat v);

            virtual void writeDouble(jdouble v);

            virtual void writeBytes(JString* str);

            virtual void writeChars(JString* str);

            virtual void writeUTF(JString* str);

            virtual ~JObjectOutputStream();
        };
    }
}
#endif
