#ifndef JCPP_LANG_REFLECT_JMEMBER_H
#define JCPP_LANG_REFLECT_JMEMBER_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/annotation/JAnnotation.h"

using namespace jcpp::lang::annotation;

namespace jcpp{
    namespace util{
        class JList;
    }
    namespace lang{
        class JString;
        class JClass;

        namespace reflect{
            class JCPP_EXPORT JMember: public JInterface{

            public:
                static jcpp::lang::JClass* getClazz();

                static jint PUBLIC;

                static jint DECLARED;

                virtual jcpp::lang::JClass* getDeclaringClass()=0;

                virtual JString* getName()=0;

                virtual jint getModifiers()=0;

                virtual ~JMember();
            };
        }
    }
}
#endif
