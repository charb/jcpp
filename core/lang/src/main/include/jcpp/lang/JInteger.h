#ifndef JCPP_LANG_JINTEGER_H
#define JCPP_LANG_JINTEGER_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JNumber.h"
#include "jcpp/lang/JPrimitiveInt.h"
#include "jcpp/lang/JComparable.h"

namespace jcpp{
    namespace lang{

    	// @Class(canonicalName="java.lang.Integer", simpleName="Integer");
        class JCPP_EXPORT JInteger : public JNumber, public JComparable{
        	private:
        		static const jlong serialVersionUID = 1360826667806852920LL;
    			static JString* toUnsignedString(jint i, jint shift);

            protected:
                JPrimitiveInt* value;
                void setPrimitiveInt(JPrimitiveInt* value);
                JPrimitiveInt* getPrimitiveInt();

            public:
                JInteger();

                JInteger(jint value);

                static jcpp::lang::JClass* getClazz();

                static jint hashCode(jint i);

                static jint compare(jint x,jint y);

                static JInteger* valueOf(JString* s);

                static JString* toString(jint i);

                static jint MIN_VALUE;

                static jint MAX_VALUE;

                static jint SIZE;

                static jint BYTES;

                static jcpp::lang::JClass* TYPE;

                static JString* toHexString(jint i);

                static JString* toOctalString(jint i);

                static JString* toBinaryString(jint i);

                virtual void set(jint value);

                virtual jint get();

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

                virtual ~JInteger();
        };
    }
}

#endif
