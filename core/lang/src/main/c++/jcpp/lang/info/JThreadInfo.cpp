#include "jcpp/lang/info/JThreadInfo.h"

using namespace jcpp::lang;
using namespace jcpp::util;

namespace jcpp {
	namespace lang {
		namespace info {

			JThreadInfo::JThreadInfo(JPrimitiveLong* threadID) :
					threadID(threadID){
				this->methodCallInfos = new JArrayList(30);
			}

			void JThreadInfo::pushMethodCallInfo(JMethodCallInfo* methodCallInfo){
				this->methodCallInfos->add(0, methodCallInfo);
			}

			void JThreadInfo::popMethodCallInfo(){
				this->methodCallInfos->remove(0);
			}

			JList* JThreadInfo::getMethodCallInfos(){
				return this->methodCallInfos;
			}

			jbool JThreadInfo::hasMethodCalls(){
				return !(this->methodCallInfos->isEmpty());
			}

			jint JThreadInfo::getSize(){
				return this->methodCallInfos->size();
			}

			JPrimitiveLong* JThreadInfo::getThreadID(){
				return threadID;
			}

			JThreadInfo::~JThreadInfo(){
			}

		}

	}
}

