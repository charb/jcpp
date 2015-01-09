#ifndef JCPP_NATIVE_UNIXOS_NET_UNIXSELECTOR
#define JCPP_NATIVE_UNIXOS_NET_UNIXSELECTOR

#include "jcpp/native/api/net/NativeSelector.h"

using namespace jcpp::native::api::net;
using namespace jcpp::native::api;

namespace jcpp {
	namespace native {
		namespace unixos {
			namespace net {

				class JCPP_EXPORT UnixSelector: public NativeSelector {

				private:
					UnixSelector(const UnixSelector&);
					UnixSelector& operator =(const UnixSelector&);

				public:
					UnixSelector();
					virtual ~UnixSelector();

				};

			}
		}
	}
}

#endif
