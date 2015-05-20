#ifndef JCPP_LANG_INFO_JOBJECTINFO_H
#define JCPP_LANG_INFO_JOBJECTINFO_H

#include "jcpp/lang/JObject.h"
#include "jcpp/util/JSet.h"
#include "jcpp/util/JHashSet.h"
#include "jcpp/lang/info/JFieldInfo.h"
#include "jcpp/gc/info/ObjectInfo.h"

using namespace jcpp::lang;
using namespace jcpp::util;
using namespace jcpp::gc::info;

namespace jcpp{
	namespace lang{
		namespace info{
			// @Class(canonicalName="java.lang.info.ObjectInfo", simpleName="ObjectInfo");
			class JCPP_EXPORT JObjectInfo : public JObject {
				private:
					JString *className;
					JPrimitiveLong *address;
					JSet *references;

				public:
					static jcpp::lang::JClass* getClazz();

					JObjectInfo(JString *_className, JPrimitiveLong *_address);

					JString *getClassName();
					JPrimitiveLong *getAddress();
					JSet *getReferences();
					void addReference(JFieldInfo *reference);

					virtual ~JObjectInfo();
			};

		}
	}
}

#endif
