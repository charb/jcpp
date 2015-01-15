#ifndef JCPP_LANG_JPRIMITIVESHORT_H
#define JCPP_LANG_JPRIMITIVESHORT_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JComparable.h"
#include "jcpp/io/JSerializable.h"
#include "jcpp/lang/JString.h"

using namespace jcpp::io;

namespace jcpp{
    namespace lang{

    	// @Primitive()
    	// @Class(canonicalName="short", simpleName="short");
        class JCPP_EXPORT JPrimitiveShort : public JObject, public JComparable, public JSerializable{
            protected:
                jshort value;

            public:
                JPrimitiveShort();

                JPrimitiveShort(jshort value);

                static jcpp::lang::JClass* getClazz();

                virtual void set(jshort value);

                virtual jshort get();

                virtual jint compareTo(JObject* o);

                virtual jbool equals(JObject* other);

                virtual jint hashCode();

                virtual JString* toString();

                virtual ~JPrimitiveShort();
        };
    }
}

#endif
