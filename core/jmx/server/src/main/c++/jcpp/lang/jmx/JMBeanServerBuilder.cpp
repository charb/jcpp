#include "jcpp/lang/jmx/JMBeanServerBuilder.h"
#include "jcpp/lang/jmx/internal/JmxMBeanServer.h"
#include "jcpp/lang/jmx/JMBeanServer.h"

using namespace jcpp::lang::jmx::internal;

namespace jcpp{
	namespace lang{
		namespace jmx{

			JMBeanServerBuilder::JMBeanServerBuilder() : JObject(JMBeanServerBuilder::getClazz()){
			}


			JMBeanServer* JMBeanServerBuilder::newMBeanServer(JString* defaultDomain, JMBeanServer* outer){
				return JmxMBeanServer::newMBeanServer(defaultDomain, outer);
			}

			JMBeanServerBuilder::~JMBeanServerBuilder(){
			}

		}
	}
}
