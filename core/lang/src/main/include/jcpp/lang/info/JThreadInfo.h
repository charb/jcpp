#ifndef JCPP_LANG_INFO_JTHREADINFO_H_
#define JCPP_LANG_INFO_JTHREADINFO_H_

#include "jcpp/lang/JObject.h"
#include "jcpp/util/JArrayList.h"
#include "jcpp/lang/JPrimitiveLong.h"
#include "jcpp/lang/info/JMethodCallInfo.h"

using namespace jcpp::lang;
using namespace jcpp::util;

namespace jcpp {
	namespace lang {
		namespace info {

			//@Class(canonicalName="java.lang.info.ThreadInfo", simpleName="ThreadInfo");
			class JCPP_EXPORT JThreadInfo: public JObject{

			private:
				JPrimitiveLong* threadID;
				JList* methodCallInfos;

			public:
				JThreadInfo(JPrimitiveLong* threadID);

				void pushMethodCallInfo(JMethodCallInfo* methodCallInfo);

				void popMethodCallInfo();

				JList* getMethodCallInfos();

				jbool hasMethodCalls();

				jint getSize();

				JPrimitiveLong* getThreadID();

				static jcpp::lang::JClass* getClazz();

				virtual ~JThreadInfo();

			};
		}
	}
}

#endif
