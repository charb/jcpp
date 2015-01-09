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

        class JCPP_EXPORT JAbstractMap: public JObject, public JMap{
        public:
        	class JSimpleEntry;

        protected:

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

            virtual JObject* clone()=0;

            virtual ~JAbstractMap();

            class JCPP_EXPORT JSimpleEntry : public JEntry, public JObject, public JSerializable{
            protected:
                class JSimpleEntryClass : public jcpp::lang::JClass{

                public:
                    JSimpleEntryClass():jcpp::lang::JClass(){
                        this->canonicalName=new JString("java.util.AbstractMap$SimpleEntry");
                        this->name=new JString("java.util.AbstractMap$SimpleEntry");
                        this->simpleName=new JString("AbstractMap$SimpleEntry");
                        this->serialVersionUID=-8499721149061103585ULL;
                    }

                    virtual void initialize(){
                        addInterface(JEntry::getClazz());
                        addInterface(JSerializable::getClazz());
                    }

                    virtual jcpp::lang::JClass* getSuperclass(){
                        return JObject::getClazz();
                    }

                    virtual jcpp::lang::JClass* getDeclaringClass(){
                        return JAbstractMap::getClazz();
                    }
                };

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


            class JCPP_EXPORT JSimpleImmutableEntry : public JObject, public JEntry , public JSerializable{
            protected:
                JObject* key;
                JObject* value;
                class JSimpleImmutableEntryClass : public jcpp::lang::JClass{

                public:
                    JSimpleImmutableEntryClass():jcpp::lang::JClass(){
                        this->canonicalName=new JString("java.util.AbstractMap$SimpleImmutableEntry");
                        this->name=new JString("java.util.AbstractMap$SimpleImmutableEntry");
                        this->simpleName=new JString("AbstractMap$SimpleImmutableEntry");
                        this->serialVersionUID=7138329143949025153ULL;
                    }

                    virtual void initialize(){
                        addInterface(JEntry::getClazz());
                        addInterface(JSerializable::getClazz());
                    }

                    virtual jcpp::lang::JClass* getSuperclass(){
                        return JObject::getClazz();
                    }

                    virtual jcpp::lang::JClass* getDeclaringClass(){
                        return JAbstractMap::getClazz();
                    }
                };

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

                virtual JObject* setValue(JObject*) {
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
