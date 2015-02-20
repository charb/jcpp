#include "jcpp/native/windows/process/WindowsProcessFactory.h"
#include "jcpp/native/api/NativeException.h"
#include "jcpp/native/windows/process/WindowsProcess.h"
#include "jcpp/native/windows/file/WindowsFile.h"
#include "jcpp/native/windows/io/WindowsFileOutputStream.h"
#include "jcpp/native/windows/io/WindowsFileInputStream.h"
#include "jcpp/native/windows/WindowsUtils.h"

#include <psapi.h>

using namespace jcpp::native::api;
using namespace jcpp::native::api::process;
using namespace jcpp::native::windows;
using namespace jcpp::native::windows::file;
using namespace jcpp::native::windows::io;

namespace jcpp {
	namespace native {
		namespace windows {
			namespace process {

				NativeString WindowsProcessFactory::className("jcpp::native::windows::process::WindowsProcessFactory");

				WindowsProcessFactory::WindowsProcessFactory() {
					hModNtDll = LoadLibrary("ntdll.dll");
					if (hModNtDll == NULL) {
						throw NativeException(className, "WindowsProcessFactory", SYSTEM_EXCEPTION, "Failed to Dynamically load ntdll.dll", GetLastError());
					}
					ZwQueryInformationProcess = (PZWQUERYINFORMATIONPROCESS) GetProcAddress(hModNtDll, "ZwQueryInformationProcess");
					if (ZwQueryInformationProcess == NULL) {
						throw NativeException(className, "WindowsProcessFactory", SYSTEM_EXCEPTION, "Failed to get the address of the exported method ZwQueryInformationProcess from the Dynamically loaded library ntdll.dll", GetLastError());
					}
				}

				WindowsProcessFactory::~WindowsProcessFactory() {
					if (hModNtDll) {
						FreeLibrary(hModNtDll);
						hModNtDll = NULL;
					}
					ZwQueryInformationProcess = NULL;
				}

				NativeProcess * WindowsProcessFactory::getLocalProcess() {
					return new WindowsProcess(GetCurrentProcessId(), ZwQueryInformationProcess);
				}

				void WindowsProcessFactory::getAllProcesses(std::vector<NativeProcess *>& processes) {
					DWORD dwProcesses[512];
					DWORD bytesReturned = 0;
					if (!EnumProcesses(dwProcesses, sizeof(DWORD) * 512, &bytesReturned)) {
						throw NativeException(className, "getAllProcesses", SYSTEM_EXCEPTION, "Failed to EnumProcesses to get all the Processes.", GetLastError());
					}
					jint numberOfProcesses = bytesReturned / sizeof(DWORD);
					for (jint i = 0; i < numberOfProcesses; i++) {
						processes.push_back(new WindowsProcess(dwProcesses[i], ZwQueryInformationProcess));
					}
				}
				
