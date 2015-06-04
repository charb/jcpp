/*
 * JOutlook.h
 *
 *  Created on: Apr 17, 2015
 *      Author: zrenno
 */

#ifndef APPLICATION_OUTLOOK_OUTLOOK_H
#define APPLICATION_OUTLOOK_OUTLOOK_H


#include "jcpp/outlook/client/JIOutlook.h"
#include "jcpp/outlook/client/JMailMessage.h"

using namespace jcpp::lang;
using namespace jcpp::util;
using namespace jcpp;
using namespace jcpp::outlook::client;

namespace jcpp {
	namespace outlook {
		namespace server{
			// @Class(canonicalName="outlook.server.Outlook", simpleName="Outlook");
			class JCPP_EXPORT JOutlook : public JObject, public JIOutlook{
			private:
				JString* tempFolder;
				JInteger* fileCounter;

				// @IgnoreReflection()
				jbool openMail(JList *to, JList *cc, JList *bcc, JString *text, JString *subject, jbool isHTML, jbool gui);
				// @IgnoreReflection()
				void addRecipients(JList *to, jlong type, void *v, int start);
				// @IgnoreReflection()
				char * heapedString(JString * st);

				static void init();

			public:
				static jcpp::lang::JClass* getClazz();

				JOutlook(JString* tempFolder);

				virtual void openMailMessageInOutlook(JMailMessage *msg);

				virtual void setTempFolder(JString* path);

				virtual JString* getTempFolder();

				virtual ~JOutlook();
			};
		}
	}
}





#endif
