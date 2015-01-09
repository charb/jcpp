#include "jcpp/nio/charset/JCodingErrorAction.h"


namespace jcpp {
	namespace nio {
		namespace charset {

		const JCodingErrorAction* JCodingErrorAction::IGNORE= new JCodingErrorAction(new JString("IGNORE"));
		const JCodingErrorAction* JCodingErrorAction::REPLACE = new JCodingErrorAction(new JString("REPLACE"));
		const JCodingErrorAction* JCodingErrorAction::REPORT = new JCodingErrorAction(new JString("REPORT"));

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
