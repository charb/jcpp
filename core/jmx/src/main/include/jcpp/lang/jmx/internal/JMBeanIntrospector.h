/*
 * JMBeanIntrospector.h
 *
 *  Created on: Jul 30, 2015
 *      Author: mmaarouf
 */

#ifndef JMBEANINTROSPECTOR_H_
#define JMBEANINTROSPECTOR_H_

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/jmx/internal/JMBeanAnalyzer.h"

namespace jcpp{
	namespace util{
		class JHashMap;
		class JList;
	}
	namespace lang{
		class JPrimitiveObjectArray;
		namespace jmx{
			namespace internal{
				class JPerInterface;
			}
		}
	}
}


using namespace jcpp::util;



namespace jcpp{
	namespace lang{
		namespace jmx{
			namespace internal{

				class JCPP_EXPORT JMBeanIntrospector: public JObject{
				private:

					static JPrimitiveObjectArray* findConstructors(JClass* c);

				protected:
					JMBeanIntrospector();

					JMBeanIntrospector(JClass* clazz);

					virtual JHashMap* getPerInterfaceMap() = 0;
					virtual JMBeanAnalyzer* getAnalyzer(JClass* mbeanInterface) = 0;
					virtual JPrimitiveObjectArray* getSignature(JObject* m) = 0;
					virtual void checkMethod(JObject* m) = 0;
					virtual JObject* mFrom(JObject* m) = 0;
					virtual JString* getName(JObject* m) = 0;
					virtual JClass* getGenericReturnType(JObject* m) = 0;
					virtual JPrimitiveObjectArray* getGenericParameterTypes(JObject* m) = 0;
					virtual JObject* invokeM2(JObject* m, JObject* target, JPrimitiveObjectArray* args, JObject* cookie) = 0;



					JPerInterface* getPerInterface(JClass* mbeanInterface);

					jbool consistent(JObject* getter, JObject* setter);

					JObject* invokeM(JObject* m, JObject* target, JPrimitiveObjectArray* args, JObject* cookie);

					void invokeSetter(JString* name, JObject* setter, JObject* target, JObject* arg, JObject* cookie);

				public:
					static JClass* getClazz();
					virtual ~JMBeanIntrospector();

					friend class JMBeanAnalyzer;
					friend class JMBeanSupport;
					friend class JPerInterface;
				};
			}
		}
	}
}


#endif /* JMBEANINTROSPECTOR_H_ */
