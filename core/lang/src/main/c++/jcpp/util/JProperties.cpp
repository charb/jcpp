#include "jcpp/util/JProperties.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;
using namespace jcpp::lang;

namespace jcpp{
    namespace util{

        JProperties::JProperties():JHashtable(getClazz()){
            defaults=null;
        }

        JProperties::JProperties(JProperties* defaults):JHashtable(getClazz()){
            this->defaults=defaults;
        }

        void JProperties::enumerate(JHashtable* h) {
            synchronized(this,{
                if (defaults != null) {
                    defaults->enumerate(h);
                }
                for (JEnumeration* e = keys() ; e->hasMoreElements() ;) {
                    JString* key = dynamic_cast<JString*>(e->nextElement());
                    h->put(key, get(key));
                }
            })
        }

        void JProperties::enumerateStringProperties(JHashtable* h) {
            synchronized(this,{
                if (defaults != null) {
                    defaults->enumerateStringProperties(h);
                }
                for (JEnumeration* e = keys() ; e->hasMoreElements() ;) {
                    JObject* k = e->nextElement();
                    JObject* v = get(k);
                    if (k->isInstanceOf(JString::getClazz()) && v->isInstanceOf(JString::getClazz())) {
                        h->put(k, v);
                    }
                }
            })
        }

        JObject* JProperties::setProperty(JString* key, JString* value){
            synchronized(this,{
                return put(key,value);
            })
        }

        JString* JProperties::getProperty(JString* key){
            JObject* oval=JHashtable::get(key);
            JString* sval=(oval->isInstanceOf(JString::getClazz()) ? dynamic_cast<JString*>(oval) : null);
            return ((sval == null) && (defaults != null)) ? defaults->getProperty(key) : sval;
        }

        JString* JProperties::getProperty(JString* key,JString* defaultValue){
            JString* val = getProperty(key);
            return (val == null) ? defaultValue : val;
        }

        JEnumeration* JProperties::propertyNames(){
            JHashtable* h = new JHashtable();
            enumerate(h);
            return h->keys();
        }

        JSet* JProperties::stringPropertyNames(){
            JHashtable* h = new JHashtable();
            enumerateStringProperties(h);
            return h->keySet();
        }

        JProperties::~JProperties(){
        }
    }
}
