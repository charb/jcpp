#include "jcpp/native/api/net/NativeSelectionKey.h"
#include "jcpp/native/api/net/NativeSelector.h"

namespace jcpp {
	namespace native {
		namespace api {
			namespace net {

				NativeSelectionKey::NativeSelectionKey(NativeSelector * selector, NativeSelectableChannel * channel, jint operations) :
						selector(selector), channel(channel), attachment(null), operations(operations), valid(true) {
					selector->addSelectionKey(*this);
				}

				NativeSelectionKey::~NativeSelectionKey() {
				}

				NativeSelectableChannel * NativeSelectionKey::getChannel() {
					return channel;
				}

				NativeSelector * NativeSelectionKey::getSelector() {
					return selector;
				}

				jint NativeSelectionKey::getInterestOps() {
					return operations;
				}

				void NativeSelectionKey::setInterestOps(jint ops) {
					operations = (ops & OP_ACCEPT) | (ops & OP_CONNECT) | (ops & OP_READ) | (ops & OP_WRITE);
				}

				jint NativeSelectionKey::getReadyOps() {
					// TODO;
					return 0;
				}

				jbool NativeSelectionKey::isValid() {
					return valid;
				}

				jbool NativeSelectionKey::isAcceptable() {
					return getReadyOps() & OP_ACCEPT;
				}

				jbool NativeSelectionKey::isConnectable() {
					return getReadyOps() & OP_CONNECT;
				}

				jbool NativeSelectionKey::isReadable() {
					return getReadyOps() & OP_READ;
				}

				jbool NativeSelectionKey::isWritable() {
					return getReadyOps() & OP_WRITE;
				}

				void NativeSelectionKey::cancel() {
					selector->removeSelectionKey(*this);
					// TODO;
				}

				void* NativeSelectionKey::setAttachment(void* att) {
					void * oldAttachment = attachment;
					attachment = att;
					return oldAttachment;
				}

				void* NativeSelectionKey::getAttachment() {
					return attachment;
				}

			}
		}
	}
}
