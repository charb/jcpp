#ifndef JCPP_LANG_JSHORT_H
#define JCPP_LANG_JSHORT_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JNumber.h"
#include "jcpp/lang/JPrimitiveShort.h"
#include "jcpp/lang/JComparable.h"

namespace jcpp{
    namespace lang{
    	class JShortClass;

        class JCPP_EXPORT JShort : public JNumber, public JComparable{
            protected:
                JPrimitiveShort* value;
                void setPrimitiveShort(JPrimitiveShort* value);
                JPrimitiveShort* getPrimitiveShort();
                friend class JShortClass;

            public:
                JShort();

                JShort(jshort value);

                static jcpp::lang::JClass* getClazz();

                static jshort MIN_VALUE;

                static jshort MAX_VALUE;

                static jint SIZE;

                static jint BYTES;

                static jcpp::lang::JClass* TYPE;

                static jint hashCode(jshort);

                static jint compare(jshort x,jshort y);

                virtual void set(jshort value);

                virtual jshort get();

                virtual jbyte byteValue();

                virtual jshort shortValue();

                virtual jint intValue();

                virtual jlong longValue();

                virtual jfloat floatValue();

                virtual jdouble doubleValue();

                virtual jint compareTo(JObject* o);

                virtual jbool equals(JObject* other);

                virtual jint hashCode();

                virtual JString* toString();

                virtual ~JShort();
        };
    }
}

#endif

