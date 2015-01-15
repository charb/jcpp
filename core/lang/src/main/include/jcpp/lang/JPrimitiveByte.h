#ifndef JCPP_LANG_JPRIMITIVEBYTE_H
#define JCPP_LANG_JPRIMITIVEBYTE_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JComparable.h"
#include "jcpp/io/JSerializable.h"

using namespace jcpp::io;

namespace jcpp{
    namespace lang{

    	// @Primitive()
    	// @Class(canonicalName="byte", simpleName="byte");
        class JCPP_EXPORT JPrimitiveByte : public JObject, public JComparable, public JSerializable{
            protected:
                jbyte value;

            public:
                JPrimitiveByte();

                JPrimitiveByte(jbyte value);

                static jcpp::lang::JClass* getClazz();

                virtual void set(jbyte value);

                virtual jbyte get();

                virtual jint compareTo(JObject* o);

                virtual jbool equals(JObject* other);

                virtual jint hashCode();

                virtual JString* toString();

                virtual ~JPrimitiveByte();
        };
    }
}
#endif
