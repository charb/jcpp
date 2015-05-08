/*
 * JOutlookTestSuite.h
 *
 *  Created on: May 8, 2015
 *      Author: zrenno
 */

#ifndef JOUTLOOKTESTSUITE_H_
#define JOUTLOOKTESTSUITE_H_

#include "jcpp/lang/JString.h"
#include "junit/framework/JTestSuite.h"

using namespace junit::framework;

namespace jcpp{
	namespace outlook{
		namespace tests{

			// @Class(canonicalName="jcpp.outlook.tests.OutlookTestSuite", simpleName="OutlookTestSuite");
		    class JCPP_EXPORT JOutlookTestSuite : public JTestSuite{
		    public:
		        JOutlookTestSuite();

		        static JClass* getClazz();

		        static JOutlookTestSuite* suite();

		        virtual ~JOutlookTestSuite();
		    };
		}
	}
}
#endif
