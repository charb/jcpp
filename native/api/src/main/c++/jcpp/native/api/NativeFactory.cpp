#include "jcpp/native/api/NativeFactory.h"

#if defined (WIN32)

#include "jcpp/native/windows/WindowsSystem.h"
#include "jcpp/native/windows/file/WindowsFileFactory.h"
#include "jcpp/native/windows/nthread/WindowsThreadFactory.h"
#include "jcpp/native/windows/io/WindowsIOFactory.h"
#include "jcpp/native/windows/net/WindowsNetFactory.h"
#include "jcpp/native/windows/process/WindowsProcessFactory.h"
#include "jcpp/native/windows/library/WindowsLibraryFactory.h"

using namespace jcpp::native::windows;
using namespace jcpp::native::windows::file;
using namespace jcpp::native::windows::nthread;
using namespace jcpp::native::windows::io;
using namespace jcpp::native::windows::net;
using namespace jcpp::native::windows::process;
using namespace jcpp::native::windows::library;

#else

#include "jcpp/native/unixos/UnixSystem.h"
#include "jcpp/native/unixos/file/UnixFileFactory.h"
#include "jcpp/native/unixos/nthread/UnixThreadFactory.h"
#include "jcpp/native/unixos/io/UnixIOFactory.h"
#include "jcpp/native/unixos/net/UnixNetFactory.h"
#include "jcpp/native/unixos/process/UnixProcessFactory.h"
#include "jcpp/native/unixos/library/UnixLibraryFactory.h"

using namespace jcpp::native::unixos;
using namespace jcpp::native::unixos::file;
using namespace jcpp::native::unixos::nthread;
using namespace jcpp::native::unixos::io;
using namespace jcpp::native::unixos::net;
using namespace jcpp::native::unixos::process;
using namespace jcpp::native::unixos::library;

#endif

namespace jcpp {
	namespace native {
		namespace api {

			jbool NativeFactory::initialized = init();

			jbool NativeFactory::init() {
				NativeSystem * nativeSystem = null;
				NativeFileFactory * fileFactory = null;
				NativeThreadFactory * threadFactory = null;
				NativeIOFactory * ioFactory = null;
				NativeNetFactory * netFactory = null;
				NativeProcessFactory * processFactory = null;
				NativeLibraryFactory * libraryFactory = null;

#if defined (WIN32)
				nativeSystem = new WindowsSystem();
				fileFactory = new WindowsFileFactory();
				threadFactory = new WindowsThreadFactory();
				ioFactory = new WindowsIOFactory();
				netFactory = new WindowsNetFactory();
				processFactory = new WindowsProcessFactory();
				libraryFactory = new WindowsLibraryFactory();
#else
				nativeSystem = new UnixSystem();
				fileFactory = new UnixFileFactory();
				threadFactory = new UnixThreadFactory();
				ioFactory = new UnixIOFactory();
				netFactory = new UnixNetFactory();
				processFactory = new UnixProcessFactory();
				libraryFactory = new UnixLibraryFactory();
#endif

				NativeSystem::setInstance(nativeSystem);
				NativeFileFactory::setInstance(fileFactory);
				NativeThreadFactory::setInstance(threadFactory);
				NativeIOFactory::setInstance(ioFactory);
				NativeNetFactory::setInstance(netFactory);
				NativeProcessFactory::setInstance(processFactory);
				NativeLibraryFactory::setInstance(libraryFactory);

				return true;
			}

			NativeSystem * NativeFactory::getNativeSystem() {
				return NativeSystem::getInstance();
			}

			NativeFileFactory * NativeFactory::getNativeFileFactory() {
				return NativeFileFactory::getInstance();
			}

			NativeThreadFactory * NativeFactory::getNativeThreadFactory() {
				return NativeThreadFactory::getInstance();
			}

			NativeIOFactory * NativeFactory::getNativeIOFactory() {
				return NativeIOFactory::getInstance();
			}

			NativeNetFactory * NativeFactory::getNativeNetFactory() {
				return NativeNetFactory::getInstance();
			}

			NativeProcessFactory * NativeFactory::getNativeProcessFactory() {
				return NativeProcessFactory::getInstance();
			}

			NativeLibraryFactory * NativeFactory::getNativeLibraryFactory() {
				return NativeLibraryFactory::getInstance();
			}

		}
	}
}
