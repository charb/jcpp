#include "jcpp/lang/JPrimitiveArray.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/io/JSerializable.h"
#include "jcpp/lang/JIllegalArgumentException.h"
#include "jcpp/lang/JStringBuilder.h"
#include "jcpp/util/JHashMap.h"
#include "jcpp/util/JMap.h"
#include "jcpp/lang/JIndexOutOfBoundsException.h"
#include "jcpp/lang/JCloneable.h"
#include "jcpp/lang/JSystem.h"

using namespace jcpp::util;

namespace jcpp {
	namespace lang {

		// @IgnoreReflection()
		class JCPP_EXPORT JPrimitiveArrayClass: public jcpp::lang::JClass{
		public:
			JPrimitiveArrayClass(jcpp::lang::JClass* componentType) :
					jcpp::lang::JClass(){
				this->componentType = componentType;
				this->bIsArray = true;
			}

			virtual JString* getCanonicalName(){
				if (canonicalName == null){
					JString* cn = componentType->getCanonicalName();
					if (!cn->isEmpty()){
						JStringBuilder* builder = new JStringBuilder();
						builder->append(cn)->append("[]");
						this->canonicalName = builder->toString();
					} else{
						canonicalName = new JString("");
					}
				}
				return canonicalName;
			}

			virtual JString* getName(){
				if (name == null){
					JStringBuilder* builder = new JStringBuilder();
					builder->append("[")->append(componentType->getSignature());
					this->name = builder->toString();
				}
				return name;
			}

			virtual JString* getSimpleName(){
				if (simpleName == null){
					JStringBuilder* builder = new JStringBuilder();
					builder->append(componentType->getSimpleName())->append("[]");
					this->simpleName = builder->toString();
				}
				return simpleName;
			}

			virtual void initialize(){
				addInterface(JSerializable::getClazz());
				addInterface(JCloneable::getClazz());
			}

			virtual jcpp::lang::JClass* getSuperclass(){
				return JObject::getClazz();
			}
		};

		JObject* JPrimitiveArray::lockObject = null;

		// @Class(canonicalName="java.lang.PrimitiveArray$PrimitiveArrayInnerFields", simpleName="PrimitiveArray$PrimitiveArrayInnerFields");
		class JCPP_EXPORT JPrimitiveArrayInnerFields: public JObject{
		public:
			static jcpp::lang::JClass* getClazz();
			static JMap* jPrimitiveArrayClasses;
			static jcpp::lang::JClass* JHashMapPrimitiveArrayClass;
		};

		JMap* JPrimitiveArrayInnerFields::jPrimitiveArrayClasses = null;
		jcpp::lang::JClass* JPrimitiveArrayInnerFields::JHashMapPrimitiveArrayClass = null;

		JObject* JPrimitiveArray::getLockObject(){
			if (lockObject == null){
				lockObject = new JObject();
			}
			return lockObject;
		}

		jcpp::lang::JClass* JPrimitiveArray::objectArrayClass = null;

		jcpp::lang::JClass* JPrimitiveArray::getObjectArrayClass(){
			if (objectArrayClass == null){
				objectArrayClass = new JPrimitiveArrayClass(JObject::getClazz());
			}
			return objectArrayClass;
		}

		jcpp::lang::JClass* JPrimitiveArray::getClazz(jcpp::lang::JClass* componentType){
			if (componentType->getDeclaringClass() == JHashMap::getClazz()){
				if (JPrimitiveArrayInnerFields::JHashMapPrimitiveArrayClass == null){
					JPrimitiveArrayInnerFields::JHashMapPrimitiveArrayClass = new JPrimitiveArrayClass(JHashMap::getClazz());
				}
				return JPrimitiveArrayInnerFields::JHashMapPrimitiveArrayClass;
			}
			if (componentType == JObject::getClazz()){
				return getObjectArrayClass();
			}
			synchronized(getLockObject(), { if (JPrimitiveArrayInnerFields::jPrimitiveArrayClasses==null){ JPrimitiveArrayInnerFields::jPrimitiveArrayClasses=new JHashMap(); } JString* componentTypeName = componentType->getName(); jcpp::lang::JPrimitiveArrayClass* jPrimitiveArrayClass = dynamic_cast<JPrimitiveArrayClass*>(JPrimitiveArrayInnerFields::jPrimitiveArrayClasses->get(componentTypeName)); if (jPrimitiveArrayClass == null){ jPrimitiveArrayClass = new JPrimitiveArrayClass(componentType); JPrimitiveArrayInnerFields::jPrimitiveArrayClasses->put(componentTypeName, jPrimitiveArrayClass); } return jPrimitiveArrayClass; })
		}

		JPrimitiveArray::JPrimitiveArray(jcpp::lang::JClass* arrayClass, jint len) :
				JObject(getClazz(arrayClass)){
			this->componentType = arrayClass;
			this->len = len;
		}

		JPrimitiveArray::JPrimitiveArray(JPrimitiveArray* a) :
				JObject(a->getClass()){
			this->componentType = a->getComponentType();
			this->len = a->size();
		}

		jbool JPrimitiveArray::equals(JObject* other){
			if ((other == null) || !other->getClass()->isArray()){
				return false;
			}
			JPrimitiveArray* s = dynamic_cast<JPrimitiveArray*>(other);
			if (s->size() == size()){
				for (jint i = 0; i < s->size(); i++){
					JObject* object1 = s->get(i);
					JObject* object2 = get(i);
					if (!(object1->equals(object2))){
						return false;
					}
				}
				return true;
			}
			return false;
		}

		jcpp::lang::JClass* JPrimitiveArray::getComponentType(){
			return componentType;
		}

		jint JPrimitiveArray::size(){
			return len;
		}

		void JPrimitiveArray::setSize(jint len){
			this->len = len;
		}

		void JPrimitiveArray::checkType(JObject* o){
		}

		JPrimitiveArray::~JPrimitiveArray(){
		}
	}
}
