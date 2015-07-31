/*
 * JMBeanServerFactory.h
 *
 *  Created on: Jul 14, 2015
 *      Author: mmaarouf
 */

#ifndef JMBEANSERVERFACTORY_H_
#define JMBEANSERVERFACTORY_H_

#include "jcpp/util/JArrayList.h"
#include "jcpp/lang/jmx/JMBeanServerBuilder.h"
#include "jcpp/lang/jmx/JMBeanServer.h"




namespace jcpp{
	namespace lang{
		namespace jmx{

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

				static JMBeanServer* newJMBeanServer();

				static jcpp::lang::JClass* getClazz();

				virtual ~JMBeanServerFactory();
			};
		}
	}
}


#endif /* JMBEANSERVERFACTORY_H_ */
