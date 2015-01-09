#include "jcpp/native/api/process/NativeForkedProcess.h"

namespace jcpp {
	namespace native {
		namespace api {
			namespace process {

				NativeForkedProcess::NativeForkedProcess(NativeProcess * process, NativeOutputStream * inputStreamWritePipeEnd, NativeInputStream * outputStreamReadPipeEnd, NativeInputStream * errorStreamReadPipeEnd) :
						process(process), inputStreamWritePipeEnd(inputStreamWritePipeEnd), outputStreamReadPipeEnd(outputStreamReadPipeEnd), errorStreamReadPipeEnd(errorStreamReadPipeEnd) {
				}

				NativeProcess * NativeForkedProcess::getProcess() const {
					return process;
				}

				NativeOutputStream * NativeForkedProcess::getInputStreamWritePipeEnd() const {
					return inputStreamWritePipeEnd;
				}

				NativeInputStream * NativeForkedProcess::getOutputStreamReadPipeEnd() const {
					return outputStreamReadPipeEnd;
				}

				NativeInputStream * NativeForkedProcess::getErrorStreamReadPipeEnd() const {
					return errorStreamReadPipeEnd;
				}

			}
		}
	}
}
