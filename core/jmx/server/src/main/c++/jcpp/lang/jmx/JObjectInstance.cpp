#include "jcpp/lang/jmx/JObjectInstance.h";


namespace jcpp{
	namespace lang{
		namespace jmx{


			JObjectInstance::JObjectInstance():JObject(JObjectInstance::getClazz()){
			}

			JObjectInstance::~JObjectInstance(){
			}

		}
	}
}
