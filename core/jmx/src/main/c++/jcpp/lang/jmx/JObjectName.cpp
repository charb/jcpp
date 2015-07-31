#include "jcpp/lang/jmx/JObjectName.h";
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "jcpp/lang/JPrimitiveCharArray.h"
#include "jcpp/util/JMap.h"

namespace jcpp{
	namespace lang{
		namespace jmx{
//----------------
//	JProperty
//----------------
			JObjectName::JProperty::JProperty(jint key_index, jint key_length, jint value_length):JObject(JProperty::getClazz()){
				this->_key_index = key_index;
				this->_key_length = key_length;
				this->_value_length = value_length;
			}

			void JObjectName::JProperty::setKeyIndex(jint key_index){
				_key_index = key_index;
			}

			JObjectName::JProperty::~JProperty(){
			}

//----------------
//	JObjectName
//----------------

		//--------------
		//	Private
		//--------------

			JPrimitiveObjectArray* JObjectName::_Empty_property_array = new JPrimitiveObjectArray(JObjectName::JProperty::getClazz(), 0);

			void JObjectName::construct(JString* name){

			}

			void JObjectName::addProperty(JProperty* prop, jint index, JMap* keys_map, JString* key_name){

			}

			void JObjectName::setCanonicalName(JPrimitiveCharArray* specified_chars, JPrimitiveCharArray* canonical_chars, JPrimitiveObjectArray* keys, JMap* keys_map, jint prop_index, jint nb_props){

			}

			JString* JObjectName::getSerializedNameString(){
				return null;
			}

		//--------------
		//	Public
		//--------------
			JObjectName* JObjectName::getInstance(JString* name){
				return null;
			}

			JObjectName* JObjectName::getInstance(JObjectName* name){
				return null;
			}

			JObjectName::JObjectName(JString* name):JObject(JObjectName::getClazz()){
			}


			JString* JObjectName::getCanonicalKeyPropertyListString(){
				return null;
			}

			JString* JObjectName::getDomain(){
				return null;
			}

			jint JObjectName::compareTo(JObjectName* o){
				return null;
			}


			JObjectName::~JObjectName(){
			}

		}
	}
}
