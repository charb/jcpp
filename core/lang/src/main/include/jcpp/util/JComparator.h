#ifndef JCPP_UTIL_JCOMPARATOR_H
#define JCPP_UTIL_JCOMPARATOR_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JInterface.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace util{

    	// @Class(canonicalName="java.util.Comparator", simpleName="Comparator");
        class JCPP_EXPORT JComparator : public JInterface{
        public:
            static JClass* getClazz();

            virtual jint compare(JObject* o1, JObject* o2)=0;

            virtual ~JComparator();
        };
    }
}

#endif
