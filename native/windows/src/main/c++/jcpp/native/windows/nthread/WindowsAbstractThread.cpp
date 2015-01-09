#include "jcpp/native/windows/nthread/WindowsMainThread.h"
#include "jcpp/native/api/NativeException.h"
#include <windows.h>
#include <DbgHelp.h>
#include <vector>
#include <string>

using namespace jcpp::native::api::nthread;


namespace jcpp {
	namespace native {
		namespace windows {
			namespace nthread {

			NativeString WindowsAbstractThread::className("jcpp::native::windows::thread::WindowsAbstractThread");

			WindowsAbstractThread::WindowsAbstractThread(NativeRunnable * runnable) :
				NativeThread(runnable), mutex(), priority(NORMAL), thread(0), name() {
			}

			NativeString WindowsAbstractThread::getName() {
				ScopedLock synchronize(mutex);
				return name;
			}

			void WindowsAbstractThread::setName(NativeString& newName) {
				ScopedLock synchronize(mutex);
				name = newName;
			}

			void WindowsAbstractThread::sleep(jlong milliseconds) {
				Sleep(DWORD(milliseconds));
			}

			void WindowsAbstractThread::yield() {
				Sleep(0);
			}

			Priority WindowsAbstractThread::getPriority() {
				ScopedLock synchronize(mutex);
				return priority;
			}

			void WindowsAbstractThread::suspend() {
				if (!isRunning()) {
					throw NativeException(className, "suspend", SYSTEM_EXCEPTION, "Thread is not running to suspend!");
				}
				if (SuspendThread(thread) < 0) {

					std::string message = "Failed to Suspend Thread ";
					message += name.getString();
					message += " Last Error Code = ";
					message += GetLastError();

					throw NativeException(className, "suspend", SYSTEM_EXCEPTION, message);
				}
			}

			void WindowsAbstractThread::resume() {
				if (!isRunning()) {
					throw NativeException(className, "resume", SYSTEM_EXCEPTION, "Thread is not running to resume!");
				}
				if (ResumeThread(thread) < 0) {
					std::string message = "Failed to Resume Thread ";
					message += name.getString();
					message += " Last Error Code = ";
					message += GetLastError();

					throw NativeException(className, "resume", SYSTEM_EXCEPTION, message);
				}
			}


			void WindowsAbstractThread::getStackTrace(std::vector<NativeStackTraceElement> &stackTrace) {
				if(!isRunning()) {
					return;
				}

				const int STACKWALK_MAX_NAMELEN = 1024;

				HANDLE process = GetCurrentProcess();
				CONTEXT context;
				STACKFRAME64 stackFrame;
				IMAGEHLP_LINE64 line;
				SYMBOL_INFO *symbol;
				DWORD arch;

				memset(&context, 0, sizeof(CONTEXT));
				context.ContextFlags = CONTEXT_FULL;
				RtlCaptureContext(&context);

				memset(&stackFrame, 0, sizeof(stackFrame));

			#ifdef _M_IX86
				arch = IMAGE_FILE_MACHINE_I386;
				stackFrame.AddrPC.Offset = context.Eip;
				stackFrame.AddrPC.Mode = AddrModeFlat;
				stackFrame.AddrFrame.Offset = context.Ebp;
				stackFrame.AddrFrame.Mode = AddrModeFlat;
				stackFrame.AddrStack.Offset = context.Esp;
				stackFrame.AddrStack.Mode = AddrModeFlat;
			#elif _M_X64
				arch = IMAGE_FILE_MACHINE_AMD64;
				stackFrame.AddrPC.Offset = context.Rip;
				stackFrame.AddrPC.Mode = AddrModeFlat;
				stackFrame.AddrFrame.Offset = context.Rsp;
				stackFrame.AddrFrame.Mode = AddrModeFlat;
				stackFrame.AddrStack.Offset = context.Rsp;
				stackFrame.AddrStack.Mode = AddrModeFlat;
			#elif _M_IA64
				arch = IMAGE_FILE_MACHINE_IA64;
				stackFrame.AddrPC.Offset = context.StIIP;
				stackFrame.AddrPC.Mode = AddrModeFlat;
				stackFrame.AddrFrame.Offset = context.IntSp;
				stackFrame.AddrFrame.Mode = AddrModeFlat;
				stackFrame.AddrBStore.Offset = context.RsBSP;
				stackFrame.AddrBStore.Mode = AddrModeFlat;
				stackFrame.AddrStack.Offset = context.IntSp;
				stackFrame.AddrStack.Mode = AddrModeFlat;
			#else
			# error "Platform not supported!"
			#endif

				symbol = (SYMBOL_INFO *)calloc(1, sizeof(SYMBOL_INFO) + STACKWALK_MAX_NAMELEN + 1);
				symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
				symbol->MaxNameLen = STACKWALK_MAX_NAMELEN;

				memset(&line, 0, sizeof(line));
				line.SizeOfStruct = sizeof(line);

				//init
				DWORD options = SymGetOptions();
				SymSetOptions(options |
					SYMOPT_LOAD_LINES |
					SYMOPT_FAIL_CRITICAL_ERRORS |
					SYMOPT_UNDNAME |
					SYMOPT_DEBUG);
				if (!SymInitialize(process,NULL,TRUE)){
					throw NativeException(className, "getStackTrace",SYSTEM_EXCEPTION,"SymInitialize() failed");
				}

				stackTrace.clear();
				for (int frameNum=0; ;frameNum++)
				{
					//getting the stack trace
					if (!StackWalk64(arch,process,thread,&stackFrame,&context,NULL,SymFunctionTableAccess64,SymGetModuleBase64,NULL)){
						break;
					}

					char methodName[255];
					char fileName[1024];
					int lineNumber;
					if (stackFrame.AddrPC.Offset != 0){
						//getting Name
						DWORD64 offset_from_symbol = 0;
						if (SymFromAddr(process,stackFrame.AddrPC.Offset,&offset_from_symbol, symbol)){
							sprintf(methodName,"%s", symbol->Name);
						}
						else{
							strcpy(methodName,"(Null)");
						}

						//getting the line
						DWORD offset_from_line = 0;
						if (SymGetLineFromAddr64(process,stackFrame.AddrPC.Offset,&offset_from_line,&line)){
							lineNumber = line.LineNumber;
							sprintf(fileName,"%s",line.FileName);
						}
						else{
							lineNumber = 0;
							strcpy(fileName,"(Null)");
						}
					}


					stackTrace.push_back(NativeStackTraceElement(NativeString(fileName),NativeString(methodName),lineNumber));
				}

			}


			}
		}
	}
}
