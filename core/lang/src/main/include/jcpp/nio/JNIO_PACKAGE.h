#ifndef JCPP_JNIO_PACKAGE_H
#define JCPP_JNIO_PACKAGE_H

#include "jcpp/lang/reflect/JPackage.h"
#include "jcpp/util/JList.h"

using namespace jcpp::lang::reflect;
using namespace jcpp::util;

namespace jcpp{
	namespace nio{

		class JCPP_EXPORT JNIO_PACKAGE : public JPackage{
		protected:
			JNIO_PACKAGE();

		public:
			static JNIO_PACKAGE* getPackage();

			virtual JPackage* getSuperPackage();

			virtual JList* getPackages();

			virtual ~JNIO_PACKAGE();
		};

	}
}

#endif /* JNIO_PACKAGE_H_ */
