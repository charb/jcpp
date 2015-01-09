#ifndef JCPP_NATIVE_API_NET_NATIVESELECTABLECHANNEL
#define JCPP_NATIVE_API_NET_NATIVESELECTABLECHANNEL

#include "jcpp/native/api/net/NativeSelector.h"

namespace jcpp {
	namespace native {
		namespace api {
			namespace net {

				/*
				 * A channel that can be multiplexed via a Selector.
				 */
				class JCPP_EXPORT NativeSelectableChannel {

				private:
					NativeSelectableChannel(const NativeSelectableChannel&);
					NativeSelectableChannel& operator =(const NativeSelectableChannel&);

				protected:
					NativeSelectableChannel();

				public:
					virtual ~NativeSelectableChannel();

					/*
					 * Adjusts this channel's blocking mode.
					 *
					 * If this channel is registered with one or more selectors then an attempt to place it into blocking mode will cause an NativeException (ILLEGAL_BLOCKING_MODE_EXCEPTION) to be thrown.
					 * This method may be invoked at any time. The new blocking mode will only affect I/O operations that are initiated after this method returns.
					 * For some implementations this may require blocking until all pending I/O operations are complete. (??)
					 *
					 * If this method is invoked while another invocation of this method or of the register method is in progress then it will first block until the other operation is complete.
					 */
					virtual void configureBlocking(jbool block) = 0;

					/*
					 * Tells whether or not every I/O operation on this channel will block until it completes. A newly-created channel is always in blocking mode.
					 *
					 * If this channel is closed then the value returned by this method is not specified.
					 */
					virtual jbool isBlocking() const = 0;

					/*
					 * Tells whether or not this channel is currently registered with any selectors. A newly-created channel is not registered.
					 * Due to the inherent delay between key cancellation and channel deregistration, a channel may remain registered for some time after all of its keys have been cancelled.
					 *
					 * A channel may also remain registered for some time after it is closed.
					 */
					virtual jbool isRegistered() const = 0;

					/*
					 * Retrieves the key representing the channel's registration with the given selector.
					 */
					virtual NativeSelectionKey keyFor(const NativeSelector * selector) = 0;

					/*
					 * Registers this channel with the given selector, returning a selection key.
					 */
					virtual NativeSelectionKey registerChannel(NativeSelector * selector, jint ops) = 0;

					/*
					 * Registers this channel with the given selector, returning a selection key.
					 * If this channel is currently registered with the given selector then the selection key representing that registration is returned.
					 * The key's interest set will have been changed to ops, as if by invoking the interestOps(int) method. If the attachment argument is not null then the key's attachment will have been set to that value.
					 * A NativeException (CANCEL_KEY_EXCEPTION) will be thrown if the key has already been cancelled.
					 *
					 * Otherwise this channel has not yet been registered with the given selector, so it is registered and the resulting new key is returned.
					 * The key's initial interest set will be ops and its attachment will be attachment.
					 *
					 * This method may be invoked at any time. If this method is invoked while another invocation of this method or of the configureBlocking method is in progress then it will first block until the other operation is complete.
					 * This method will then synchronize on the selector's key set and therefore may block if invoked concurrently with another registration or selection operation involving the same selector.
					 *
					 * If this channel is closed while this operation is in progress then the key returned by this method will have been cancelled and will therefore be invalid.
					 */
					virtual NativeSelectionKey registerChannel(NativeSelector * selector, jint ops, void * attachment) = 0;

					/*
					 * Returns an operation set identifying this channel's supported operations. The bits that are set in this integer value denote exactly the operations that are valid for this channel.
					 */
					virtual jint validOps() const = 0;
					;

				};

			}
		}
	}
}

#endif
