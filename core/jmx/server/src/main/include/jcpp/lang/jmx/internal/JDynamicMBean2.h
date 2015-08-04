/*
 * JDynamicMBean2.h
 *
 *  Created on: Jul 30, 2015
 *      Author: mmaarouf
 */

#ifndef JDYNAMICMBEAN2_H_
#define JDYNAMICMBEAN2_H_

#include "jcpp/lang/jmx/JDynamicMBean.h"

namespace jcpp{
	namespace lang{
		namespace jmx{
			class JMBeanServer;
			class JObjectName;
		}
	}
}


namespace jcpp{
	namespace lang{
		namespace jmx{
			namespace internal{

			// @Class(canonicalName="com.sun.jmx.mbeanserver.DynamicMBean2", simpleName="DynamicMBean2");
				class JCPP_EXPORT JDynamicMBean2: public JDynamicMBean{
				public:
					virtual JObject* getResource() = 0;

					virtual void registerFailed() = 0;

					virtual void preRegister2(JMBeanServer* mbs, JObjectName* name) = 0;

					static jcpp::lang::JClass* getClazz();

					virtual ~JDynamicMBean2();
				};
			}
		}
	}
}



#endif /* JDYNAMICMBEAN2_H_ */
