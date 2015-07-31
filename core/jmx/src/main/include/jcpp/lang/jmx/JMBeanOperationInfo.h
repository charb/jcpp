/*
 * JMBeanOperationInfo.h
 *
 *  Created on: Jul 20, 2015
 *      Author: mmaarouf
 */

#ifndef JMBEANOPERATIONINFO_H_
#define JMBEANOPERATIONINFO_H_

#include "jcpp/lang/JCloneable.h"
#include "jcpp/lang/jmx/JMBeanFeatureInfo.h"

namespace jcpp{
	namespace lang{
		class JPrimitiveObjectArray;
		namespace reflect{
			class JMethod;
		}
	}
}


using namespace jcpp::lang::reflect;

namespace jcpp{
	namespace lang{
		class JPrimitiveObjectArray;

		namespace jmx{

			class JCPP_EXPORT JMBeanOperationInfo: public JMBeanFeatureInfo, public JCloneable{
			private:
				static const jlong serialVersionUID = -6178860474881375330LL;

				static JPrimitiveObjectArray* methodSignature(JMethod* method);

				void init(JPrimitiveObjectArray* signature, JString* type);
			protected:
				static JPrimitiveObjectArray* parameters(JPrimitiveObjectArray* classes, JPrimitiveObjectArray* annots);
			public:
				static JPrimitiveObjectArray* NO_OPERATIONS;

				static const jint INFO = 0;
				static const jint ACTION = 1;
				static const jint ACTION_INFO = 2;
				static const jint UNKNOWN = 3;

				JMBeanOperationInfo(JString* description, JMethod* method);

				JMBeanOperationInfo(JString* name, JString* description, JPrimitiveObjectArray* signature, JString* type);

				static jcpp::lang::JClass* getClazz();
				virtual ~JMBeanOperationInfo();
			};
		}
	}
}



#endif /* JMBEANOPERATIONINFO_H_ */
