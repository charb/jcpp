/*
 * JMBeanServerInterceptor.h
 *
 *  Created on: Jul 15, 2015
 *      Author: mmaarouf
 */

#ifndef JMBEANSERVERINTERCEPTOR_H_
#define JMBEANSERVERINTERCEPTOR_H_

#include "jcpp/lang/jmx/JMBeanServerConnection.h"

namespace jcpp{
	namespace lang{
		class JPrimitiveObjectArray;
		class JObject;
		class JClass;
		namespace jmx{
			class JObjectName;
			class JObjectInstance;
		}
	}
}

namespace jcpp{
	namespace lang{
		namespace jmx{
			namespace internal{

			// @Class(canonicalName="com.sun.jmx.interceptor.MBeanServerInterceptor", simpleName="MBeanServerInterceptor");
				class JCPP_EXPORT JMBeanServerInterceptor : public JMBeanServerConnection{
				public:

					virtual JObjectInstance* registerMBean(JObject* object, JObjectName* name) = 0;

					virtual JObject* invoke(JObjectName* name, JString* operationName, JPrimitiveObjectArray* params, JPrimitiveObjectArray* signature) = 0;

					static jcpp::lang::JClass* getClazz();

					virtual ~JMBeanServerInterceptor();

				};
			}
		}
	}
}



#endif /* JMBEANSERVERINTERCEPTOR_H_ */
