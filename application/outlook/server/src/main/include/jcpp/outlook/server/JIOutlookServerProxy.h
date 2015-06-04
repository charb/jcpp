
#ifndef APPLICATION_OUTLOOK_IOUTLOOKSERVER_PROXY_H
#define APPLICATION_OUTLOOK_IOUTLOOKSERVER_PROXY_H


#include "jcpp/outlook/client/JIOutlookServer.h"
#include "jcpp/lang/reflect/JProxy.h"
#include "jcpp/lang/JString.h"

using namespace jcpp::lang::reflect;
using namespace jcpp::lang;
using namespace jcpp::util;
using namespace jcpp;
using namespace jcpp::outlook::client;

namespace jcpp{
	namespace outlook {
		namespace server{
			// @Class(canonicalName="outlook.server.IOutlookServerProxy", simpleName="IOutlookServerProxy");
			class JCPP_EXPORT JIOutlookServerProxy : public JProxy, public JIOutlookServer {

			public:
				JIOutlookServerProxy();

				static jcpp::lang::JClass* getClazz();

				virtual void setTempFolder(JString* path);

				virtual JString* getTempFolder();

				virtual void openMailMessageInOutlook(JMailMessage *msg);

				virtual void shutdown();

				virtual ~JIOutlookServerProxy();
			};
		}
	}
}





#endif
