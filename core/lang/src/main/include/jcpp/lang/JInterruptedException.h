#ifndef JCPP_LANG_JINTERRUPTED_EXCEPTION_H
#define JCPP_LANG_JINTERRUPTED_EXCEPTION_H

#include "jcpp/lang/JException.h"
#include "jcpp/lang/JClass.h"

namespace jcpp{
    namespace lang{

    	// @Class(canonicalName="java.lang.InterruptedException", simpleName="InterruptedException");
        class JCPP_EXPORT JInterruptedException : public JException{
        private:
        	static const jlong serialVersionUID = 6700697376100628473LL;

        public:
            JInterruptedException();

            JInterruptedException(JString* message);

            static jcpp::lang::JClass* getClazz();

            virtual ~JInterruptedException();
        };
    }
}

#endif
