/*
 * JHell.h
 *
 *  Created on: Aug 6, 2015
 *      Author: mmaarouf
 */

#ifndef JHELL_H_
#define JHELL_H_

#include "jcpp/lang/jmx/tests/innertest/JHellMBean.h"
#include "jcpp/lang/JObject.h"


namespace jcpp{
	namespace lang{
		namespace jmx{
			namespace tests{
				namespace innertest{

				// @Class(canonicalName="jcpp.lang.jmx.tests.Hell", simpleName="Hell");
					class JCPP_EXPORT JHell: public JObject, public JHellMBean{
					private:
						JString* name;

						JInteger* cacheSize;
					public:
						JHell();

						void sayHello();
						JInteger* add(JInteger* x, JInteger* y);


						JString* getName();

						void setCacheSize(JInteger* size);

						static JClass* getClazz();
						virtual ~JHell();
					};
				}
			}
		}
	}
}




#endif /* JHELL_H_ */
