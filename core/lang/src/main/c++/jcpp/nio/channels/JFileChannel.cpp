#include "jcpp/nio/channels/JFileChannel.h"
#include "jcpp/nio/channels/JFileLock.h"
#include "jcpp/lang/JLong.h"

namespace jcpp {
	namespace nio {
		namespace channels {

		JFileChannel::JFileChannel(){
		}

		jlong JFileChannel::read(JPrimitiveObjectArray* dsts) {
			return read(dsts, 0, dsts->size());
		}

		jlong JFileChannel::write(JPrimitiveObjectArray* srcs) {
			return write(srcs, 0, srcs->size());
		}

		JFileLock* JFileChannel::lock() {
			return lock(0LL, JLong::MAX_VALUE, false);
		}

		JFileLock* JFileChannel::tryLock() {
			return tryLock(0LL, JLong::MAX_VALUE, false);
		}

		JFileChannel::~JFileChannel(){
		}

		}
	}
}

