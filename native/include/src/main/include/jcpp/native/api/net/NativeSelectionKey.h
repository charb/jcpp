#ifndef JCPP_NATIVE_API_NET_NATIVESELECTIONKEY
#define JCPP_NATIVE_API_NET_NATIVESELECTIONKEY

#include "jcpp/native/api/NativeInclude.h"

namespace jcpp {
	namespace native {
		namespace api {
			namespace net {

				class NativeSelectableChannel;
				class NativeSelector;

				/*
				 * A token representing the registration of a SelectableChannel with a Selector.
				 */
				class JCPP_EXPORT NativeSelectionKey {

					friend class NativeSelectableChannel;

				private:
					NativeSelector * selector;
					NativeSelectableChannel * channel;
					void * attachment;
					jint operations;
					jbool valid;

				protected:
					NativeSelectionKey(NativeSelector * selector, NativeSelectableChannel * channel, jint operations);

				public:
					/*
					 * Operation-set bit for read operations.
					 *
					 * Suppose that a selection key's interest set contains OP_READ at the start of a selection operation. If the selector detects that the corresponding channel is ready for reading, has reached end-of-stream, has been remotely shut down for further reading, or has an error pending, then it will add OP_READ to the key's ready-operation set and add the key to its selected-key set.
					 */
					static const int OP_READ = 1;

					/*
					 * Operation-set bit for write operations.
					 *
					 * Suppose that a selection key's interest set contains OP_WRITE at the start of a selection operation. If the selector detects that the corresponding channel is ready for writing, has been remotely shut down for further writing, or has an error pending, then it will add OP_WRITE to the key's ready set and add the key to its selected-key set.
					 */
					static const int OP_WRITE = 2;

					/*
					 * Operation-set bit for socket-connect operations
					 *
					 * Suppose that a selection key's interest set contains OP_CONNECT at the start of a selection operation. If the selector detects that the corresponding socket channel is ready to complete its connection sequence, or has an error pending, then it will add OP_CONNECT to the key's ready set and add the key to its selected-key set.
					 */
					static const int OP_CONNECT = 4;

					/*
					 * Operation-set bit for socket-accept operations.
					 *
					 * Suppose that a selection key's interest set contains OP_ACCEPT at the start of a selection operation. If the selector detects that the corresponding server-socket channel is ready to accept another connection, or has an error pending, then it will add OP_ACCEPT to the key's ready set and add the key to its selected-key set.
					 */
					static const int OP_ACCEPT = 8;

					~NativeSelectionKey();

					/*
					 * Returns the channel for which this key was created. This method will continue to return the channel even after the key is cancelled.
					 */
					NativeSelectableChannel * getChannel();

					/*
					 * Returns the selector for which this key was created. This method will continue to return the selector even after the key is cancelled.
					 */
					NativeSelector * getSelector();

					/*
					 * Retrieves this key's interest set. It is guaranteed that the returned set will only contain operation bits that are valid for this key's channel.
					 */
					jint getInterestOps();

					/*
					 * Sets this key's interest set to the given value.
					 */
					void setInterestOps(jint ops);

					/*
					 * Retrieves this key's ready-operation set.
					 */
					jint getReadyOps();

					/*
					 * Tells whether or not this key is valid
					 *
					 * A key is valid upon creation and remains so until it is cancelled, its channel is closed, or its selector is closed.
					 */
					jbool isValid();

					/*
					 * Tests whether this key's channel is ready to accept a new socket connection.
					 * An invocation of this method of the form k.isAcceptable() behaves in exactly the same way as the expression k.readyOps() & OP_ACCEPT != 0
					 */
					jbool isAcceptable();

					/*
					 * Tests whether this key's channel has either finished, or failed to finish, its socket-connection operation.
					 * An invocation of this method of the form k.isConnectable() behaves in exactly the same way as the expression k.readyOps() & OP_CONNECT != 0
					 */
					jbool isConnectable();

					/*
					 * Tests whether this key's channel is ready for reading.
					 * An invocation of this method of the form k.isReadable() behaves in exactly the same way as the expression k.readyOps() & OP_READ != 0
					 */
					jbool isReadable();

					/*
					 * Tests whether this key's channel is ready for writing.
					 * An invocation of this method of the form k.isWritable() behaves in exactly the same way as the expression k.readyOps() & OP_WRITE != 0
					 */
					jbool isWritable();

					/*
					 * Requests that the registration of this key's channel with its selector be cancelled. Upon return the key will be invalid and will have been added to its selector's cancelled-key set.
					 * The key will be removed from all of the selector's key sets during the next selection operation.
					 * If this key has already been cancelled then invoking this method has no effect. Once cancelled, a key remains forever invalid.
					 */
					void cancel();

					/*
					 * Attaches the given object to this key.
					 * An attached object may later be retrieved via the attachment method. Only one object may be attached at a time;
					 * invoking this method causes any previous attachment to be discarded. The current attachment may be discarded by attaching null.
					 *
					 * Returns: The previously-attached object, if any, otherwise null
					 */
					void* setAttachment(void* object);

					/*
					 * Retrieves the current attachment.
					 */
					void* getAttachment();

				};

			}
		}
	}
}

#endif
