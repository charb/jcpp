#include "jcpp/lang/jmx/JMBeanServerBuilder.h"
#include "jcpp/lang/jmx/internal/JmxMBeanServer.h"

namespace jcpp{
	namespace lang{
		namespace jmx{

			JMBeanServerBuilder::JMBeanServerBuilder() : JObject(JMBeanServerBuilder::getClazz()){
			}

			JMBeanServerDelegate* JMBeanServerBuilder::newJMBeanServerDelegate(){
				return null;
			}

			JMBeanServer* JMBeanServerBuilder::newJMBeanServer(JString* defaultDomain, JMBeanServer* outer, JMBeanServerDelegate* delegate){
				return null;
			}

			JMBeanServerBuilder::~JMBeanServerBuilder(){
			}

		}
	}
}
