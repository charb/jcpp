#ifndef JCPP_NATIVE_WINDOWS_PROCESS_WINDOWSPROCESSFACTORY
#define JCPP_NATIVE_WINDOWS_PROCESS_WINDOWSPROCESSFACTORY

#include "jcpp/native/api/process/NativeProcessFactory.h"
#include "jcpp/native/windows/process/WindowsProcess.h"

using namespace jcpp::native::api;
using namespace jcpp::native::api::process;

namespace jcpp {
	namespace native {
		namespace windows {
			namespace process {

				class JCPP_EXPORT WindowsProcessFactory: public NativeProcessFactory {

				private:
					static NativeString className;

					HMODULE hModNtDll;
					PZWQUERYINFORMATIONPROCESS ZwQueryInformationProcess;

				public:
					WindowsProcessFactory();
					virtual ~WindowsProcessFactory();

					virtual NativeProcess * getLocalProcess();

					virtual void getAllProcesses(std::vector<NativeProcess *>& processes);

					virtual NativeForkedProcess createNativeProcess(NativeProcessBuilder& builder);

				};

			}
		}
	}
}

#endif
