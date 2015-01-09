#include "jcpp/native/unixos/io/UnixFileDescriptor.h"

namespace jcpp {
	namespace native {
		namespace unixos {
			namespace io {

				UnixFileDescriptor::UnixFileDescriptor() :
						descriptor(-1) {
				}

				UnixFileDescriptor::UnixFileDescriptor(int descriptor) :
						descriptor(descriptor) {
				}

				UnixFileDescriptor::~UnixFileDescriptor() {
				}

				void UnixFileDescriptor::setDescriptor(int newDescriptor) {
					descriptor = newDescriptor;
				}

				int UnixFileDescriptor::getDescriptor() {
					return descriptor;
				}

			}
		}
	}
}

