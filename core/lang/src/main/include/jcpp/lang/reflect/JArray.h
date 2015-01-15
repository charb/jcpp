#ifndef JCPP_LANG_REFLECT_JARRAY_H
#define JCPP_LANG_REFLECT_JARRAY_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace lang{
    	namespace reflect{

    		// @Class(canonicalName="java.lang.reflect.Array", simpleName="Array");
	        class JCPP_EXPORT JArray : public JObject{
	            public:
	                static jcpp::lang::JClass* getClazz();
	                
					static JObject* newInstance(jcpp::lang::JClass* componentType, jint length);

					static jint getLength(JObject* array);

                    static JObject* get(JObject* array, jint index);

    				static jbool getBoolean(JObject* array, jint index);

					static jbyte getByte(JObject* array, jint index);

    				static jchar getChar(JObject* array, jint index);

					static jshort getShort(JObject* array, jint index);

    				static jint getInt(JObject* array, jint index);
    		
    				static jlong getLong(JObject* array, jint index);

    				static jfloat getFloat(JObject* array, jint index);

    				static jdouble getDouble(JObject* array, jint index);

    				static void set(JObject* array, jint index, JObject* value);

    				static void setBoolean(JObject* array, jint index, jbool z);
    	
    				static void setByte(JObject* array, jint index, jbyte b);

					static void setChar(JObject* array, jint index, jchar c);

    				static void setShort(JObject* array, jint index, jshort s);

    				static void setInt(JObject* array, jint index, jint i);

    				static void setLong(JObject* array, jint index, jlong l);

    				static void setFloat(JObject* array, jint index, jfloat f);
    
    				static void setDouble(JObject* array, jint index, jdouble d);

                    virtual ~JArray();
	        };
	    }
    }
}

#endif
