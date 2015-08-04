/*
 * JObjectInstance.h
 *
 *  Created on: Jul 14, 2015
 *      Author: mmaarouf
 */

#ifndef JOBJECTINSTANCE_H_
#define JOBJECTINSTANCE_H_

#include "jcpp/io/JSerializable.h"
#include "jcpp/lang/JObject.h"

using namespace jcpp::io;

namespace jcpp{
	namespace lang{
		namespace jmx{

			// @Class(canonicalName="javax.management.ObjectInstance", simpleName="ObjectInstance");
			class JCPP_EXPORT JObjectInstance: public JObject, public JSerializable{
			private:
				static const jlong serialVersionUID = -4099952623687795850LL;

			public:

				JObjectInstance();

				static jcpp::lang::JClass *getClazz();

				virtual ~JObjectInstance();
			};
		}
	}
}



#endif /* JOBJECTINSTANCE_H_ */
