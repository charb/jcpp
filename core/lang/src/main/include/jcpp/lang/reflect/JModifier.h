#ifndef JCPP_LANG_REFLECT_JMODIFIER_H
#define JCPP_LANG_REFLECT_JMODIFIER_H

#include "jcpp/lang/JObject.h"

namespace jcpp{
    namespace lang{
        namespace reflect{

            class JCPP_EXPORT JModifier: public JObject{
            public:

                static jcpp::lang::JClass* getClazz();

                static jint PUBLIC;

                static jint PRIVATE;

                static jint PROTECTED;

                static jint STATIC;

                static jint FINAL;

                static jint SYNCHRONIZED;

                static jint VOLATILE;

                static jint TRANSIENT;

                static jint NATIVE;

                static jint INTERFACE;

                static jint ABSTRACT;

                static jint STRICT;

                static jint BRIDGE;

                static jint VARARGS;

                static jint SYNTHETIC;

                static jint ANNOTATION;

                static jint ENUM;

                static jint SYNTHESIZED;

                static jbool isAbstract(jint mod);
                
                static jbool isFinal(jint mod);

                static jbool isInterface(jint mod);

                static jbool isNative(jint mod);

                static jbool isPrivate(jint mod);

                static jbool isProtected(jint mod);

                static jbool isPublic(jint mod);

                static jbool isStatic(jint mod);

                static jbool isStrict(jint mod);

                static jbool isSynchronized(jint mod);

                static jbool isTransient(jint mod);

                static jbool isVolatile(jint mod);

                static JString* toString(jint mod);

                virtual ~JModifier();
            };
        }
    }
}
#endif
