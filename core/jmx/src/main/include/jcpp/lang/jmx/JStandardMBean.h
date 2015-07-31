/*
 * JStandardMBean.h
 *
 *  Created on: Jul 30, 2015
 *      Author: mmaarouf
 */

#ifndef JSTANDARDMBEAN_H_
#define JSTANDARDMBEAN_H_


#include "jcpp/lang/jmx/JDynamicMBean.h"
#include "jcpp/lang/jmx/JMBeanRegistration.h"
#include "jcpp/lang/JObject.h"


namespace jcpp{
	namespace lang{
		namespace jmx{
			class JObjectName;
			class JMBeanInfo;
			class JAttribute;
			class JMBeanServer;
			namespace internal{
				class JMBeanSupport;
			}
		}
	}
}

using namespace jcpp::lang::jmx::internal;

namespace jcpp{
	namespace lang{
		namespace jmx{

			class JCPP_EXPORT JStandardMBean: public JObject, public JDynamicMBean, public JMBeanRegistration{
			private:
				/*TODO volatile*/ JMBeanSupport* mbean;

				void construct(JObject* implementation, JClass* mbeanInterface, jbool nullImplementationAllowed);

			public:
				JStandardMBean(JObject* implementation, JClass* mbeanInterface);

				virtual void postRegister(jbool registrationDone);

				virtual JObjectName* preRegister(JMBeanServer* server, JObjectName* name);

				virtual JObject* invoke(JString* actionName, JPrimitiveObjectArray* params, JPrimitiveObjectArray* signature);

				virtual JMBeanInfo* getMBeanInfo();

				virtual JObject* getAttribute(JString* attribute);

				virtual void setAttribute(JAttribute* attribute);


				static jcpp::lang::JClass* getClazz();
				virtual ~JStandardMBean();
			};
		}
	}
}



#endif /* JSTANDARDMBEAN_H_ */
