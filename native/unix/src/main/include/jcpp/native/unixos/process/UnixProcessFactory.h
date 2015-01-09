#ifndef JCPP_NATIVE_UNIXOS_PROCESS_UNIXPROCESSFACTORY
#define JCPP_NATIVE_UNIXOS_PROCESS_UNIXPROCESSFACTORY

#include "jcpp/native/api/process/NativeProcessFactory.h"

using namespace jcpp::native::api;
using namespace jcpp::native::api::process;

namespace jcpp {
	namespace native {
		namespace unixos {
			namespace process {

				class JCPP_EXPORT UnixProcessFactory: public NativeProcessFactory {

				private:
					static NativeString className;

#if defined(Linux)
					unsigned long long hertz;
#endif

				public:
					UnixProcessFactory();
					virtual ~UnixProcessFactory();

					virtual NativeProcess * getLocalProcess();
					virtual void getAllProcesses(std::vector<NativeProcess *>& processes);
					virtual NativeForkedProcess createNativeProcess(NativeProcessBuilder& builder);

				};

			}
		}
	}
}

#endif
