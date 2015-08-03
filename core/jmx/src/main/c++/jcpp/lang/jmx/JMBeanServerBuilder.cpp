#include "jcpp/lang/jmx/JMBeanServerBuilder.h"
#include "jcpp/lang/jmx/internal/JmxMBeanServer.h"

namespace jcpp{
	namespace lang{
		namespace jmx{

			JMBeanServerBuilder::JMBeanServerBuilder() : JObject(JMBeanServerBuilder::getClazz()){
			}

			JMBeanServerDelegate* JMBeanServerBuilder::newMBeanServerDelegate(){
				return JmxMBeanServer::newMBeanServerDelegate();
			}

			JMBeanServer* JMBeanServerBuilder::newMBeanServer(JString* defaultDomain, JMBeanServer* outer, JMBeanServerDelegate* delegate){
				return JmxMBeanServer::newMBeanServer(defaultDomain, outer, delegate);
			}

			JMBeanServerBuilder::~JMBeanServerBuilder(){
			}

		}
	}
}
