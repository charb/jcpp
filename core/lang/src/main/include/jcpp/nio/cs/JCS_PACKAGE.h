#ifndef JCPP_NIO_CS_JCS_PACKAGE_H
#define JCPP_NIO_CS_JCS_PACKAGE_H

#include "jcpp/lang/reflect/JPackage.h"
#include "jcpp/util/JList.h"

using namespace jcpp::lang::reflect;
using namespace jcpp::util;

namespace jcpp{
	namespace nio{
		namespace cs{

		class JCPP_EXPORT JCS_PACKAGE : public JPackage{
		protected:
			JCS_PACKAGE();

		public:
			static JCS_PACKAGE* getPackage();

			virtual JPackage* getSuperPackage();

			virtual JList* getPackages();

			virtual ~JCS_PACKAGE();

		};


		}
	}
}

#endif /* JCS_PACKAGE_H_ */
