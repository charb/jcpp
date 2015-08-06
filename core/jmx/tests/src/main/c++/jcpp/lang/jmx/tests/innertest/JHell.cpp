/*
 * JHell.cpp
 *
 *  Created on: Aug 6, 2015
 *      Author: mmaarouf
 */

#ifndef JHELL_CPP_
#define JHELL_CPP_

#include "jcpp/lang/jmx/tests/innertest/JHell.h"
#include "jcpp/lang/JSystem.h"
#include "jcpp/lang/JString.h"

namespace jcpp{
	namespace lang{
		namespace jmx{
			namespace tests{
				namespace innertest{
					JHell::JHell():JObject(JHell::getClazz()){
						name = new JString("INNER MAN");
						cacheSize = new JInteger(200);
					}

					void JHell::sayHello(){
						JSystem::out->println(new JString("hello, world"));
					}

					JInteger* JHell::add(JInteger* x, JInteger* y){
						JInteger* ans = new JInteger(0);
						ans->set(x->get() + y->get());
						return ans;
					}

					JString* JHell::getName(){
						return name;
					}

					void JHell::setCacheSize(JInteger* size){
						this->cacheSize = size;

						JSystem::out->println((new JString("Cache size now :"))->concat(cacheSize->toString()));
					}

					JHell::~JHell(){
					}
				}
			}
		}
	}
}




#endif /* JHELL_CPP_ */
