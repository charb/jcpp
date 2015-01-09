#ifndef JCPP_NIO_CHARSET_PACKAGE_H
#define JCPP_NIO_CHARSET_PACKAGE_H

#include "jcpp/lang/reflect/JPackage.h"
#include "jcpp/util/JList.h"

using namespace jcpp::lang::reflect;
using namespace jcpp::util;

namespace jcpp{
	namespace nio{
		namespace charset{

		class JCPP_EXPORT JCHARSET_PACKAGE : public JPackage{
		protected:
			JCHARSET_PACKAGE();

		public:
			static JCHARSET_PACKAGE* getPackage();

			virtual JPackage* getSuperPackage();

			virtual JList* getPackages();

			virtual ~JCHARSET_PACKAGE();
		};


		}
	}
}


#endif /* JCHARSET_PACKAGE_H_ */
