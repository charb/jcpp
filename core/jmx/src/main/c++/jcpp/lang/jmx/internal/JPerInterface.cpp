#include "jcpp/lang/jmx/internal/JPerInterface.h"
#include "jcpp/lang/jmx/internal/JUtil.h"
#include "jcpp/util/JMap.h"

namespace jcpp{
	namespace lang{
		namespace jmx{
			namespace internal{
			//------------
			//	initMaps
			//------------
				JPerInterface::InitMaps::InitMaps():JObject(InitMaps::getClazz()){
				}

				void JPerInterface::InitMaps::visitAttribute(JString* attributeName, JObject* getter, JObject* setter){

				}
				void JPerInterface::InitMaps::visitOperation(JString* operationName, JObject* operation){

				}

				JPerInterface::InitMaps::~InitMaps(){
				}


			//----------
			//	MethodAndSig
			//----------
				JPerInterface::MethodAndSig::MethodAndSig():JObject(MethodAndSig::getClazz()){
				}

				JPerInterface::MethodAndSig::~MethodAndSig(){
				}

			//------------
			//	Private
			//------------

				JObject* JPerInterface::noSuchMethod(JString* msg, JObject* resource, JString* operation, JPrimitiveObjectArray* params, JPrimitiveObjectArray* signature, JObject* cookie){
					return null;
				}

				JString* JPerInterface::sigString(JPrimitiveObjectArray* signature){
					return null;
				}


			//----------
			//	Protected
			//----------
				JPerInterface::JPerInterface(JClass* mbeanInterface, JMBeanIntrospector* introspector, JMBeanAnalyzer* analyzer)
				:JObject(JPerInterface::getClazz()){
					this->getters = JUtil::newMap();
					this->setters = JUtil::newMap();
					this->ops = JUtil::newMap();
				}

				JClass* JPerInterface::getMBeanInterface(){
					return null;
				}


				JObject* JPerInterface::invoke(JObject* resource, JString* operation, JPrimitiveObjectArray* params, JPrimitiveObjectArray* signature, JObject* cookie){
					return null;
				}

				JObject* JPerInterface::getAttribute(JObject* resource, JString* attribute, JObject* cookie){
					return null;
				}

				void JPerInterface::setAttribute(JObject* resource, JString* attribute, JObject* value, JObject* cookie){

				}

				JPerInterface::~JPerInterface(){
				}
			}
		}
	}
}
