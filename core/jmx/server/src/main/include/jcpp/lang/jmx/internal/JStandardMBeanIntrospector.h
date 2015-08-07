/*
 * JStandardMBeanIntrospector.h
 *
 *  Created on: Aug 3, 2015
 *      Author: mmaarouf
 */

#ifndef JSTANDARDMBEANINTROSPECTOR_H_
#define JSTANDARDMBEANINTROSPECTOR_H_

#include "jcpp/lang/jmx/internal/JMBeanIntrospector.h"


namespace jcpp{
	namespace util{
		class JHashMap;
	}
	namespace lang{
		class JPrimitiveObjectArray;
		class JClass;

		namespace jmx{
			namespace internal{
				class JMBeanAnalyzer;
			}
		}
	}
}

using namespace jcpp::util;



namespace jcpp{
	namespace lang{
		namespace jmx{
			namespace internal{

			// @Class(canonicalName="jcpp.jmx.mbeanserver.StandardMBeanIntrospector", simpleName="StandardMBeanIntrospector");
				class JCPP_EXPORT JStandardMBeanIntrospector: public JMBeanIntrospector{
				private:
					static JStandardMBeanIntrospector* instance;
					static JHashMap* perInterfaceMap;
				protected:
					static JStandardMBeanIntrospector* getInstance();

					JStandardMBeanIntrospector();

					JHashMap* getPerInterfaceMap();

					JMBeanAnalyzer* getAnalyzer(JClass* mbeanInterface);

					JPrimitiveObjectArray* getSignature(JObject* m);

					void checkMethod(JObject* m);

					JObject* mFrom(JObject* m);

					JClass* getGenericReturnType(JObject* m);

					JPrimitiveObjectArray* getGenericParameterTypes(JObject* m);

					JString* getName(JObject* m);

					virtual JObject* invokeM2(JObject* m, JObject* target, JPrimitiveObjectArray* args, JObject* cookie);

				public:

					static JClass* getClazz();
					virtual ~JStandardMBeanIntrospector();
					friend class JStandardMBeanSupport;
				};
			}
		}
	}
}


#endif /* JSTANDARDMBEANINTROSPECTOR_H_ */
