/*
 * JMBeanServerProxy.h
 *
 *  Created on: Aug 6, 2015
 *      Author: mmaarouf
 */

#ifndef JMBEANSERVERPROXY_H_
#define JMBEANSERVERPROXY_H_


#include "jcpp/lang/reflect/JProxy.h"
#include "jcpp/lang/jmx/JMBeanServer.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
	namespace lang{
		namespace jmx{


			// @Class(canonicalName="jcpp.lang.jmx.MBeanServerProxy", simpleName="MBeanServerProxy");
			class JCPP_EXPORT JMBeanServerProxy: public JProxy, public JMBeanServer{
			public:

				JMBeanServerProxy();

				JObjectInstance* registerMBean(JObject* object, JObjectName* name);

				JObject* invoke(JObjectName* name, JString* operationName, JPrimitiveObjectArray* params, JPrimitiveObjectArray* signature);

				JObject* getAttribute(JObjectName* name, JString* attribute);

				void setAttribute(JObjectName* name, JAttribute* attribute);

				static JClass* getClazz();
				virtual ~JMBeanServerProxy();
			};
		}
	}
}


#endif /* JMBEANSERVERPROXY_H_ */
