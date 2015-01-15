#ifndef JCPP_LANG_REFLECT_JANNOTATED_ELEMENT_H
#define JCPP_LANG_REFLECT_JANNOTATED_ELEMENT_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/annotation/JAnnotation.h"

using namespace jcpp::lang;
using namespace jcpp::lang::annotation;

namespace jcpp{
	namespace util{
		class JList;
	}
    namespace lang{
    	class JClass;
    	namespace reflect{        	

    		// @Class(canonicalName="java.lang.reflect.AnnotatedElement", simpleName="AnnotatedElement");
	        class JCPP_EXPORT JAnnotatedElement : public JInterface{
	            public:
	                static jcpp::lang::JClass* getClazz();
	                
	                virtual JAnnotation* getAnnotation(jcpp::lang::JClass* annotationClass)=0;

	                virtual jcpp::util::JList* getAnnotations()=0;

	                virtual ~JAnnotatedElement();
	        };
	    }
    }
}

#endif
