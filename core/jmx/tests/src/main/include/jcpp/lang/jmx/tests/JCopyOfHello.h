/*
 * JCopyOFHello.h
 *
 *  Created on: Aug 6, 2015
 *      Author: mmaarouf
 */

#ifndef JCOPYOFHELLO_H_
#define JCOPYOFHELLO_H_


#include "jcpp/lang/jmx/tests/JCopyOfHelloMBean.h"
#include "jcpp/lang/JObject.h"

namespace jcpp{
	namespace lang{
		namespace jmx{
			namespace tests{

			// @Class(canonicalName="jcpp.lang.jmx.tests.CopyOfHello", simpleName="CopyOfHello");
				class JCPP_EXPORT JCopyOfHello: public JObject, public JCopyOfHelloMBean{
				private:
					JString* name;

					JInteger* cacheSize;
				public:
					JCopyOfHello();

					void sayHello();
					JInteger* add(JInteger* x, JInteger* y);


					JString* getName();

					void setCacheSize(JInteger* size);

					static JClass* getClazz();
					virtual ~JCopyOfHello();
				};
			}
		}
	}
}


#endif /* JCOPYOFHELLO_H_ */
