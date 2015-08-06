/*
 * JHellMBean.h
 *
 *  Created on: Aug 6, 2015
 *      Author: mmaarouf
 */

#ifndef JHELLMBEAN_H_
#define JHELLMBEAN_H_

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
				namespace innertest{
				// @Class(canonicalName="jcpp.lang.jmx.tests.HellMBean", simpleName="HellMBean");
					class JCPP_EXPORT JHellMBean: public JInterface{
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
						virtual ~JHellMBean();
					};
				}
			}
		}
	}
}



#endif /* JHELLMBEAN_H_ */
