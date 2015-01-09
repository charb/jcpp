#include "jcpp/native/api/NativeException.h"
#include "jcpp/native/windows/process/WindowsProcess.h"
#include "jcpp/native/api/NativeException.h"
#include "jcpp/native/windows/WindowsUtils.h"

#include <stdlib.h>
#include <TlHelp32.h>
#include <psapi.h>

using namespace jcpp::native::windows;
using namespace jcpp::native::api;
using namespace jcpp::native::api::process;

typedef struct _CURDIR {
	UNICODE_STRING DosPath;
	HANDLE Handle;
} CURDIR, *PCURDIR;

typedef struct _RTL_DRIVE_LETTER_CURDIR {
	WORD Flags;
	WORD Length;
	DWORD TimeStamp;
	UNICODE_STRING DosPath;
} RTL_DRIVE_LETTER_CURDIR, *PRTL_DRIVE_LETTER_CURDIR;

typedef struct _PROCESS_PARAMETERS {
	ULONG MaximumLength;
	ULONG Length;
	ULONG Flags; // PROCESS_PARAMETERS_NORMALIZED
	ULONG DebugFlags;
	HANDLE ConsoleHandle;
	ULONG ConsoleFlags;
	HANDLE StandardInput;
	HANDLE StandardOutput;
	HANDLE StandardError;
	CURDIR CurrentDirectory;
	UNICODE_STRING DllPath;
	UNICODE_STRING ImagePathName;
	UNICODE_STRING CommandLine;
	PWSTR Environment;
	ULONG StartingX;
	ULONG StartingY;
	ULONG CountX;
	ULONG CountY;
	ULONG CountCharsX;
	ULONG CountCharsY;
	ULONG FillAttribute;
	ULONG WindowFlags;
	ULONG ShowWindowFlags;
	UNICODE_STRING WindowTitle;
	UNICODE_STRING Desktop;
	UNICODE_STRING ShellInfo;
	UNICODE_STRING RuntimeInfo;
	RTL_DRIVE_LETTER_CURDIR CurrentDirectores[32];
} PROCESS_PARAMETERS, *PPROCESS_PARAMETERS;

namespace jcpp {
	namespace native {
		namespace windows {
			namespace process {

				NativeString WindowsProcess::className("jcpp::native::windows::process::WindowsProcess");

				WindowsProcess::WindowsProcess(DWORD pid, PZWQUERYINFORMATIONPROCESS ZwQueryInformationProcess) :
						pid(pid), ZwQueryInformationProcess(ZwQueryInformationProcess), processFinished(false), exitValue(0) {
				}

				WindowsProcess::~WindowsProcess() {
				}

				NativeString WindowsProcess::getPid() {
					char buf[20];
					_itoa_s(pid, buf, 20, 10);
					return NativeString(buf);
				}

				void WindowsProcess::getProcessTree(std::vector<NativeString>& tree) {
					char buf[20];
					_itoa_s(pid, buf, 20, 10);

					PROCESSENTRY32 processEntry;
					memset(&processEntry, 0, sizeof(processEntry));
					processEntry.dwSize = sizeof(processEntry);

					int currentPid = pid;
					jbool processFound = true;
					HANDLE snapshotHandle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, -1);
					while (processFound && (currentPid != 0)) {
						processFound = false;
						if (Process32First(snapshotHandle, &processEntry)) {
							do {
								if (processEntry.th32ProcessID == currentPid) {
									int parentPid = processEntry.th32ParentProcessID;
									_itoa_s(parentPid, buf, 20, 10);
									tree.push_back(NativeString(buf));
									currentPid = parentPid;
									processFound = true;
									break;
								}
							} while (Process32Next(snapshotHandle, &processEntry));
						}
					}
					CloseHandle(snapshotHandle);
				}

