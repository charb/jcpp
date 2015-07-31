/*
 * JMBeanAttributeInfo.h
 *
 *  Created on: Jul 20, 2015
 *      Author: mmaarouf
 */

#ifndef JMBEANATTRIBUTEINFO_H_
#define JMBEANATTRIBUTEINFO_H_

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
		namespace jmx{

			class JCPP_EXPORT JMBeanAttributeInfo: public JMBeanFeatureInfo, public JCloneable{
			private:
				static const jlong serialVersionUID = 1452116342341778410LL;

				jbool is;

				static jbool isIs(JMethod* getter);

				static JString* attributeType(JMethod* getter, JMethod* setter);

				void init(JString* type, jbool isReadable, jbool isWritable, jbool isIs);


			protected:

			public:
				static JPrimitiveObjectArray* NO_ATTRIBUTES;

				JMBeanAttributeInfo(JString* name, JString* description, JMethod* getter, JMethod* setter);

				JMBeanAttributeInfo(JString* name, JString* type, JString* description, jbool isReadable, jbool isWritable, jbool isIs);

				jbool isIs();

				static jcpp::lang::JClass* getClazz();
				virtual ~JMBeanAttributeInfo();
			};
		}
	}
}


#endif /* JMBEANATTRIBUTEINFO_H_ */
