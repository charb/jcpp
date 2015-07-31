/*
 * JMBeanServerConnection.h
 *
 *  Created on: Jul 14, 2015
 *      Author: mmaarouf
 */

#ifndef JMBEANSERVERCONNECTION_H_
#define JMBEANSERVERCONNECTION_H_

#include "jcpp/lang/JInterface.h"


namespace jcpp{
	namespace lang{
		class JPrimitiveObjectArray;
		class JObject;
		class JString;
		class JClass;
		namespace jmx{
			class JObjectName;
			class JAttribute;
		}
	}
}


namespace jcpp{
	namespace lang{
		namespace jmx{

			class JCPP_EXPORT JMBeanServerConnection : public JInterface{
			public:

				static jcpp::lang::JClass* getClazz();

				virtual JObject* invoke(JObjectName *name, JString *operationName, JPrimitiveObjectArray *params, JPrimitiveObjectArray *signature) = 0;

				virtual JObject* getAttribute(JObjectName *name, JString *attribute) = 0;

				virtual void setAttribute(JObjectName *name, JAttribute *attribute) = 0;

				virtual ~JMBeanServerConnection();

			};
		}
	}
}



#endif /* JMBEANSERVERCONNECTION_H_ */
