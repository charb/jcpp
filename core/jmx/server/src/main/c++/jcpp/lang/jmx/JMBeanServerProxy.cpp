#include "jcpp/lang/jmx/JMBeanServerProxy.h"

#include "jcpp/lang/jmx/JAttribute.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "jcpp/lang/jmx/JObjectName.h"
#include "jcpp/lang/jmx/JObjectInstance.h"

#include "jcpp/util/JArrayList.h"



using namespace jcpp::util;

namespace jcpp{
	namespace lang{
		namespace jmx{

			JMBeanServerProxy::JMBeanServerProxy():JProxy(JMBeanServerProxy::getClazz()){
			}

			JObjectInstance* JMBeanServerProxy::registerMBean(JObject* object, JObjectName* name){
				JList* args = new JArrayList();
				args->add(object);
				args->add(name);
				JList* types = new JArrayList();
				types->add(JObject::getClazz());
				types->add(JObjectName::getClazz());

				JObjectInstance* ans = dynamic_cast<JObjectInstance*> (JProxy::invoke(new JString("registerMBean"), args, types));
				return ans;	// TODo check name of the method
			}

			JObject* JMBeanServerProxy::invoke(JObjectName* name, JString* operationName, JPrimitiveObjectArray* params, JPrimitiveObjectArray* signature){
				JList* args = new JArrayList();
				args->add(name);
				args->add(operationName);
				args->add(params);
				args->add(signature);

				JList* types = new JArrayList();
				types->add(JObjectName::getClazz());
				types->add(JString::getClazz());
				types->add(JPrimitiveObjectArray::getClazz());
				types->add(JPrimitiveObjectArray::getClazz());

				return JProxy::invoke(new JString("invoke"), args, types);
			}


			JObject* JMBeanServerProxy::getAttribute(JObjectName* name, JString* attribute){
				JList* args = new JArrayList();
				args->add(name);
				args->add(attribute);
				JList* types = new JArrayList();
				types->add(JObjectName::getClazz());
				types->add(JString::getClazz());

				return JProxy::invoke(new JString("getAttribute"), args, types);
			}

			void JMBeanServerProxy::setAttribute(JObjectName* name, JAttribute* attribute){
				JList* args = new JArrayList();
				args->add(name);
				args->add(attribute);
				JList* types = new JArrayList();
				types->add(JObjectName::getClazz());
				types->add(JAttribute::getClazz());
				JProxy::invoke(new JString("setAttribute"), args, types);
			}

			JMBeanServerProxy::~JMBeanServerProxy(){
			}

		}
	}
}