				NativeString WindowsProcess::getCmd() {
					NativeString strPID = getPid();
					HANDLE handle = OpenProcess(PROCESS_VM_READ | PROCESS_QUERY_INFORMATION, false, pid);
					if (handle == null) {
						throw NativeException(className, "getCmd", SYSTEM_EXCEPTION, "Failed to Open Process Handle of Process id = " + strPID, GetLastError());
					}

					PROCESS_BASIC_INFORMATION processBasicInformation;
					ULONG returnLength = 0;

					NTSTATUS status = ZwQueryInformationProcess(handle, ProcessBasicInformation, &processBasicInformation, sizeof(processBasicInformation), &returnLength);
					if (status < 0) {
						CloseHandle(handle);
						throw NativeException(className, "getCmd", SYSTEM_EXCEPTION, "Failed to call ZwQueryInformationProcess on the process handle of Process id = " + strPID);
					}
					PEB peb;
					if (!ReadProcessMemory(handle, processBasicInformation.PebBaseAddress, &peb, sizeof(peb), NULL)) {
						CloseHandle(handle);
						throw NativeException(className, "getCmd", SYSTEM_EXCEPTION, "Could not read process memory of Process id = " + strPID, GetLastError());
					}
					PROCESS_PARAMETERS process_parameters;
					if (!ReadProcessMemory(handle, peb.ProcessParameters, &process_parameters, sizeof(process_parameters), NULL)) {
						throw NativeException(className, "getCmd", SYSTEM_EXCEPTION, "Could not read process memory of Process id = " + strPID, GetLastError());
					}
					WCHAR * buf = new WCHAR[process_parameters.CommandLine.Length / 2 + 1];
					if (!ReadProcessMemory(handle, process_parameters.CommandLine.Buffer, buf, process_parameters.CommandLine.Length, null)) {
						throw NativeException(className, "getCmd", SYSTEM_EXCEPTION, "Could not read process memory while reading the command line of Process id = " + strPID, GetLastError());
					}
					buf[process_parameters.CommandLine.Length / 2] = (WCHAR) 0;
					CloseHandle(handle);
					return NativeString(buf);
				}

				void WindowsProcess::getEnvironment(std::map<NativeString, NativeString>& environment) {
					NativeString strPID = getPid();
					HANDLE handle = OpenProcess(PROCESS_VM_READ | PROCESS_QUERY_INFORMATION, false, pid);
					if (handle == null) {
						throw NativeException(className, "getEnvironment", SYSTEM_EXCEPTION, "Failed to Open Process Handle of Process id = " + strPID, GetLastError());
					}

					PROCESS_BASIC_INFORMATION processBasicInformation;
					ULONG returnLength = 0;

					NTSTATUS status = ZwQueryInformationProcess(handle, ProcessBasicInformation, &processBasicInformation, sizeof(processBasicInformation), &returnLength);
					if (status < 0) {
						CloseHandle(handle);
						throw NativeException(className, "getEnvironment", SYSTEM_EXCEPTION, "Failed to call ZwQueryInformationProcess on the process handle of Process id = " + strPID);
					}
					PEB peb;
					if (!ReadProcessMemory(handle, processBasicInformation.PebBaseAddress, &peb, sizeof(peb), NULL)) {
						CloseHandle(handle);
						throw NativeException(className, "getEnvironment", SYSTEM_EXCEPTION, "Could not read process memory of Process id = " + strPID, GetLastError());
					}
					PROCESS_PARAMETERS process_parameters;
					if (!ReadProcessMemory(handle, peb.ProcessParameters, &process_parameters, sizeof(process_parameters), NULL)) {
						throw NativeException(className, "getCmd", SYSTEM_EXCEPTION, "Could not read process memory of Process id = " + strPID, GetLastError());
					}

					NativeString currentEnvKeyValue;
					WCHAR * buf = new WCHAR[512];
					WCHAR nullChar = (WCHAR) 0;

					jbool doubleNullFound = false;
					int offset = 0;
					while (!doubleNullFound) {
						memset(buf, 0, sizeof(WCHAR) * 512);
						if (!ReadProcessMemory(handle, process_parameters.Environment + offset, buf, sizeof(WCHAR) * 512, null)) {
							break;
						}
						offset += 512;

						int startIndex = 0;
						int nullCharIndex = -1;
						jbool nullCharFound = false;

						while(true) {
							for (int i = startIndex; i < 512; i++) {
								if (buf[i] == nullChar) {
									nullCharFound = true;
									nullCharIndex = i;
									break;
								}
							}

							if (nullCharFound) {
								nullCharFound = false;
								if(nullCharIndex == startIndex) {
									doubleNullFound = true;
									break;
								}

								NativeString envKeyValuePart(buf, startIndex, nullCharIndex - startIndex);
								currentEnvKeyValue += envKeyValuePart;

								int equalIndex = currentEnvKeyValue.indexOf('=');
								if (equalIndex > 0) {
									environment.insert(std::pair<NativeString, NativeString>(currentEnvKeyValue.substring(0, equalIndex), currentEnvKeyValue.substring(equalIndex + 1)));
								}

								currentEnvKeyValue = "";
								startIndex = nullCharIndex + 1;
							} else {
								currentEnvKeyValue += NativeString(buf, startIndex, 512 - startIndex);
								break;
							}
						}
					}

					CloseHandle(handle);
				}

