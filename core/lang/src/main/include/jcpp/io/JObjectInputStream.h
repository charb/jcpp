#ifndef JCPP_IO_JOBJECTINPUTSTREAM_H
#define JCPP_IO_JOBJECTINPUTSTREAM_H

#include "jcpp/io/JInputStream.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/io/JObjectStreamConstants.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JClassLoader.h"
#include "jcpp/io/JObjectStreamClass.h"
#include "jcpp/lang/JEnum.h"
#include "jcpp/io/JBits.h"
#include "jcpp/io/JSerialCallbackContext.h"
#include "jcpp/io/JInputHandleList.h"
#include "jcpp/io/JInputHandleTable.h"
#include "jcpp/io/JBlockDataInputStream.h"
#include "jcpp/io/JIOException.h"
#include "jcpp/io/JObjectInput.h"
#include "jcpp/lang/JPrimitiveBooleanArray.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace lang{
        class JString;
    }
    namespace io{
        class JObjectStreamClass;
        class JGetFieldImpl;
        class JObjectStreamClass;

        static const jint NULL_HANDLE = -1;

        //@Class(canonicalName="java.io.ObjectInputStream", simpleName="ObjectInputStream");
        class JCPP_EXPORT JObjectInputStream : public JInputStream, public JObjectInput, public JObjectStreamConstants{
        private:
        	static JObject* unsharedMarker;
        public:
            class JCPP_EXPORT JGetField : public JObject{
            protected:
                JGetField(jcpp::lang::JClass* _class):JObject(_class){
                }

            public:
                static jcpp::lang::JClass* getClazz();
                virtual JObjectStreamClass* getObjectStreamClass()=0;
                virtual jbool defaulted(JString* name)=0;
                virtual jbool get(JString* name,jbool val)=0;
                virtual jbyte get(JString* name,jbyte val)=0;
                virtual jchar get(JString* name,jchar val)=0;
                virtual jshort get(JString* name,jshort val)=0;
                virtual jint get(JString* name,jint val)=0;
                virtual jlong get(JString* name,jlong val)=0;
                virtual jfloat get(JString* name,jfloat val)=0;
                virtual jdouble get(JString* name,jdouble val)=0;
                virtual JObject* get(JString* name,JObject* val)=0;
                virtual ~JGetField();
            };

        protected:
            JBlockDataInputStream* bin;
            jint depth;
            jbool closed;
            JInputHandleTable* handles;
            jint passHandle;
            JPrimitiveByteArray* primVals;
            jbool enableOverride;
            jbool enableResolve;
            JSerialCallbackContext* curContext;

            JObjectInputStream(JInputStream* inputStrean,jcpp::lang::JClass* _class);
            virtual void init(JInputStream* in);
            virtual JObject* readObjectOverride();
            virtual jcpp::lang::JClass* resolveClass(JObjectStreamClass* jObjectStreamClass);
            virtual jcpp::lang::JClass* resolveProxyClass(JPrimitiveObjectArray* str);
            virtual JObject* resolveObject(JObject* jobject);
            virtual jbool enableResolveObject(jbool enable);
            virtual void readStreamHeader();
            virtual JObjectStreamClass* readClassDescriptor();
            virtual void clear();
            virtual JObject* readObject0(jbool unshared);
            virtual JObject* checkResolve(JObject*);
            virtual JString* readTypeString();
            virtual JObject* readNull();
            virtual JObject* readHandle(jbool unshared);
            virtual JObject* readClass(jbool unshared);
            virtual JObjectStreamClass* readClassDesc(jbool unshared);
            virtual JObjectStreamClass* readProxyDesc(jbool unshared);
            virtual JObjectStreamClass* readNonProxyDesc(jbool unshared);
            virtual JString* readString(jbool unshared);
            virtual JObject* readArray(jbool unshared);
            virtual JObject* readEnum(jbool unshared);
            virtual JObject* readOrdinaryObject(jbool unshared);
            virtual void readExternalData(JObject*, JObjectStreamClass*);
            virtual void readSerialData(JObject*, JObjectStreamClass*);
            virtual void skipCustomData();
            virtual void defaultReadFields(JObject*, JObjectStreamClass*);
            virtual JIOException* readFatalException();
            virtual void handleReset();
            friend class JGetFieldImpl;
            friend class JObjectStreamClass;

        public:
            JObjectInputStream(JInputStream* inputStrean);
                        
            static jcpp::lang::JClass* getClazz();
            
            virtual JObject* readObject();

            virtual JObject* readUnshared();

            virtual void defaultReadObject();

            virtual JGetField* readFields();

            virtual jint read();

            virtual jint read(JPrimitiveByteArray* b);

            virtual jint read(JPrimitiveByteArray* b, jint off, jint len);

            virtual jlong skip(jlong n);

            virtual jint available();

            virtual void close();

            virtual jbool readBoolean();

            virtual jbyte readByte();

            virtual jint readUnsignedByte();

            virtual jchar readChar();

            virtual jshort readShort();

            virtual jint readUnsignedShort();

            virtual jint readInt();

            virtual jlong readLong();
            
            virtual jfloat readFloat();
            
            virtual jdouble readDouble();
            
            virtual void readFully(JPrimitiveByteArray* b);
            
            virtual void readFully(JPrimitiveByteArray* b, jint off, jint len);
            
            virtual jint skipBytes(jint n);
            
            virtual JString* readUTF();
            
            virtual ~JObjectInputStream();
        };
    }
}

#endif
