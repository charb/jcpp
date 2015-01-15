#ifndef JCPP_LANG_JBOOLEAN_H
#define JCPP_LANG_JBOOLEAN_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JPrimitiveBoolean.h"
#include "jcpp/lang/JComparable.h"
#include "jcpp/io/JSerializable.h"
#include "jcpp/lang/JString.h"

using namespace jcpp::io;

#ifdef TRUE
#undef TRUE
#endif

#ifdef FALSE
#undef FALSE
#endif

namespace jcpp{
    namespace lang{

    	// @Class(canonicalName="java.lang.Boolean", simpleName="Boolean");
        class JCPP_EXPORT JBoolean : public JObject,public JComparable, public JSerializable{
        	private:
        		static const jlong serialVersionUID = -3665804199014368530LL;

           protected:
                JPrimitiveBoolean* value;
                void setPrimitiveBoolean(JPrimitiveBoolean* value);
                JPrimitiveBoolean* getPrimitiveBoolean();

            public:
                JBoolean();

                JBoolean(jbool value);

                static jcpp::lang::JClass* getClazz();

                static JBoolean* TRUE;

                static JBoolean* FALSE;

                static JString* TRUE_STRING;

                static JString* FALSE_STRING;        

                static jcpp::lang::JClass* TYPE;

                static jbool parseBoolean(JString* s);

                static JBoolean* valueOf(jbool b);

                static JBoolean* valueOf(JString* s);

                static JString* toString(jbool b);

                static jint hashCode(jbool value);

                static jint compare(jbool v1,jbool v2);

                static jbool getBoolean(JString* name);

                virtual void set(jbool value);

                virtual jbool get();

                virtual jbool booleanValue();

                virtual jint compareTo(JObject* o);

                virtual jbool equals(JObject* other);

                virtual jint hashCode();

                virtual JString* toString();

                virtual ~JBoolean();
        };
    }
}
#endif
