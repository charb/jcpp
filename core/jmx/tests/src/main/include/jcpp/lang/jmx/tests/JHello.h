/*
 * JHello.h
 *
 *  Created on: Aug 5, 2015
 *      Author: mmaarouf
 */

#ifndef JHELLO_H_
#define JHELLO_H_


#include "jcpp/lang/jmx/tests/JHelloMBean.h"
#include "jcpp/lang/JObject.h"

namespace jcpp{
	namespace lang{
		namespace jmx{
			namespace tests{

			// @Class(canonicalName="jcpp.lang.jmx.tests.Hello", simpleName="Hello");
				class JCPP_EXPORT JHello: public JObject, public JHelloMBean{
				private:
					JString* name;

					JInteger* cacheSize;
				public:
					JHello();

					void sayHello();
					JInteger* add(JInteger* x, JInteger* y);


					JString* getName();

					void setCacheSize(JInteger* size);

					static JClass* getClazz();
					virtual ~JHello();
				};
			}
		}
	}
}


#endif /* JHELLO_H_ */
