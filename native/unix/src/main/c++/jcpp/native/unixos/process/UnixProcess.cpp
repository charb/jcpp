#include "jcpp/native/unixos/process/UnixProcess.h"
#include "jcpp/native/api/NativeException.h"
#include "jcpp/native/unixos/UnixUtils.h"
#include "jcpp/native/unixos/io/UnixFileInputStream.h"
#include "jcpp/native/unixos/nthread/UnixThread.h"
#include "jcpp/native/api/nthread/ScopedLock.h"

#if defined(Linux)
extern "C" {
#include "jcpp/native/unixos/process/LinuxReadProc.h"
}
#endif

#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <math.h>
#include <pwd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace jcpp::native::api;
using namespace jcpp::native::api::process;
using namespace jcpp::native::api::nthread;
using namespace jcpp::native::unixos::io;
using namespace jcpp::native::unixos::nthread;

namespace jcpp {
	namespace native {
		namespace unixos {
			namespace process {

				NativeString UnixProcess::className("jcpp::native::unixos::process::UnixProcess");

#if defined(SOLARIS2) || defined(_AIX)
				UnixMutex UnixProcess::getpwuidMutex;
#endif

#if defined(SOLARIS2) || defined(_AIX)
				UnixProcess::UnixProcess(int pid) :
						pid(pid), processFinished(false), exitValue(0) {
				}
#elif defined(Linux)
				UnixProcess::UnixProcess(int pid, unsigned long long hertz) :
						pid(pid), processFinished(false), exitValue(0), hertz(hertz) {
				}
#endif

				UnixProcess::~UnixProcess() {
				}

				//~---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

				NativeString UnixProcess::getPid() {
					char buf[20];
					snprintf(buf, 20, "%d", pid);
					return NativeString(buf);
				}

				//~---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

				void UnixProcess::getProcessTree(std::vector<NativeString>& tree) {
					NativeString currentPid = getPid();
					char buf[20];
#if defined(SOLARIS2) || defined(_AIX)
					while (true) {
						psinfo_t psinfo;
						try {
							readPsinfo(psinfo, currentPid);
						} catch (...) {
							break;
						}

						int parentPid = psinfo.pr_ppid;
						snprintf(buf, 20, "%d", parentPid);
						currentPid = buf;
						tree.push_back(currentPid);
						if (parentPid <= 0) {
							break;
						}
					}
#elif defined(Linux)
					std::map<int, int> processParents;
					PROCTAB* proctab = openproc(PROC_FILLSTAT | PROC_FILLSTATUS | PROC_FILLUSR | PROC_FILLMEM);
					proc_t* procPointer = NULL;
					while ((procPointer = readproc(proctab, null)) != null) {
						processParents.insert(std::pair<int, int>(procPointer->tid, procPointer->ppid));
						freeproc(procPointer);
						procPointer = null;
					}
					closeproc(proctab);

					int pidTemp = pid;
					while (true) {
						pidTemp = processParents[pidTemp];
						snprintf(buf, 20, "%d", pidTemp);
						currentPid = buf;
						tree.push_back(currentPid);
						if (pidTemp <= 0) {
							break;
						}
					}
#endif
				}

				//~---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

				NativeString UnixProcess::getCmd() {
					NativeString commandArgs;
#if defined(SOLARIS2) || defined(_AIX)
					psinfo_t psinfo;
					readPsinfo(psinfo);

					uintptr_t offset = psinfo.pr_argv;

					NativeString asFilePath = "/proc/" + getPid() + "/as";
					UnixFileInputStream asInputStream(asFilePath);
					UnixFileDescriptor* unixFD = (UnixFileDescriptor*) asInputStream.getNativeFileDescriptor();

					int ioff = 0;
					int address = 0;
					int readLength = 0;
					char* memory = new char[8192]; // 8k

					EINTR_RETRY_R(readLength, pread(unixFD->getDescriptor(), memory, 8192, offset))
					if (readLength > 0) {
#if defined(_AIX)
						offset = *((int*) memory);
						EINTR_RETRY_R(readLength, pread(unixFD->getDescriptor(), memory, 8192, offset))
						if (readLength > 0) {
#endif
							while (((address = abs((int)(*((int*) (memory + ioff)) - offset))) < readLength) && (address > 0)) {
								NativeString argv(memory + address);
								commandArgs += argv;
								commandArgs += " ";
								ioff += sizeof(void *);
							}
#if defined(_AIX)
						}
#endif
					}
					delete memory;
					try {
						asInputStream.close();
					} catch (NativeException& e2) {
						// TODO log later
					}
#elif defined(Linux)
					jbool found = false;
					PROCTAB* proctab = openproc(PROC_FILLSTAT | PROC_FILLSTATUS | PROC_FILLUSR | PROC_FILLMEM);
					proc_t* procPointer = NULL;
					while ((procPointer = readproc(proctab, null)) != null) {
						if (procPointer->tid == pid) {
							found = true;
							int index = 0;
							//TODO cmdline is always null, check reason why...
							while (procPointer->cmdline!=null && procPointer->cmdline[index] != NULL) {
								commandArgs = commandArgs + procPointer->cmdline[index++];
							}
							freeproc(procPointer);
							procPointer = null;
							break;
						}
						freeproc(procPointer);
						procPointer = null;
					}
					closeproc(proctab);
					if (!found) {
						throw NativeException(className, "getCmd", SYSTEM_EXCEPTION, "Failed to find a process with pid = " + getPid());
					}
#endif
					return commandArgs;
				}

