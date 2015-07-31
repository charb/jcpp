#ifndef JCPP_UTIL_JABSTRACTMAP_H
#define JCPP_UTIL_JABSTRACTMAP_H

#include "jcpp/lang/JObject.h"
#include "jcpp/util/JMap.h"
#include "jcpp/util/JCollection.h"
#include "jcpp/util/JSet.h"
#include "jcpp/io/JSerializable.h"
#include "jcpp/lang/JUnsupportedOperationException.h"
#include "jcpp/lang/JStringBuilder.h"

using namespace jcpp::lang;
using namespace jcpp::io;

namespace jcpp{
    namespace util{

    	// @Class(canonicalName="java.util.AbstractMap", simpleName="AbstractMap");
        class JCPP_EXPORT JAbstractMap: public JObject, virtual public JMap{
        public:
        	class JSimpleEntry;

        protected:
        	/*TODO: transient volatile*/ JCollection* valuesMember;

            JAbstractMap(jcpp::lang::JClass* _class);
            friend class JSimpleEntry;

        public:
            static jcpp::lang::JClass* getClazz();

            virtual jint size();

            virtual jbool isEmpty();

            virtual jbool containsValue(JObject* value);

            virtual jbool containsKey(JObject* key);

            virtual JObject* get(JObject* key);

            virtual JObject* put(JObject*, JObject*);

            virtual JObject* remove(JObject* key);

            virtual void putAll(JMap* m);

            virtual void clear();

            virtual JSet* keySet();

            virtual JCollection* values();

            virtual JSet* entrySet()=0;

            virtual jbool equals(JObject* o);

            virtual jint hashCode();

            virtual JString* toString();

            virtual JObject* clone() = 0;

            virtual ~JAbstractMap();

            // @Class(canonicalName="java.util.AbstractMap$SimpleEntry", simpleName="AbstractMap$SimpleEntry");
            class JCPP_EXPORT JSimpleEntry : public JEntry, public JObject, public JSerializable{
            private:
            	static const jlong serialVersionUID = -8499721149061103585LL;

            protected:
                JObject* key;
                JObject* value;

            public:
                static jcpp::lang::JClass* getClazz();

                JSimpleEntry(JObject* key, JObject* value) {
                    this->key = key;
                    this->value = value;
                }

                JSimpleEntry(JEntry* entry) {
                    this->key   = entry->getKey();
                    this->value = entry->getValue();
                }

                virtual JObject* getKey() {
                    return key;
                }

                virtual JObject* getValue() {
                    return value;
                }

                virtual JObject* setValue(JObject* value) {
                    JObject* oldValue = this->value;
                    this->value = value;
                    return oldValue;
                }

                virtual jbool equals(JObject* o) {
                    if (!(JEntry::getClazz()->isAssignableFrom(o->getClass()))){
                        return false;
                    }
                    JEntry* e = dynamic_cast<JEntry*>(o);
                    return (key==null ? e->getKey()==null : key->equals(e->getKey())) &&
                           (value==null ? e->getValue()==null : value->equals(e->getValue()));
                }

                virtual jint hashCode() {
                    return (key   == null ? 0 :   key->hashCode()) ^ (value == null ? 0 : value->hashCode());
                }

                virtual JString* toString() {
                    JStringBuilder* builder=new JStringBuilder();
                    if (getKey()==null){
                        builder->append("null=");
                    }else{
                        builder->append(getKey()->toString())->append("=");
                    }
                    if (getValue()==null){
                        builder->append("null");
                    }else{
                        builder->append(getValue()->toString());
                    }
                    return builder->toString();
                }
            };

            // @Class(canonicalName="java.util.AbstractMap$SimpleImmutableEntry", simpleName="AbstractMap$SimpleImmutableEntry");
            class JCPP_EXPORT JSimpleImmutableEntry : public JObject, public JEntry , public JSerializable{
            private:
            	static const jlong serialVersionUID = 7138329143949025153LL;
            protected:
                JObject* key;
                JObject* value;

            public:
                static jcpp::lang::JClass* getClazz();

                JSimpleImmutableEntry(JObject* key, JObject* value) {
                    this->key   = key;
                    this->value = value;
                }

                JSimpleImmutableEntry(JEntry* entry) {
                    this->key   = entry->getKey();
                    this->value = entry->getValue();
                }

                virtual JObject* getKey() {
                    return key;
                }

                virtual JObject* getValue() {
                    return value;
                }

                virtual JObject* setValue(JObject* obj) {
                    throw new JUnsupportedOperationException();
                }

                virtual jbool equals(JObject* o) {
                    if (!(JEntry::getClazz()->isAssignableFrom(o->getClass()))){
                        return false;
                    }
                    JEntry* e = dynamic_cast<JEntry*>(o);
                    return (key==null ? e->getKey()==null : key->equals(e->getKey())) && (value==null ? e->getValue()==null : value->equals(e->getValue()));
                }

                virtual jint hashCode() {
                    return (key == null ? 0 : key->hashCode()) ^ (value == null ? 0 : value->hashCode());
                }

                virtual JString* toString() {
                    JStringBuilder* builder=new JStringBuilder();
                    if (getKey()==null){
                        builder->append("null=");
                    }else{
                        builder->append(getKey()->toString())->append("=");
                    }
                    if (getValue()==null){
                        builder->append("null");
                    }else{
                        builder->append(getValue()->toString());
                    }
                    return builder->toString();
                }
            };
        };
    }
}

#endif
