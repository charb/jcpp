#ifndef JCPP_NATIVE_WINDOWS_PROCESS_WINDOWSPROCESS
#define JCPP_NATIVE_WINDOWS_PROCESS_WINDOWSPROCESS

#include "jcpp/native/api/process/NativeProcess.h"
#include "jcpp/native/windows/WindowsInclude.h"

#include <Winternl.h>
typedef NTSTATUS (__stdcall *PZWQUERYINFORMATIONPROCESS)(HANDLE ProcessHandle, PROCESSINFOCLASS ProcessInformationClass, PVOID ProcessInformation, ULONG ProcessInformationLength, PULONG ReturnLength);

using namespace jcpp::native::api;
using namespace jcpp::native::api::process;

namespace jcpp {
	namespace native {
		namespace windows {
			namespace process {

				class JCPP_EXPORT WindowsProcess: public NativeProcess {

				private:
					static NativeString className;
					PZWQUERYINFORMATIONPROCESS ZwQueryInformationProcess;
					DWORD pid;
					jbool processFinished;
					jint exitValue;

				public:
					WindowsProcess(DWORD pid, PZWQUERYINFORMATIONPROCESS ZwQueryInformationProcess);

					virtual ~WindowsProcess();

					virtual NativeString getPid();

					virtual void getProcessTree(std::vector<NativeString>& tree);

					virtual NativeString getCmd();

					virtual void getEnvironment(std::map<NativeString, NativeString>& env);

					virtual jint getExitValue();

					virtual NativeString getOwner();

					virtual jlong getStartDate();

					virtual NativeString getWorkingDirectory();

					virtual jint waitFor();

					virtual void kill();

					virtual jdouble getCpuUsage();

					virtual jlong getRealMemoryUsage();

					virtual jlong getVirtualMemoryUsage();

				};

			}
		}
	}
}

#endif
