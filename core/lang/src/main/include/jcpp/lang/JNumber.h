#ifndef JCPP_LANG_JNUMBER_H
#define JCPP_LANG_JNUMBER_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/io/JSerializable.h"

using namespace jcpp::io;

namespace jcpp{
    namespace lang{
        class JCPP_EXPORT JNumber: public JObject, public JSerializable{
            protected :
                JNumber(jcpp::lang::JClass* _class);

            public:
                static jcpp::lang::JClass* getClazz();
 
                virtual jint intValue()=0;
 
                virtual jlong longValue()=0;
 
                virtual jfloat floatValue()=0;
 
                virtual jdouble doubleValue()=0;
 
                virtual jbyte byteValue() {
                    return (jbyte)intValue();
                }
 
                virtual jshort shortValue() {
                    return (jshort)intValue();
                }
 
                virtual JString* toString()=0;
 
                virtual ~JNumber();
        };
    }
}
#endif
