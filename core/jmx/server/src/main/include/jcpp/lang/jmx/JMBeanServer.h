/*
 * JMBeanServer.h
 *
 *  Created on: Jul 14, 2015
 *      Author: mmaarouf
 */

#ifndef JMBEANSERVER_H_
#define JMBEANSERVER_H_

#include "jcpp/lang/jmx/JMBeanServerConnection.h"
#include "jcpp/lang/JObject.h"

namespace jcpp{
	namespace lang{
		class JPrimitiveObjectArray;
		class JClass;
		class JString;
		namespace jmx{
			class JObjectInstance;
			class JObjectName;
			class JAttribute;
		}
	}
}

namespace jcpp{
	namespace lang{
		namespace jmx{

		// @Class(canonicalName="javax.management.MBeanServer", simpleName="MBeanServer");
			class JCPP_EXPORT JMBeanServer : public JMBeanServerConnection{
			public:

				JMBeanServer();

				virtual JObjectInstance* registerMBean(JObject *jobject, JObjectName *name) = 0;

				virtual JObject* invoke(JObjectName *name, JString *operationName, JPrimitiveObjectArray *params, JPrimitiveObjectArray *signature) = 0;

				virtual JObject* getAttribute(JObjectName *name, JString *attribute) = 0;

				virtual void setAttribute(JObjectName *name, JAttribute *attribute) = 0;


				static jcpp::lang::JClass* getClazz();
				virtual ~JMBeanServer();
			};
		}
	}
}

#endif /* JMBEANSERVER_H_ */