				//~---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

				void UnixProcess::getEnvironment(std::map<NativeString, NativeString>& env) {
#if defined(SOLARIS2) || defined(_AIX)
					psinfo_t psinfo;
					readPsinfo(psinfo);

					uintptr_t offset = psinfo.pr_envp;

					NativeString asFilePath = "/proc/" + getPid() + "/as";
					UnixFileInputStream asInputStream(asFilePath);
					UnixFileDescriptor* unixFD = (UnixFileDescriptor*) asInputStream.getNativeFileDescriptor();

					int ioff = 0;
					int address = 0;
					int readLength = 0;
					char* memory = new char[8192]; // 8k
					EINTR_RETRY_R(readLength, pread(unixFD->getDescriptor(), memory, 8192, offset))
					if (readLength > 0) {
#if defined(_AIX)
						offset = *((int*) memory);
						EINTR_RETRY_R(readLength, pread(unixFD->getDescriptor(), memory, 8192, offset))
						if (readLength > 0) {
#endif
							while (((address = abs((int)(*((int*) (memory + ioff)) - offset))) < readLength) && (address > 0)) {
								NativeString envKeyValue(memory + address);
								int equalIndex = envKeyValue.indexOf('=');
								if (equalIndex >= 0) {
									env.insert(std::pair<NativeString, NativeString>(envKeyValue.substring(0, equalIndex), envKeyValue.substring(equalIndex + 1)));
								}
								ioff += sizeof(void *);
							}
#if defined(_AIX)
						}
#endif
					}
					delete memory;
					try {
						asInputStream.close();
					} catch (NativeException& e2) {
						// TODO log later
					}
#elif defined(Linux)
					jbool found = false;
					PROCTAB* proctab = openproc(PROC_FILLSTAT | PROC_FILLSTATUS | PROC_FILLUSR | PROC_FILLMEM);
					proc_t* procPointer = NULL;
					while ((procPointer = readproc(proctab, null)) != null) {
						if (procPointer->tid == pid) {
							found = true;
							int index = 0;	//TODO environ is always null, check reason
							while (procPointer->environ!=null && procPointer->environ[index++] != NULL) {
								NativeString envKeyValue(procPointer->environ[index]);
								int equalIndex = envKeyValue.indexOf('=');
								if (equalIndex >= 0) {
									env.insert(std::pair<NativeString, NativeString>(envKeyValue.substring(0, equalIndex), envKeyValue.substring(equalIndex + 1)));
								}
							}
							freeproc(procPointer);
							procPointer = null;
							break;
						}
						freeproc(procPointer);
						procPointer = null;
					}
					closeproc(proctab);
					if (!found) {
						throw NativeException(className, "getEnvironment", SYSTEM_EXCEPTION, "Failed to find a process with pid = " + getPid());
					}
#endif
				}

				//~---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

				jint UnixProcess::getExitValue() {
					if (!processFinished) {
						throw NativeException(className, "getExitValue", SYSTEM_EXCEPTION, "Process still did not finished. PID = " + getPid());
					}
					return exitValue;
				}

				//~---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

