#include "jcpp/lang/info/JClassInfoVisitor.h"
#include "jcpp/lang/JString.h"
#include "jcpp/lang/JPrimitiveLong.h"
#include "jcpp/lang/JSystem.h"
#include "jcpp/util/JArrayList.h"

namespace jcpp {
	namespace lang {
		namespace info {
			JClassInfoVisitor::JClassInfoVisitor(){
				current = null;
				result = new JArrayList(10);
			}
			void JClassInfoVisitor::startVisitClassInfo(ClassInfo *ci){
				current = new JClassInfo((new JStringBuilder())->append(ci->getNamespaceName()->getString().c_str())->toString(), (new JStringBuilder())->append(ci->getClassName()->getString().c_str())->toString(), ci->getStaticFieldCount());
			}
			void JClassInfoVisitor::visitStaticFieldInfo(FieldInfo *fi){

				current->addStaticFieldInfo(new JFieldInfo((new JStringBuilder())->append(fi->getName()->getString().c_str())->toString(), new JPrimitiveLong(fi->getPointedToAddress()), fi->isStaticField()));
			}
			void JClassInfoVisitor::endVisitClassInfo(ClassInfo *ci){
				result->add(current);
			}

			JList* JClassInfoVisitor::getResult(){
				return this->result;
			}

			JClassInfoVisitor::~JClassInfoVisitor(){
			}
		}
	}
}
