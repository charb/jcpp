#ifndef JCPP_GC_IOBJECTINFOGROUPVISITOR_H
#define JCPP_GC_IOBJECTINFOGROUPVISITOR_H

#include "jcpp/gc/ObjectInfoGroup.h"
#include "jcpp/gc/info/FieldInfo.h"
#include "jcpp/gc/info/ObjectInfo.h"

using namespace jcpp::gc::info;

namespace jcpp {
	namespace gc {
		namespace visitor {


			class JCPP_EXPORT IObjectInfoGroupVisitor {

				public:
					virtual void startVisitObjectInfoGroup(ObjectInfoGroup *oi) = 0;
					virtual void startVisitObjectInfo(ObjectInfo *oi) = 0;
					virtual void visitFieldInfo(FieldInfo *fi) = 0;
					virtual void endVisitObjectInfo(ObjectInfo *oi) = 0;
					virtual void endVisitObjectInfoGroup(ObjectInfoGroup *oi) = 0;
					virtual ~IObjectInfoGroupVisitor() = 0;
			};

		}
	}
}

#endif
