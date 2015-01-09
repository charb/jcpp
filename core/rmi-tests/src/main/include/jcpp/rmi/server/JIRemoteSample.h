#ifndef JCPP_RMI_SERVER_JIREMOTESAMPLE_H
#define JCPP_RMI_SERVER_JIREMOTESAMPLE_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/rmi/server/JSampleObject.h"

namespace jcpp{
    namespace rmi{
        namespace server{
            class JSampleObject;

        	// @Class(canonicalName="jcpp.rmi.server.IRemoteSample", simpleName="IRemoteSample");
            class JIRemoteSample : public JInterface{
            public:
                static JClass* getClazz();

                virtual JSampleObject* getSampleObject()=0;

                virtual JIRemoteSample* getRemoteSample()=0;

                virtual void checkRemoteSample(JIRemoteSample* rs)=0;

                virtual void checkCallback(JIRemoteSample* rs)=0;

                virtual ~JIRemoteSample();
            };
        }
    }
}

#endif
