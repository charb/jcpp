#include "jcpp/lang/info/JFieldInfo.h"
#include "jcpp/lang/info/JClassInfo.h"

namespace jcpp {
	namespace lang {
		namespace info {

			JFieldInfo::JFieldInfo( JString* _name, JPrimitiveLong *_address, jbool _bStaticField) : address(_address), name(_name), bStaticField(_bStaticField) {
			}

			JFieldInfo::JFieldInfo( JString* _name, JPrimitiveLong *_address) : address(_address), name(_name), bStaticField(false) {
						}

			JPrimitiveLong *JFieldInfo::getAddress(){
				return this->address;
			}

			JString *JFieldInfo::getName(){
				return this->name;
			}

			jbool JFieldInfo::isStaticField() {
				return bStaticField;
			}
			JFieldInfo::~JFieldInfo(){
			}
		}
	}
}

