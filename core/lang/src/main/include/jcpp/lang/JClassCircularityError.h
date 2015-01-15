#ifndef JCPP_LANG_JCLASS_CIRCULARITY_ERROR_H
#define JCPP_LANG_JCLASS_CIRCULARITY_ERROR_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JLinkageError.h"

namespace jcpp{
    namespace lang{

    	// @Class(canonicalName="java.lang.ClassCircularityError", simpleName="ClassCircularityError");
        class JCPP_EXPORT JClassCircularityError : public JLinkageError {
        private:
        	static const jlong serialVersionUID = 1054362542914539689LL;

        protected:
            JClassCircularityError(jcpp::lang::JClass* _class);

        public:
            JClassCircularityError();

            JClassCircularityError(JString* message);

            static jcpp::lang::JClass* getClazz();
            
            virtual ~JClassCircularityError();
        };
    }
}

#endif
