#ifndef JCPP_LANG_ANNOTATION_JANNOTATION_H
#define JCPP_LANG_ANNOTATION_JANNOTATION_H

#include "jcpp/native/api/NativeInclude.h"

namespace jcpp{
    namespace lang{
        class JClass;

        namespace annotation{
	        class JCPP_EXPORT JAnnotation{
	            public:
	                static jcpp::lang::JClass* getClazz();
	                
	                virtual jcpp::lang::JClass* annotationType();

	                virtual ~JAnnotation();
	        };
	    }
    }
}

#endif
