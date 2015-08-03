/*
 * JmxMBeanServer.h
 *
 *  Created on: Jul 15, 2015
 *      Author: mmaarouf
 */

#ifndef JMXMBEANSERVER_H_
#define JMXMBEANSERVER_H_

#include "jcpp/lang/jmx/JMBeanServer.h"
#include "jcpp/lang/jmx/internal/JMBeanServerInterceptor.h"



namespace jcpp{
	namespace lang{
		class JPrimitiveObjectArray;
		class JString;
		namespace jmx{
			class JObjectName;
			class JAttribute;
			class JObjectInstance;

			namespace internal{
				class JMBeanServerDelegate;
			}
		}
	}
}

namespace jcpp{
	namespace lang{
		namespace jmx{
			namespace internal{

				class JCPP_EXPORT JmxMBeanServer: public JMBeanServerInterceptor, public JMBeanServer{
				private:
					/*TODO transient*/ JMBeanServerInterceptor* mbsInterceptor;

					JObjectName* cloneObjectName(JObjectName* name);

					JAttribute* cloneAttribute(JAttribute* attribute);

					void init(JString* domain, JMBeanServer* outer, JMBeanServerDelegate* delegate, jbool failLock);
				public:
					static const jbool DEFAULT_FAIR_LOCK_POLICY = true;

					static JMBeanServerDelegate* newMBeanServerDelegate();

					static JMBeanServer* newMBeanServer(JString* defaultDomain, JMBeanServer* outer, JMBeanServerDelegate* delegate);


					JmxMBeanServer(JString* domain, JMBeanServer* outer, JMBeanServerDelegate* delegate);

					JmxMBeanServer(JString* domain, JMBeanServer* outer, JMBeanServerDelegate* delegate, jbool fairLock);

					virtual JObjectInstance* registerMBean(JObject* object, JObjectName* name);

					virtual JObject* invoke(JObjectName* name, JString* operationName, JPrimitiveObjectArray* params, JPrimitiveObjectArray* signature);

					virtual JObject* getAttribute(JObjectName* name, JString* attribute);

					virtual void setAttribute(JObjectName* name, JAttribute* attribute);


					static jcpp::lang::JClass* getClazz();
					virtual ~JmxMBeanServer();
				};
			}
		}
	}
}

#endif /* JMXMBEANSERVER_H_ */
