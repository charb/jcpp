#ifndef JCPP_LANG_JPRIMITIVECHAR_H
#define JCPP_LANG_JPRIMITIVECHAR_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JComparable.h"
#include "jcpp/io/JSerializable.h"
#include "jcpp/lang/JPrimitiveArray.h"
#include "jcpp/lang/JString.h"

using namespace jcpp::io;

namespace jcpp{
    namespace lang{
        class JCPP_EXPORT JPrimitiveChar : public JObject, public JComparable, public JSerializable{
            protected:
                jchar value;

            public:
                JPrimitiveChar();

                JPrimitiveChar(char value);

                JPrimitiveChar(jchar value);

                static jcpp::lang::JClass* getClazz();

                virtual void set(jchar value);

                virtual jchar get();

                virtual jint compareTo(JObject* o);

                virtual jbool equals(JObject* other);

                virtual jint hashCode();

                virtual JString* toString();

                virtual ~JPrimitiveChar();
        };
    }
}
#endif
