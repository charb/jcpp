#ifndef JCPP_LANG_JPRIMITIVELONG_H
#define JCPP_LANG_JPRIMITIVELONG_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JComparable.h"
#include "jcpp/io/JSerializable.h"
#include "jcpp/lang/JString.h"

using namespace jcpp::io;

namespace jcpp{
    namespace lang{
        class JCPP_EXPORT JPrimitiveLong : public JObject, public JComparable, public JSerializable{
            protected:
                jlong value;

            public:
                JPrimitiveLong();

                JPrimitiveLong(jlong value);

                static jcpp::lang::JClass* getClazz();

                virtual void set(jlong value);
                
                virtual jlong get();

                virtual jint compareTo(JObject* o);

                virtual jbool equals(JObject* other);

                virtual jint hashCode();

                virtual JString* toString();

                virtual ~JPrimitiveLong();
        };
    }
}

#endif
