#ifndef JCPP_LANG_JBYTE_H
#define JCPP_LANG_JBYTE_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JNumber.h"
#include "jcpp/lang/JPrimitiveByte.h"
#include "jcpp/lang/JComparable.h"
#include "jcpp/lang/JString.h"

namespace jcpp{
    namespace lang{

    	// @Class(canonicalName="java.lang.Byte", simpleName="Byte");
        class JCPP_EXPORT JByte : public JNumber, public JComparable{
        	private:
        		static const jlong serialVersionUID = -7183698231559129828LL;

            protected:
                JPrimitiveByte* value;
                void setPrimitiveByte(JPrimitiveByte* value);
                JPrimitiveByte* getPrimitiveByte();

            public:
                JByte();

                JByte(jbyte value);

                static jcpp::lang::JClass* getClazz();

                static jint hashCode(jbyte b);

                static jint compare(jbyte x,jbyte y);

                static jbyte MIN_VALUE;

                static jbyte MAX_VALUE;

                static jcpp::lang::JClass* TYPE;

                static jint toUnsignedInt(jbyte x);

                static jlong toUnsignedLong(jbyte x);

                static jint SIZE;

                static jint BYTES;

                virtual void set(jbyte value);

                virtual jbyte get();

                virtual jbyte byteValue();

                virtual jshort shortValue();

                virtual jint intValue();

                virtual jlong longValue();

                virtual jfloat floatValue();

                virtual jdouble doubleValue();

                virtual jint compareTo(JObject * o);

                virtual jint hashCode();

                virtual jbool equals(JObject* other);

                virtual JString* toString();

                virtual ~JByte();
        };
    }
}

#endif
