/*
 * JNavigableSet.h
 *
 *  Created on: Jul 24, 2015
 *      Author: mmaarouf
 */

#ifndef JNAVIGABLESET_H_
#define JNAVIGABLESET_H_

#include "jcpp/util/JSortedSet.h"


namespace jcpp{
	namespace util{

		class JCPP_EXPORT JNavigableSet: public JSortedSet{
		public:
			virtual JObject* lower(JObject* e) = 0;

			virtual JObject* floor(JObject* e) = 0;

			virtual JObject* ceiling(JObject* e) = 0;

			virtual JObject* higher(JObject* e) = 0;

			virtual JObject* pollFirst() = 0;

			virtual JObject* pollLast() = 0;

			virtual JIterator* iterator() = 0;

			virtual JNavigableSet* descendingSet() = 0;

			virtual JIterator* descendingIterator() = 0;

			virtual JNavigableSet* subSet(JObject* fromElement, jbool fromInclusive, JObject* toElement, jbool toInclusive) = 0;

			virtual JNavigableSet* headSet(JObject* toElement, jbool inclusive) = 0;

			virtual JNavigableSet* tailSet(JObject* fromElement, jbool inclusive) = 0;

			virtual JSortedSet* subSet(JObject* fromElement, JObject* toElement) = 0;

			virtual JSortedSet* headSet(JObject* toElement) = 0;

			virtual JSortedSet* tailSet(JObject* fromElement) = 0;

			static jcpp::lang::JClass* getClazz();
			virtual ~JNavigableSet();
		};
	}
}



#endif /* JNAVIGABLESET_H_ */