				jint WindowsProcess::getExitValue() {
					if (!processFinished) {
						throw NativeException(className, "getExitValue", SYSTEM_EXCEPTION, "Process still did not finished. PID = " + getPid());
					}
					return exitValue;
				}

				NativeString WindowsProcess::getOwner() {
					NativeString strPID = getPid();
					HANDLE handle = OpenProcess(PROCESS_QUERY_INFORMATION, false, pid);
					if (handle == null) {
						throw NativeException(className, "getOwner", SYSTEM_EXCEPTION, "Failed to Open Process Handle of Process id = " + strPID, GetLastError());
					}
					HANDLE tokenHandle = NULL;
					if (!OpenProcessToken(handle, TOKEN_QUERY, &tokenHandle)) {
						CloseHandle(handle);
						throw NativeException(className, "getOwner", SYSTEM_EXCEPTION, "Could not open process token of Process id = " + strPID, GetLastError());
					}

					DWORD returnLength;
					void * buf = malloc(256);
					if (!GetTokenInformation(tokenHandle, TokenUser, buf, 300, &returnLength)) {
						delete[] buf;
						CloseHandle(tokenHandle);
						CloseHandle(handle);
						throw NativeException(className, "getOwner", SYSTEM_EXCEPTION, "Could not get token information of Process id = " + strPID, GetLastError());
					}

					TOKEN_USER * tokenUser = (TOKEN_USER *) buf;

					DWORD nameLength = 256;
					char* name = new char[nameLength];

					DWORD referencedDomainNameLength = 256;
					char* referencedDomainName = new char[referencedDomainNameLength];

					SID_NAME_USE nameUse;

					if (!LookupAccountSid(NULL, tokenUser->User.Sid, name, &nameLength, referencedDomainName, &referencedDomainNameLength, &nameUse)) {
						free(buf);
						delete name;
						delete referencedDomainName;
						CloseHandle(tokenHandle);
						CloseHandle(handle);
						throw NativeException(className, "getOwner", SYSTEM_EXCEPTION, "Failed to Lookup Account Sid to get the owner Process id = " + strPID, GetLastError());
					}

					NativeString owner = NativeString(referencedDomainName) + "\\" + NativeString(name);

					free(buf);
					delete name;
					delete referencedDomainName;
					CloseHandle(tokenHandle);
					CloseHandle(handle);

					return owner;
				}

				jlong WindowsProcess::getStartDate() {
					jdouble cpuUsage = -1;

					NativeString strPID = getPid();
					HANDLE handle = OpenProcess(PROCESS_QUERY_INFORMATION, false, pid);
					if (handle == null) {
						throw NativeException(className, "getStartDate", SYSTEM_EXCEPTION, "Failed to Open Process Handle of Process id = " + strPID, GetLastError());
					}

					FILETIME creationTime;
					FILETIME exitTime;
					FILETIME kernelTime;
					FILETIME userTime;
					if (!GetProcessTimes(handle, &creationTime, &exitTime, &kernelTime, &userTime)) {
						CloseHandle(handle);
						throw NativeException(className, "getStartDate", SYSTEM_EXCEPTION, "Failed to Get Process Times of Process id = " + strPID, GetLastError());
					}
					CloseHandle(handle);
					return WindowsUtils::fileTimeToJlong(creationTime);
				}

