#include "jcpp/lang/jmx/JMBeanAttributeInfo.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "jcpp/lang/JBoolean.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/JException.h"
#include "jcpp/lang/JIllegalArgumentException.h"
#include "jcpp/lang/jmx/internal/JIntrospector.h"

using namespace jcpp::lang::jmx::internal;

namespace jcpp{
	namespace lang{
		namespace jmx{

			//-------------------
			//	FIELDS
			//-------------------
			JPrimitiveObjectArray* JMBeanAttributeInfo::NO_ATTRIBUTES = new JPrimitiveObjectArray(JMBeanAttributeInfo::getClazz(), 0);

			//-------------------
			//	PRIVATE
			//-------------------

			jbool JMBeanAttributeInfo::isIs(JMethod* getter){
				return (getter != null && getter->getName()->startsWith(new JString("is")) && (getter->getReturnType()->equals(JBoolean::TYPE) || getter->getReturnType()->equals(JBoolean::getClazz())));
			}

			JString* JMBeanAttributeInfo::attributeType(JMethod* getter, JMethod* setter){
				JClass* type = null;
				if(getter != null){
					if(getter->getParameterTypes()->size() != 0){
						throw new JException(new JString("bad getter arg count"));
					}
					type = getter->getReturnType();
					if(type == JVoid::TYPE){
						throw new JException(((new JString("getter"))->concat(getter->getName()))->concat(new JString(" returns void")));
					}
				}
				if(setter != null){
					JPrimitiveObjectArray* params = setter->getParameterTypes()->toArray();
					if(params->size() != 1){
						throw new JException(new JString("bad setter arg count"));
					}
					if(type == null){
						type = dynamic_cast<JClass*>(params->get(0));
					}
					else if(!type->equals(params->get(0))){
						throw new JException(new JString("type mismatch between getter and setter"));
					}
				}
				if(type == null){
					throw new JException(new JString("getter and setter cannot both be null"));
				}
				return type->getName();
			}

			void JMBeanAttributeInfo::init(JString* type, jbool isReadable, jbool isWritable, jbool isIs){
				if(isIs && !isReadable){
					throw new JIllegalArgumentException(new JString("Cannot have and \"is\" getter for a non-readable attribute"));
				}
//				if(isIs && !type->equals(new JString("")))TODO

				this->is = isIs;
			}



			//-------------------
			//	PUBLIC
			//-------------------






			JMBeanAttributeInfo::JMBeanAttributeInfo(JString* name, JString* type, JString* description, jbool isReadable, jbool isWritable, jbool isIs)
			:JMBeanFeatureInfo(name, description, JMBeanAttributeInfo::getClazz()){
				init(type, isReadable, isWritable, isIs);
			}

			jbool JMBeanAttributeInfo::isIs(){
				return is;
			}



			JMBeanAttributeInfo::~JMBeanAttributeInfo(){
			}
		}
	}
}
