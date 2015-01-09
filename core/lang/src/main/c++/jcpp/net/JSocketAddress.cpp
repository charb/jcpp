#include "jcpp/net/JSocketAddress.h"
#include "jcpp/native/api/NativeFactory.h"
#include "jcpp/lang/JClass.h"

using namespace jcpp::native::api;
using namespace jcpp::lang;

namespace jcpp {
	namespace net {

		JSocketAddress::JSocketAddress(JClass* _class) : JObject(_class) {
		}

		JSocketAddress::~JSocketAddress() {
		}

	}
}
