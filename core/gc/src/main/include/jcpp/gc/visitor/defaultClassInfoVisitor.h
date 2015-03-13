#ifndef JCPP_GC_DEFAULTCLASSINFOVISITOR_H
#define JCPP_GC_DEFAULTCLASSINFOVISITOR_H

#include "jcpp/gc/visitor/IClassInfoVisitor.h"

namespace jcpp {
	namespace gc {
		namespace visitor {

			class defaultClassInfoVisitor : public IClassInfoVisitor {
			public:
				virtual void startVisitClassInfo(ClassInfo *ci);
				virtual void visitStaticFieldInfo(FieldInfo *fi);
				virtual void endVisitClassInfo(ClassInfo *ci);
				virtual ~defaultClassInfoVisitor();
			};

		}
	}
}

#endif
