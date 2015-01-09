#ifndef JCPP_LANG_JPRIMITIVEDOUBLE_H
#define JCPP_LANG_JPRIMITIVEDOUBLE_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JComparable.h"
#include "jcpp/io/JSerializable.h"
#include "jcpp/lang/JString.h"

using namespace jcpp::io;

namespace jcpp{
    namespace lang{
        class JCPP_EXPORT JPrimitiveDouble : public JObject, public JComparable, public JSerializable{
            protected:
                jdouble value;

            public:
                JPrimitiveDouble();

                JPrimitiveDouble(jdouble value);

                static jcpp::lang::JClass* getClazz();

                virtual void set(jdouble value);

                virtual jdouble get();

                virtual jint compareTo(JObject* o);

                virtual jbool equals(JObject* other);

                virtual jint hashCode();

                virtual JString* toString();

                virtual ~JPrimitiveDouble();
        };
    }
}

#endif
