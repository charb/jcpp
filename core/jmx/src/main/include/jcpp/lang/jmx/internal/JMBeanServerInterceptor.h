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
		namespace jmx{
			namespace internal{

				class JCPP_EXPORT JMBeanServerInterceptor : public JMBeanServerConnection{
				public:

					static jcpp::lang::JClass* getClazz();

					virtual ~JMBeanServerInterceptor();

				};
			}
		}
	}
}



#endif /* JMBEANSERVERINTERCEPTOR_H_ */
