#ifndef JCPP_LANG_REFLECT_JANNOTATED_TYPE_H
#define JCPP_LANG_REFLECT_JANNOTATED_TYPE_H

#include "jcpp/lang/reflect/JAnnotatedElement.h"

namespace jcpp{
    namespace lang{
    	class JClass;
    	namespace reflect{        	

    		// @Class(canonicalName="java.lang.reflect.AnnotatedType", simpleName="AnnotatedType");
	        class JCPP_EXPORT JAnnotatedType : public JAnnotatedElement{
	            public:
	                static jcpp::lang::JClass* getClazz();

	                virtual jcpp::lang::JClass* getType()=0;
	                
	                virtual ~JAnnotatedType();
	        };
	    }
    }
}

#endif
