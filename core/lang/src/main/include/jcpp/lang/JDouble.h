#ifndef JCPP_LANG_JDOUBLE_H
#define JCPP_LANG_JDOUBLE_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JNumber.h"
#include "jcpp/lang/JPrimitiveDouble.h"
#include "jcpp/lang/JComparable.h"

namespace jcpp{
    namespace lang{
    	class JDoubleClass;

        class JCPP_EXPORT JDouble : public JNumber, public JComparable{
            protected:
                JPrimitiveDouble* value;
                void setPrimitiveDouble(JPrimitiveDouble* value);
                JPrimitiveDouble* getPrimitiveDouble();
                friend class JDoubleClass;

            public:
                JDouble();
 
                JDouble(jdouble value);
 
                static jcpp::lang::JClass* getClazz();
 
                static jdouble MIN_VALUE;
 
                static jdouble MAX_VALUE;
 
                static jint SIZE;
 
                static jint BYTES;
 
                static jcpp::lang::JClass* TYPE;
 
                static jint hashCode(jdouble);
 
                static jint compare(jdouble d1,jdouble d2);

                static JDouble* valueOf(JString* s);

                static JString* toString(jdouble d);

                static jdouble parseDouble(JString* s);                
 
                virtual void set(jdouble value);

                virtual jdouble get();

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

                virtual ~JDouble();
        };
    }
}

#endif
