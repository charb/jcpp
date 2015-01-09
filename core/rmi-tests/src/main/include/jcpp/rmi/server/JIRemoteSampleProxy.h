#ifndef JCPP_RMI_SERVER_JIREMOTESAMPLEPROXY_H
#define JCPP_RMI_SERVER_JIREMOTESAMPLEPROXY_H

#include "jcpp/lang/reflect/JProxy.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/rmi/server/JIRemoteSample.h"

using namespace jcpp::lang::reflect;
using namespace jcpp::lang;

namespace jcpp{
    namespace rmi{
        namespace server{

        	// @Class(canonicalName="jcpp.rmi.server.IRemoteSampleProxy", simpleName="IRemoteSampleProxy");
            class JIRemoteSampleProxy : public JProxy, public JIRemoteSample{

            public:
                JIRemoteSampleProxy();

                static JClass* getClazz();

                virtual JSampleObject* getSampleObject();

                virtual JIRemoteSample* getRemoteSample();

                virtual void checkRemoteSample(JIRemoteSample* rs);

                virtual void checkCallback(JIRemoteSample* rs);

                virtual ~JIRemoteSampleProxy();
            };
        }
    }
}


#endif
