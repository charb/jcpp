#ifndef JCPP_UTIL_JMAP_H
#define JCPP_UTIL_JMAP_H

#include "jcpp/lang/JObject.h"
#include "jcpp/util/JCollection.h"
#include "jcpp/util/JSet.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace util{
        class JCPP_EXPORT JMap : public JInterface{
        public:
            class JCPP_EXPORT JEntry : public JInterface {
            public:
                static jcpp::lang::JClass* getClazz();

                virtual JObject* getKey()=0;

                virtual JObject* getValue()=0;

                virtual JObject* setValue(JObject* value)=0;

                virtual jbool equals(JObject* o)=0;

                virtual jint hashCode()=0;

                virtual ~JEntry();
            };

            static jcpp::lang::JClass* getClazz();

            virtual jint size()=0;

            virtual jbool isEmpty()=0;

            virtual jbool containsKey(JObject* key)=0;

            virtual jbool containsValue(JObject* value)=0;

            virtual JObject* get(JObject* key)=0;

            virtual JObject* put(JObject* key, JObject* value)=0;

            virtual JObject* remove(JObject* key)=0;

            virtual void putAll(JMap* m)=0;

            virtual void clear()=0;

            virtual JSet* keySet()=0;

            virtual JCollection* values()=0;

            virtual JSet* entrySet()=0;

            virtual jbool equals(JObject* o)=0;

            virtual jint hashCode()=0;

            virtual ~JMap();
        };
    }
}
#endif
