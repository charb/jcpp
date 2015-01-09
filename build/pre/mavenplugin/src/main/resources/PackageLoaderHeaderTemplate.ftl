#ifndef ${model.name}_H
#define ${model.name}_H

#include "jcpp/lang/reflect/JPackage.h"
#include "jcpp/lang/reflect/JPackageLoader.h"

using namespace jcpp::lang::reflect;

class JCPP_EXPORT ${model.name} : public JPackageLoader {
public:
	${model.name}();

	virtual JPackage* getPackage();

    virtual ~${model.name}();
};


#endif
