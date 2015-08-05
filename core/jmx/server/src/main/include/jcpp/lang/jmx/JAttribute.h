/*
 * JAttribute.h
 *
 *  Created on: Jul 14, 2015
 *      Author: mmaarouf
 */

#ifndef JATTRIBUTE_H_
#define JATTRIBUTE_H_

#include "jcpp/lang/JObject.h"
#include "jcpp/io/JSerializable.h"

using namespace jcpp::io;


namespace jcpp{
	namespace lang{
		namespace jmx{

		// @Class(canonicalName="javax.management.Attribute", simpleName="Attribute");
			class JCPP_EXPORT JAttribute : public JObject, public JSerializable{
			private:
				static const jlong serialVersionUID = 2484220110589082382LL;

				JString* name;

				JObject* value;

			public:

				JAttribute();

				JAttribute(JString* name, JObject* Value);

				JString* getName();

				JObject* getValue();

				static jcpp::lang::JClass* getClazz();

				virtual ~JAttribute();

			};
		}
	}
}


#endif /* JATTRIBUTE_H_ */
