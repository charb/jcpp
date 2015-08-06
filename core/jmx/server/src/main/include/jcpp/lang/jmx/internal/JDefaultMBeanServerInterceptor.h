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
				class JRepository;
			}
		}
	}
}

namespace jcpp{
	namespace lang{
		namespace jmx{
			namespace internal{

			// @Class(canonicalName="com.sun.jmx.interceptor.DefaultMBeanServerInterceptor", simpleName="DefaultMBeanServerInterceptor");
				class JCPP_EXPORT JDefaultMBeanServerInterceptor: public JObject, public JMBeanServerInterceptor{
				private:
					/*TODO Transient*/ JMBeanServer* server;

					/*TODO Transient*/ JRepository* repository;



					static JString* getNewMBeanClassName(JObject* mbeanToRegister);

					static void postRegisterInvoke(JMBeanRegistration* moi, jbool registrationDone, jbool registrationFailed);

					static JObjectName* preRegisterInvoke(JMBeanRegistration* moi, JObjectName* name, JMBeanServer* mbs);

					JObjectInstance* registerObject(JString* classname, JObject* object, JObjectName* name);

					JObjectInstance* registerDynamicMBean(JString* classname, JDynamicMBean* mbean, JObjectName* name);


					void internal_addObject(JDynamicMBean* object, JObjectName* logicalName);

				protected:
					JDynamicMBean* getMBean(JObjectName* name);
				public:
					JDefaultMBeanServerInterceptor(JMBeanServer* outer, JRepository* repository);

					JObjectInstance* registerMBean(JObject* object, JObjectName* name);

					JObject* invoke(JObjectName* name, JString* operationName, JPrimitiveObjectArray* params, JPrimitiveObjectArray* signature);

					JObject* getAttribute(JObjectName* name, JString* attribute);

					void setAttribute(JObjectName* name, JAttribute* attribute);

					static JClass* getClazz();
					virtual ~JDefaultMBeanServerInterceptor();
				};
			}
		}
	}
}



#endif /* JDEFAULTMBEANSERVERINTERCEPTOR_H_ */
