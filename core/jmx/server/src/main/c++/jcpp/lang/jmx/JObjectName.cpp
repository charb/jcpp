#include "jcpp/lang/jmx/JObjectName.h";
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "jcpp/lang/JPrimitiveCharArray.h"
#include "jcpp/util/JHashMap.h"
#include "jcpp/lang/JIllegalArgumentException.h"
#include "jcpp/lang/JNullPointerException.h"
#include "jcpp/lang/JPrimitiveCharArray.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "jcpp/lang/JSystem.h"
#include "jcpp/util/JArrays.h"

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
				if(name == null){
					throw new JNullPointerException(new JString("name cannot be null"));
				}

				if(name->length() == 0){
					throw new JIllegalArgumentException(new JString("Argument is empty"));
				}
				JPrimitiveCharArray* name_chars = name->toCharArray();
				jint len = name_chars->size();
				JPrimitiveCharArray* canonical_chars = new JPrimitiveCharArray(len);

				jint cname_index = 0;
				jint index = 0;
				jchar c1;

			domain_parsing: while(index < len){
					switch(name_chars->getChar(index)){
					jint i;
					case ':':
						_domain_length = index++;
						goto AFTER_domain_parsing;
					case '=':
						i = ++index;
						while((i < len) && (name_chars->getChar(i++) != ':')){
							if(i == len)
								throw new JException(new JString("Domain part must be specified"));
						}
						break;
					case '\n':
						throw new JException(new JString("Invalid character '\\n' in domain name"));
					default:
						index++;
						break;
					}
				}
			AFTER_domain_parsing:
				if(index == len)
					throw new JException(new JString("key properties cannot be empty"));

				JSystem::arraycopy(name_chars, 0, canonical_chars, 0, _domain_length);
				canonical_chars->setChar(_domain_length, ':');
				cname_index = _domain_length + 1;

				JProperty* prop;
				JMap* keys_map = new JHashMap();
				JPrimitiveObjectArray* keys;
				JString* key_name;
				jbool quoted_value;
				jint property_index = 0;
				jint in_index;
				jint key_index, key_length, value_index, value_length;

				keys = new JPrimitiveObjectArray(JString::getClazz(), 10);
				_kp_array = new JPrimitiveObjectArray(JProperty::getClazz(), 10);

				while(index < len){
					in_index = index;
					key_index = in_index;
					if(name_chars->getChar(in_index) == '='){
						throw new JException(new JString("Invalid key (empty)"));
					}
					while((in_index < len) && ((c1 = name_chars->getChar(in_index++)) != '=')){
						switch(c1){
						case ',':
						case ':':
						case '\n':
							JString* ichar = ((c1 == '\n') ? new JString("\\n") : ((new JString(""))->concat(new JString(c1))));
							throw new JException(((new JString("Invalid character '"))->concat(ichar))->concat(new JString("' in key part of property")));
						}
					}
					if(name_chars->getChar(in_index - 1) != '='){
						throw new JException(new JString("Unterminated key property part"));
					}
					value_index = in_index;
					key_length = value_index - key_index - 1;

					if(in_index < len && name_chars->getChar(in_index) == '\"'){
						quoted_value = true;
						while((++in_index < len) && ((c1 = name_chars->getChar(in_index)) != '\"')){
							if(c1 == '\\'){
								if(++in_index == len){
									throw new JException(new JString("Unterminated quoted value"));
								}
								switch(c1 = name_chars->getChar(in_index)){
								case '\\':
								case '\"':
								case 'n':
									break;
								default:
									throw new JException(((new JString("Invalid escape sequence '\\"))->concat(new JString(c1)))->concat(new JString("' in quoted value")));
								}
							}else if(c1 == '\n'){
								throw new JException(new JString("Newline in quoted value"));
							}
						}
						if(in_index == len){
							throw new JException(new JString("Unterminated quoted value"));
						}
						else{
							value_length = ++in_index - value_index;
						}
					}else{
						quoted_value = false;
						while((in_index < len) && ((c1 = name_chars->getChar(in_index)) != ',')){
							switch (c1) {
							case '=':
							case ':':
							case '"':
							case '\n':
								throw new JException(((new JString("Invalid character '"))->concat(new JString(c1)))->concat(new JString("' in key part of property")));
							default:
								in_index++;
//								break;
							}
							value_length = in_index - value_index;
						}
					}

					if(in_index == len - 1){
						if(quoted_value){
							throw new JException(((new JString("Invalid ending character '"))->concat(new JString(name_chars->getChar(in_index))))->concat(new JString("'")));
						}
						else{
							throw new JException(new JString("Invalid ending comma"));
						}
					}else{
						in_index++;
					}

					prop = new JProperty(key_index, key_length, value_length);

					key_name = name->substring(key_index, key_index + key_length);

					if(property_index == keys->size()){
						JPrimitiveObjectArray* tmp_string_array = new JPrimitiveObjectArray(JString::getClazz(), property_index + 10);
						JSystem::arraycopy(keys, 0, tmp_string_array, 0, property_index);
						keys = tmp_string_array;
					}
					keys->set(property_index, key_name);

					addProperty(prop, property_index, keys_map, key_name);
					property_index++;
					index = in_index;
				}

				setCanonicalName(name_chars, canonical_chars, keys, keys_map, cname_index, property_index);
			}

			void JObjectName::addProperty(JProperty* prop, jint index, JMap* keys_map, JString* key_name){
				if(keys_map->containsKey(key_name)){
					throw new JException( ((new JString("key '"))->concat(key_name))->concat(new JString("' already defined")));
				}

				if(index == _kp_array->size()){
					JPrimitiveObjectArray* tmp_prop_array = new JPrimitiveObjectArray(JProperty::getClazz(), index + 10);
					JSystem::arraycopy(_kp_array, 0, tmp_prop_array, 0, index);
					_kp_array = tmp_prop_array;
				}
				_kp_array->set(index, prop);
				keys_map->put(key_name, prop);
			}

			void JObjectName::setCanonicalName(JPrimitiveCharArray* specified_chars, JPrimitiveCharArray* canonical_chars, JPrimitiveObjectArray* keys, JMap* keys_map, jint prop_index, jint nb_props){
				if(_kp_array != _Empty_property_array){
					JPrimitiveObjectArray* tmp_keys = new JPrimitiveObjectArray(JString::getClazz(), nb_props);
					JPrimitiveObjectArray* tmp_props = new JPrimitiveObjectArray(JProperty::getClazz(), nb_props);

					JSystem::arraycopy(keys, 0, tmp_keys, 0, nb_props);
					JArrays::sort(tmp_keys);
					keys = tmp_keys;
					JSystem::arraycopy(_kp_array, 0, tmp_props, 0, nb_props);
					_kp_array = tmp_props;
					_ca_array = new JPrimitiveObjectArray(JProperty::getClazz(), nb_props);

					for(jint i = 0; i < nb_props; i++){
						_ca_array->set(i, keys_map->get(keys->get(i)));
					}

					jint last_index = nb_props - 1;
					jint prop_len;
					JProperty* prop;
					for(jint i = 0; i <=  last_index; i++){
						prop = dynamic_cast<JProperty*>(_ca_array->get(i));
						prop_len = prop->_key_length + prop->_value_length + 1;
						JSystem::arraycopy(specified_chars, prop->_key_index, canonical_chars, prop_index, prop_len);
						prop->setKeyIndex(prop_index);
						prop_index += prop_len;
						if(i != last_index){
							canonical_chars->setChar(prop_index, ',');
							prop_index++;
						}
					}
				}

				_canonicalName = new JString(canonical_chars, 0, prop_index);
			}

			JString* JObjectName::getSerializedNameString(){
				jint total_size = _canonicalName->length();
				JPrimitiveCharArray* dest_chars = new JPrimitiveCharArray(total_size);
				JPrimitiveCharArray* value = _canonicalName->toCharArray();
				jint offset = _domain_length + 1;

				JSystem::arraycopy(value, 0, dest_chars, 0, offset);

				return new JString(dest_chars);
			}

		//--------------
		//	Public
		//--------------
			JObjectName* JObjectName::getInstance(JString* name){
				return new JObjectName(name);
			}

			JObjectName* JObjectName::getInstance(JObjectName* name){
				if(name->getClass()->equals(JObjectName::getClazz())){
					return name;
				}
				try{
					return new JObjectName(name->getSerializedNameString());
				}catch(JException* e){
					throw new JIllegalArgumentException((new JString("Unexpected: "))->concat(e->toString()));
				}
			}
			JObjectName::JObjectName() :JObject(JObjectName::getClazz()){
			}

			JObjectName::JObjectName(JString* name):JObject(JObjectName::getClazz()){
				construct(name);
			}


			JString* JObjectName::getCanonicalKeyPropertyListString(){
				if(_ca_array->size() == 0)
					return new JString("");

				jint len = _canonicalName->length();

				return _canonicalName->substring(_domain_length + 1, len);
			}

			JString* JObjectName::getDomain(){
				return _canonicalName->substring(0, _domain_length);
			}

			jint JObjectName::compareTo(JObjectName* o){
				JSystem::out->println((new JString("implement me"))->concat(this->getClass()->getName()));
				return null;
			}


			JObjectName::~JObjectName(){
			}

		}
	}
}
