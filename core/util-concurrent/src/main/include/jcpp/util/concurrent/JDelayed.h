#ifndef JCPP_UTIL_CONCURRENT_JDELAYED_H
#define JCPP_UTIL_CONCURRENT_JDELAYED_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JComparable.h"

namespace jcpp{
    namespace util{
        namespace concurrent{

        	// @Class(canonicalName="java.util.concurrent.Delayed", simpleName="Delayed");
            class JCPP_EXPORT JDelayed : public JComparable{
            public:
                static JClass* getClazz();

                virtual jlong getDelay()=0;

                virtual ~JDelayed();
            };
        }
    }
}

#endif
