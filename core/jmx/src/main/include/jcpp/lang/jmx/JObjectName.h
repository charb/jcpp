/*
 * JObjectName.h
 *
 *  Created on: Jul 14, 2015
 *      Author: mmaarouf
 */

#ifndef JOBJECTNAME_H_
#define JOBJECTNAME_H_

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"



namespace jcpp{
	namespace util{
		class JMap;
	}
	namespace lang{
		class JPrimitiveObjectArray;
		class JPrimitiveCharArray;
	}
}

using namespace jcpp::util;
using namespace jcpp::lang;

namespace jcpp{
	namespace lang{
		namespace jmx{

			class JCPP_EXPORT JObjectName : public JObject{
			private:
				static class JCPP_EXPORT JProperty: public JObject{
					jint _key_index;
					jint _key_length;
					jint _value_length;

					JProperty(jint key_index, jint key_length, jint value_length);

					void setKeyIndex(jint key_index);

				public:
					static jcpp::lang::JClass* getClazz();
					~JProperty();
				};


				static const jlong serialVersionUID = 1081892073854801359LL;

				static JPrimitiveObjectArray* _Empty_property_array;

				/*TODO transient*/ JString* _canonicalName;
				/*TODO transient*/ JPrimitiveObjectArray* _kp_array;
				/*TODO transient*/ JPrimitiveObjectArray* _ca_array;
				/*TODO transient*/ jint _domain_length;
				/*TODO transient*/ JMap* _propertyList;

				void construct(JString* name);

				void addProperty(JProperty* prop, jint index, JMap* keys_map, JString* key_name);

				void setCanonicalName(JPrimitiveCharArray* specified_chars, JPrimitiveCharArray* canonical_chars, JPrimitiveObjectArray* keys, JMap* keys_map, jint prop_index, jint nb_props);

				JString* getSerializedNameString();

			public:
				static JObjectName* getInstance(JString* name);

				static JObjectName* getInstance(JObjectName* name);

				JObjectName(JString* name);


				JString* getCanonicalKeyPropertyListString();

				JString* getDomain();

				jint compareTo(JObjectName* o);

				static jcpp::lang::JClass* getClazz();
				virtual ~JObjectName();

			};
		}
	}
}



#endif /* JOBJECTNAME_H_ */
