#ifndef JCPP_LANG_JCHARSEQUENCE_H
#define JCPP_LANG_JCHARSEQUENCE_H

#include "jcpp/lang/JInterface.h"

namespace jcpp{
    namespace lang{
        class JString;

        class JCPP_EXPORT JCharSequence : public JInterface  {
            public:
                static jcpp::lang::JClass* getClazz();

                virtual jchar charAt(jint i)=0;

                virtual jint length()=0;

                virtual JCharSequence* subSequence(jint start, jint end)=0;

                virtual JString* toString()=0;

                virtual ~JCharSequence();
        };
    }
}

#endif
