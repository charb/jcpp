#ifndef ${model.name}_H
#define ${model.name}_H

#include "jcpp/lang/reflect/JPackage.h"
#include "jcpp/util/JList.h"

using namespace jcpp::lang::reflect;
using namespace jcpp::util;

<#list model.namespaces as namespace>
namespace ${namespace}{
</#list>

	class JCPP_EXPORT ${model.name} : public JPackage {
	protected:
		${model.name}();
		
	public:
		static ${model.name}* getPackage();
		
		virtual JPackage* getSuperPackage();
		
		virtual JList* getPackages();
		
		virtual ~${model.name}();	
	};
	
<#list model.namespaces as namespace>
}
</#list>


#endif