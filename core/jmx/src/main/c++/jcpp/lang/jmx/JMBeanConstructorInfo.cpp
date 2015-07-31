#include "jcpp/lang/jmx/JMBeanConstructorInfo.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "jcpp/lang/JPrimitiveArray.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/util/JList.h"
#include "jcpp/lang/jmx/internal/JIntrospector.h"


using namespace jcpp::lang::jmx::internal;

namespace jcpp{
	namespace lang{
		namespace jmx{

		//---------------
		//	Private
		//---------------

			JPrimitiveObjectArray* JMBeanConstructorInfo::NO_CONSTRUCTORS = new JPrimitiveObjectArray(JMBeanConstructorInfo::getClazz(), 0);

			JPrimitiveObjectArray* JMBeanConstructorInfo::constructorSignature(JConstructor* cn){
				return null;
			}

			void JMBeanConstructorInfo::init(JPrimitiveObjectArray* signature){

			}

		//---------------
		//	Public
		//---------------



			JMBeanConstructorInfo::JMBeanConstructorInfo(JString* name, JString* description, JPrimitiveObjectArray* signature)
				:JMBeanFeatureInfo(name, description, JMBeanConstructorInfo::getClazz()){
				init(signature);
			}

			JMBeanConstructorInfo::JMBeanConstructorInfo(JString* name, JString* description, JPrimitiveObjectArray* signature)
				:JMBeanFeatureInfo(name, description, JMBeanConstructorInfo::getClazz()){
				init(signature);
			}

			JMBeanConstructorInfo::~JMBeanConstructorInfo(){
			}

		}
	}
}
