#include "jcpp/lang/jmx/JAttribute.h";
#include "jcpp/lang/JString.h"
#include "jcpp/lang/JException.h"

namespace jcpp{
	namespace lang{
		namespace jmx{

			JAttribute::JAttribute():JObject(JAttribute::getClazz()){
				this->name = null;
			}

			JAttribute::JAttribute(JString* name, JObject* value) : JObject(JAttribute::getClazz()){
				if(name == null){
					throw new JException(new JString("Attribute name cannot be null"));
				}
				this->name = name;
				this->value = value;
			}

			JString* JAttribute::getName(){
				return this->name;
			}

			JObject* JAttribute::getValue(){
				return this->value;
			}

			JAttribute::~JAttribute(){
			}

		}
	}
}
