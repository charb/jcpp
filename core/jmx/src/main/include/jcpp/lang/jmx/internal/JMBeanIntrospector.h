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
			class JMBeanAttributeInfo;
			class JMBeanOperationInfo;
			class JMBeanInfo;
			namespace internal{
				class JPerInterface;
//				class JMBeanAnalyzer::JMBeanVisitor;
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

					class JCPP_EXPORT JMBeanInfoMaker: public JObject{
					private:
						JList* attrs;
						JList* ops;
					protected:
						JMBeanInfoMaker();
						JMBeanInfo* makeMBeanInfo(JClass* mbeanInterface, JString* description);
					public:
						void visitAttribute(JString* attributeName, JObject* getter, JObject* setter);
						void visitOperation(JString* operationName, JObject* operation);

						static JClass* getClazz();
						virtual ~JMBeanInfoMaker();
						friend class JMBeanIntrospector;

					};

					static JPrimitiveObjectArray* findConstructors(JClass* c);

					JMBeanInfo* makeInterfaceMBeanInfo(JClass* mbeanInterface, JMBeanAnalyzer* analyzer);

				protected:
					virtual JHashMap* getPerInterfaceMap() = 0;
					virtual JMBeanAnalyzer* getAnalyzer(JClass* mbeanInterface) = 0;
					virtual JPrimitiveObjectArray* getSignature(JObject* m) = 0;
					virtual void checkMethod(JObject* m) = 0;
					virtual JHashMap* getMBeanInfoMap() = 0;
					virtual JObject* mFrom(JObject* m) = 0;
					virtual JString* getName(JObject* m) = 0;
					virtual JClass* getGenericReturnType(JObject* m) = 0;
					virtual JPrimitiveObjectArray* getGenericParameterTypes(JObject* m) = 0;
					virtual JMBeanAttributeInfo* getMBeanAttributeInfo(JString* attributeName, JObject* getter, JObject* setter) = 0;
					virtual JMBeanOperationInfo* getMBeanOperationInfo(JString* operationName, JObject* operation) = 0;
					virtual JObject* invokeM2(JObject* m, JObject* target, JPrimitiveObjectArray* args, JObject* cookie) = 0;



					JPerInterface* getPerInterface(JClass* mbeanInterface, JMBeanAnalyzer* analyzer);

					jbool consistent(JObject* getter, JObject* setter);

					JMBeanInfo* getMBeanInfo(JObject* resource, JPerInterface* perInterface);

					JMBeanInfo* getClassMBeanInfo(JClass* resourceClass, JPerInterface* perInterface);

					JObject* invokeM(JObject* m, JObject* target, JPrimitiveObjectArray* args, JObject* cookie);

					void invokeSetter(JString* name, JObject* setter, JObject* target, JObject* arg, JObject* cookie);

				public:
					static JClass* getClazz();
					virtual ~JMBeanIntrospector();
				};
			}
		}
	}
}


#endif /* JMBEANINTROSPECTOR_H_ */
