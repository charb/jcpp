/*
 * JRepository.h
 *
 *  Created on: Jul 31, 2015
 *      Author: mmaarouf
 */

#ifndef JREPOSITORY_H_
#define JREPOSITORY_H_

#include "jcpp/lang/JObject.h"

namespace jcpp{
	namespace util{
		class JMap;
	}
	namespace lang{
		class JClass;
		class JString;
		class JInteger;
		class JPrimitiveObjectArray;
		namespace jmx{
			class JDynamicMBean;
			class JObjectName;
			namespace internal{
				class JNamedObject;
			}
		}
	}
}

using namespace jcpp::util;

namespace jcpp{
	namespace lang{
		namespace jmx{
			namespace internal{

			// @Class(canonicalName="com.sun.jmx.mbeanserver.Repository", simpleName="Repository");
				class JCPP_EXPORT JRepository:public JObject{
				private:
					JMap* domainTb;
					/*TODO volatile*/ jint nbElements;
					JString* domain;

					JObject* lock;	//TODO should be replaced by readWriteLock

					void addNewDomainMoi(JDynamicMBean* object, JString* dom, JObjectName* name);

					JNamedObject* retrieveNamedObject(JObjectName* name);

				public:
					JRepository(JString* domain, jbool fairLock);

					JPrimitiveObjectArray* getDomains();

					void addMBean(JDynamicMBean* object, JObjectName* name);

					jbool contains(JObjectName* name);

					JDynamicMBean* retrieve(JObjectName* name);

					JInteger* getCount();

					JString* getDefaultDomain();

					static JClass* getClazz();
					virtual ~JRepository();
				};
			}
		}
	}
}



#endif /* JREPOSITORY_H_ */
