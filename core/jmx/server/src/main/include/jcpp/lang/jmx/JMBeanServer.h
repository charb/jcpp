/*
 * JMBeanServer.h
 *
 *  Created on: Jul 14, 2015
 *      Author: mmaarouf
 */

#ifndef JMBEANSERVER_H_
#define JMBEANSERVER_H_


#include "jcpp/lang/JInterface.h"

namespace jcpp{
	namespace lang{
		class JPrimitiveObjectArray;
		class JClass;
		class JString;
		class JObject;
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

		// @Class(canonicalName="jcpp.management.MBeanServer", simpleName="MBeanServer");
			class JCPP_EXPORT JMBeanServer: public JInterface{
			public:

				JMBeanServer();

				virtual JObjectInstance* registerMBean(JObject *jobject, JString *name) = 0;

				virtual JObject* invoke(JString *name, JString *operationName, JPrimitiveObjectArray *params, JPrimitiveObjectArray *signature) = 0;

				virtual JObject* getAttribute(JString *name, JString *attribute) = 0;

				virtual void setAttribute(JString *name, JAttribute *attribute) = 0;


				static jcpp::lang::JClass* getClazz();
				virtual ~JMBeanServer();

			};
		}
	}
}

#endif /* JMBEANSERVER_H_ */
