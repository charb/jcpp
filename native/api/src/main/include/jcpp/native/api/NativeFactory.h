#ifndef JCPP_NATIVE_API_NATIVEFACTORY
#define JCPP_NATIVE_API_NATIVEFACTORY

#include "jcpp/native/api/NativeSystem.h"
#include "jcpp/native/api/file/NativeFileFactory.h"
#include "jcpp/native/api/nthread/NativeThreadFactory.h"
#include "jcpp/native/api/io/NativeIOFactory.h"
#include "jcpp/native/api/net/NativeNetFactory.h"
#include "jcpp/native/api/process/NativeProcessFactory.h"
#include "jcpp/native/api/library/NativeLibraryFactory.h"


using namespace jcpp::native::api::file;
using namespace jcpp::native::api::nthread;
using namespace jcpp::native::api::io;
using namespace jcpp::native::api::net;
using namespace jcpp::native::api::process;
using namespace jcpp::native::api::library;

namespace jcpp {
	namespace native {
		namespace api {

			class JCPP_EXPORT NativeFactory {

			private:
				static jbool initialized;
				static jbool init();

			public:

				static NativeSystem * getNativeSystem();

				static NativeFileFactory * getNativeFileFactory();

				static NativeThreadFactory * getNativeThreadFactory();

				static NativeIOFactory * getNativeIOFactory();

				static NativeNetFactory * getNativeNetFactory();

				static NativeProcessFactory * getNativeProcessFactory();

				static NativeLibraryFactory * getNativeLibraryFactory();
			};

		}
	}
}

#endif
