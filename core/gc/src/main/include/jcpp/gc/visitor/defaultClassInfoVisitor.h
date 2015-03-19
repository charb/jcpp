#ifndef JCPP_GC_DefaULTCLASSINFOVISITOR_H
#define JCPP_GC_DefaULTCLASSINFOVISITOR_H

#include "jcpp/gc/visitor/IClassInfoVisitor.h"

namespace jcpp {
	namespace gc {
		namespace visitor {

			class DefaultClassInfoVisitor : public IClassInfoVisitor {
			public:
				virtual void startVisitClassInfo(ClassInfo *ci);
				virtual void visitStaticFieldInfo(FieldInfo *fi);
				virtual void endVisitClassInfo(ClassInfo *ci);
				virtual ~DefaultClassInfoVisitor();
			};

		}
	}
}

#endif
