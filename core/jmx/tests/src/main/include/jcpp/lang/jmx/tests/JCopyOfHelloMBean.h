/*
 * JCopyOfHelloMBean.h
 *
 *  Created on: Aug 6, 2015
 *      Author: mmaarouf
 */

#ifndef JCOPYOFHELLOMBEAN_H_
#define JCOPYOFHELLOMBEAN_H_

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JInteger.h"


namespace jcpp{
	namespace lang{
		class JString;
	}
}
namespace jcpp{
	namespace lang{
		namespace jmx{
			namespace tests{

			// @Class(canonicalName="jcpp.lang.jmx.tests.CopyOfHelloMBean", simpleName="CopyOfHelloMBean");
				class JCPP_EXPORT JCopyOfHelloMBean: public JInterface{
				public:

				    //-----------
				    // operations
				    //-----------

					virtual void sayHello() = 0;
					virtual JInteger* add(JInteger* x, JInteger* y) = 0;

				    //-----------
				    // attributes
				    //-----------
					virtual JString* getName() = 0;

					virtual void setCacheSize(JInteger* size) = 0;

					static JClass* getClazz();
					virtual ~JCopyOfHelloMBean();
				};
			}
		}
	}
}




#endif /* JCOPYOFHELLOMBEAN_H_ */
