#ifndef JCPP_IO_JOBJECTINPUT_H
#define JCPP_IO_JOBJECTINPUT_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/io/JDataInput.h"
#include "jcpp/lang/JAutoCloseable.h"
#include "jcpp/lang/JPrimitiveByteArray.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{

    	//@Class(canonicalName="java.io.ObjectInput", simpleName="ObjectInput");
        class JCPP_EXPORT JObjectInput : public JDataInput, public JAutoCloseable{
        public:
            static jcpp::lang::JClass* getClazz();

            virtual jcpp::lang::JObject* readObject()=0;

            virtual jint read()=0;

            virtual jint read(JPrimitiveByteArray* b)=0;

            virtual jint read(JPrimitiveByteArray* b, jint off, jint len)=0;

            virtual jlong skip(jlong n)=0;

            virtual jint available()=0;

            virtual void close()=0;

            virtual ~JObjectInput();
        };
    }
}

#endif
