#ifndef JCPP_NATIVE_API_NET_NATIVESELECTOR
#define JCPP_NATIVE_API_NET_NATIVESELECTOR


#include <set>
#include "jcpp/native/api/net/NativeSelectionKey.h"

namespace jcpp {
	namespace native {
		namespace api {
			namespace net {

				/*
				 * A multiplexor of NativeSelectableChannel objects.
				 */
				class JCPP_EXPORT NativeSelector {

					friend class NativeSelectionKey;

				private:
					NativeSelector(const NativeSelector&);
					NativeSelector& operator =(const NativeSelector&);

				protected:
					NativeSelector();

					virtual void removeSelectionKey(const NativeSelectionKey& key) = 0;
					virtual void addSelectionKey(const NativeSelectionKey& key) = 0;

				public:
					virtual ~NativeSelector();

					/*
					 * Gets all the registered selection keys with this selector
					 */
					virtual void keys(std::set<NativeSelectionKey>& keys) = 0;

					virtual void selectedKeys(std::set<NativeSelectionKey>& keys) = 0;

					/*
					 * Selects a set of keys whose corresponding channels are ready for I/O operations.
					 *
					 * This method performs a blocking selection operation. It returns only after at least one channel is selected,
					 * this selector's wakeup method is invoked, or the current thread is interrupted, whichever comes first.
					 */
					virtual jint select() = 0;

					/*
					 * Selects a set of keys whose corresponding channels are ready for I/O operations.
					 *
					 * This method performs a blocking selection operation. It returns only after at least one channel is selected,
					 * this selector's wakeup method is invoked, the current thread is interrupted, or the given timeout period expires, whichever comes first.
					 */
					virtual jint select(jlong timeout) = 0;

					/*
					 * Selects a set of keys whose corresponding channels are ready for I/O operations.
					 *
					 * This method performs a non-blocking selection operation. If no channels have become selectable since the previous selection operation
					 * then this method immediately returns zero.
					 *
					 * Invoking this method clears the effect of any previous invocations of the wakeup method.
					 */
					virtual jint selectNow() = 0;

					/*
					 * Causes the first selection operation that has not yet returned to return immediately.
					 *
					 * If another thread is currently blocked in an invocation of the select() or select(long) methods then that invocation will return immediately.
					 * If no selection operation is currently in progress then the next invocation of one of these methods will return immediately unless the selectNow()
					 * method is invoked in the meantime. In any case the value returned by that invocation may be non-zero. Subsequent invocations of the select() or select(long)
					 * methods will block as usual unless this method is invoked again in the meantime.
					 *
					 * Invoking this method more than once between two successive selection operations has the same effect as invoking it just once.
					 */
					virtual void wakeup() = 0;

					/*
					 * Closes this selector.
					 *
					 * If a thread is currently blocked in one of this selector's selection methods then it is interrupted as if by invoking the selector's wakeup method.
					 * Any uncancelled keys still associated with this selector are invalidated, their channels are deregistered, and any other resources associated with this selector are released.
					 *
					 * If this selector is already closed then invoking this method has no effect.
					 *
					 * After a selector is closed, any further attempt to use it, except by invoking this method or the wakeup method, will cause a NativeException (CLOSED_SELECTOR_EXCEPTION) to be thrown.
					 */
					virtual void close() = 0;

					/*
					 * Tells whether or not this selector is open.
					 */
					virtual jbool isOpen() const = 0;
				};

			}
		}
	}
}

#endif
