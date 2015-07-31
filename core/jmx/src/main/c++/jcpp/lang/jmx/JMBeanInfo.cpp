#include "jcpp/lang/jmx/JMBeanInfo.h"
#include "jcpp/lang/jmx/JMBeanAttributeInfo.h"
#include "jcpp/lang/jmx/JMBeanConstructorInfo.h"
#include "jcpp/lang/jmx/JMBeanOperationInfo.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"

namespace jcpp{
	namespace lang{
		namespace jmx{
		//---------------
		//	Private
		//---------------
			JPrimitiveObjectArray* JMBeanInfo::nonNullConstructors(){
				return (constructors == null) ? JMBeanConstructorInfo::NO_CONSTRUCTORS : constructors;
			}

			JPrimitiveObjectArray* JMBeanInfo::nonNullOperations(){
				return (operations == null) ? JMBeanOperationInfo::NO_OPERATIONS : operations;
			}

			JPrimitiveObjectArray* JMBeanInfo::nonNullAttributes(){
				return (attributes == null) ? JMBeanAttributeInfo::NO_ATTRIBUTES : attributes;
			}


		//--------------
		//	Public
		//--------------
			JMBeanInfo::JMBeanInfo(JString* className, JString* description, JPrimitiveObjectArray* attributes, JPrimitiveObjectArray* constructors, JPrimitiveObjectArray* operations)
			:JObject(JMBeanInfo::getClazz()){
				this->className = className;
				this->description = description;

				if(attributes == null)
					attributes = JMBeanAttributeInfo::NO_ATTRIBUTES;
				this->attributes = attributes;

				if(operations == null)
					operations = JMBeanOperationInfo::NO_OPERATIONS;
				this->operations = operations;

				if(constructors == null)
					constructors = JMBeanConstructorInfo::NO_CONSTRUCTORS;
				this->constructors = constructors;
			}


			JString* JMBeanInfo::getDescription(){
				return description;
			}

			JPrimitiveObjectArray* JMBeanInfo::getAttributes(){
				JPrimitiveObjectArray* as = nonNullAttributes();
				if(as->size() == 0)
					return as;
				else
					return as->clone();
			}

			JPrimitiveObjectArray* JMBeanInfo::getOperations(){
				JPrimitiveObjectArray* os = nonNullOperations();
				if(os->size() == 0)
					return os;
				else
					return os->clone();
			}

			JPrimitiveObjectArray* JMBeanInfo::getConstructors(){
				JPrimitiveObjectArray* cs = nonNullConstructors();
				if(cs->size() == 0)
					return cs;
				else
					return cs->clone();
			}

			JString* JMBeanInfo::getClassName(){
				return className;
			}
			JMBeanInfo::~JMBeanInfo(){
			}
		}
	}
}
