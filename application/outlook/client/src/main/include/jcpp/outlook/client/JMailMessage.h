/*
 * mailmessage.h
 *
 *  Created on: Apr 17, 2015
 *      Author: zrenno
 */

#ifndef APPLICATION_OUTLOOK_MAIL_MESSAGE_H
#define APPLICATION_OUTLOOK_MAIL_MESSAGE_H

#include "jcpp/lang/JSystem.h"
#include "jcpp/lang/JString.h"
#include "jcpp/util/JList.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"

using namespace jcpp::lang;
using namespace jcpp::util;
using namespace jcpp;

namespace jcpp {
	namespace outlook {
		namespace client{

			// @Class(canonicalName="outlook.client.MailMessage", simpleName="MailMessage");
			class JCPP_EXPORT JMailMessage : public JObject, JSerializable {
			private:
				static const jlong serialVersionUID = 5916566037215035809LL;

				JList *ccList;
				JList *bccList;
				JList *toList;
				JString *body;
				JString *subject;
				JString *tempFolder;

			public:
				JMailMessage();

				JList* getCcList();
				void setCcList(JList* ccList);

				JList* getBccList();
				void setBccList(JList* bccList);

				JList* getToList();
				void setToList(JList* toList);

				JString* getSubject();
				void setSubject(JString* subject);

				JString* getBody();
				void setBody(JString* body);

				JString* getTempFolder();
				void setTempFolder(JString* tempFolder);

				static JClass* getClazz();

				virtual ~JMailMessage();
			};
		}
	}
}




#endif
