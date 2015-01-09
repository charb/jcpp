#include "jcpp/rmi/server/connection/JConnectionConfiguration.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace connection{
                
                JConnectionConfiguration::JConnectionConfiguration():JObject(getClazz()) {
                    this->transportConfiguration=new JTransportConfiguration();
                    this->gcTimeout=new JLong(GC_TIMEOUT);
                    this->gcClientTimeout=new JLong(GCCLIENT_TIMEOUT);
                    this->gcClientExceptionThreshold=new JInteger(GCCLIENT_EXCEPTION_THRESHOLD);
                    this->executorCorePoolSize=new JInteger(EXECUTOR_CORE_POOL_SIZE);
                }

                JConnectionConfiguration::JConnectionConfiguration(JTransportConfiguration* transportConfiguration,JLong* gcTimeout,JLong* gcClientTimeout,JInteger* gcClientExceptionThreshold,JInteger* executorCorePoolSize) : JObject(getClazz()){
                    this->transportConfiguration=transportConfiguration;
                    this->gcTimeout=gcTimeout;
                    this->gcClientTimeout=gcClientTimeout;
                    this->gcClientExceptionThreshold=gcClientExceptionThreshold;
                    this->executorCorePoolSize=executorCorePoolSize;
                }

                JTransportConfiguration* JConnectionConfiguration::getTransportConfiguration(){
                    return transportConfiguration;
                }

                void JConnectionConfiguration::setTransportConfiguration(JTransportConfiguration* tc){
                    this->transportConfiguration=tc;
                }

                JLong* JConnectionConfiguration::getGcTimeout(){
                    return gcTimeout;
                }

                void JConnectionConfiguration::setGcTimeout(JLong* gcTimeout){
                    this->gcTimeout=gcTimeout;
                }

                JLong* JConnectionConfiguration::getGcClientTimeout(){
                    return gcClientTimeout;
                }

                void JConnectionConfiguration::setGcClientTimeout(JLong* gcClientTimeout){
                    this->gcClientTimeout=gcClientTimeout;
                }

                JInteger* JConnectionConfiguration::getGcClientExceptionThreshold(){
                    return gcClientExceptionThreshold;
                }

                void JConnectionConfiguration::setGcClientExceptionThreshold(JInteger* t){
                    this->gcClientExceptionThreshold=t;
                }

                JInteger* JConnectionConfiguration::getExecutorCorePoolSize(){
                    return executorCorePoolSize;
                }

                void JConnectionConfiguration::setExecutorCorePoolSize(JInteger* s){
                    this->executorCorePoolSize=s;
                }

                JConnectionConfiguration::~JConnectionConfiguration(){
                }
            }
        }
    }
}


