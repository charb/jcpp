#ifndef JCPP_NATIVE_API_PROCESS_NATIVEFORKEDPROCESS
#define JCPP_NATIVE_API_PROCESS_NATIVEFORKEDPROCESS

#include "jcpp/native/api/io/NativeInputStream.h"
#include "jcpp/native/api/io/NativeOutputStream.h"
#include "jcpp/native/api/io/NativeOutputStream.h"
#include "jcpp/native/api/process/NativeProcess.h"

using namespace jcpp::native::api::io;

namespace jcpp {
	namespace native {
		namespace api {
			namespace process {

				class JCPP_EXPORT NativeForkedProcess {

				private:
					NativeProcess * process;
					NativeOutputStream * inputStreamWritePipeEnd;
					NativeInputStream * outputStreamReadPipeEnd;
					NativeInputStream * errorStreamReadPipeEnd;

				public:
					NativeForkedProcess(NativeProcess * process, NativeOutputStream * inputStreamWritePipeEnd, NativeInputStream * outputStreamReadPipeEnd, NativeInputStream * errorStreamReadPipeEnd);

					/**
					 * The new Forked Process
					 */
					NativeProcess * getProcess() const;

					/**
					 * The Output Stream connected to the child process if the Builder Input Redirect was set to PIPE,
					 * other wise null will be returned
					 */
					NativeOutputStream * getInputStreamWritePipeEnd() const;

					/**
					 * The Input Stream connected to the child process  if the Builder Output Redirect was set to PIPE,
					 * other wise null will be return
					 */
					NativeInputStream * getOutputStreamReadPipeEnd() const;

					/**
					 * The Input Stream connected to the child process if the Builder Error Redirect was set to PIPE and the builder redirectErrorStreamToOutputStream is set to false,
					 * other wise null will be return
					 */
					NativeInputStream * getErrorStreamReadPipeEnd() const;

				};

			}
		}
	}
}

#endif
