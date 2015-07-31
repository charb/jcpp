/*
 * JMBeanServerDelegate.cpp
 *
 *  Created on: Jul 15, 2015
 *      Author: mmaarouf
 */

#ifndef JMBEANSERVERDELEGATE_H_
#define JMBEANSERVERDELEGATE_H_

#include "jcpp/lang/JObject.h";
#include "jcpp/lang/jmx/JDynamicMBean.h";
#include "jcpp/lang/jmx/JMBeanRegistration.h";

namespace jcpp{
	namespace lang{

		namespace jmx{
			class JMBeanServer;
			class JObjectName;
			class JAttribute;
		}
	}
}


namespace jcpp{
	namespace lang{
		namespace jmx{
			namespace internal{

				class JCPP_EXPORT JMBeanServerDelegate : public JObject, public JDynamicMBean, public JMBeanRegistration{
				public:

					JMBeanServerDelegate();

					virtual JObject* invoke(JString* actionName, JPrimitiveObjectArray* params, JPrimitiveObjectArray* signature);


					virtual JObject* getAttribute(JString* jattribute);

					virtual void setJAttribute(JAttribute* attribute);

					virtual void postRegister(jbool registrationDone);

					virtual JObjectName* preRegister(JMBeanServer* server, JObjectName* name);

					static jcpp::lang::JClass *getClazz();
					virtual ~JMBeanServerDelegate();
				};
			}
		}
	}
}



#endif /* JMBEANSERVERDELEGATE_CPP_ */
