/*
 * JMBeanServerFactory.h
 *
 *  Created on: Jul 14, 2015
 *      Author: mmaarouf
 */

#ifndef JMBEANSERVERFACTORY_H_
#define JMBEANSERVERFACTORY_H_

#include "jcpp/lang/JObject.h"

namespace jcpp{
	namespace util{
		class JList;
	}
	namespace lang{
		namespace jmx{
			class JMBeanServer;
			class JMBeanServerBuilder;
		}
	}
}

using namespace jcpp::util;


namespace jcpp{
	namespace lang{
		namespace jmx{

		// @Class(canonicalName="javax.management.MBeanServerFactory", simpleName="MBeanServerFactory");
			class JCPP_EXPORT JMBeanServerFactory : public JObject{
			private:
				static JMBeanServerBuilder* builder;

				static JList* jmBeanServerList;

				static void addJMBeanServer(JMBeanServer* jmbs);

				static JMBeanServerBuilder* getNewJMBeanServerBuilder();

				static void checkJMBeanServerBuilder();

				static JMBeanServerBuilder* newBuilder(JClass* builderClass);

			public:

				static JMBeanServer* createJMBeanServer();

				static JMBeanServer* newMBeanServer();

				static jcpp::lang::JClass* getClazz();

				virtual ~JMBeanServerFactory();
			};
		}
	}
}


#endif /* JMBEANSERVERFACTORY_H_ */
