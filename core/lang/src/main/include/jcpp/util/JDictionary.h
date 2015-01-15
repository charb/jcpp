#ifndef JCPP_UTIL_JDICTIONARY_H
#define JCPP_UTIL_JDICTIONARY_H

#include "jcpp/lang/JObject.h"
#include "jcpp/util/JEnumeration.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace util{

    	// @Class(canonicalName="java.util.Dictionary", simpleName="Dictionary");
        class JCPP_EXPORT JDictionary : public JObject{
        protected:
            JDictionary(JClass* _class);

        public:
            static JClass* getClazz();

            virtual jint size()=0;

            virtual jbool isEmpty()=0;

            virtual JEnumeration* keys()=0;

            virtual JEnumeration* elements()=0;

            virtual JObject* get(JObject* key)=0;

            virtual JObject* put(JObject* key,JObject* value)=0;

            virtual JObject* remove(JObject* key)=0;

            virtual ~JDictionary();
        };
    }
}

#endif
