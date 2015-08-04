/*
 * JNavigableMap.h
 *
 *  Created on: Jul 27, 2015
 *      Author: mmaarouf
 */

#ifndef JNAVIGABLEMAP_H_
#define JNAVIGABLEMAP_H_

#include "jcpp/util/JSortedMap.h"

namespace jcpp{
	namespace util{

		class JMap;
		class JSortedMap;
		class JNavigableSet;


		// @Class(canonicalName="java.util.NavigableMap", simpleName="NavigableMap");
		class JNavigableMap: public JSortedMap{
		public:
			virtual JMap::JEntry* lowerEntry(JObject* key) = 0;

			virtual JObject* lowerKey(JObject* key) = 0;

			virtual JMap::JEntry* floorEntry(JObject* key) = 0;

			virtual JObject* floorKey(JObject* key) = 0;

			virtual JMap::JEntry* ceilingEntry(JObject* key) = 0;

			virtual JObject* ceilingKey(JObject* key) = 0;

			virtual JMap::JEntry* higherEntry(JObject* key) = 0;

			virtual JObject* higherKey(JObject* key) = 0;

			virtual JMap::JEntry* firstEntry() = 0;

			virtual JMap::JEntry* lastEntry() = 0;

			virtual JMap::JEntry* pollFirstEntry() = 0;

			virtual JMap::JEntry* pollLastEntry() = 0;

			virtual JNavigableMap* descendingMap() = 0;

			virtual JNavigableSet* navigableKeySet() = 0;

			virtual JNavigableSet* descendingKeySet() = 0;

			virtual JNavigableMap* subMap(JObject* fromKey, jbool fromInclusive, JObject* toKey, jbool toInclusive) = 0;

			virtual JNavigableMap* headMap(JObject* toKey, jbool inclusive) = 0;

			virtual JNavigableMap* tailMap(JObject* fromKey, jbool inclusive) = 0;

			virtual JSortedMap* subMap(JObject* fromKey, JObject* toKey) = 0;

			virtual JSortedMap* headMap(JObject* toKey) = 0;

			virtual JSortedMap* tailMap(JObject* fromKey)= 0;

			static jcpp::lang::JClass* getClazz();
			virtual ~JNavigableMap();

		};
	}
}



#endif /* JNAVIGABLEMAP_H_ */
