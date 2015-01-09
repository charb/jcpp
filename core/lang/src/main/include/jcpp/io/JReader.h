#ifndef JCPP_IO_JREADER_H
#define JCPP_IO_JREADER_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JReadable.h"
#include "jcpp/io/JCloseable.h"
#include "jcpp/lang/JPrimitiveCharArray.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{

    	//@Class(canonicalName="java.io.Reader", simpleName="Reader");
        class JCPP_EXPORT JReader : public JObject  , public JReadable  , public JCloseable  {
            protected:
                JObject* lock;
                JPrimitiveCharArray* skipBuffer;
                JPrimitiveCharArray* readBuffer;
                jint length;
                JReader(jcpp::lang::JClass* _class);
                JReader(jcpp::lang::JClass* _class,JObject* lock);

            public:
                static jcpp::lang::JClass* getClazz();

                virtual jint read();

                virtual jint read(JPrimitiveCharArray* b, jint off, jint len)=0;

                virtual jlong skip(jlong n);

                virtual jbool ready();

                virtual jbool markSupported();

                virtual void mark(jint);

                virtual void reset();

                virtual void close()=0;

                virtual ~JReader();
        };
    }
}

#endif
