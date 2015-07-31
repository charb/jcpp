/*
 * SortedMap.h
 *
 *  Created on: Jul 21, 2015
 *      Author: mmaarouf
 */

#ifndef SORTEDMAP_H_
#define SORTEDMAP_H_

#include "jcpp/util/JMap.h"


// Note: some of the java.util.SortedMap methods are missing

namespace jcpp{
	namespace util{

		class JComparator;
		class JSet;

		class JCPP_EXPORT JSortedMap: virtual public JMap{
		public:

			virtual JComparator* getComparator() = 0;

			virtual JSortedMap* subMap(JObject* fromKey, JObject* toKey) = 0;

			virtual JObject* firstKey() = 0;

			virtual JObject* lastKey() = 0;

			virtual JSet* entrySet() = 0;

			static jcpp::lang::JClass* getClazz();
			virtual ~JSortedMap();
		};
	}
}



#endif /* SORTEDMAP_H_ */
