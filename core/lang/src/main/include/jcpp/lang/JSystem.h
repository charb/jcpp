#ifndef JCPP_LANG_JSYSTEM_H
#define JCPP_LANG_JSYSTEM_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JString.h"
#include "jcpp/lang/JPrimitiveCharArray.h"
#include "jcpp/lang/JPrimitiveByteArray.h"
#include "jcpp/lang/JPrimitiveBooleanArray.h"
#include "jcpp/lang/JPrimitiveIntArray.h"
#include "jcpp/io/JPrintStream.h"
#include "jcpp/io/JInputStream.h"
#include "jcpp/util/JProperties.h"

using namespace jcpp::io;
using namespace jcpp::util;

int main(int argc, char* argv[]);

namespace jcpp{
    namespace lang{
        class JCPP_EXPORT JSystem : public JObject{
        protected:
            static JString* lSeparator;
            static JProperties* props;
            static JProperties* initProperties(JProperties* props);

            class ExitListener{
            public:
                virtual void exit(jint code)=0;
            };
            static ExitListener* exitListener;

            friend int ::main(int argc, char* argv[]);

        public:
            static jcpp::lang::JClass* getClazz();

            static JPrintStream* out;

            static JPrintStream* err;

            static JInputStream* in;

            static jlong currentTimeMillis();

            static jint identityHashCode(JObject* x);

            static void arraycopy(JPrimitiveObjectArray* src,jint srcPos, JPrimitiveObjectArray* dest, jint destPos, jint length);

            static void arraycopy(JPrimitiveCharArray* src,jint srcPos, JPrimitiveCharArray* dest, jint destPos, jint length);

            static void arraycopy(JPrimitiveByteArray* src,jint srcPos, JPrimitiveByteArray* dest, jint destPos, jint length);

            static void arraycopy(JPrimitiveBooleanArray* src,jint srcPos, JPrimitiveBooleanArray* dest, jint destPos, jint length);

            static void arraycopy(JPrimitiveIntArray* src,jint srcPos, JPrimitiveIntArray* dest, jint destPos, jint length);

            static JString* lineSeparator();

            static JProperties* getProperties();

            static void setProperties(JProperties* props);

            static JString* getProperty(JString* key);

            static JString* getProperty(JString* key,JString* def);

            static JString* setProperty(JString* key, JString* value);

            static JString* clearProperty(JString* key);

            static void exit(jint code);

            virtual ~JSystem();
        };
    }
}
#endif

