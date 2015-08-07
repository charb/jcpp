/*
 * JStandardMBeanSupport.h
 *
 *  Created on: Aug 3, 2015
 *      Author: mmaarouf
 */

#ifndef JSTANDARDMBEANSUPPORT_H_
#define JSTANDARDMBEANSUPPORT_H_

#include "jcpp/lang/jmx/internal/JMBeanSupport.h"


namespace jcpp{
	namespace lang{
		namespace jmx{
			class JMBeanServer;
			class JObjectName;
			namespace internal{
				class JMBeanIntrospector;
			}
		}
	}
}

namespace jcpp{
	namespace lang{
		namespace jmx{
			namespace internal{

			// @Class(canonicalName="jcpp.jmx.mbeanserver.StandardMBeanSupport", simpleName="StandardMBeanSupport");
				class JCPP_EXPORT JStandardMBeanSupport: public JMBeanSupport{
				protected:
					virtual JMBeanIntrospector* getMBeanIntrospector();

					JObject* getCookie();
				public:
					JStandardMBeanSupport(JObject* resource, JClass* mbeanInterface);

					void registerFailed();

					void jRegister(JMBeanServer* mbs, JObjectName* name);

					void unregister();


					static JClass* getClazz();
					virtual ~JStandardMBeanSupport();
				};
			}
		}
	}
}


#endif /* JSTANDARDMBEANSUPPORT_H_ */
