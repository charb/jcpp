#ifndef JCPP_LANG_JFLOAT_H
#define JCPP_LANG_JFLOAT_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JNumber.h"
#include "jcpp/lang/JPrimitiveFloat.h"
#include "jcpp/lang/JComparable.h"

namespace jcpp{
    namespace lang{

    	// @Class(canonicalName="java.lang.Float", simpleName="Float");
        class JCPP_EXPORT JFloat : public JNumber, public JComparable{
        	private:
        		static const jlong serialVersionUID = -2671257302660747028LL;

            protected:
                JPrimitiveFloat* value;
                void setPrimitiveFloat(JPrimitiveFloat* value);
                JPrimitiveFloat* getPrimitiveFloat();

            public:
                JFloat();

                JFloat(jfloat value);

                static jcpp::lang::JClass* getClazz();

                static jfloat MIN_VALUE;

                static jfloat MAX_VALUE;

                static jint SIZE;

                static jint BYTES;

                static jcpp::lang::JClass* TYPE;

                static jint hashCode(jfloat f);

                static jint compare(jfloat f1,jfloat f2);

                static JFloat* valueOf(JString* s);

                static JString* toString(jfloat f);

                virtual void set(jfloat value);

                virtual jfloat get();

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

                virtual ~JFloat();
        };
    }
}

#endif
