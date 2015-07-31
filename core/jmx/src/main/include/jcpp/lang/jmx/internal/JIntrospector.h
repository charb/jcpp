/*
 * JIntrospector.h
 *
 *  Created on: Jul 29, 2015
 *      Author: mmaarouf
 */

#ifndef JINTROSPECTOR_H_
#define JINTROSPECTOR_H_

#include "jcpp/lang/JObject.h"

namespace jcpp{
	namespace lang{
		namespace reflect{
			class JAnnotatedElement;
		}
	}
}

namespace jcpp{
	namespace lang{
		class JPrimitiveObjectArray;
		class JThrowable;
		class JString;
		class JClass;
		class JException;
	}
}

namespace jcpp{
	namespace lang{
		namespace jmx{
			class JDynamicMBean;
		}
	}
}

using namespace jcpp::lang::reflect;
using namespace jcpp::lang;
using namespace jcpp::lang::jmx;

namespace jcpp{
	namespace lang{
		namespace jmx{
			namespace internal{

				class JCPP_EXPORT JIntrospector: public JObject{
				protected:
					static JException* throwException(JClass* notCompliant, JThrowable* cause);
				public:
					static void checkCompliance(JClass* mbeanClass);

					static JDynamicMBean* makeDynamicMBean(JObject* mbean);

					static JClass* getStandardMBeanInterface(JClass* baseClass);


					static JClass* findMBeanInterface(JClass* aClass, JString* aName);

					static JClass* implementsMBean(JClass* c, JString* clName);



					static jcpp::lang::JClass* getClazz();
					virtual ~JIntrospector();
				};
			}
		}
	}
}



#endif /* JINTROSPECTOR_H_ */
