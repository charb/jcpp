#include "jcpp/lang/jmx/tests/JCopyOfHello.h"
#include "jcpp/lang/JSystem.h"
#include "jcpp/lang/JString.h"


namespace jcpp{
	namespace lang{
		namespace jmx{
			namespace tests{

				JCopyOfHello::JCopyOfHello():JObject(JCopyOfHello::getClazz()){
						name = new JString("COPY OF THE MAN");
						cacheSize = new JInteger(200);
					}

					void JCopyOfHello::sayHello(){
						JSystem::out->println(new JString("hello, world"));
					}

					JInteger* JCopyOfHello::add(JInteger* x, JInteger* y){
						JInteger* ans = new JInteger(0);
						ans->set(x->get() + y->get());
						return ans;
					}

					JString* JCopyOfHello::getName(){
						return name;
					}

					void JCopyOfHello::setCacheSize(JInteger* size){
						this->cacheSize = size;

						JSystem::out->println((new JString("Cache size now :"))->concat(cacheSize->toString()));
					}

					JCopyOfHello::~JCopyOfHello(){
					}

			}
		}
	}
}
