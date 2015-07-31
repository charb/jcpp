/*
 * JMBeanInfo.h
 *
 *  Created on: Jul 16, 2015
 *      Author: mmaarouf
 */

#ifndef JMBEANINFO_H_
#define JMBEANINFO_H_

#include "jcpp/io/JSerializable.h"
#include "jcpp/lang/JCloneable.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JString.h"

using namespace jcpp::io;

namespace jcpp{
	namespace lang{

		class JString;
		class JPrimitiveObjectArray;

		namespace jmx{

			class JCPP_EXPORT JMBeanInfo: public JObject, public JSerializable, public JCloneable{
			private:
				static const jlong serialVersionUID = -6451021435135161911LL;



				JString* className;

				JString* description;

				JPrimitiveObjectArray* attributes;

				JPrimitiveObjectArray* operations;

				JPrimitiveObjectArray* constructors;

				JPrimitiveObjectArray* nonNullConstructors();

				JPrimitiveObjectArray* nonNullOperations();

				JPrimitiveObjectArray* nonNullAttributes();


			public:

				JMBeanInfo(JString* className, JString* description, JPrimitiveObjectArray* attributes, JPrimitiveObjectArray* constructors, JPrimitiveObjectArray* operations);


				JString* getDescription();

				JPrimitiveObjectArray* getAttributes();

				JPrimitiveObjectArray* getOperations();

				JPrimitiveObjectArray* getConstructors();

				JString* getClassName();

				static jcpp::lang::JClass* getClazz();
				virtual ~JMBeanInfo();
			};
		}
	}
}



#endif /* JMBEANINFO_H_ */
