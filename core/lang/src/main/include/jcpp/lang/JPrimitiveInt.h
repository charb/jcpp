#ifndef JCPP_LANG_JPRIMITIVEINT_H
#define JCPP_LANG_JPRIMITIVEINT_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JComparable.h"
#include "jcpp/io/JSerializable.h"
#include "jcpp/lang/JString.h"

using namespace jcpp::io;

namespace jcpp{
    namespace lang{
        class JCPP_EXPORT JPrimitiveInt : public JObject, public JComparable, public JSerializable{
            protected:
                jint value;

            public:
                JPrimitiveInt();

                JPrimitiveInt(jint value);

                static jcpp::lang::JClass* getClazz();

                virtual void set(jint value);
                
                virtual jint get();

                virtual jint compareTo(JObject* o);

                virtual jbool equals(JObject* other);

                virtual jint hashCode();

                virtual JString* toString();

                virtual JPrimitiveInt* clone();

                virtual ~JPrimitiveInt();
        };
    }
}

#endif
