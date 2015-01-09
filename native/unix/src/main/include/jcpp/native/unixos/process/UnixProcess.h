#ifndef JCPP_NATIVE_UNIXOS_PROCESS_UNIXPROCESS
#define JCPP_NATIVE_UNIXOS_PROCESS_UNIXPROCESS

#include "jcpp/native/api/process/NativeProcess.h"
#include "jcpp/native/unixos/nthread/UnixMutex.h"

#if defined(SOLARIS2)
#include <procfs.h>
#elif defined(_AIX)
#include <sys/procfs.h>
#endif

using namespace jcpp::native::api;
using namespace jcpp::native::api::process;
using namespace jcpp::native::unixos::nthread;

namespace jcpp {
	namespace native {
		namespace unixos {
			namespace process {

				class JCPP_EXPORT UnixProcess: public NativeProcess {

				private:
					static NativeString className;

#if defined(SOLARIS2) || defined(_AIX)
					static UnixMutex getpwuidMutex;
#endif

					int pid;
					jbool processFinished;
					jint exitValue;
#if defined(Linux)
					unsigned long long hertz;
#endif

#if defined(SOLARIS2) || defined(_AIX)
					void readPsinfo(psinfo_t& psinfo);
					void readPsinfo(psinfo_t& psinfo, const NativeString& pid);
#endif

				public:
#if defined(SOLARIS2) || defined(_AIX)
					UnixProcess(int pid);
#elif defined(Linux)
					UnixProcess(int pid, unsigned long long hertz);
#endif

					virtual ~UnixProcess();

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