				NativeString UnixProcess::getOwner() {
					NativeString owner;
#if defined(SOLARIS2) || defined(_AIX)
					psinfo_t psinfo;
					readPsinfo(psinfo);
					ScopedLock synchronize(getpwuidMutex);
					passwd * passwdInfo = getpwuid(psinfo.pr_uid);
					owner = passwdInfo->pw_name;
#elif defined(Linux)
					jbool found = false;
					PROCTAB* proctab = openproc(PROC_FILLSTAT | PROC_FILLSTATUS | PROC_FILLUSR | PROC_FILLMEM);
					proc_t* procPointer = NULL;
					while ((procPointer = readproc(proctab, null)) != null) {
						if (procPointer->tid == pid) {
							found = true;
							owner = procPointer->euser;
							freeproc(procPointer);
							procPointer = null;
							break;
						}
						freeproc(procPointer);
						procPointer = null;
					}
					closeproc(proctab);
					if (!found) {
						throw NativeException(className, "getOwner", SYSTEM_EXCEPTION, "Failed to find a process with pid = " + getPid());
					}
#endif
					return owner;
				}

				//~---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

				jlong UnixProcess::getStartDate() {
					jlong startDate = 0;
#if defined(SOLARIS2) || defined(_AIX)
					psinfo_t psinfo;
					readPsinfo(psinfo);
					startDate = (psinfo.pr_start.tv_sec * 1000) + (psinfo.pr_start.tv_nsec / 1000000);
#elif defined(Linux)
					jbool found = false;
					PROCTAB* proctab = openproc(PROC_FILLSTAT | PROC_FILLSTATUS | PROC_FILLUSR | PROC_FILLMEM);
					proc_t* procPointer = NULL;
					while ((procPointer = readproc(proctab, null)) != null) {
						if (procPointer->tid == pid) {
							found = true;
							startDate = procPointer->start_time;
							freeproc(procPointer);
							procPointer = null;
							break;
						}
						freeproc(procPointer);
						procPointer = null;
					}
					closeproc(proctab);
					if (!found) {
						throw NativeException(className, "getStartDate", SYSTEM_EXCEPTION, "Failed to find a process with pid = " + getPid());
					}
#endif
				return startDate;
				}

				//~---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

				NativeString UnixProcess::getWorkingDirectory() {
					char workdir[1024];
					char cwdPath[100];
#if defined(SOLARIS2)
					snprintf(cwdPath, 100, "/proc/%d/path/cwd", pid);
#else
					snprintf(cwdPath, 100, "/proc/%d/cwd", pid);
#endif
					if (readlink(cwdPath, workdir, 1024) == -1) {
						throw NativeException(className, "getWorkingDirectory", SYSTEM_EXCEPTION, "Failed to read the working directory of process id " + getPid(), errno);
					}
					return NativeString(workdir);
				}

				//~---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

				jint UnixProcess::waitFor() {
					int status = 0;
					if (waitpid(pid, &status, WUNTRACED) == -1) {
						throw NativeException(className, "waitFor", SYSTEM_EXCEPTION, "Failed to wait for process to finish. PID = " + getPid());
					}
					processFinished = true;

#if defined(Linux)
					if (status > 255) {
						status = status >> 8;
					}
#endif
					exitValue = status;
					return status;
				}

				//~---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

				void UnixProcess::kill() {
					::kill(pid, SIGKILL);
				}

				//~---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

