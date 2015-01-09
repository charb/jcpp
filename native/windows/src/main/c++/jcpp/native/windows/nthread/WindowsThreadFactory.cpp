#include "jcpp/native/windows/nthread/WindowsThreadFactory.h"
#include "jcpp/native/windows/nthread/WindowsMutex.h"
#include "jcpp/native/windows/nthread/WindowsCondition.h"
#include "jcpp/native/windows/nthread/WindowsThread.h"
#include "jcpp/native/windows/nthread/WindowsMainThread.h"
#include "jcpp/native/windows/nthread/WindowsThreadPointerStorage.h"
#include "jcpp/native/api/nthread/ScopedLock.h"

namespace jcpp {
	namespace native {
		namespace windows {
			namespace nthread {

				WindowsThreadFactory::WindowsThreadFactory() {
					mutex = createNativeMutex();
				}

				WindowsThreadFactory::~WindowsThreadFactory() {

				}

				NativeMutex * WindowsThreadFactory::createNativeMutex() {
					return new WindowsMutex();
				}

				NativeCondition * WindowsThreadFactory::createNativeCondition(NativeMutex * mutex) {
					return new WindowsCondition((WindowsMutex *) mutex);
				}

				NativeThread * WindowsThreadFactory::createNativeThread(NativeRunnable * runnable) {
					ScopedLock lock(*mutex);
					WindowsThread * thread = new WindowsThread(runnable);
					threads.push_back(thread);
					return thread;
				}

				NativeThread * WindowsThreadFactory::currentThread() {
					WindowsThread* current = WindowsThreadPointerStorage::getInstance()->get();
					return current == null ? mainThread() : current;
				}

				NativeThread * WindowsThreadFactory::mainThread() {
					return WindowsMainThread::getInstance();
				}

			}
		}
	}
}
