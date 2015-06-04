#ifndef APPLICATION_OUTLOOK_OUTLOOKSERVER_H
#define APPLICATION_OUTLOOK_OUTLOOKSERVER_H


#include "jcpp/outlook/client/JIOutlookServer.h"
#include "jcpp/lang/JString.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "jcpp/rmi/server/gateway/JAddress.h"
#include "jcpp/rmi/server/transport/JEndPoint.h"
#include "jcpp/rmi/server/transport/JTransportRouter.h"
#include "jcpp/rmi/server/connection/JConnectionConfiguration.h"
#include "jcpp/rmi/server/connection/JServer.h"
#include "jcpp/rmi/server/connection/JIRegistry.h"
#include "jcpp/outlook/server/JOutlook.h"

using namespace jcpp::lang;
using namespace jcpp::util;
using namespace jcpp;
using namespace jcpp::outlook::client;
using namespace jcpp::rmi::server::connection;

namespace jcpp{
	namespace outlook {
		namespace server{
			// @Class(canonicalName="outlook.server.OutlookServer", simpleName="OutlookServer");
			class JCPP_EXPORT JOutlookServer : public JObject, public JIOutlookServer {

			private:
				JString* tempFolder;
				JOutlook* outlook;
				JServer* server1;

			public:
				JOutlookServer(JString* tempFolder);

				static jcpp::lang::JClass* getClazz();

				static void main(JPrimitiveObjectArray* args);

				virtual void setTempFolder(JString* path);

				virtual JString* getTempFolder();

				virtual void openMailMessageInOutlook(JMailMessage *msg);

				virtual void init(int port);

				virtual void shutdown();

				virtual ~JOutlookServer();
			};
		}
	}
}





#endif
