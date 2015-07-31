#include "jcpp/lang/jmx/internal/JUtil.h"
#include "jcpp/util/JMap.h"
#include "jcpp/util/JList.h"
#include "jcpp/util/JSet.h"
#include "jcpp/util/JHashMap.h"
#include "jcpp/util/JSortedMap.h"

namespace jcpp{
	namespace lang{
		namespace jmx{
			namespace internal{
				JUtil::JUtil():JObject(JUtil::getClazz()){
				}

				JMap* JUtil::newInsertionOrderMap(){
					return null;
				}

				JMap* JUtil::newMap(){
					return null;
				}

				JList* JUtil::newList(){
					return null;
				}

				JList* JUtil::newList(JCollection* c){
					return null;
				}

				JSet* JUtil::newSet(){
					return null;
				}
				JHashMap* JUtil::newIdentityHashMap(){
					return null;
				}

				JSortedMap* JUtil::newSortedMap(){
					return null;
				}


				JUtil::~JUtil(){
				}
			}
		}
	}
}
