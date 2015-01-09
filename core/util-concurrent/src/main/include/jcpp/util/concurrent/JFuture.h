#ifndef JCPP_UTIL_CONCURRENT_JFUTURE_H
#define JCPP_UTIL_CONCURRENT_JFUTURE_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"

namespace jcpp{
    namespace util{
        namespace concurrent{

        	// @Class(canonicalName="java.util.concurrent.Future", simpleName="Future");
            class JCPP_EXPORT JFuture : public JInterface{
            public:
                static JClass* getClazz();

                virtual jbool cancel()=0;

                virtual jbool isCancelled()=0;

                virtual jbool isDone()=0;

                virtual JObject* get()=0;

                virtual JObject* get(jlong l)=0;

                virtual ~JFuture();
            };
        }
    }
}

#endif
