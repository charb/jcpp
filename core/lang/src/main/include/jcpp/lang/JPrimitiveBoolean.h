#ifndef JCPP_LANG_JPRIMITIVEBOOLEAN_H
#define JCPP_LANG_JPRIMITIVEBOOLEAN_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JComparable.h"
#include "jcpp/io/JSerializable.h"

using namespace jcpp::io;

namespace jcpp{
    namespace lang{
        class JCPP_EXPORT JPrimitiveBoolean : public JObject, public JComparable, public JSerializable{
            protected:
                jbool value;

            public:
                JPrimitiveBoolean();

                JPrimitiveBoolean(jbool value);

                static jcpp::lang::JClass* getClazz();

                virtual void set(jbool value);

                virtual jbool get();

                virtual jint compareTo(JObject* o);

                virtual jbool equals(JObject* other);

                virtual jint hashCode();

                virtual JString* toString();

                virtual ~JPrimitiveBoolean();
        };
    }
}
#endif
