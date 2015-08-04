#include "jcpp/lang/jmx/internal/JNamedObject.h"

namespace jcpp{
	namespace lang{
		namespace jmx{
			namespace internal{
				JNamedObject::JNamedObject(JDynamicMBean* object): JObject(JNamedObject::getClazz()){
					this->object = object;
				}

				JDynamicMBean* JNamedObject::getObject(){
					return object;
				}

				JNamedObject::~JNamedObject(){
				}
			}
		}
	}
}