				NativeForkedProcess WindowsProcessFactory::createNativeProcess(NativeProcessBuilder& builder) {
				
					NativeString commandLine;
					std::vector<NativeString> command;
					builder.getCommand(command);
					
					for (std::vector<NativeString>::iterator it = command.begin(); it != command.end(); it++) {
						if (!it->isEmpty()) {
							commandLine = commandLine + " " + *it;
						}
					}
					
					if (commandLine.isEmpty()) {
						throw NativeException(className, "createNativeProcess", ILLEGAL_ARGUMENT_EXCEPTION, "The command list is empty.");
					}
					
					WindowsFile workDirFile(builder.getDirectory());
					workDirFile.createDirectories();
					NativeString currentDirectory = workDirFile.getAbsolutePath();

					STARTUPINFO startUpInfo;
					memset(&startUpInfo, 0, sizeof(STARTUPINFO));
					startUpInfo.cb = sizeof(STARTUPINFO);
					startUpInfo.dwFlags = STARTF_USESTDHANDLES;
					
					SECURITY_ATTRIBUTES securityAttributes;
					memset(&securityAttributes, 0, sizeof(SECURITY_ATTRIBUTES));
					securityAttributes.nLength = sizeof(SECURITY_ATTRIBUTES);
					securityAttributes.bInheritHandle = true;
					
					HANDLE currentProcessHandle = GetCurrentProcess();
					
					NativeProcessBuilderRedirect redirectInput = builder.getRedirectInput();
					HANDLE inputStreamHandle = INVALID_HANDLE_VALUE;
					HANDLE inputStreamPipeWriteHandle = INVALID_HANDLE_VALUE;
					
					switch (redirectInput.getType()) {
						case INHERIT:
							inputStreamHandle = GetStdHandle(STD_INPUT_HANDLE);
							break;
						case PIPE:
							if (!CreatePipe(&inputStreamHandle, &inputStreamPipeWriteHandle, &securityAttributes, 0)) {
								throw NativeException(className, "createNativeProcess", SYSTEM_EXCEPTION, "Failed to create the Input Stream Pipe for the child process.", GetLastError());
							}
							if (!SetHandleInformation(inputStreamPipeWriteHandle, HANDLE_FLAG_INHERIT, 0)) {
								CloseHandle(inputStreamPipeWriteHandle);
								CloseHandle(inputStreamHandle);
								throw NativeException(className, "createNativeProcess", SYSTEM_EXCEPTION, "Failed To disable Handle Inherit Flag on the Child Input Stream Pipe Write Handle", GetLastError());
							}
							break;
						case READ:
							NativeString inputStreamFilePath = WindowsFile(redirectInput.getFile()).getAbsolutePath();
							HANDLE inputStreamFileHandle = CreateFileA(inputStreamFilePath.getString().c_str(), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, &securityAttributes, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, null);
							if (inputStreamFileHandle == INVALID_HANDLE_VALUE) {
								throw NativeException(className, "createNativeProcess", SYSTEM_EXCEPTION, "Failed to open Input Stream Redirect File while creating a new process path = " + inputStreamFilePath, GetLastError());
							}
							DuplicateHandle(currentProcessHandle, inputStreamFileHandle, currentProcessHandle, &inputStreamHandle, 0, true, DUPLICATE_SAME_ACCESS);
							CloseHandle(inputStreamFileHandle);
							break;
					}
					startUpInfo.hStdInput = inputStreamHandle;
					
					NativeProcessBuilderRedirect redirectOutput = builder.getRedirectOutput();
					HANDLE outputStreamHandle = INVALID_HANDLE_VALUE;
					HANDLE outputStreamPipeReadHandle = INVALID_HANDLE_VALUE;
					
					switch (redirectOutput.getType()) {
						case INHERIT:
							outputStreamHandle = GetStdHandle(STD_OUTPUT_HANDLE);
							break;
						case PIPE:
							if (!CreatePipe(&outputStreamPipeReadHandle, &outputStreamHandle, &securityAttributes, 0)) {
								if (redirectInput.getType() != INHERIT) {
									CloseHandle(inputStreamHandle);
									if (inputStreamPipeWriteHandle != INVALID_HANDLE_VALUE) {
										CloseHandle(inputStreamPipeWriteHandle);
									}
								}
								throw NativeException(className, "createNativeProcess", SYSTEM_EXCEPTION, "Failed to create the Output Stream Pipe for the child process.", GetLastError());
							}
							if (!SetHandleInformation(outputStreamPipeReadHandle, HANDLE_FLAG_INHERIT, 0)) {
								CloseHandle(outputStreamPipeReadHandle);
								CloseHandle(outputStreamHandle);
								if (redirectInput.getType() != INHERIT) {
									CloseHandle(inputStreamHandle);
									if (inputStreamPipeWriteHandle != INVALID_HANDLE_VALUE) {
										CloseHandle(inputStreamPipeWriteHandle);
									}
								}
								throw NativeException(className, "createNativeProcess", SYSTEM_EXCEPTION, "Failed To disable Handle Inherit Flag on the Child Output Stream Pipe Read Handle", GetLastError());
							}
							break;
						case WRITE:
						case APPEND:
							const DWORD access = redirectOutput.getType() == APPEND ? (FILE_GENERIC_WRITE & ~FILE_WRITE_DATA) : GENERIC_WRITE;
							const DWORD disposition = redirectOutput.getType() == APPEND ? OPEN_ALWAYS : CREATE_ALWAYS;
							WindowsFile outputStreamFile(redirectOutput.getFile());
							WindowsFile(outputStreamFile.getParentPath()).createDirectories();
							NativeString outputStreamFilePath = outputStreamFile.getAbsolutePath();
							HANDLE outputStreamFileHandle = CreateFileA(outputStreamFilePath.getString().c_str(), access, FILE_SHARE_READ | FILE_SHARE_WRITE, &securityAttributes, disposition, FILE_ATTRIBUTE_NORMAL, null);
							if (outputStreamFileHandle == INVALID_HANDLE_VALUE) {
								if (redirectInput.getType() != INHERIT) {
									CloseHandle(inputStreamHandle);
									if (inputStreamPipeWriteHandle != INVALID_HANDLE_VALUE) {
										CloseHandle(inputStreamPipeWriteHandle);
									}
								}
								throw NativeException(className, "createNativeProcess", SYSTEM_EXCEPTION, "Failed to open Output Stream Redirect File while creating a new process path = " + outputStreamFilePath, GetLastError());
							}
							DuplicateHandle(currentProcessHandle, outputStreamFileHandle, currentProcessHandle, &outputStreamHandle, 0, true, DUPLICATE_SAME_ACCESS);
							CloseHandle(outputStreamFileHandle);
							break;
					}
					startUpInfo.hStdOutput = outputStreamHandle;
					
					NativeProcessBuilderRedirect redirectError = builder.getRedirectError();
					HANDLE errorStreamHandle = INVALID_HANDLE_VALUE;
					HANDLE errorStreamPipeReadHandle = INVALID_HANDLE_VALUE;
					
					if (builder.isRedirectErrorStreamToOutputStream()) {
						errorStreamHandle = outputStreamHandle;
					} else {
						switch (redirectError.getType()) {
							case INHERIT:
								errorStreamHandle = GetStdHandle(STD_ERROR_HANDLE);
								break;
							case PIPE:
								if (!CreatePipe(&errorStreamPipeReadHandle, &errorStreamHandle, &securityAttributes, 0)) {
									if (redirectInput.getType() != INHERIT) {
										CloseHandle(inputStreamHandle);
										if (inputStreamPipeWriteHandle != INVALID_HANDLE_VALUE) {
											CloseHandle(inputStreamPipeWriteHandle);
										}
									}
									if (redirectOutput.getType() != INHERIT) {
										CloseHandle(outputStreamHandle);
										if (outputStreamPipeReadHandle != INVALID_HANDLE_VALUE) {
											CloseHandle(outputStreamPipeReadHandle);
										}
									}
									throw NativeException(className, "createNativeProcess", SYSTEM_EXCEPTION, "Failed to create the Error Stream Pipe for the child process.", GetLastError());
								}
								if (!SetHandleInformation(errorStreamPipeReadHandle, HANDLE_FLAG_INHERIT, 0)) {
									CloseHandle(errorStreamPipeReadHandle);
									CloseHandle(errorStreamHandle);
									if (redirectInput.getType() != INHERIT) {
										CloseHandle(inputStreamHandle);
										if (inputStreamPipeWriteHandle != INVALID_HANDLE_VALUE) {
											CloseHandle(inputStreamPipeWriteHandle);
										}
									}
									if (redirectOutput.getType() != INHERIT) {
										CloseHandle(outputStreamHandle);
										if (outputStreamPipeReadHandle != INVALID_HANDLE_VALUE) {
											CloseHandle(outputStreamPipeReadHandle);
										}
									}
									throw NativeException(className, "createNativeProcess", SYSTEM_EXCEPTION, "Failed To disable Handle Inherit Flag on the Child Error Stream Pipe Read Handle", GetLastError());
								}
								break;
							case WRITE:
							case APPEND:
								const DWORD access = redirectError.getType() == APPEND ? (FILE_GENERIC_WRITE & ~FILE_WRITE_DATA) : GENERIC_WRITE;
								const DWORD disposition = redirectError.getType() == APPEND ? OPEN_ALWAYS : CREATE_ALWAYS;
								WindowsFile errorStreamFile(redirectError.getFile());
								WindowsFile(errorStreamFile.getParentPath()).createDirectories();
								NativeString errorStreamFilePath = errorStreamFile.getAbsolutePath();
								HANDLE errorStreamFileHandle = CreateFileA(errorStreamFilePath.getString().c_str(), access, FILE_SHARE_READ | FILE_SHARE_WRITE, &securityAttributes, disposition, FILE_ATTRIBUTE_NORMAL, null);
								if (errorStreamFileHandle == INVALID_HANDLE_VALUE) {
									if (redirectInput.getType() != INHERIT) {
										CloseHandle(inputStreamHandle);
										if (inputStreamPipeWriteHandle != INVALID_HANDLE_VALUE) {
											CloseHandle(inputStreamPipeWriteHandle);
										}
									}
									if (redirectOutput.getType() != INHERIT) {
										CloseHandle(outputStreamHandle);
										if (outputStreamPipeReadHandle != INVALID_HANDLE_VALUE) {
											CloseHandle(outputStreamPipeReadHandle);
										}
									}
									throw NativeException(className, "createNativeProcess", SYSTEM_EXCEPTION, "Failed to open Error Stream Redirect File while creating a new process path = " + errorStreamFilePath, GetLastError());
								}
								DuplicateHandle(currentProcessHandle, errorStreamFileHandle, currentProcessHandle, &errorStreamHandle, 0, true, DUPLICATE_SAME_ACCESS);
								CloseHandle(errorStreamFileHandle);
								break;
						}
					}
					startUpInfo.hStdError = errorStreamHandle;
					
					std::map<NativeString, NativeString> env;
					if (builder.isInheritEnvironment()) {
						WindowsUtils::getEnv(env);
					}
					builder.getEnvironment(env);
					
					int size = 1024;
					int index = 0;
					char* environment = new char[size];
					memset(environment, 0, size);
					
					for (std::map<NativeString, NativeString>::iterator it = env.begin(); it != env.end(); it++) {

						NativeString key = it->first.trim();
						NativeString value = it->second.trim();

						jint requiredSpace = key.length() + value.length() + 3; // '=' & \0 env end & \0 possible envs end

						if ((size - index) < requiredSpace) {
							jint newSize = size;
							while (newSize < (size + requiredSpace)) {
								newSize += 1024;
							}

							char* newEnvironment = new char[newSize];
							memset(newEnvironment, 0, newSize);
							memcpy(newEnvironment, environment, size);

							size = newSize;
							delete[] environment;

							environment = newEnvironment;
						}

						memcpy(environment + index, key.getString().c_str(), key.length());
						index += key.length();

						environment[index++] = '=';

						memcpy(environment + index, value.getString().c_str(), value.length());
						index += value.length();

						index++; // for the \0
					}
					
					index++; // for the envs \0

					PROCESS_INFORMATION processInformation;
					memset(&processInformation, 0, sizeof(PROCESS_INFORMATION));



					if (!CreateProcessA(NULL, (LPSTR)(commandLine.trim().getString().c_str()), &securityAttributes, &securityAttributes, true, CREATE_NEW_PROCESS_GROUP, (void *) environment, currentDirectory.getString().c_str(), &startUpInfo,
							&processInformation)) {

						if (redirectInput.getType() != INHERIT) {
							CloseHandle(inputStreamHandle);
							if (inputStreamPipeWriteHandle != INVALID_HANDLE_VALUE) {
								CloseHandle(inputStreamPipeWriteHandle);
							}
						}
						if (redirectOutput.getType() != INHERIT) {
							CloseHandle(outputStreamHandle);
							if (outputStreamPipeReadHandle != INVALID_HANDLE_VALUE) {
								CloseHandle(outputStreamPipeReadHandle);
							}
						}
						if (!builder.isRedirectErrorStreamToOutputStream() && (redirectError.getType() != INHERIT)) {
							CloseHandle(errorStreamHandle);
							if (errorStreamPipeReadHandle != INVALID_HANDLE_VALUE) {
								CloseHandle(errorStreamPipeReadHandle);
							}
						}
						delete environment;
						throw NativeException(className, "createNativeProcess", SYSTEM_EXCEPTION, "Could not create a new process on Windows machine with command = " + commandLine, GetLastError());
					}
					
					CloseHandle(processInformation.hThread);
					CloseHandle(processInformation.hProcess);

					if (redirectInput.getType() != INHERIT) {
						CloseHandle(inputStreamHandle);
					}
					if (redirectOutput.getType() != INHERIT) {
						CloseHandle(outputStreamHandle);
					}
					if (!builder.isRedirectErrorStreamToOutputStream() && (redirectError.getType() != INHERIT)) {
						CloseHandle(errorStreamHandle);
					}
					
					delete environment;
					
					NativeProcess * process = new WindowsProcess(processInformation.dwProcessId, ZwQueryInformationProcess);
					NativeOutputStream * inputStream = redirectInput.getType() == PIPE ? new WindowsFileOutputStream(WindowsFileDescriptor(inputStreamPipeWriteHandle)) : null;
					NativeInputStream * outputStream = redirectOutput.getType() == PIPE ? new WindowsFileInputStream(WindowsFileDescriptor(outputStreamPipeReadHandle)) : null;
					NativeInputStream * errorStream = !builder.isRedirectErrorStreamToOutputStream() && (redirectError.getType() == PIPE) ? new WindowsFileInputStream(WindowsFileDescriptor(errorStreamPipeReadHandle)) : null;
					return NativeForkedProcess(process, inputStream, outputStream, errorStream);
				}

			}
		}
	}
}