				NativeString WindowsProcess::getWorkingDirectory() {
					NativeString strPID = getPid();
					HANDLE handle = OpenProcess(PROCESS_VM_READ | PROCESS_QUERY_INFORMATION, false, pid);
					if (handle == null) {
						throw NativeException(className, "getWorkingDirectory", SYSTEM_EXCEPTION, "Failed to Open Process Handle of Process id = " + strPID, GetLastError());
					}

					PROCESS_BASIC_INFORMATION processBasicInformation;
					ULONG returnLength = 0;

					NTSTATUS status = ZwQueryInformationProcess(handle, ProcessBasicInformation, &processBasicInformation, sizeof(processBasicInformation), &returnLength);
					if (status < 0) {
						CloseHandle(handle);
						throw NativeException(className, "getWorkingDirectory", SYSTEM_EXCEPTION, "Failed to call ZwQueryInformationProcess on the process handle of Process id = " + strPID);
					}
					PEB peb;
					if (!ReadProcessMemory(handle, processBasicInformation.PebBaseAddress, &peb, sizeof(peb), NULL)) {
						CloseHandle(handle);
						throw NativeException(className, "getWorkingDirectory", SYSTEM_EXCEPTION, "Could not read process memory of Process id = " + strPID, GetLastError());
					}
					PROCESS_PARAMETERS process_parameters;
					if (!ReadProcessMemory(handle, peb.ProcessParameters, &process_parameters, sizeof(process_parameters), NULL)) {
						throw NativeException(className, "getWorkingDirectory", SYSTEM_EXCEPTION, "Could not read process memory of Process id = " + strPID, GetLastError());
					}
					WCHAR * buf = new WCHAR[process_parameters.CurrentDirectory.DosPath.Length / 2 + 1];
					if (!ReadProcessMemory(handle, process_parameters.CurrentDirectory.DosPath.Buffer, buf, process_parameters.CurrentDirectory.DosPath.Length, null)) {
						throw NativeException(className, "getWorkingDirectory", SYSTEM_EXCEPTION, "Could not read process memory while reading the working directory of Process id = " + strPID, GetLastError());
					}
					buf[process_parameters.CurrentDirectory.DosPath.Length / 2] = (WCHAR) 0;
					CloseHandle(handle);
					return NativeString(buf);
				}

				jint WindowsProcess::waitFor() {
					NativeString strPID = getPid();
					HANDLE handle = OpenProcess(SYNCHRONIZE | PROCESS_QUERY_INFORMATION, false, pid);
					if (handle == null) {
						throw NativeException(className, "waitFor", SYSTEM_EXCEPTION, "Failed to Open Process Handle of Process id = " + strPID, GetLastError());
					}

					WaitForSingleObject(handle, INFINITE);

					DWORD exitCode;
					if (!GetExitCodeProcess(handle, &exitCode)) {
						CloseHandle(handle);
						throw NativeException(className, "waitFor", SYSTEM_EXCEPTION, "Failed to Get the Exit Code of Process id = " + strPID, GetLastError());
					}
					CloseHandle(handle);

					processFinished = true;
					exitValue = exitCode;

					return exitCode;
				}

				void WindowsProcess::kill() {
					NativeString strPID = getPid();
					HANDLE handle = OpenProcess(PROCESS_TERMINATE | PROCESS_QUERY_INFORMATION, false, pid);
					if (handle == null) {
						throw NativeException(className, "kill", SYSTEM_EXCEPTION, "Failed to Open Process Handle of Process id = " + strPID, GetLastError());
					}
					if (!TerminateProcess(handle, 2)) {
						throw NativeException(className, "kill", SYSTEM_EXCEPTION, "Failed to kill Process id = " + strPID, GetLastError());
					}
					CloseHandle(handle);
				}

