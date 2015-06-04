#ifndef APPLICATION_OUTLOOK_IOUTLOOKSERVER_H
#define APPLICATION_OUTLOOK_IOUTLOOKSERVER_H


#include "jcpp/outlook/client/JIOutlook.h"
#include "jcpp/lang/JString.h"

using namespace jcpp::lang;
using namespace jcpp::util;
using namespace jcpp;


namespace jcpp{
	namespace outlook {
		namespace client{
			// @Class(canonicalName="outlook.client.IOutlookServer", simpleName="IOutlookServer");
			class JCPP_EXPORT JIOutlookServer : public JInterface {

			public:
				static jcpp::lang::JClass* getClazz();

				virtual void setTempFolder(JString* path) = 0;

				virtual JString* getTempFolder() = 0;

				virtual void openMailMessageInOutlook(JMailMessage *msg) = 0;

				virtual void shutdown() = 0;

				virtual ~JIOutlookServer();
			};
		}
	}
}





#endif
