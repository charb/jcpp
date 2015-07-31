/*
 * JMBeanParameterInfo.h
 *
 *  Created on: Jul 29, 2015
 *      Author: mmaarouf
 */

#ifndef JMBEANPARAMETERINFO_H_
#define JMBEANPARAMETERINFO_H_

#include "jcpp/lang/jmx/JMBeanFeatureInfo.h"
#include "jcpp/lang/JCloneable.h"


namespace jcpp{
	namespace lang{
	class JPrimitiveObjectArray;
	}
}

using namespace jcpp::lang;

namespace jcpp{
	namespace lang{

		namespace jmx{

			class JCPP_EXPORT JMBeanParameterInfo: public JMBeanFeatureInfo, public JCloneable{
			private:
				static const jint serialVersionUID = 7432616882776782338LL;
			public:
				static JPrimitiveObjectArray* NO_PARAMS;

				JMBeanParameterInfo(JString* name, JString* description);

				static jcpp::lang::JClass* getClazz();
				virtual ~JMBeanParameterInfo();
			};
		}
	}
}


#endif /* JMBEANPARAMETERINFO_H_ */
