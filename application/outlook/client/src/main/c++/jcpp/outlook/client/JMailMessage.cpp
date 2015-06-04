/*
 * JMailMessage.cpp
 *
 *  Created on: Apr 24, 2015
 *      Author: zrenno
 */
#include "jcpp/outlook/client/JMailMessage.h"


namespace jcpp {
	namespace outlook {
		namespace client{
			JMailMessage::JMailMessage() : JObject(getClazz()), ccList(NULL), bccList(NULL), toList(NULL), subject(NULL), body(NULL) {
			}

			JList* JMailMessage::getCcList(){
				if(ccList == NULL) {
					ccList = new JArrayList();
				}
				return this->ccList;
			}

			void JMailMessage::setCcList(JList* ccList){
				this->ccList = ccList;
			}

			JList* JMailMessage::getBccList(){
				if(bccList == NULL) {
					bccList = new JArrayList();
				}
				return this->bccList;
			}

			void JMailMessage::setBccList(JList* bccList){
				this->bccList = bccList;
			}

			JList* JMailMessage::getToList(){
				if(toList == NULL) {
					toList = new JArrayList();
				}
				return this->toList;
			}

			void JMailMessage::setToList(JList* tos){
				this->toList = toList;
			}

			JString* JMailMessage::getSubject(){
				return this->subject;
			}

			void JMailMessage::setSubject(JString* subject){
				this->subject = subject;
			}

			JString* JMailMessage::getBody(){
				return this->body;
			}

			void JMailMessage::setBody(JString* body){
				this->body = body;
			}

			JMailMessage::~JMailMessage() {

			}


		}
	}
}



