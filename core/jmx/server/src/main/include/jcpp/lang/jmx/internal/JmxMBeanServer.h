/*
 * JmxMBeanServer.h
 *
 *  Created on: Jul 15, 2015
 *      Author: mmaarouf
 */

#ifndef JMXMBEANSERVER_H_
#define JMXMBEANSERVER_H_

#include "jcpp/lang/jmx/JMBeanServer.h"
#include "jcpp/lang/JObject.h"



namespace jcpp{
	namespace lang{
		class JPrimitiveObjectArray;
		class JString;

		namespace jmx{
			class JObjectName;
			class JAttribute;
			class JObjectInstance;

			namespace internal{
				class JMBeanServerInterceptor;
			}
		}
	}
}

namespace jcpp{
	namespace lang{
		namespace jmx{
			namespace internal{


			// @Class(canonicalName="jcpp.jmx.mbeanserver.JmxMBeanServer", simpleName="JmxMBeanServer");
				class JCPP_EXPORT JmxMBeanServer: public JObject , public JMBeanServer{
				private:
					/*TODO transient*/ JMBeanServerInterceptor* mbsInterceptor;

					JObjectName* cloneObjectName(JObjectName* name);

					JAttribute* cloneAttribute(JAttribute* attribute);

					void init(JString* domain, JMBeanServer* outer, jbool fairLock);
				public:
					static const jbool DEFAULT_FAIR_LOCK_POLICY = true;


					static JMBeanServer* newMBeanServer(JString* defaultDomain, JMBeanServer* outer);


					JmxMBeanServer(JString* domain, JMBeanServer* outer);

					JmxMBeanServer(JString* domain, JMBeanServer* outer, jbool fairLock);

					virtual JObjectInstance* registerMBean(JObject* object, JString* name);

					virtual JObject* invoke(JString* name, JString* operationName, JPrimitiveObjectArray* params, JPrimitiveObjectArray* signature);

					virtual JObject* getAttribute(JString* name, JString* attribute);

					virtual void setAttribute(JString* name, JAttribute* attribute);


					static jcpp::lang::JClass* getClazz();
					virtual ~JmxMBeanServer();


				};
			}
		}
	}
}

#endif /* JMXMBEANSERVER_H_ */
