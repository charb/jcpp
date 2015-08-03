/*
 * JNamedObject.h
 *
 *  Created on: Aug 3, 2015
 *      Author: mmaarouf
 */

#ifndef JNAMEDOBJECT_H_
#define JNAMEDOBJECT_H_

#include "jcpp/lang/JObject.h"

namespace jcpp{
	namespace lang{
		namespace jmx{
			class JDynamicMBean;
		}
	}
}

namespace jcpp{
	namespace lang{
		namespace jmx{
			namespace internal{

				class JCPP_EXPORT JNamedObject: public JObject{
				private:
					JDynamicMBean* object;
				public:
					JNamedObject(JDynamicMBean* object);

					JDynamicMBean* getObject();

					static JClass* getClazz();
					virtual ~JNamedObject();
				};
			}
		}
	}
}



#endif /* JNAMEDOBJECT_H_ */
