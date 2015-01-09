#include "jcpp/native/unixos/process/UnixProcessFactory.h"
#include "jcpp/native/api/NativeException.h"
#include "jcpp/native/unixos/process/UnixProcess.h"
#include "jcpp/native/unixos/file/UnixFile.h"
#include "jcpp/native/unixos/io/UnixFileOutputStream.h"
#include "jcpp/native/unixos/io/UnixFileInputStream.h"
#include "jcpp/native/unixos/UnixUtils.h"

#if defined(Linux)
extern "C" {
#include "jcpp/native/unixos/process/LinuxReadProc.h"
}
#endif

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <limits.h>
#include <errno.h>
#include <ctype.h>
#include <sys/stat.h>

using namespace jcpp::native::api;
using namespace jcpp::native::api::process;
using namespace jcpp::native::unixos;
using namespace jcpp::native::unixos::file;
using namespace jcpp::native::unixos::io;

namespace jcpp {
	namespace native {
		namespace unixos {
			namespace process {

				NativeString UnixProcessFactory::className("jcpp::native::unixos::process::UnixProcessFactory");

				UnixProcessFactory::UnixProcessFactory() {
#if defined(Linux)
					hertz = getHertz(); // TODO
#endif
				}

				UnixProcessFactory::~UnixProcessFactory() {
				}

				NativeProcess * UnixProcessFactory::getLocalProcess() {
					NativeProcess* localProcess = null;
#if defined(SOLARIS2) || defined(_AIX)
					localProcess = new UnixProcess(getpid());
#elif defined(Linux)
					localProcess = new UnixProcess(getpid(), hertz);
#endif
					return localProcess;
				}

				void UnixProcessFactory::getAllProcesses(std::vector<NativeProcess *>& processes) {
#if defined(SOLARIS2) || defined(_AIX)
					UnixFile procFile("/proc/");
					std::vector<NativeString> files;
					procFile.list(files);
					for (std::vector<NativeString>::iterator iter = files.begin(); iter != files.end(); iter++) {
						std::string str = iter->getString();
						std::string::const_iterator it = str.begin();
						while (it != str.end() && isdigit(*it))
						++it;
						if(!str.empty() && it == str.end()) {
							processes.push_back(new UnixProcess(atoi(str.c_str())));
						}
					}
#elif defined(Linux)
					PROCTAB* proctab = openproc(PROC_FILLSTAT | PROC_FILLSTATUS | PROC_FILLUSR | PROC_FILLMEM);
					proc_t* procPointer = NULL;
					while ((procPointer = readproc(proctab, null)) != null) {
						processes.push_back(new UnixProcess(procPointer->tid, hertz));
						freeproc(procPointer);
						procPointer = null;
					}
					closeproc(proctab);
#endif
				}