				jdouble WindowsProcess::getCpuUsage() {
					jdouble cpuUsage = -1;

					NativeString strPID = getPid();
					HANDLE handle = OpenProcess(PROCESS_QUERY_INFORMATION, false, pid);
					if (handle == null) {
						throw NativeException(className, "getCpuUsage", SYSTEM_EXCEPTION, "Failed to Open Process Handle of Process id = " + strPID, GetLastError());
					}

					FILETIME creationTime1;
					FILETIME exitTime1;
					FILETIME kernelTime1;
					FILETIME userTime1;
					if (!GetProcessTimes(handle, &creationTime1, &exitTime1, &kernelTime1, &userTime1)) {
						CloseHandle(handle);
						throw NativeException(className, "getCpuUsage", SYSTEM_EXCEPTION, "Failed to Get Process Times of Process id = " + strPID, GetLastError());
					}
					jlong l1 = WindowsUtils::getCurrentTimeMillis();
					Sleep(1000);
					FILETIME creationTime2;
					FILETIME exitTime2;
					FILETIME kernelTime2;
					FILETIME userTime2;
					if (!GetProcessTimes(handle, &creationTime2, &exitTime2, &kernelTime2, &userTime2)) {
						CloseHandle(handle);
						throw NativeException(className, "getCpuUsage", SYSTEM_EXCEPTION, "Failed to Get Process Times of Process id = " + strPID, GetLastError());
					}
					jlong l2 = WindowsUtils::getCurrentTimeMillis();
					jlong t1 = ((((jlong) kernelTime1.dwHighDateTime) << 32) + kernelTime1.dwLowDateTime) + ((((jlong) userTime1.dwHighDateTime) << 32) + userTime1.dwLowDateTime);
					jlong t2 = ((((jlong) kernelTime2.dwHighDateTime) << 32) + kernelTime2.dwLowDateTime) + ((((jlong) userTime2.dwHighDateTime) << 32) + userTime2.dwLowDateTime);
					jdouble cpuElapsed = ((jdouble) (t2 - t1)) / ((jdouble) 10000);

					SYSTEM_INFO systemInfo;
					GetNativeSystemInfo(&systemInfo);

					cpuUsage = cpuElapsed / ((jdouble) (l2 - l1)) / ((jdouble) systemInfo.dwNumberOfProcessors) * ((jdouble) 100);

					CloseHandle(handle);
					return cpuUsage;
				}

				jlong WindowsProcess::getRealMemoryUsage() {
					NativeString strPID = getPid();
					HANDLE handle = OpenProcess(PROCESS_QUERY_INFORMATION, false, pid);
					if (handle == null) {
						throw NativeException(className, "getRealMemoryUsage", SYSTEM_EXCEPTION, "Failed to Open Process Handle of Process id = " + strPID, GetLastError());
					}
					PROCESS_MEMORY_COUNTERS process_memory_counters;
					memset(&process_memory_counters, 0, sizeof(process_memory_counters));
					process_memory_counters.cb = sizeof(process_memory_counters);
					if (!GetProcessMemoryInfo(handle, &process_memory_counters, sizeof(process_memory_counters))) {
						throw NativeException(className, "getRealMemoryUsage", SYSTEM_EXCEPTION, "Could not get the Process Memory Info of Process id = " + strPID, GetLastError());
					}
					CloseHandle(handle);
					return process_memory_counters.WorkingSetSize;
				}

				jlong WindowsProcess::getVirtualMemoryUsage() {
					NativeString strPID = getPid();
					HANDLE handle = OpenProcess(PROCESS_QUERY_INFORMATION, false, pid);
					if (handle == null) {
						throw NativeException(className, "getVirtualMemoryUsage", SYSTEM_EXCEPTION, "Failed to Open Process Handle of Process id = " + strPID, GetLastError());
					}
					PROCESS_MEMORY_COUNTERS process_memory_counters;
					memset(&process_memory_counters, 0, sizeof(process_memory_counters));
					process_memory_counters.cb = sizeof(process_memory_counters);
					if (!GetProcessMemoryInfo(handle, &process_memory_counters, sizeof(process_memory_counters))) {
						throw NativeException(className, "getVirtualMemoryUsage", SYSTEM_EXCEPTION, "Could not get the Process Memory Info of Process id = " + strPID, GetLastError());
					}
					CloseHandle(handle);
					return process_memory_counters.QuotaPagedPoolUsage;
				}

			}
		}
	}
}
