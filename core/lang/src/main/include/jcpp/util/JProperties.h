#ifndef JCPP_UTIL_JPROPERTIES_H
#define JCPP_UTIL_JPROPERTIES_H

#include "jcpp/util/JHashtable.h"

//TODO implement all missing methods
namespace jcpp{
    namespace util{
        class JCPP_EXPORT JProperties : public JHashtable{
        protected:
            JProperties* defaults;
            virtual void enumerate(JHashtable* h);
            virtual void enumerateStringProperties(JHashtable* h);
            friend class JPropertiesClass;

        public:
            JProperties();

            JProperties(JProperties* defaults);

            static JClass* getClazz();

            virtual JObject* setProperty(JString* key, JString* value);

            virtual JString* getProperty(JString* key);

            virtual JString* getProperty(JString* key,JString* defaultValue);

            virtual JEnumeration* propertyNames();

            virtual JSet* stringPropertyNames();

            virtual ~JProperties();
        };
    }
}

#endif
