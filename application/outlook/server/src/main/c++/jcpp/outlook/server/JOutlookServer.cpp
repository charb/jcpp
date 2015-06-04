#include "jcpp/outlook/server/JOutlookServer.h"
#include "org/apache/commons/cli/JOptions.h"
#include "org/apache/commons/cli/JCommandLineParser.h"
#include "org/apache/commons/cli/JDefaultParser.h"
#include "org/apache/commons/cli/JCommandLine.h"

using namespace org::apache::commons::cli;

namespace jcpp {
	namespace outlook {
		namespace server {

		void JOutlookServer::main(JPrimitiveObjectArray* args) {
			JOutlookServer* server = new JOutlookServer(new JString("."));

			jint argc = args->size();
			jint port = JInteger::valueOf(reinterpret_cast<JString*>(args->get(argc-1)))->intValue();
			server->init(port);
		}

		JOutlookServer::JOutlookServer(JString* tempFolder) : JObject(getClazz()) {
			this->tempFolder = tempFolder;
		}

		void JOutlookServer::init(int port) {
			JAddress* adr=new JAddress();
			adr->setHostName(JInetAddress::getLocalHost()->getHostName());
			adr->setPort(port);
			JEndPoint* localEndPoint1=new JEndPoint(adr,new JString("site1"));

			//initializing server
			JTransportRouter* router1=new JTransportRouter();
			JConnectionConfiguration* cc1=new JConnectionConfiguration();
			server1=new JServer(localEndPoint1,router1,cc1);

			//exporting object
			outlook = new JOutlook(tempFolder);
			JList *interfaces = new JArrayList();
			interfaces->add(JIOutlook::getClazz());
			server1->getIRegistry()->bind(JIOutlook::getClazz()->getName(), outlook, interfaces);

			interfaces = new JArrayList();
			interfaces->add(JIOutlookServer::getClazz());
			server1->getIRegistry()->bind(JIOutlookServer::getClazz()->getName(), this, interfaces);

            synchronized(this,{
                wait();
            })
		}

		void JOutlookServer::setTempFolder(JString* path) {
			this->tempFolder = path;
			if (outlook!=NULL){
				outlook->setTempFolder(path);
			}
		}

		JString* JOutlookServer::getTempFolder() {
			return tempFolder;
		}

		void JOutlookServer::openMailMessageInOutlook(JMailMessage *msg) {
			outlook->openMailMessageInOutlook(msg);
		}

		void JOutlookServer::shutdown() {
			try {
				server1->unexport();
			} catch(...) {
			}
			synchronized(this,{
				notifyAll();
			})
		}

		JOutlookServer::~JOutlookServer() {
		}

		}
	}
}
