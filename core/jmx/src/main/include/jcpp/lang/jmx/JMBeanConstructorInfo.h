/*
 * JMBeanConstructorInfo.h
 *
 *  Created on: Jul 20, 2015
 *      Author: mmaarouf
 */

#ifndef JMBEANCONSTRUCTORINFO_H_
#define JMBEANCONSTRUCTORINFO_H_

#include "jcpp/lang/jmx/JMBeanFeatureInfo.h"
#include "jcpp/lang/JCloneable.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"



namespace jcpp{
	namespace lang{
		class JPrimitiveObjectArray;

		namespace jmx{

			class JCPP_EXPORT JMBeanConstructorInfo: public JMBeanFeatureInfo, public JCloneable{
			private:
				static const jlong serialVersionUID = 4433990064191844427LL;

				static JPrimitiveObjectArray* constructorSignature(JConstructor* cn);

				void init(JPrimitiveObjectArray* signature);


			public:
				static JPrimitiveObjectArray* NO_CONSTRUCTORS;

				JMBeanConstructorInfo(JString* description, JConstructor* constructor);

				JMBeanConstructorInfo(JString* name, JString* description, JPrimitiveObjectArray* signature);


				static jcpp::lang::JClass* getClazz();
				virtual ~JMBeanConstructorInfo();
			};
		}
	}
}



#endif /* JMBEANCONSTRUCTORINFO_H_ */
