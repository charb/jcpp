#include "jcpp/lang/jmx/JMBeanOperationInfo.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/jmx/internal/JIntrospector.h"

using namespace jcpp::lang::jmx::internal;

namespace jcpp{
	namespace lang{
		namespace jmx{
		//----------------
		//	Fields
		//----------------
			JPrimitiveObjectArray* JMBeanOperationInfo::NO_OPERATIONS = new JPrimitiveObjectArray(JMBeanOperationInfo::getClazz(), 0);

		//----------------
		//	Private
		//----------------
			JPrimitiveObjectArray* JMBeanOperationInfo::methodSignature(JMethod* method){
				return null;
			}

			void JMBeanOperationInfo::init(JPrimitiveObjectArray* signature, JString* type){

			}
		//----------------
		//	Protected
		//----------------

			JPrimitiveObjectArray* JMBeanOperationInfo::parameters(JPrimitiveObjectArray* classes, JPrimitiveObjectArray* annots){
				return null;
			}
		//----------------
		//	Public
		//----------------

			JMBeanOperationInfo::JMBeanOperationInfo(JString* description, JMethod* method)
				:JMBeanFeatureInfo(method->getName(), description, JMBeanOperationInfo::getClazz()){
				init(methodSignature(method), method->getReturnType()->getName());
			}

			JMBeanOperationInfo::JMBeanOperationInfo(JString* name, JString* description, JPrimitiveObjectArray* signature, JString* type)
				:JMBeanFeatureInfo(name, description, JMBeanOperationInfo::getClazz()){
				init(signature, type);
			}


			JMBeanOperationInfo::~JMBeanOperationInfo(){
			}

		}
	}
}
