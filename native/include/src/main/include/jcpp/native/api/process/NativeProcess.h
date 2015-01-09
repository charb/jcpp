#ifndef JCPP_NATIVE_API_PROCESS_NATIVEPROCESS
#define JCPP_NATIVE_API_PROCESS_NATIVEPROCESS

#include <vector>
#include <map>
#include "jcpp/native/api/NativeString.h"

using namespace jcpp::native::api;

namespace jcpp {
	namespace native {
		namespace api {
			namespace process {

				class JCPP_EXPORT NativeProcess {

				private:
					NativeProcess(const NativeProcess&);
					NativeProcess& operator =(const NativeProcess&);

				protected:
					NativeProcess();

				public:
					virtual ~NativeProcess();

					/**
					 * Return the PID of this Process as a String Value
					 */
					virtual NativeString getPid() = 0;

					/**
					 * Return The Process Hierarchy Tree of this process.
					 *
					 * Throws: NativeException
					 */
					virtual void getProcessTree(std::vector<NativeString>& tree) = 0;

					/**
					 * Returns the Process Command Arguments
					 *
					 * Throws: NativeException
					 */
					virtual NativeString getCmd() = 0;

					/**
					 * Gets the environment variables of the Process
					 *
					 * Throws: NativeException
					 */
					virtual void getEnvironment(std::map<NativeString, NativeString>& env) = 0;

					/**
					 * This method should be called only after calling "waitFor" method. Otherwise an exception is thrown
					 * Returns the exit value saved from calling "waitFor"
					 *
					 * Throws: NativeException
					 */
					virtual jint getExitValue() = 0;

					/**
					 * Returns the owner user of this Process
					 *
					 * Throws: NativeException
					 */
					virtual NativeString getOwner() = 0;

					/**
					 * Return the start date of this process in milli seconds from EPOC
					 *
					 * Throws: NativeException
					 */
					virtual jlong getStartDate() = 0;

					/**
					 * Returns the working directory of this process
					 *
					 * Throws: NativeException;
					 */
					virtual NativeString getWorkingDirectory() = 0;

					/**
					 * This method call will block until the process terminates.
					 * Returns the exist value of the process
					 *
					 * Throws: NativeException
					 */
					virtual jint waitFor() = 0;

					/**
					 * Kills the process
					 *
					 * Throws: NativeException
					 */
					virtual void kill() = 0;

					/**
					 * Get the CPU usage percentage of this process
					 *
					 * Throws: NativeException
					 */
					virtual jdouble getCpuUsage() = 0;

					/**
					 * Returns the Real Memory Usage (Working Set) of this Process in bytes
					 *
					 * Throws: NativeException
					 */
					virtual jlong getRealMemoryUsage() = 0;

					/**
					 * Returns the Virtual Memory Usage of this Process in bytes
					 *
					 * Throws: NativeException
					 */
					virtual jlong getVirtualMemoryUsage() = 0;

				};

			}
		}
	}
}

#endif
