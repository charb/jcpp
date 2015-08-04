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

			// @Class(canonicalName="com.sun.jmx.mbeanserver.Introspector", simpleName="Introspector");
				class JCPP_EXPORT JIntrospector: public JObject{
				private:
					static JClass* findMBeanInterface(JClass* aClass, JString* aName);

					static JClass* implementsMBean(JClass* c, JString* clName);

				protected:
					static JException* throwException(JClass* notCompliant, JThrowable* cause);
				public:
					static void checkCompliance(JClass* mbeanClass);

					static JDynamicMBean* makeDynamicMBean(JObject* mbean);

					static JClass* getStandardMBeanInterface(JClass* baseClass);

					static jcpp::lang::JClass* getClazz();
					virtual ~JIntrospector();

					friend class JMBeanAnalyzer;
					friend class JMBeanIntrospector;
				};
			}
		}
	}
}



#endif /* JINTROSPECTOR_H_ */
