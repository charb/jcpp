#ifndef JCPP_LANG_JPRIMITIVEFLOAT_H
#define JCPP_LANG_JPRIMITIVEFLOAT_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JComparable.h"
#include "jcpp/io/JSerializable.h"
#include "jcpp/lang/JString.h"

using namespace jcpp::io;

namespace jcpp{
    namespace lang{
        class JCPP_EXPORT JPrimitiveFloat : public JObject, public JComparable, public JSerializable{
            protected:
                jfloat value;

            public:
                JPrimitiveFloat();

                JPrimitiveFloat(jfloat value);

                static jcpp::lang::JClass* getClazz();

                virtual void set(jfloat value);

                virtual jfloat get();

                virtual jint compareTo(JObject* o);

                virtual jbool equals(JObject* other);

                virtual jint hashCode();

                virtual JString* toString();

                virtual ~JPrimitiveFloat();
        };
    }
}

#endif
