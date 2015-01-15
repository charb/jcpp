#ifndef JCPP_LANG_JEXCEPTION_H
#define JCPP_LANG_JEXCEPTION_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JThrowable.h"

namespace jcpp{
    namespace lang{

    	// @Class(canonicalName="java.lang.Exception", simpleName="Exception");
        class JCPP_EXPORT JException: public JThrowable {
        private:
        	static const jlong serialVersionUID = -3387516993124229948LL;

        protected:
            JException(jcpp::lang::JClass* _class);

        public:
            JException();

            JException(JString* message);

            JException(JString* message, JThrowable *cause);

            static jcpp::lang::JClass* getClazz();

            virtual ~JException();
        };
    }
}


#endif
