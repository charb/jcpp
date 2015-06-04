#include "jcpp/outlook/server/JIOutlookServerProxy.h"
#include "jcpp/outlook/server/JOutlook.h"
#include "jcpp/util/JList.h"
#include "jcpp/util/JArrayList.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JPrimitiveBoolean.h"

using namespace jcpp::lang::reflect;
using namespace jcpp::lang;
using namespace jcpp::util;
using namespace jcpp;


namespace jcpp{
	namespace outlook {
		namespace server{

		JIOutlookServerProxy::JIOutlookServerProxy():JProxy(getClazz()) {
		}

		void JIOutlookServerProxy::setTempFolder(JString* path) {
            JList* args=new JArrayList();
            args->add(dynamic_cast<JObject*>(path));
            JList* types=new JArrayList();
            types->add(JString::getClazz());
            invoke(new JString("setTempFolder"),types,args);
            return;
		}

		JString* JIOutlookServerProxy::getTempFolder() {
            JList* args=new JArrayList();
            JList* types=new JArrayList();
            return dynamic_cast<JString*>(invoke(new JString("getTempFolder"),types,args));
		}

		void JIOutlookServerProxy::openMailMessageInOutlook(JMailMessage *msg) {
            JList* args=new JArrayList();
            args->add(dynamic_cast<JObject*>(msg));
            JList* types=new JArrayList();
            types->add(JMailMessage::getClazz());
            invoke(new JString("openMailMessageInOutlook"),types,args);
            return;
		}

		void JIOutlookServerProxy::shutdown() {
            JList* args=new JArrayList();
            JList* types=new JArrayList();
            invoke(new JString("shutdown"),types,args);
            return;
		}

		JIOutlookServerProxy::~JIOutlookServerProxy(){
		}

		}
	}
}
