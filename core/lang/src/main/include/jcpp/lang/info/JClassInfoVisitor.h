#ifndef JCPP_LANG_INFO_JCLASSINFOVISITOR_H_
#define JCPP_LANG_INFO_JCLASSINFOVISITOR_H_


#include "jcpp/gc/info/FieldInfo.h"
#include "jcpp/gc/info/ClassInfo.h"
#include "jcpp/lang/info/JClassInfo.h"
#include "jcpp/gc/visitor/IClassInfoVisitor.h"
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
			class JCPP_EXPORT JClassInfoVisitor: public IClassInfoVisitor {
			private:
				JList* result;
				JClassInfo* current;


			public:
				JClassInfoVisitor();
				virtual void startVisitClassInfo(ClassInfo *ci);
				virtual void visitStaticFieldInfo(FieldInfo *fi);
				virtual void endVisitClassInfo(ClassInfo *ci);
				JList* getResult();
				virtual ~JClassInfoVisitor();

			};
		}
	}
}



#endif
