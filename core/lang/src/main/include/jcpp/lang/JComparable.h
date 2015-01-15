#ifndef JCPP_LANG_JCOMPARABLE_H
#define JCPP_LANG_JCOMPARABLE_H

#include "jcpp/lang/JInterface.h"

namespace jcpp{
    namespace lang{
        class JClass;
        class JObject;

        // @Class(canonicalName="java.lang.Comparable", simpleName="Comparable");
        class JCPP_EXPORT JComparable : public JInterface{
        public:
            static jcpp::lang::JClass* getClazz();

            virtual jint compareTo(JObject*)=0;

            virtual ~JComparable();
        };
    }
}

#endif
