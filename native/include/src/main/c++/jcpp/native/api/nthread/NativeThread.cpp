#include "jcpp/native/api/nthread/NativeThread.h"
#include "jcpp/native/api/nthread/NativeThreadFactory.h"

namespace jcpp {
	namespace native {
		namespace api {
			namespace nthread {

				NativeThread::NativeThread(NativeRunnable * runnable) :
						storage(new NativeThreadLocalStorage()), runnable(runnable), attachment(null), gcThreadInfo(null), deleteOnFinish(false), state(NTH_NEW) {
				}

				NativeThread::~NativeThread() {
					runnable = null;
					delete storage;
					storage = null;
					NativeThreadFactory::getInstance()->removeThread(this);
				}

				NativeThreadLocalStorage * NativeThread::getStorage() {
					return storage;
				}


				void NativeThread::setAttachment(void* attach) {
					attachment = attach;
				}

				void* NativeThread::getAttachment() {
					return attachment;
				}

				void NativeThread::setGcThreadInfo(void* threadInfo) {
					gcThreadInfo = threadInfo;
				}

				void* NativeThread::getGcThreadInfo() {
					return gcThreadInfo;
				}

				void NativeThread::setDeleteOnFinish(jbool _deleteOnFinish) {
					deleteOnFinish = _deleteOnFinish;
				}

				jbool NativeThread::isDeleteOnFinish() {
					return deleteOnFinish;
				}

				ThreadState NativeThread::getState() {
					return state;
				}

			}
		}
	}
}
