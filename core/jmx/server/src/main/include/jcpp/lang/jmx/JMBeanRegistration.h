/*
 * JMBeanRegistraion.h
 *
 *  Created on: Jul 15, 2015
 *      Author: mmaarouf
 */

#ifndef JMBEANREGISTRAION_H_
#define JMBEANREGISTRAION_H_

#include "jcpp/lang/JInterface.h"

namespace jcpp{
	namespace lang{
		class JClass;
		namespace jmx{
			class JObjectName;
			class JMBeanServer;
		}
	}
}

namespace jcpp{
	namespace lang{
		namespace jmx{

		// @Class(canonicalName="javax.management.MBeanServerRegistration", simpleName="MBeanServerRegistration");
			class JCPP_EXPORT JMBeanRegistration : public JInterface{
			public:

				virtual void postRegister(jbool registrationDone) = 0;

				virtual JObjectName* preRegister(JMBeanServer* server, JObjectName* name) = 0;

				static jcpp::lang::JClass* getClazz();
				virtual ~JMBeanRegistration();

			};
		}
	}
}



#endif /* JMBEANREGISTRAION_H_ */
