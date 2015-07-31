/*
 * JPerInterface.h
 *
 *  Created on: Jul 30, 2015
 *      Author: mmaarouf
 */

#ifndef JPERINTERFACE_H_
#define JPERINTERFACE_H_

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/jmx/internal/JMBeanAnalyzer.h"


namespace jcpp{
	namespace util{
		class JMap;
	}
	namespace lang{
		class JPrimitiveObjectArray;
		namespace jmx{
			class JMBeanInfo;
			namespace internal{
				class JMBeanIntrospector;
			}
		}
	}
}

using namespace jcpp::util;

namespace jcpp{
	namespace lang{
		namespace jmx{
			namespace internal{

				class JCPP_EXPORT JPerInterface: public JObject{
				private:

					class JCPP_EXPORT InitMaps: public JObject, public JMBeanAnalyzer::JMBeanVisitor{
					protected:
						InitMaps();
					public:
						void visitAttribute(JString* attributeName, JObject* getter, JObject* setter);
						void visitOperation(JString* operationName, JObject* operation);

						static JClass* getClazz();
						virtual ~InitMaps();
						friend class JPerInterface;
					};

					class JCPP_EXPORT MethodAndSig: public JObject{
					protected:
						MethodAndSig();
						JObject* method;
						JPrimitiveObjectArray* signature;
					public:
						static JClass* getClazz();
						virtual ~MethodAndSig();
						friend class JPerInterface;
					};

					JClass* mbeanInterface;
					JMBeanIntrospector* introspector;
					JMBeanInfo* mbeanInfo;
					JMap* getters;
					JMap* setters;
					JMap* ops;

					JObject* noSuchMethod(JString* msg, JObject* resource, JString* operation, JPrimitiveObjectArray* params, JPrimitiveObjectArray* signature, JObject* cookie);

					JString* sigString(JPrimitiveObjectArray* signature);


				protected:
					JPerInterface(JClass* mbeanInterface, JMBeanIntrospector* introspector, JMBeanAnalyzer* analyzer, JMBeanInfo* mbeanInfo);

					JClass* getMBeanInterface();

					JMBeanInfo* getMBeanInfo();

					JObject* invoke(JObject* resource, JString* operation, JPrimitiveObjectArray* params, JPrimitiveObjectArray* signature, JObject* cookie);

					JObject* getAttribute(JObject* resource, JString* attribute, JObject* cookie);

					void setAttribute(JObject* resource, JString* attribute, JObject* value, JObject* cookie);

				public:


					static JClass* getClazz();
					virtual ~JPerInterface();
				};
			}
		}
	}
}


#endif /* JPERINTERFACE_H_ */
