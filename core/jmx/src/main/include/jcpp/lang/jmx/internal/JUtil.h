/*
 * JUtil.h
 *
 *  Created on: Jul 31, 2015
 *      Author: mmaarouf
 */

#ifndef JUTIL_H_
#define JUTIL_H_

#include "jcpp/lang/JObject.h"


namespace jcpp{
	namespace util{
		class JMap;
		class JList;
		class JSet;
		class JHashMap;
		class JSortedMap;
		class JCollection;
	}
	namespace lang{
		class JClass;
	}
}

using namespace jcpp::util;

namespace jcpp{
	namespace lang{
		namespace jmx{
			namespace internal{

				class JCPP_EXPORT JUtil: public JObject{
				private:
					JUtil();
				public:

					static JMap* newInsertionOrderMap();

					static JMap* newMap();

					static JList* newList();

					static JList* newList(JCollection* c);

					static JSet* newSet();

					static JHashMap* newIdentityHashMap();


					static JClass* getClazz();
					virtual ~JUtil();
				};
			}
		}
	}
}


#endif /* JUTIL_H_ */
