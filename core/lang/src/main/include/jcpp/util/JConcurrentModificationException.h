#ifndef JCPP_UTIL_JCONCURRENTMODIFICATIONEXCEPTION_H
#define JCPP_UTIL_JCONCURRENTMODIFICATIONEXCEPTION_H

#include "jcpp/lang/JRuntimeException.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace util{

    	// @Class(canonicalName="java.util.ConcurrentModificationException", simpleName="ConcurrentModificationException");
        class JCPP_EXPORT JConcurrentModificationException : public JRuntimeException{
        private:
        	static const jlong serialVersionUID = 3666751008965953603LL;

        protected:
            JConcurrentModificationException(jcpp::lang::JClass* _class);

        public:
            JConcurrentModificationException();

            JConcurrentModificationException(JString* message);

            static jcpp::lang::JClass* getClazz();

            virtual ~JConcurrentModificationException();
        };
    }
}
#endif
