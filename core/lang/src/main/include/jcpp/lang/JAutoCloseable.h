#ifndef JCPP_LANG_JAUTOCLOSEABLE_H
#define JCPP_LANG_JAUTOCLOSEABLE_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"

namespace jcpp{
    namespace lang{

    	// @Class(canonicalName="java.lang.AutoCloseable", simpleName="AutoCloseable");
        class JCPP_EXPORT JAutoCloseable : public JInterface{
        public:
            static jcpp::lang::JClass* getClazz();

            virtual void close()=0;

            virtual ~JAutoCloseable();
        };
    }
}
#endif
