#include "jcpp/nio/charset/JCodingErrorAction.h"


namespace jcpp {
	namespace nio {
		namespace charset {

		JCodingErrorAction* JCodingErrorAction::IGNORE= new JCodingErrorAction(new JString("IGNORE"));
		JCodingErrorAction* JCodingErrorAction::REPLACE = new JCodingErrorAction(new JString("REPLACE"));
		JCodingErrorAction* JCodingErrorAction::REPORT = new JCodingErrorAction(new JString("REPORT"));

		JCodingErrorAction::JCodingErrorAction(JString* name)
			:	JObject(getClazz())
		{
			this->name = name;
		}


		JString* JCodingErrorAction::toString(){
			return this->name;
		}

		JCodingErrorAction::~JCodingErrorAction()
		{	}


		}
	}
}
