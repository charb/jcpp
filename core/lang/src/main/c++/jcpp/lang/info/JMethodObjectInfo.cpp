#include "jcpp/lang/info/JMethodObjectInfo.h"

namespace jcpp {
	namespace lang {
		namespace info {

			JMethodObjectInfo::JMethodObjectInfo(JPrimitiveLong* _address){
				address = _address;
			}

			JPrimitiveLong* JMethodObjectInfo::getAddress(){
				return address;
			}

			JMethodObjectInfo::~JMethodObjectInfo(){

			}
		}
	}
}
