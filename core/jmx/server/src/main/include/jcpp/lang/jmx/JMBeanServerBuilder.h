/*
 * JMBeanServerBuilder.h
 *
 *  Created on: Jul 14, 2015
 *      Author: mmaarouf
 */

#ifndef JMBEANSERVERBUILDER_H_
#define JMBEANSERVERBUILDER_H_

#include "jcpp/lang/JObject.h"

namespace jcpp{
	namespace lang{
		namespace jmx{
			class JMBeanServer;
		}
	}
}




namespace jcpp{
	namespace lang{
		namespace jmx{

		// @Class(canonicalName="jcpp.management.MBeanServerBuilder", simpleName="MBeanServerBuilder");
			class JCPP_EXPORT JMBeanServerBuilder : public JObject{
			public:

				JMBeanServerBuilder();



				JMBeanServer* newMBeanServer(JString* defaultDomain, JMBeanServer* outer);

				static jcpp::lang::JClass* getClazz();

				virtual ~JMBeanServerBuilder();

			};
		}
	}
}



#endif /* JMBEANSERVERBUILDER_H_ */
