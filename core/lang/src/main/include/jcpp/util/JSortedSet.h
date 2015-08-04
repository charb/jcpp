/*
 * JSortedSet.h
 *
 *  Created on: Jul 24, 2015
 *      Author: mmaarouf
 */

#include "jcpp/util/JSet.h"


#ifndef JSORTEDSET_H_
#define JSORTEDSET_H_



namespace jcpp{
	namespace util{

		class JComparator;

		// @Class(canonicalName="java.util.SortedSet", simpleName="SortedSet");
		class JCPP_EXPORT JSortedSet: public JSet{
		public:

			virtual JComparator* comparator() = 0;

			virtual JSortedSet* subSet(JObject* fromElement, JObject* toElement) = 0;

			virtual JSortedSet* headSet(JObject* toElement) = 0;

			virtual JSortedSet* tailSet(JObject* fromElement) = 0;

			virtual JObject* first() = 0;

			virtual JObject* last() = 0;

			static jcpp::lang::JClass* getClazz();
			virtual ~JSortedSet();
		};
	}
}



#endif /* JSORTEDSET_H_ */
