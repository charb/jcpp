#include "jcpp/lang/jmx/internal/JRepository.h"
#include "jcpp/lang/JInteger.h"
#include "jcpp/util/JMap.h"

namespace jcpp{
	namespace lang{
		namespace jmx{
			namespace internal{
			//------------
			//	Private
			//------------
				void JRepository::addNewDomainMoi(JDynamicMBean* object, JString* dom, JObjectName* name){

				}

				JNamedObject* JRepository::retrieveNamedObject(JObjectName* name){
					return null;
				}

			//-------------
			//	Public
			//-------------
				JRepository::JRepository(JString* domain):JObject(JRepository::getClazz()){
					nbElements = 0;
				}

				JPrimitiveObjectArray* JRepository::getDomains(){
					return null;
				}

				void JRepository::addMBean(JDynamicMBean* object, JObjectName* name){

				}

				jbool JRepository::contains(JObjectName* name){
					return null;
				}

				JDynamicMBean* JRepository::retrieve(JObjectName* name){
					return null;
				}

				JInteger* JRepository::getCount(){
					return null;
				}

				JString* JRepository::getDefaultDomain(){
					return null;
				}


				JRepository::~JRepository(){
				}
			}
		}
	}
}
