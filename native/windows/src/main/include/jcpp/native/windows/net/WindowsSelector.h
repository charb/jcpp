#ifndef JCPP_NATIVE_WINDOWS_NET_WINDOWSSELECTOR
#define JCPP_NATIVE_WINDOWS_NET_WINDOWSSELECTOR

#include "jcpp/native/api/net/NativeSelector.h"

using namespace jcpp::native::api::net;
using namespace jcpp::native::api;

namespace jcpp {
	namespace native {
		namespace windows {
			namespace net {

				class JCPP_EXPORT WindowsSelector: public NativeSelector {

				private:
					WindowsSelector(const WindowsSelector&);
					WindowsSelector& operator =(const WindowsSelector&);

				public:
					WindowsSelector();
					virtual ~WindowsSelector();

				};

			}
		}
	}
}

#endif
