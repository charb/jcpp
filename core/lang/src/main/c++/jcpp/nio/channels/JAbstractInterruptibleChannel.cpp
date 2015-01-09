#include "jcpp/nio/channels/JAbstractInterruptibleChannel.h"

namespace jcpp {
	namespace nio {
		namespace channels {

		JAbstractInterruptibleChannel::JAbstractInterruptibleChannel() {
			closeLock = new JObject();
			open = true;
			interrupted = false;
		}

		void JAbstractInterruptibleChannel::close() {
			synchronized(closeLock,
				if (!open)
					return;
				open = false;
				implCloseChannel();
			);
		}

		jbool JAbstractInterruptibleChannel::isOpen() {
			return open;
		}

		void JAbstractInterruptibleChannel::begin() {
			//TODO
		}

		void JAbstractInterruptibleChannel::end(jbool completed) {
			//TODO
		}

		}
	}
}

