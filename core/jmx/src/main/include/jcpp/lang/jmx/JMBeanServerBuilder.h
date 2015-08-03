/*
 * JMBeanServerBuilder.h
 *
 *  Created on: Jul 14, 2015
 *      Author: mmaarouf
 */

#ifndef JMBEANSERVERBUILDER_H_
#define JMBEANSERVERBUILDER_H_

#include "jcpp/lang/jmx/JMBeanServer.h"
#include "jcpp/lang/jmx/internal/JMBeanServerDelegate.h"


using namespace jcpp::lang::jmx::internal;

namespace jcpp{
	namespace lang{
		namespace jmx{

			class JCPP_EXPORT JMBeanServerBuilder : public JObject{
			public:

				JMBeanServerBuilder();

				JMBeanServerDelegate* newMBeanServerDelegate();

				JMBeanServer* newMBeanServer(JString* defaultDomain, JMBeanServer* outer, JMBeanServerDelegate* delegate);

				static jcpp::lang::JClass* getClazz();

				virtual ~JMBeanServerBuilder();

			};
		}
	}
}



#endif /* JMBEANSERVERBUILDER_H_ */
