/*
 * JMBeanSupport.h
 *
 *  Created on: Jul 30, 2015
 *      Author: mmaarouf
 */

#ifndef JMBEANSUPPORT_H_
#define JMBEANSUPPORT_H_

#include "jcpp/lang/jmx/JMBeanRegistration.h"
#include "jcpp/lang/jmx/internal/JDynamicMBean2.h"
#include "jcpp/lang/JObject.h"

namespace jcpp{
	namespace lang{
		class JPrimitiveObjectArray;
		namespace jmx{
			class JMBeanServer;
			class JObjectName;
			class JAttribute;
			namespace internal{
				class JMBeanIntrospector;
				class JPerInterface;
			}
		}
	}
}


namespace jcpp{
	namespace lang{
		namespace jmx{
			namespace internal{

			// @Class(canonicalName="com.sun.jmx.mbeanserver.MBeanSupport", simpleName="MBeanSupport");
				class JCPP_EXPORT JMBeanSupport: public JObject, public JDynamicMBean2, public JMBeanRegistration{
				private:
					JObject* resource;

					JPerInterface* perInterface;

					void init(JObject* resource, JClass* mbeanInterface);

				protected:
					JMBeanSupport(JObject* resource, JClass* mbeanInterface);

					JMBeanSupport(JObject* resource, JClass* mbeanInterface, JClass* clazz);

					virtual JMBeanIntrospector* getMBeanIntrospector() = 0;

					virtual JObject* getCookie() = 0;
				public:
					virtual void jRegister(JMBeanServer* mbs, JObjectName* name) = 0;

					virtual void unregister() = 0;

					JObject* getResource();

					JObjectName* preRegister(JMBeanServer* server, JObjectName* name);

					void preRegister2(JMBeanServer* server, JObjectName* name);

					void postRegister(jbool registrationDone);

					JObject* invoke(JString* operation, JPrimitiveObjectArray* params, JPrimitiveObjectArray* signature);

					JObject* getAttribute(JString* attribute);

					void setAttribute(JAttribute* attribute);


					static jcpp::lang::JClass* getClazz();
					virtual ~JMBeanSupport();
				};
			}
		}
	}
}



#endif /* JMBEANSUPPORT_H_ */
