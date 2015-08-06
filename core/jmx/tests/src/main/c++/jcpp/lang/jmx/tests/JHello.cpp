
#include "jcpp/lang/jmx/tests/JHello.h"
#include "jcpp/lang/JSystem.h"
#include "jcpp/lang/JString.h"


namespace jcpp{
	namespace lang{
		namespace jmx{
			namespace tests{

					JHello::JHello():JObject(JHello::getClazz()){
						name = new JString("THE MAN");
						cacheSize = new JInteger(200);
					}

					void JHello::sayHello(){
						JSystem::out->println(new JString("hello, world"));
					}

					JInteger* JHello::add(JInteger* x, JInteger* y){
						JInteger* ans = new JInteger(0);
						ans->set(x->get() + y->get());
						return ans;
					}

					JString* JHello::getName(){
						return name;
					}

					void JHello::setCacheSize(JInteger* size){
						this->cacheSize = size;

						JSystem::out->println((new JString("Cache size now :"))->concat(cacheSize->toString()));
					}

					JHello::~JHello(){
					}

			}
		}
	}
}
