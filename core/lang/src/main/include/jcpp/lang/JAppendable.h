#ifndef JCPP_LANG_JAPPENDABLE_H
#define JCPP_LANG_JAPPENDABLE_H

#include "jcpp/lang/JCharSequence.h"
#include "jcpp/lang/JInterface.h"

namespace jcpp{
    namespace lang{

    	// @Class(canonicalName="java.lang.Appendable", simpleName="Appendable");
        class JCPP_EXPORT JAppendable : public JInterface  {
        public:
            static jcpp::lang::JClass* getClazz();

            virtual JAppendable* append(jchar c)=0;

            virtual JAppendable* append(JCharSequence* csq)=0;

            virtual JAppendable* append(JCharSequence* csq,jint start,jint end)=0;

            virtual ~JAppendable();
        };
    }
}

#endif
