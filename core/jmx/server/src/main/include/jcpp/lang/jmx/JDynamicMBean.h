/*
 * JDynamicMBean.h
 *
 *  Created on: Jul 15, 2015
 *      Author: mmaarouf
 */

#ifndef JDYNAMICMBEAN_H_
#define JDYNAMICMBEAN_H_


#include "jcpp/lang/JInterface.h"


namespace jcpp{
	namespace lang{

		class JString;
		class JPrimitiveObjectArray;
		class JClass;
		class JObject;
		namespace jmx{
			class JAttribute;
		};
	}
}

namespace jcpp{
	namespace lang{
		namespace jmx{

		// @Class(canonicalName="jcpp.management.DynamicMBean", simpleName="DynamicMBean");
			class JCPP_EXPORT JDynamicMBean : public JInterface{
			public:

				virtual JObject* invoke(JString* actionName, JPrimitiveObjectArray* params, JPrimitiveObjectArray* signature) = 0;

				virtual JObject* getAttribute(JString* jattribute) = 0;

				virtual void setAttribute(JAttribute* attribute) = 0;

				static jcpp::lang::JClass* getClazz();
				virtual ~JDynamicMBean();
			};

		}
	}
}



#endif /* JDYNAMICMBEAN_H_ */
