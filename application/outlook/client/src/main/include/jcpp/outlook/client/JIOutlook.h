/*
 * JIOutlook.h
 *
 *  Created on: Apr 17, 2015
 *      Author: zrenno
 */

#ifndef APPLICATION_OUTLOOK_IOUTLOOK_H
#define APPLICATION_OUTLOOK_IOUTLOOK_H


#include "jcpp/outlook/client/JMailMessage.h"

using namespace jcpp::lang;
using namespace jcpp::util;
using namespace jcpp;


namespace jcpp{
	namespace outlook {
		namespace client{
			// @Class(canonicalName="outlook.client.IOutlook", simpleName="IOutlook");
			class JCPP_EXPORT JIOutlook : public JInterface {

			public:
				static jcpp::lang::JClass* getClazz();

				virtual void openMailMessageInOutlook(JMailMessage *msg) = 0;

				virtual ~JIOutlook();
			};
		}
	}
}





#endif
