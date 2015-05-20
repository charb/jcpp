#include "jcpp/lang/info/JMethodCallVisitor.h"
#include "jcpp/lang/info/JMethodObjectInfo.h"
using namespace jcpp::gc::info;
using namespace jcpp::gc::visitor;
using namespace jcpp::gc;
using namespace jcpp::lang::info;
using namespace jcpp::lang;
using namespace jcpp::native::api;
using namespace jcpp::native;

namespace jcpp {
	namespace lang {
		namespace info {

			JMethodCallVisitor::JMethodCallVisitor(){
				result = new JArrayList(10);

				currentThreadInfo = null;
				currentMethodCallInfo = null;
			}
			void JMethodCallVisitor::startVisitThreadInfo(ThreadInfo *ti){

				currentThreadInfo = new JThreadInfo(new JPrimitiveLong(ti->getNativeThread()->getId()));
			}
			void JMethodCallVisitor::startVisitMethodCallInfo(MethodCallInfo *mi){
				currentMethodCallInfo = new JMethodCallInfo();
				//currentMethodCallInfo = new JMethodCallInfo(((new JStringBuilder())->append(mi->getName()->getString().c_str()))->toString(), new JObjectInfo((new JStringBuilder())->append(mi->getObjectInfo()->getClassInfo()->getClassName()->getString().c_str())->toString(), new JPrimitiveLong(mi->getObjectInfo()->getAddress())));
			}
			void JMethodCallVisitor::visitParameterInfo(ParameterInfo *pi){
				currentMethodCallInfo->addMethodObject(new JMethodObjectInfo(new JPrimitiveLong(pi->getPointedToAddress())));
			}
			void JMethodCallVisitor::visitVariableInfo(VariableInfo *vi){
				if(vi != NULL) {
					currentMethodCallInfo->addMethodObject(new JMethodObjectInfo(new JPrimitiveLong(vi->getPointedToAddress())));
				}
			}
			void JMethodCallVisitor::endVisitMethodCallInfo(MethodCallInfo *mi){
				currentThreadInfo->pushMethodCallInfo(currentMethodCallInfo);
			}
			void JMethodCallVisitor::endVisitThreadInfo(ThreadInfo *ti){
				result->add(currentThreadInfo);
			}

			JList* JMethodCallVisitor::getResult(){
				return result;
			}

			JMethodCallVisitor::~JMethodCallVisitor(){

			}

		}
	}
}
