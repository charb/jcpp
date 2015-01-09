#include "jcpp/util/JProperties.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;
using namespace jcpp::lang;

namespace jcpp{
    namespace util{
        class JPropertiesClass : public JClass{
        protected:
            static JObject* createJProperties(jcpp::util::JList* args){
                return new JProperties();
            }

            static JObject* staticGetDefaults(JObject* object){
                JProperties* prop=dynamic_cast<JProperties*>(object);
                return prop->defaults;
            }

            static void staticSetDefaults(JObject* object,JObject* value){
                JProperties* prop=dynamic_cast<JProperties*>(object);
                prop->defaults=dynamic_cast<JProperties*>(value);
            }

            static JObject** adrDefaults(JObject* object){
                JProperties* prop=dynamic_cast<JProperties*>(object);
                return (JObject**)(&prop->defaults);
            }

        public:
            JPropertiesClass(){
                this->canonicalName=new JString("java.util.Properties");
                this->name=new JString("java.util.Properties");
                this->simpleName=new JString("Properties");
                this->serialVersionUID=4112578634029874840L;
            }

            virtual void initialize(){
                addConstructor(new JConstructor(JProperties::getClazz(),JModifier::PUBLIC,createJProperties));
                addField(new JField(new JString("defaults"),JProperties::getClazz(),this,staticGetDefaults,staticSetDefaults,adrDefaults));
            }

            JClass* getSuperclass(){
                return JHashtable::getClazz();
            }
        };

        static JClass* clazz;

        JClass* JProperties::getClazz(){
            if (clazz==null){
                clazz=new JPropertiesClass();
            }
            return clazz;
        }

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
