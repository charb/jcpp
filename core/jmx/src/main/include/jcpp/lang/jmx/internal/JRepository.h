/*
 * JRepository.h
 *
 *  Created on: Jul 31, 2015
 *      Author: mmaarouf
 */

#ifndef JREPOSITORY_H_
#define JREPOSITORY_H_

#include "jcpp/lang/JObject.h"


namespace jcpp{
	namespace lang{
		namespace jmx{
			namespace internal{

				class JCPP_EXPORT JRepository:public JObject{
				public:


					static JClass* getClazz();
					virtual ~JRepository();
				};
			}
		}
	}
}



#endif /* JREPOSITORY_H_ */
