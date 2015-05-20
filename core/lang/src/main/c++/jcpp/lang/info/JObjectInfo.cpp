#include "jcpp/lang/info/JObjectInfo.h"

using namespace jcpp::util;

namespace jcpp {
	namespace lang {
		namespace info {

			JObjectInfo::JObjectInfo(JString *_className, JPrimitiveLong *_address) :
					className(_className), address(_address){
				references = new JHashSet();
			}

			JPrimitiveLong *JObjectInfo::getAddress(){
				return this->address;
			}

			JString *JObjectInfo::getClassName(){
				return this->className;
			}

			JSet *JObjectInfo::getReferences(){
				return this->references;
			}

			void JObjectInfo::addReference(JFieldInfo *reference){
				this->references->add(reference);
			}

			JObjectInfo::~JObjectInfo(){
			}

		}
	}
}
