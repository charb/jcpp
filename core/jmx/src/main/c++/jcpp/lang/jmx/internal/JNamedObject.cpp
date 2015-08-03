#include "jcpp/lang/jmx/internal/JNamedObject.h"

namespace jcpp{
	namespace lang{
		namespace jmx{
			namespace internal{
				JNamedObject::JNamedObject(JDynamicMBean* object): JObject(JNamedObject::getClazz()){

				}

				JDynamicMBean* JNamedObject::getObject(){
					return null;
				}

				JNamedObject::~JNamedObject(){
				}
			}
		}
	}
}
