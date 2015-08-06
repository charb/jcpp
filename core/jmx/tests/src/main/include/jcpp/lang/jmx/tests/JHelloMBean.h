/*
 * JHelloMBean.h
 *
 *  Created on: Aug 5, 2015
 *      Author: mmaarouf
 */

#ifndef JHELLOMBEAN_H_
#define JHELLOMBEAN_H_

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

			// @Class(canonicalName="jcpp.lang.jmx.tests.HelloMBean", simpleName="HelloMBean");
				class JCPP_EXPORT JHelloMBean: public JInterface{
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
					virtual ~JHelloMBean();
				};
			}
		}
	}
}


#endif /* JHELLOMBEAN_H_ */
