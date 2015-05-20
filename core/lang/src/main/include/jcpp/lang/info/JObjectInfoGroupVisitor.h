#ifndef JCPP_LANG_INFO_JOBJECTINFOGROUPVISITOR_H
#define JCPP_LANG_INFO_JOBJECTINFOGROUPVISITOR_H


#include "jcpp/lang/JObject.h"
#include "jcpp/gc/ObjectInfoGroup.h"
#include "jcpp/gc/info/ObjectInfo.h"
#include "jcpp/gc/info/FieldInfo.h"
#include "jcpp/lang/info/JObjectInfo.h"
#include "jcpp/lang/info/JFieldInfo.h"
#include "jcpp/gc/visitor/IObjectInfoGroupVisitor.h"
#include "jcpp/util/JList.h"

using namespace jcpp::gc::info;
using namespace jcpp::gc::visitor;
using namespace jcpp::gc;
using namespace jcpp::lang::info;
using namespace jcpp::lang;

namespace jcpp {
	namespace lang {
		namespace info {

			// @IgnoreReflection();
			// @IgnorePackageReflection();
			class JCPP_EXPORT JObjectInfoGroupVisitor : public IObjectInfoGroupVisitor {
			private:
				JList* result;
				JObjectInfo* current;

			public:

				JObjectInfoGroupVisitor();
				//static jcpp::lang::JClass* getClazz();

				virtual JList *getResult();

				virtual void startVisitObjectInfoGroup(ObjectInfoGroup *oig);
				virtual void startVisitObjectInfo(ObjectInfo *oi);
				virtual void visitFieldInfo(FieldInfo *fi);
				virtual void endVisitObjectInfo(ObjectInfo *oi);
				virtual void endVisitObjectInfoGroup(ObjectInfoGroup *oi);

				virtual ~JObjectInfoGroupVisitor();
			};
		}
	}
}

#endif
