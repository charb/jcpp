#ifndef JCPP_RMI_SERVER_CONNECTION_JCONNECTIONCONFIGURATION_H
#define JCPP_RMI_SERVER_CONNECTION_JCONNECTIONCONFIGURATION_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JLong.h"
#include "jcpp/lang/JInteger.h"
#include "jcpp/io/JSerializable.h"
#include "jcpp/rmi/server/transport/JTransportConfiguration.h"

using namespace jcpp::io;
using namespace jcpp::rmi::server::gateway;
using namespace jcpp::rmi::server::transport;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace connection{
            // @Class(canonicalName="jcpp.rmi.server.connection.ConnectionConfiguration", simpleName="ConnectionConfiguration");
                class JCPP_EXPORT JConnectionConfiguration : public JObject, public JSerializable{
                	private:
                		static const jlong serialVersionUID = -7733929591819747912LL;

                    protected:
                        JTransportConfiguration* transportConfiguration;
                        JLong* gcTimeout;
                        JLong* gcClientTimeout;
                        JInteger* gcClientExceptionThreshold;
                        JInteger* executorCorePoolSize;

                    public:
                        static const jlong GC_TIMEOUT       = 20 * 60000;
                        static const jlong GCCLIENT_TIMEOUT = 2 * 60000;
                        static const jint GCCLIENT_EXCEPTION_THRESHOLD  = 10;
                        static const jint EXECUTOR_CORE_POOL_SIZE       = 2;

                        JConnectionConfiguration();

                        JConnectionConfiguration(JTransportConfiguration* transportConfiguration,JLong* gcTimeout,JLong* gcClientTimeout,JInteger* gcClientExceptionThreshold,JInteger* executorCorePoolSize);

                        static JClass* getClazz();

                        virtual JTransportConfiguration* getTransportConfiguration();

                        virtual void setTransportConfiguration(JTransportConfiguration* tc);

                        virtual JLong* getGcTimeout();

                        virtual void setGcTimeout(JLong* gcTimeout);

                        virtual JLong* getGcClientTimeout();

                        virtual void setGcClientTimeout(JLong* gcTimeout);

                        virtual JInteger* getGcClientExceptionThreshold();

                        virtual void setGcClientExceptionThreshold(JInteger* t);

                        virtual JInteger* getExecutorCorePoolSize();

                        virtual void setExecutorCorePoolSize(JInteger* s);

                        virtual ~JConnectionConfiguration();
                };
            }
        }
    }
}

#endif
