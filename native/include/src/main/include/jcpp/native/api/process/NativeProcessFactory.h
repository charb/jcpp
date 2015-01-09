#ifndef JCPP_NATIVE_API_PROCESS_NATIVEPROCESSFACTORY
#define JCPP_NATIVE_API_PROCESS_NATIVEPROCESSFACTORY

#include <vector>
#include "jcpp/native/api/process/NativeProcess.h"
#include "jcpp/native/api/process/NativeForkedProcess.h"
#include "jcpp/native/api/process/NativeProcessBuilder.h"

namespace jcpp {
	namespace native {
		namespace api {
			class NativeFactory;
		}
	}
}

namespace jcpp {
	namespace native {
		namespace api {
			namespace process {

				class JCPP_EXPORT NativeProcessFactory {

					friend class jcpp::native::api::NativeFactory;

				private:
					static NativeProcessFactory * instance;

				protected:
					NativeProcessFactory();

					static NativeProcessFactory * getInstance();
					static void setInstance(NativeProcessFactory * instance);

				public:
					virtual ~NativeProcessFactory();

					/**
					 * Returns the current process Native Process
					 *
					 * Note: Returned Process Pointer should be deleted by the user
					 */
					virtual NativeProcess * getLocalProcess() = 0;

					/**
					 * Fills the vector with all the Processes running on the machine.
					 *
					 * Note: Returned Process Pointers should be deleted by the user
					 */
					virtual void getAllProcesses(std::vector<NativeProcess *>& processes) = 0;

					/**
					 * Forks a new process using the configuration set in the process builder
					 *
					 * Note: Returned Process Pointer should be deleted by the user
					 */
					virtual NativeForkedProcess createNativeProcess(NativeProcessBuilder& builder) = 0;
				};

			}
		}
	}
}

#endif
