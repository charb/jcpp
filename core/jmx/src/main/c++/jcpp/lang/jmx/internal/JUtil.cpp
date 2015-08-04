#include "jcpp/lang/jmx/internal/JUtil.h"
#include "jcpp/util/JMap.h"
#include "jcpp/util/JList.h"
#include "jcpp/util/JSet.h"
#include "jcpp/util/JHashMap.h"
#include "jcpp/util/JSortedMap.h"
#include "jcpp/util/JHashSet.h"

namespace jcpp{
	namespace lang{
		namespace jmx{
			namespace internal{
				JUtil::JUtil():JObject(JUtil::getClazz()){
				}


				JMap* JUtil::newInsertionOrderMap(){
					return new JHashMap();		// It should return LinkedHashMap;
				}

				JMap* JUtil::newMap(){
					return new JHashMap();
				}

				JList* JUtil::newList(){
					return new JArrayList();
				}

				JList* JUtil::newList(JCollection* c){
					return new JArrayList(c);
				}

				JSet* JUtil::newSet(){
					return new JHashSet();
				}
				JHashMap* JUtil::newIdentityHashMap(){				// TODO this should be IdentityHashMap
					return new JHashMap();
				}


				JUtil::~JUtil(){
				}
			}
		}
	}
}
