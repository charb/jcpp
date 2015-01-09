#ifndef JCPP_RMI_SERVER_JREMOTESAMPLE_H
#define JCPP_RMI_SERVER_JREMOTESAMPLE_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/rmi/server/JIRemoteSample.h"

namespace jcpp{
    namespace rmi{
        namespace server{

        	// @Class(canonicalName="jcpp.rmi.server.RemoteSample", simpleName="RemoteSample");
            class JRemoteSample : public JObject, public JIRemoteSample{
            public:
                JRemoteSample();
                
                static JClass* getClazz();
                
                virtual JSampleObject* getSampleObject();
                
                virtual JIRemoteSample* getRemoteSample();
                
                virtual void checkRemoteSample(JIRemoteSample* rs);
                
                virtual void checkCallback(JIRemoteSample* rs);
                
                virtual ~JRemoteSample();
            };
        }
    }
}

#endif
