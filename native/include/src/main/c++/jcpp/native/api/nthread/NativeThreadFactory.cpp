#include "jcpp/native/api/nthread/NativeThreadFactory.h"
#include "jcpp/native/api/nthread/ScopedLock.h"

namespace jcpp {
	namespace native {
		namespace api {
			namespace nthread {

				NativeThreadFactory * NativeThreadFactory::instance = null;

				NativeThreadFactory::NativeThreadFactory() :
						mutex(null), threads() {
				}

				NativeThreadFactory::~NativeThreadFactory() {
					delete mutex;
					mutex = null;
				}

				NativeThreadFactory * NativeThreadFactory::getInstance() {
					return instance;
				}

				void NativeThreadFactory::setInstance(NativeThreadFactory * instance) {
					NativeThreadFactory::instance = instance;
				}

				void NativeThreadFactory::getAllThreads(std::vector<NativeThread *>& vthreads) {
					ScopedLock lock(*mutex);
					vthreads.push_back(mainThread());
					for (std::vector<NativeThread *>::iterator it = threads.begin(); it != threads.end(); ++it) {
						vthreads.push_back(*it);
					}
				}

				void NativeThreadFactory::removeThread(NativeThread * thread) {
					ScopedLock lock(*mutex);
					for (std::vector<NativeThread *>::iterator it = threads.begin(); it != threads.end(); ++it) {
						if ((*it) == thread) {
							threads.erase(it);
							break;
						}
					}
				}

			}
		}
	}
}