				jdouble UnixProcess::getCpuUsage() {
					jdouble cpuUsage = 0;
#if defined(SOLARIS2) || defined(_AIX)
					psinfo_t psinfo1;
#if defined(_AIX)
					psinfo_t psinfo2;
					jlong time1 = UnixUtils::getCurrentTimeMillis();
#endif
					readPsinfo(psinfo1);

#if defined(SOLARIS2)
					cpuUsage = ((jdouble) psinfo1.pr_pctcpu * 100) / (jdouble) (0x8000);
#elif defined(_AIX)
					UnixUtils::sleep(1000);
					jlong time2 = UnixUtils::getCurrentTimeMillis();
					readPsinfo(psinfo2);

					cpuUsage = ((jdouble) ((psinfo2.pr_time.tv_sec + ((jdouble) psinfo2.pr_time.tv_nsec / 1000000000.0)) - (psinfo1.pr_time.tv_sec + ((double) psinfo1.pr_time.tv_nsec / 1000000000.0)))) * 100.0 / (((jdouble) (time2 - time1)) / 1000.0);
#endif

#elif defined(Linux)
					jlong time1 = 0;
					jlong startTime = 0;
					jlong time2 = 0;
					jlong endTime = 0;

					jbool found = false;
					startTime = UnixUtils::getCurrentTimeMillis();
					PROCTAB* proctab = openproc(PROC_FILLSTAT | PROC_FILLSTATUS | PROC_FILLUSR | PROC_FILLMEM);
					proc_t* procPointer = NULL;
					while ((procPointer = readproc(proctab, null)) != null) {
						if (procPointer->tid == pid) {
							found = true;
							time1 = procPointer->utime + procPointer->stime;
							freeproc(procPointer);
							procPointer = null;
							break;
						}
						freeproc(procPointer);
						procPointer = null;
					}
					closeproc(proctab);
					if (!found) {
						throw NativeException(className, "getCpuUsage", SYSTEM_EXCEPTION, "Failed to find a process with pid = " + getPid());
					}

					UnixUtils::sleep(1000);

					found = false;
					endTime = UnixUtils::getCurrentTimeMillis();
					proctab = openproc(PROC_FILLSTAT | PROC_FILLSTATUS | PROC_FILLUSR | PROC_FILLMEM);
					procPointer = NULL;
					while ((procPointer = readproc(proctab, null)) != null) {
						if (procPointer->tid == pid) {
							found = true;
							time2 = procPointer->utime + procPointer->stime;
							freeproc(procPointer);
							procPointer = null;
							break;
						}
						freeproc(procPointer);
						procPointer = null;
					}
					closeproc(proctab);
					if (!found) {
						throw NativeException(className, "getCpuUsage", SYSTEM_EXCEPTION, "Failed to find a process with pid = " + getPid());
					}
					cpuUsage =  ((jdouble) (time2 - time1) * 100.0 / ((jdouble) hertz)) / (((jdouble) (endTime - startTime)) / 1000.0);
#endif
					return cpuUsage;
				}

				//~---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

				jlong UnixProcess::getRealMemoryUsage() {
					jlong rmem = 0;
#if defined(SOLARIS2) || defined(_AIX)
					psinfo_t psinfo;
					readPsinfo(psinfo);
					rmem = (jlong) psinfo.pr_rssize;
#elif defined(Linux)
					jbool found = false;
					PROCTAB* proctab = openproc(PROC_FILLSTAT | PROC_FILLSTATUS | PROC_FILLUSR | PROC_FILLMEM);
					proc_t* procPointer = NULL;
					while ((procPointer = readproc(proctab, null)) != null) {
						if (procPointer->tid == pid) {
							found = true;
							rmem = procPointer->resident * getpagesize();
							freeproc(procPointer);
							procPointer = null;
							break;
						}
						freeproc(procPointer);
						procPointer = null;
					}
					closeproc(proctab);
					if (!found) {
						throw NativeException(className, "getRealMemoryUsage", SYSTEM_EXCEPTION, "Failed to find a process with pid = " + getPid());
					}
#endif
					return rmem;
				}

				//~---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

				jlong UnixProcess::getVirtualMemoryUsage() {
					jlong vmem = 0;
#if defined(SOLARIS2) || defined(_AIX)
					psinfo_t psinfo;
					readPsinfo(psinfo);
					vmem = (jlong) psinfo.pr_size;
#elif defined(Linux)
					jbool found = false;
					PROCTAB* proctab = openproc(PROC_FILLSTAT | PROC_FILLSTATUS | PROC_FILLUSR | PROC_FILLMEM);
					proc_t* procPointer = NULL;
					while ((procPointer = readproc(proctab, null)) != null) {
						if (procPointer->tid == pid) {
							found = true;
							vmem = procPointer->vm_size * 1024;
							freeproc(procPointer);
							procPointer = null;
							break;
						}
						freeproc(procPointer);
						procPointer = null;
					}
					closeproc(proctab);
					if (!found) {
						throw NativeException(className, "getVirtualMemoryUsage", SYSTEM_EXCEPTION, "Failed to find a process with pid = " + getPid());
					}
#endif
					return vmem;
				}

			//~---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#if defined(SOLARIS2) || defined(_AIX)
			void UnixProcess::readPsinfo(psinfo_t& psinfo) {
				readPsinfo(psinfo, getPid());
			}

			void UnixProcess::readPsinfo(psinfo_t& psinfo, const NativeString& pid) {
				NativeString psinfoFilePath = "/proc/" + pid + "/psinfo";
				UnixFileInputStream psinfoInputStream(psinfoFilePath);

				try {
					psinfoInputStream.read((jbyte*) &psinfo, 0, sizeof(psinfo_t));
				} catch (NativeException& e) {
					try {
						psinfoInputStream.close();
					} catch (NativeException& e2) {
						// TODO log later
					}
					throw e;
				}
			}
#endif

		}
	}
}
}
