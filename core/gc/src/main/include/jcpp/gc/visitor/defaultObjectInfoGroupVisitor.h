#ifndef JCPP_GC_DEFAULTOBJECTINFOGROUPVISITOR_H
#define JCPP_GC_DEFAULTOBJECTINFOGROUPVISITOR_H

#include "jcpp/gc/visitor/IObjectInfoGroupVisitor.h"

using namespace jcpp::gc::info;

namespace jcpp {
	namespace gc {
		namespace visitor {

			class defaultObjectInfoGroupVisitor : public IObjectInfoGroupVisitor {
				public:
					virtual void startVisitObjectInfoGroup(ObjectInfoGroup *oi);
					virtual void startVisitObjectInfo(ObjectInfo *oi);
					virtual void visitFieldInfo(FieldInfo *fi);
					virtual void endVisitObjectInfo(ObjectInfo *oi);
					virtual void endVisitObjectInfoGroup(ObjectInfoGroup *oi);
					virtual ~defaultObjectInfoGroupVisitor();
			};

		}
	}
}

#endif
