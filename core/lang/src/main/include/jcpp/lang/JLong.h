#ifndef JCPP_LANG_JLONG_H
#define JCPP_LANG_JLONG_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JNumber.h"
#include "jcpp/lang/JPrimitiveLong.h"
#include "jcpp/lang/JComparable.h"

namespace jcpp{
    namespace lang{

    	// @Class(canonicalName="java.lang.Long", simpleName="Long");
        class JCPP_EXPORT JLong : public JNumber, public JComparable{
        	private:
        		static const jlong serialVersionUID = 4290774380558885855LL;

            protected:
                JPrimitiveLong* value;
                void setPrimitiveLong(JPrimitiveLong* value);
                JPrimitiveLong* getPrimitiveLong();

            public:
                JLong();

                JLong(jlong value);

                static jcpp::lang::JClass* getClazz();

                static jlong MIN_VALUE;

                static jlong MAX_VALUE;

                static jint SIZE;

                static jint BYTES;

                static jcpp::lang::JClass* TYPE;

                static jint hashCode(jlong l);

                static jint compare(jlong x,jlong y);

                static JLong* valueOf(JString* s);

                static JString* toString(jlong l);

                virtual void set(jlong value);

                virtual jlong get();

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

                virtual ~JLong();
        };
    }
}

#endif