				NativeForkedProcess UnixProcessFactory::createNativeProcess(NativeProcessBuilder& builder) {
					int result = 0;

					jint spaceIndex = -1;
					std::vector<NativeString> formatedCommand;
					std::vector<NativeString> command;
					builder.getCommand(command);
					for (std::vector<NativeString>::iterator it = command.begin(); it != command.end(); it++) {
						if (!it->isEmpty()) {
							NativeString trimmedCommand = it->trim();
							while ((spaceIndex = trimmedCommand.indexOf(' ')) > 0) {
								formatedCommand.push_back(trimmedCommand.substring(0, spaceIndex));
								trimmedCommand = trimmedCommand.substring(spaceIndex + 1);
							}
							formatedCommand.push_back(trimmedCommand);
						}
					}
					if (formatedCommand.size() == 0) {
						throw NativeException(className, "createNativeProcess", ILLEGAL_ARGUMENT_EXCEPTION, "The command list is empty.");
					}

					UnixFile workDirFile(builder.getDirectory());
					workDirFile.createDirectories();
					NativeString currentDirectory = workDirFile.getAbsolutePath();

					NativeProcessBuilderRedirect redirectInput = builder.getRedirectInput();
					int inputStreamHandle = -1;
					int inputStreamPipeWriteHandle = -1;

					NativeString inputStreamFilePath;

					switch (redirectInput.getType()) {
						case INHERIT:
							inputStreamHandle = STDIN_FILENO;
							break;
						case PIPE:
							int fds[2];
							if (pipe(fds) == -1) {
								throw NativeException(className, "createNativeProcess", SYSTEM_EXCEPTION, "Failed to create the Input Stream Pipe for the child process.", errno);
							}
							inputStreamHandle = fds[0];
							inputStreamPipeWriteHandle = fds[1];
							break;
						case READ:
							inputStreamFilePath = UnixFile(redirectInput.getFile()).getAbsolutePath();
							EINTR_RETRY_R(inputStreamHandle, open(inputStreamFilePath.getString().c_str(), O_RDONLY))
							if (inputStreamHandle == -1) {
								throw NativeException(className, "createNativeProcess", SYSTEM_EXCEPTION, "Failed to open Input Stream Redirect File while creating a new process path = " + inputStreamFilePath, errno);
							}
							break;
						default:
							break;
					}

					NativeProcessBuilderRedirect redirectOutput = builder.getRedirectOutput();
					int outputStreamHandle = -1;
					int outputStreamPipeReadHandle = -1;
					NativeString outputStreamFilePath;
					UnixFile outputStreamFile;

					switch (redirectOutput.getType()) {
						case INHERIT:
							outputStreamHandle = STDOUT_FILENO;
							break;
						case PIPE:
							int fds[2];
							if (pipe(fds) == -1) {
								if (redirectInput.getType() != INHERIT) {
									EINTR_RETRY_R(result, close(inputStreamHandle));
									if (inputStreamPipeWriteHandle != -1) {
										EINTR_RETRY_R(result, close(inputStreamPipeWriteHandle));
									}
								}
								throw NativeException(className, "createNativeProcess", SYSTEM_EXCEPTION, "Failed to create the Output Stream Pipe for the child process.", errno);
							}
							outputStreamPipeReadHandle = fds[0];
							outputStreamHandle = fds[1];
							break;
						case WRITE:
						case APPEND:
							outputStreamFile = UnixFile(redirectOutput.getFile());
							UnixFile(outputStreamFile.getParentPath()).createDirectories();
							outputStreamFilePath = outputStreamFile.getAbsolutePath();
							EINTR_RETRY_R(outputStreamHandle, open(outputStreamFilePath.getString().c_str(), O_WRONLY | O_CREAT | (redirectOutput.getType() == APPEND ? O_APPEND : O_TRUNC), (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH)))
							if (outputStreamHandle == -1) {
								if (redirectInput.getType() != INHERIT) {
									EINTR_RETRY_R(result, close(inputStreamHandle));
									if (inputStreamPipeWriteHandle != -1) {
										EINTR_RETRY_R(result, close(inputStreamPipeWriteHandle));
									}
								}
								throw NativeException(className, "createNativeProcess", SYSTEM_EXCEPTION, "Failed to open Output Stream Redirect File while creating a new process path = " + outputStreamFilePath, errno);
							}
							break;
						default:
							break;
					}

					NativeProcessBuilderRedirect redirectError = builder.getRedirectError();
					int errorStreamHandle = -1;
					int errorStreamPipeReadHandle = -1;
					NativeString errorStreamFilePath;
					UnixFile errorStreamFile;
					if (builder.isRedirectErrorStreamToOutputStream()) {
						errorStreamHandle = outputStreamHandle;
					} else {
						switch (redirectError.getType()) {
							case INHERIT:
								errorStreamHandle = STDERR_FILENO;
								break;
							case PIPE:
								int fds[2];
								pipe(fds);
								if (pipe(fds) == -1) {
									if (redirectInput.getType() != INHERIT) {
										EINTR_RETRY_R(result, close(inputStreamHandle));
										if (inputStreamPipeWriteHandle != -1) {
											EINTR_RETRY_R(result, close(inputStreamPipeWriteHandle));
										}
									}
									if (redirectOutput.getType() != INHERIT) {
										EINTR_RETRY_R(result, close(outputStreamHandle));
										if (outputStreamPipeReadHandle != -1) {
											EINTR_RETRY_R(result, close(outputStreamPipeReadHandle));
										}
									}
									throw NativeException(className, "createNativeProcess", SYSTEM_EXCEPTION, "Failed to create the Error Stream Pipe for the child process.", errno);
								}
								errorStreamPipeReadHandle = fds[0];
								errorStreamHandle = fds[1];
								break;
							case WRITE:
							case APPEND:
								errorStreamFile = UnixFile(redirectError.getFile());
								UnixFile(errorStreamFile.getParentPath()).createDirectories();
								errorStreamFilePath = errorStreamFile.getAbsolutePath();
								EINTR_RETRY_R(errorStreamHandle, open(errorStreamFilePath.getString().c_str(), O_WRONLY | O_CREAT | (redirectError.getType() == APPEND ? O_APPEND : O_TRUNC), (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH)))
								if (errorStreamHandle == -1) {
									if (redirectInput.getType() != INHERIT) {
										EINTR_RETRY_R(result, close(inputStreamHandle));
										if (inputStreamPipeWriteHandle != -1) {
											EINTR_RETRY_R(result, close(inputStreamPipeWriteHandle));
										}
									}
									if (redirectOutput.getType() != INHERIT) {
										EINTR_RETRY_R(result, close(outputStreamHandle));
										if (outputStreamPipeReadHandle != -1) {
											EINTR_RETRY_R(result, close(outputStreamPipeReadHandle));
										}
									}
									throw NativeException(className, "createNativeProcess", SYSTEM_EXCEPTION, "Failed to open Error Stream Redirect File while creating a new process path = " + errorStreamFilePath, errno);
								}
								break;
							default:
								break;
						}
					}

					std::map<NativeString, NativeString> env;
					if (builder.isInheritEnvironment()) {
						UnixUtils::getEnv(env);
					}
					builder.getEnvironment(env);

					char** environ = new char*[env.size() + 1];
					environ[env.size()] = NULL;
					int i = 0;
					for (std::map<NativeString, NativeString>::iterator it = env.begin(); it != env.end(); it++) {
						NativeString key = it->first.trim();
						NativeString value = it->second.trim();
						NativeString envKeyValue = key + "=" + value;
						environ[i] = new char[envKeyValue.length() + 1];
						environ[i][envKeyValue.length()] = '\0';
						memcpy(environ[i], envKeyValue.getString().c_str(), envKeyValue.length());
					}

					NativeString commandFileName = formatedCommand[0];
					char** argv = new char*[formatedCommand.size() + 1];
					argv[formatedCommand.size()] = NULL;
					i = 0;
					for (std::vector<NativeString>::iterator it = formatedCommand.begin(); it != formatedCommand.end(); it++) {
						argv[i] = new char[it->length() + 1];
						argv[i][it->length()] = '\0';
						memcpy(argv[i], it->getString().c_str(), it->length());
					}

					int pid = fork();

					if (pid == 0) {
						EINTR_RETRY_R(result, dup2(inputStreamHandle, STDIN_FILENO))
						EINTR_RETRY_R(result, close(inputStreamHandle))

						EINTR_RETRY_R(result, dup2(outputStreamHandle, STDOUT_FILENO))
						EINTR_RETRY_R(result, close(outputStreamHandle))

						EINTR_RETRY_R(result, dup2(errorStreamHandle, STDERR_FILENO))
						EINTR_RETRY_R(result, close(errorStreamHandle))

						long max_fd = sysconf(_SC_OPEN_MAX);
						max_fd = (max_fd < 65535) ? max_fd : 65535;

						for (int fd = STDERR_FILENO + 1; fd < max_fd; fd++) {
							EINTR_RETRY_R(result, close(fd))
						}

						setsid();

						chdir(currentDirectory.getString().c_str());

						execve((const char *) commandFileName.getString().c_str(), (char * const *) argv, (char * const *) environ);
						perror("An error has occured while executing execv!");
						exit(1);
					}

					for (i = 0; i < (int) env.size(); i++) {
						delete[] environ[i];
					}
					delete environ;

					for (i = 0; i < (int)formatedCommand.size(); i++) {
						delete[] argv[i];
					}
					delete argv;

					if (pid < 0) {
						if (redirectInput.getType() != INHERIT) {
							EINTR_RETRY_R(result, close(inputStreamHandle));
							if (inputStreamPipeWriteHandle != -1) {
								EINTR_RETRY_R(result, close(inputStreamPipeWriteHandle));
							}
						}
						if (redirectOutput.getType() != INHERIT) {
							EINTR_RETRY_R(result, close(outputStreamHandle));
							if (outputStreamPipeReadHandle != -1) {
								EINTR_RETRY_R(result, close(outputStreamPipeReadHandle));
							}
						}
						if (!builder.isRedirectErrorStreamToOutputStream() && (redirectError.getType() != INHERIT)) {
							EINTR_RETRY_R(result, close(errorStreamHandle));
							if (errorStreamPipeReadHandle != -1) {
								EINTR_RETRY_R(result, close(errorStreamPipeReadHandle));
							}
						}

						NativeString commandLine;
						for (std::vector<NativeString>::iterator it = formatedCommand.begin(); it != formatedCommand.end(); it++) {
							commandLine = commandLine + " " + *it;
						}

						throw NativeException(className, "createNativeProcess", SYSTEM_EXCEPTION, "Could not create a new process on Unix machine with command = " + commandLine, errno);
					}

					if (redirectInput.getType() != INHERIT) {
						EINTR_RETRY_R(result, close(inputStreamHandle));
					}
					if (redirectOutput.getType() != INHERIT) {
						EINTR_RETRY_R(result, close(outputStreamHandle));
					}
					if (!builder.isRedirectErrorStreamToOutputStream() && (redirectError.getType() != INHERIT)) {
						EINTR_RETRY_R(result, close(errorStreamHandle));
					}

					NativeProcess * process = NULL;

#if defined(SOLARIS2) || defined(_AIX)
					process = new UnixProcess(pid);
#elif defined(Linux)
					process = new UnixProcess(pid, hertz);
#endif

					NativeOutputStream * inputStream = redirectInput.getType() == PIPE ? new UnixFileOutputStream(UnixFileDescriptor(inputStreamPipeWriteHandle)) : null;
					NativeInputStream * outputStream = redirectOutput.getType() == PIPE ? new UnixFileInputStream(UnixFileDescriptor(outputStreamPipeReadHandle)) : null;
					NativeInputStream * errorStream = !builder.isRedirectErrorStreamToOutputStream() && (redirectError.getType() == PIPE) ? new UnixFileInputStream(UnixFileDescriptor(errorStreamPipeReadHandle)) : null;
					return NativeForkedProcess(process, inputStream, outputStream, errorStream);
				}

			}
		}
	}
}
