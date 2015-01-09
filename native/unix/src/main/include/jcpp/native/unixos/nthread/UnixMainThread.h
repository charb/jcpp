#ifndef JCPP_NATIVE_UNIXOS_THREAD_UNIXMAINTHREAD
#define JCPP_NATIVE_UNIXOS_THREAD_UNIXMAINTHREAD

#include "jcpp/native/unixos/nthread/UnixAbstractThread.h"
#include "jcpp/native/unixos/nthread/UnixMutex.h"

using namespace jcpp::native::api;
using namespace jcpp::native::api::nthread;

namespace jcpp {
	namespace native {
		namespace unixos {
			namespace nthread {

				class JCPP_EXPORT UnixMainThread: public UnixAbstractThread {

				private:
					static NativeString className;
					static UnixMainThread instance;

					UnixMainThread();
				public:
					static UnixMainThread * getInstance();

					virtual ~UnixMainThread();

					virtual jlong getId() const;

					virtual void start();

					virtual void join();
					virtual jbool join(jlong milliseconds);

					virtual jbool isRunning();

					virtual void sleep(jlong milliseconds);
				};

			}
		}
	}
}

#endif
