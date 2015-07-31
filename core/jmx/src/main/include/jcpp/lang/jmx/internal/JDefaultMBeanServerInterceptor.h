/*
 * JDefaultMBeanServerInterceptor.h
 *
 *  Created on: Jul 31, 2015
 *      Author: mmaarouf
 */

#ifndef JDEFAULTMBEANSERVERINTERCEPTOR_H_
#define JDEFAULTMBEANSERVERINTERCEPTOR_H_

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/jmx/internal/JMBeanServerInterceptor.h"


namespace jcpp{
	namespace lang{
		class JPrimitiveObjectArray;
		namespace jmx{
			class JMBeanServer;
			class JObjectName;
			class JObjectInstance;
			class JDynamicMBean;
			class JMBeanRegistration;
			class JAttribute;
			namespace internal{
				class JMBeanServerDelegate;
				class JRepository;
			}
		}
	}
}

namespace jcpp{
	namespace lang{
		namespace jmx{
			namespace internal{

				class JCPP_EXPORT JDefaultMBeanInterceptor: public JObject, public JMBeanServerInterceptor{
				private:
					/*TODO Transient*/ JMBeanServer* server;

					JString* domain;


					static JString* getNewMBeanClassName(JObject* mbeanToRegister);

					static void postRegisterInvoke(JMBeanRegistration* moi, jbool registrationDone, jbool registrationFailed);

					static JObjectName* preRegisterInvoke(JMBeanRegistration* moi, JObjectName* name, JMBeanServer* mbs);

					JObjectInstance* registerObject(JString* classname, JDynamicMBean* mbean, JObjectName* name);

					JObjectInstance* registerDynamicMBean(JString* classname, JDynamicMBean* mbean, JObjectName* name);

					JObjectName* nonDefaultDomain(JObjectName* name);

					void internal_addObject(JDynamicMBean* object, JObjectName* logicalName);

				protected:
					JDynamicMBean* getMBean(JObjectName* name);
				public:
					JDefaultMBeanInterceptor(JMBeanServer* outer, JMBeanServerDelegate* delegate, JRepository* repository);

					JObjectInstance* registerMBean(JObject* object, JObjectName* name);

					JObject* invoke(JObjectName* name, JString* operationName, JPrimitiveObjectArray* params, JPrimitiveObjectArray* signature);

					JObject* getAttribute(JObjectName* name, JString* attribute);

					void setAttribute(JObjectName* name, JAttribute* attribute);

					static JClass* getClazz();
					virtual ~JDefaultMBeanInterceptor();
				};
			}
		}
	}
}



#endif /* JDEFAULTMBEANSERVERINTERCEPTOR_H_ */
