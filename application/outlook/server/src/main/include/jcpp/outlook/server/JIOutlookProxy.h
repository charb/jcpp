/*
 * JIOutlook.h
 *
 *  Created on: Apr 17, 2015
 *      Author: zrenno
 */

#ifndef APPLICATION_OUTLOOK_IOUTLOOK_PROXY_H
#define APPLICATION_OUTLOOK_IOUTLOOK_PROXY_H


#include "jcpp/outlook/client/JIOutlook.h"
#include "jcpp/lang/reflect/JProxy.h"

using namespace jcpp::lang::reflect;
using namespace jcpp::lang;
using namespace jcpp::util;
using namespace jcpp;
using namespace jcpp::outlook::client;

namespace jcpp{
	namespace outlook {
		namespace server{
			// @Class(canonicalName="outlook.server.IOutlookProxy", simpleName="IOutlookProxy");
			class JCPP_EXPORT JIOutlookProxy : public JProxy, public JIOutlook {

			public:
				JIOutlookProxy();

				static jcpp::lang::JClass* getClazz();

				virtual void openMailMessageInOutlook(JMailMessage *msg);

				virtual ~JIOutlookProxy();
			};
		}
	}
}





#endif
