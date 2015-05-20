#include "jcpp/lang/info/JObjectInfoGroupVisitor.h"
#include "jcpp/lang/JString.h"
#include "jcpp/lang/JPrimitiveLong.h"
#include "jcpp/lang/JSystem.h"
#include "jcpp/util/JArrayList.h"

namespace jcpp {
	namespace lang {
		namespace info {
			JObjectInfoGroupVisitor::JObjectInfoGroupVisitor() /*:
			 JObject(getClazz())*/{
				current = null;
				result = new JArrayList(100000);
			}
			void JObjectInfoGroupVisitor::startVisitObjectInfoGroup(ObjectInfoGroup *oig){
			current = new JObjectInfo(((new JStringBuilder())->append(oig->getObjectInfos()[oig->getSize() - 1]->getClassInfo()
													->getClassName()->getString().c_str()))->toString(), new JPrimitiveLong(oig->getAddress()));
			}

			void JObjectInfoGroupVisitor::startVisitObjectInfo(ObjectInfo *oi){
			}

			void JObjectInfoGroupVisitor::visitFieldInfo(FieldInfo *fi){
				current->addReference( new JFieldInfo(((new JStringBuilder())->append(fi->getName()->getString().c_str() ) )->toString(), new JPrimitiveLong(fi->getPointedToAddress())));
			}

			void JObjectInfoGroupVisitor::endVisitObjectInfo(ObjectInfo *oi){
			}

			void JObjectInfoGroupVisitor::endVisitObjectInfoGroup(ObjectInfoGroup *oi){
				result->add(current);

			}

			JObjectInfoGroupVisitor::~JObjectInfoGroupVisitor(){
			}

			JList *JObjectInfoGroupVisitor::getResult(){
				return this->result;
			}
		}
	}
}

