#ifndef JCPP_LANG_JRUNNABLE_H
#define JCPP_LANG_JRUNNABLE_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/native/api/nthread/NativeRunnable.h"

using namespace jcpp::lang;
using jcpp::native::api::nthread::NativeRunnable;

namespace jcpp{
	namespace lang{

        class JCPP_EXPORT JRunnable : public JInterface, public NativeRunnable {
        public:
            static jcpp::lang::JClass* getClazz();

            virtual void run() = 0;

            virtual ~JRunnable();
        };
    }
}

#endif
