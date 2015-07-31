/*
 * JMBeanFeatureInfo.h
 *
 *  Created on: Jul 20, 2015
 *      Author: mmaarouf
 */

#ifndef JMBEANFEATUREINFO_H_
#define JMBEANFEATUREINFO_H_

#include "jcpp/lang/JObject.h"
#include "jcpp/io/JSerializable.h"

using namespace jcpp::io;

namespace jcpp{
	namespace lang{
		namespace jmx{

			class JCPP_EXPORT JMBeanFeatureInfo: public JObject, public JSerializable{
			private:
				static const jlong serialVersionUID = 3952882688968447265LL;

				JString* name;

				JString* description;


				void init(JString* name, JString* description);

			public:


				JMBeanFeatureInfo(JString* name, JString* description, JClass* clazz);

				JString* getName();

				JString* getDescription();



				static jcpp::lang::JClass* getClazz();
				virtual ~JMBeanFeatureInfo();
			};
		}
	}
}



#endif /* JMBEANFEATUREINFO_H_ */
