#include "jcpp/util/JHashtable.h"
#include "jcpp/util/JAbstractSet.h"
#include "jcpp/util/JConcurrentModificationException.h"
#include "jcpp/util/JNoSuchElementException.h"
#include "jcpp/io/JInvalidObjectException.h"
#include "jcpp/io/JStreamCorruptedException.h"
#include "jcpp/util/JCollections.h"
#include "jcpp/util/JList.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/JUnsupportedOperationException.h"
#include "jcpp/lang/JInteger.h"
#include "jcpp/lang/JIllegalArgumentException.h"
#include "jcpp/lang/JIllegalStateException.h"
#include "jcpp/lang/JNullPointerException.h"
#include "jcpp/lang/JClassCastException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;
using namespace jcpp::lang;

namespace jcpp{
    namespace util{
        static jint KEYS=0;
        static jint VALUES=1;
        static jint ENTRIES=2;
        static jint MAX_ARRAY_SIZE = JInteger::MAX_VALUE - 8;

        // @Class(canonicalName="java.util.Hashtable$Entry", simpleName="Hashtable$Entry");
        class JEntryImpl : public JMap::JEntry, public JObject{
        protected:
        jint hash;
        JObject* key;
        JObject* value;
        JEntryImpl* next;
        friend JHashtable;
        friend JHashtableEntrySetImpl;
        friend JHashtableEnumeratorImpl;

        public:

            static JClass* getClazz();

            JEntryImpl(jint hash, JObject* key, JObject* value, JEntryImpl* next) :JObject(getClazz()){
                this->hash = hash;
                this->key =  key;
                this->value = value;
                this->next = next;
            }

            virtual JObject* clone() {
                return new JEntryImpl(hash, key, value, (next==null ? null : dynamic_cast<JEntryImpl*>(next->clone())));
            }

            virtual JObject* getKey() {
                return key;
            }

            virtual JObject* getValue() {
                return value;
            }

            virtual JObject* setValue(JObject* value) {
                if (value == null){
                    throw new JNullPointerException();
                }

                JObject* oldValue = this->value;
                this->value = value;
                return oldValue;
            }

            virtual jbool equals(JObject* o) {
                if (!(o->isInstanceOf(JMap::JEntry::getClazz()))){
                    return false;
                }
                JMap::JEntry* e = dynamic_cast<JMap::JEntry*>(o);

                return (key==null ? e->getKey()==null : key->equals(e->getKey())) &&
                     (value==null ? e->getValue()==null : value->equals(e->getValue()));
            }

            virtual jint hashCode() {
                return hash ^ (value != null ? value->hashCode() : 0);
            }

            virtual JString* toString() {
                JStringBuilder* builder=new JStringBuilder();
                builder->append(getKey()->toString())->append("=")->append(getValue()->toString());
                return builder->toString();
            }
        };

        JHashtable::JHashtable(JClass* _class):JDictionary(_class){
            init(11,0.75f);
        }

        JHashtable::JHashtable(jint initialCapacity, jfloat loadFactor):JDictionary(getClazz()){
            init(initialCapacity,loadFactor);
        }

        JHashtable::JHashtable(jint initialCapacity):JDictionary(getClazz()) {
            init(initialCapacity, 0.75f);
        }

        JHashtable::JHashtable():JDictionary(getClazz()) {
            init(11, 0.75f);
        }

        JHashtable::JHashtable(JMap* m):JDictionary(getClazz()){
            init((2*m->size() > 11 ? 2*m->size() : 11 ), 0.75f);
            putAll(m);
        }

        void JHashtable::init(jint initialCapacity, jfloat loadFactor){
            count=0;
            modCount=0;

            if (initialCapacity < 0){
                throw new JIllegalArgumentException(new JString("Illegal initial capacity: "));
            }
            if (loadFactor <= 0){
                throw new JIllegalArgumentException(new JString("Illegal load factor: "));
            }

            if (initialCapacity==0){
                initialCapacity = 1;
            }

            this->loadFactor=new JPrimitiveFloat(loadFactor);
            table=new JPrimitiveObjectArray(JEntryImpl::getClazz(),initialCapacity);
            this->threshold=new JPrimitiveInt((initialCapacity * loadFactor < MAX_ARRAY_SIZE+1 ? initialCapacity * loadFactor : MAX_ARRAY_SIZE+1));
        }

        jint JHashtable::size(){
            synchronized(this,{
                return count;
            });
        }

        jbool JHashtable::isEmpty(){
            synchronized(this,{
                return count==0;
            })
        }

        JEnumeration* JHashtable::keys(){
            synchronized(this,{
                return getEnumeration(KEYS);
            })
        }

        JEnumeration* JHashtable::elements(){
            synchronized(this,{
                return getEnumeration(VALUES);
            })
        }

        jbool JHashtable::contains(JObject* value){
            synchronized(this,{
                if (value==null){
                    throw new JNullPointerException();
                }
                JPrimitiveObjectArray* tab = table;
                for (jint i = tab->size() ; i-- > 0 ;) {
                    for (JEntryImpl* e = dynamic_cast<JEntryImpl*>(tab->get(i)) ; e != null ; e = e->next) {
                        if (e->value->equals(value)) {
                            return true;
                        }
                    }
                }
                return false;
            })
        }

        jbool JHashtable::containsValue(JObject* value){
            return contains(value);
        }

        jbool JHashtable::containsKey(JObject* key){
            synchronized(this,{
                JPrimitiveObjectArray* tab = table;
                jint hash = key->hashCode();
                jint index = (hash & 0x7FFFFFFF) % tab->size();
                for (JEntryImpl* e = dynamic_cast<JEntryImpl*>(tab->get(index)) ; e != null ; e = e->next) {
                    if ((e->hash == hash) && e->key->equals(key)) {
                        return true;
                    }
                }
                return false;
            })
        }

        JObject* JHashtable::get(JObject* key){
            synchronized(this,{
                JPrimitiveObjectArray* tab = table;
                jint hash = key->hashCode();
                jint index = (hash & 0x7FFFFFFF) % tab->size();
                for (JEntryImpl* e = dynamic_cast<JEntryImpl*>(tab->get(index)) ; e != null ; e = e->next) {
                    if ((e->hash == hash) && e->key->equals(key)) {
                        return e->value;
                    }
                }
                return null;
            })
        }

        void JHashtable::rehash() {
            jint oldCapacity = table->size();
            JPrimitiveObjectArray* oldMap = table;

            jint newCapacity = (oldCapacity << 1) + 1;
            if (newCapacity - MAX_ARRAY_SIZE > 0) {
                if (oldCapacity == MAX_ARRAY_SIZE){
                    return;
                }
                newCapacity = MAX_ARRAY_SIZE;
            }
            JPrimitiveObjectArray* newMap = new JPrimitiveObjectArray(JEntryImpl::getClazz(),newCapacity);
            modCount++;
            threshold->set((newCapacity * loadFactor->get() < MAX_ARRAY_SIZE + 1 ? newCapacity * loadFactor->get() : MAX_ARRAY_SIZE + 1));
            table = newMap;

            for (jint i = oldCapacity ; i-- > 0 ;) {
                for (JEntryImpl* old = dynamic_cast<JEntryImpl*>(oldMap->get(i)) ; old != null ; ) {
                    JEntryImpl* e = old;
                    old = old->next;

                    jint index = (e->hash & 0x7FFFFFFF) % newCapacity;
                    e->next = dynamic_cast<JEntryImpl*>(newMap->get(index));
                    newMap->set(index, e);
                }
            }
        }

        void JHashtable::addEntry(jint hash, JObject* key, JObject* value, jint index) {
            modCount++;

            JPrimitiveObjectArray* tab = table;
            if (count >= threshold->get()) {
                rehash();
                tab = table;
                hash = key->hashCode();
                index = (hash & 0x7FFFFFFF) % tab->size();
            }

            JEntryImpl* e = dynamic_cast<JEntryImpl*>(tab->get(index));
            tab->set(index, new JEntryImpl(hash, key, value, e));
            count++;
        }

        JObject* JHashtable::put(JObject* key, JObject* value){
            synchronized(this,{
                if (value == null) {
                    throw new JNullPointerException();
                }

                JPrimitiveObjectArray* tab = table;
                jint hash = key->hashCode();
                jint index = (hash & 0x7FFFFFFF) % tab->size();

                JEntryImpl* entry = dynamic_cast<JEntryImpl*>(tab->get(index));
                for(; entry != null ; entry = entry->next) {
                    if ((entry->hash == hash) && entry->key->equals(key)) {
                        JObject* old = entry->value;
                        entry->value = value;
                        return old;
                    }
                }

                addEntry(hash, key, value, index);
                return null;
            })
        }

        JObject* JHashtable::remove(JObject* key){
            synchronized(this,{
                JPrimitiveObjectArray* tab = table;
                jint hash = key->hashCode();
                jint index = (hash & 0x7FFFFFFF) % tab->size();

                JEntryImpl* e = dynamic_cast<JEntryImpl*>(tab->get(index));
                for (JEntryImpl* prev = null ; e != null ; prev = e, e = e->next) {
                    if ((e->hash == hash) && e->key->equals(key)) {
                        modCount++;
                        if (prev != null) {
                            prev->next = e->next;
                        } else {
                            tab->set(index, e->next);
                        }
                        count--;
                        JObject* oldValue = e->value;
                        e->value = null;
                        return oldValue;
                    }
                }
                return null;
            })
        }

        void JHashtable::putAll(JMap* m) {
            synchronized(this,{
                JIterator* it=m->entrySet()->iterator();
                while (it->hasNext()){
                    JMap::JEntry* e = dynamic_cast<JMap::JEntry*>(it->next());
                    put(e->getKey(), e->getValue());
                }
            })
        }

        void JHashtable::clear(){
            synchronized(this,{
                JPrimitiveObjectArray* tab = table;
                modCount++;
                for (jint index = tab->size(); --index >= 0; ){
                    tab->set(index,null);
                }
                count = 0;
            })
        }

        JHashtable* JHashtable::clone(){
            synchronized(this,{
                return new JHashtable(this);
            })
        }

        JString* JHashtable::toString(){
            synchronized(this,{
                jint max = size() - 1;
                if (max == -1){
                    return new JString("{}");
                }

                JStringBuilder* sb = new JStringBuilder();
                JIterator* it = entrySet()->iterator();

                sb->append('{');
                for (jint i = 0; ; i++) {
                    JMap::JEntry* e = dynamic_cast<JMap::JEntry*>(it->next());
                    JObject* key = e->getKey();
                    JObject* value = e->getValue();
                    sb->append(key   == this ? new JString("(this Map)") : key->toString());
                    sb->append('=');
                    sb->append(value == this ? new JString("(this Map)") : value->toString());

                    if (i == max){
                        return sb->append('}')->toString();
                    }
                    sb->append(", ");
                }
            })
        }

        // @Class(canonicalName="java.util.Hashtable$KeySet", simpleName="Hashtable$KeySet");
        class JHashtableKeySetImpl : public JAbstractSet {
        protected:
            JHashtable* map;

        public:
            static JClass* getClazz();

            JHashtableKeySetImpl(JHashtable* map):JAbstractSet(getClazz()){
                this->map=map;
            }

            virtual JIterator* iterator() {
                return map->getIterator(KEYS);
            }

            virtual jint size() {
                return map->size();
            }

            virtual jbool contains(JObject* o) {
                return map->containsKey(o);
            }

            virtual jbool remove(JObject* o) {
                return map->remove(o) != null;
            }

            virtual void clear() {
                map->clear();
            }
        };

        JSet* JHashtable::keySet(){
            return JCollections::synchronizedSet(new JHashtableKeySetImpl(this),this);
        }

        // @Class(canonicalName="java.util.Hashtable$EntrySet", simpleName="Hashtable$EntrySet");
        class JHashtableEntrySetImpl : public JAbstractSet{
        protected:
            JHashtable* map;

        public:
            static JClass* getClazz();

            JHashtableEntrySetImpl(JHashtable* map):JAbstractSet(getClazz()){
                this->map=map;
            }

            virtual JIterator* iterator() {
                return map->getIterator(ENTRIES);
            }

            virtual jbool add(JMap::JEntry* e){
                return JAbstractSet::add(dynamic_cast<JObject*>(e));
            }

            virtual jbool contains(JObject* o) {
                 if (!(o->isInstanceOf(JMap::JEntry::getClazz()))){
                    return false;
                }
                JMap::JEntry* entry = dynamic_cast<JMap::JEntry*>(o);
                JObject* key = entry->getKey();
                JPrimitiveObjectArray* tab = map->table;
                jint hash = key->hashCode();
                jint index = (hash & 0x7FFFFFFF) % tab->size();

                for (JEntryImpl* e = dynamic_cast<JEntryImpl*>(tab->get(index)); e != null; e = e->next){
                    if (e->hash==hash && e->equals(dynamic_cast<JObject*>(entry))){
                        return true;
                    }
                }
                return false;
            }

            virtual jbool remove(JObject* o) {
                if (!(o->isInstanceOf(JMap::JEntry::getClazz()))){
                    return false;
                }
                JMap::JEntry* entry = dynamic_cast<JMap::JEntry*>(o);
                JObject* key = entry->getKey();
                JPrimitiveObjectArray* tab = map->table;
                jint hash = key->hashCode();
                jint index = (hash & 0x7FFFFFFF) % tab->size();

                JEntryImpl* e = dynamic_cast<JEntryImpl*>(tab->get(index));
                for (JEntryImpl* prev = null; e != null; prev = e, e = e->next) {
                    if (e->hash==hash && e->equals(dynamic_cast<JObject*>(entry))) {
                        map->modCount++;
                        if (prev != null){
                            prev->next = e->next;
                        }else{
                            tab->set(index, e->next);
                        }

                        map->count--;
                        e->value = null;
                        return true;
                    }
                }
                return false;
            }

            virtual jint size() {
                return map->size();
            }

            virtual void clear() {
                map->clear();
            }
        };

        JSet* JHashtable::entrySet(){
            return JCollections::synchronizedSet(new JHashtableEntrySetImpl(this),this);
        }

        // @Class(canonicalName="java.util.Hashtable$ValueCollection", simpleName="Hashtable$ValueCollection");
        class JHashtableValues : public JAbstractCollection {
        protected:
            JHashtable* map;

        public:
            static JClass* getClazz();

            JHashtableValues(JHashtable* map):JAbstractCollection(getClazz()){
                this->map=map;
            }

            virtual JIterator* iterator() {
                return map->getIterator(VALUES);
            }

            virtual jint size() {
                return map->size();
            }

            virtual jbool contains(JObject* o) {
                return map->containsValue(o);
            }

            virtual void clear() {
                map->clear();
            }
        };

        JCollection* JHashtable::values(){
            return JCollections::synchronizedCollection(new JHashtableValues(this),this);
        }

        jbool JHashtable::equals(JObject* o) {
            synchronized(this,{
                if (o == this){
                    return true;
                }

                if (!(JMap::getClazz()->isAssignableFrom(o->getClass()))){
                    return false;
                }
                JMap* t = dynamic_cast<JMap*>(o);
                if (t->size() != size()){
                    return false;
                }

                JIterator* i = entrySet()->iterator();
                try {
                    while (i->hasNext()) {
                        JMap::JEntry* e = dynamic_cast<JMap::JEntry*>(i->next());
                        JObject* key = e->getKey();
                        JObject* value = e->getValue();
                        if (value == null) {
                            if (!(t->get(key)==null && t->containsKey(key))){
                                return false;
                            }
                        } else {
                            if (!value->equals(t->get(key))){
                                return false;
                            }
                        }
                    }
                } catch (JClassCastException* unused)   {
                    return false;
                } catch (JNullPointerException* unused) {
                    return false;
                }
                return true;
            })
        }

        jint JHashtable::hashCode() {
            synchronized(this,{
                jint h = 0;
                if (size()== 0 || loadFactor->get() < 0){
                    return h;
                }
                loadFactor->set(-loadFactor->get());
                
                JPrimitiveObjectArray* tab = table;
                for (jint i=0;i<tab->size();i++) {
                    JEntryImpl* entry=dynamic_cast<JEntryImpl*>(tab->get(i));
                    while (entry != null) {
                        h += entry->hashCode();
                        entry = entry->next;
                    }
                }
                loadFactor->set(-loadFactor->get());
                return h;
            })
        }

        void JHashtable::writeObject(JObjectOutputStream* out){
            JEntryImpl* entryStack = null;

            synchronized(this,{
                out->defaultWriteObject();

                out->writeInt(table->size());
                out->writeInt(count);

                for (jint index = 0; index < table->size(); index++) {
                    JEntryImpl* entry = dynamic_cast<JEntryImpl*>(table->get(index));
                    while (entry != null) {
                        entryStack =new JEntryImpl(0, entry->key, entry->value, entryStack);
                        entry = entry->next;
                    }
                }
            })

            while (entryStack != null) {
                out->writeObject(entryStack->key);
                out->writeObject(entryStack->value);
                entryStack = entryStack->next;
            }
        }

        void JHashtable::readObject(JObjectInputStream* in){
            in->defaultReadObject();

            jint origlength = in->readInt();
            jint elements = in->readInt();

            jint length = (jint)(elements * loadFactor->get()) + (elements / 20) + 3;
            if (length > elements && (length & 1) == 0){
                length--;
            }
            if (origlength > 0 && length > origlength){
                length = origlength;
            }
            table = new JPrimitiveObjectArray(JEntryImpl::getClazz(),length);
            threshold->set((length * loadFactor->get()< MAX_ARRAY_SIZE + 1 ? length * loadFactor->get() : MAX_ARRAY_SIZE + 1));
            count = 0;

            for (; elements > 0; elements--) {
                JObject* key = in->readObject();
                JObject* value = in->readObject();
                reconstitutionPut(table, key, value);
            }
        }

        void JHashtable::reconstitutionPut(JPrimitiveObjectArray* tab, JObject* key, JObject* value){
            if (value == null) {
                throw new JStreamCorruptedException();
            }

            jint hash = key->hashCode();
            jint index = (hash & 0x7FFFFFFF) % tab->size();
            for (JEntryImpl* e = dynamic_cast<JEntryImpl*>(tab->get(index)) ; e != null ; e = e->next) {
                if ((e->hash == hash) && e->key->equals(key)) {
                    throw new JStreamCorruptedException();
                }
            }

            JEntryImpl* e = dynamic_cast<JEntryImpl*>(tab->get(index));
            tab->set(index, new JEntryImpl(hash, key, value, e));
            count++;
        }

        // @Class(canonicalName="java.util.Hashtable$Enumerator", simpleName="Hashtable$Enumerator");
        class JHashtableEnumeratorImpl: public JObject, public JEnumeration, public JIterator {
        protected:
            JHashtable* hashtable;
            JPrimitiveObjectArray* table;
            jint index;
            JEntryImpl* entry;
            JEntryImpl* lastReturned;
            jint type;
            jbool isIterator;
            jint expectedModCount;

        public:
            static JClass* getClazz();

            JHashtableEnumeratorImpl(JHashtable* hashtable,jint type, jbool isIterator):JObject(getClazz()) {
                this->hashtable=hashtable;
                this->type = type;
                this->isIterator = isIterator;
                this->expectedModCount = hashtable->modCount;
                this->table=hashtable->table;
                index=table->size();
                entry=null;
                lastReturned=null;
            }

            virtual jbool hasMoreElements() {
                JEntryImpl* e = entry;
                jint i = index;
                JPrimitiveObjectArray* t = table;
                while (e == null && i > 0) {
                    e = dynamic_cast<JEntryImpl*>(t->get(--i));
                }
                entry = e;
                index = i;
                return e != null;
            }

            virtual JObject* nextElement() {
                JEntryImpl* et = entry;
                jint i = index;
                JPrimitiveObjectArray* t = table;

                while (et == null && i > 0) {
                    et = dynamic_cast<JEntryImpl*>(t->get(--i));
                }
                entry = et;
                index = i;
                if (et != null) {
                    JEntryImpl* e = lastReturned = entry;
                    entry = e->next;
                    return type == KEYS ? e->key : (type == VALUES ? e->value : e);
                }
                throw new JNoSuchElementException(new JString("Hashtable Enumerator"));
            }

            virtual jbool hasNext() {
                return hasMoreElements();
            }

            virtual JObject* next() {
                if (hashtable->modCount != expectedModCount){
                    throw new JConcurrentModificationException();
                }
                return nextElement();
            }

            virtual void remove() {
                if (!isIterator){
                    throw new JUnsupportedOperationException();
                }
                if (lastReturned == null){
                    throw new JIllegalStateException(new JString("Hashtable Enumerator"));
                }
                if (hashtable->modCount != expectedModCount){
                    throw new JConcurrentModificationException();
                }

                synchronized(hashtable,{
                    JPrimitiveObjectArray* tab = hashtable->table;
                    jint index = (lastReturned->hash & 0x7FFFFFFF) % tab->size();

                    JEntryImpl* e = dynamic_cast<JEntryImpl*>(tab->get(index));
                    for (JEntryImpl* prev = null; e != null; prev = e, e = e->next) {
                        if (e == lastReturned) {
                            hashtable->modCount++;
                            expectedModCount++;
                            if (prev == null){
                                tab->set(index, e->next);
                            }else{
                                prev->next = e->next;
                            }
                            hashtable->count--;
                            lastReturned = null;
                            return;
                        }
                    }
                    throw new JConcurrentModificationException();
                })
            }
        };

        JEnumeration* JHashtable::getEnumeration(int type) {
            if (size() == 0) {
                return JCollections::emptyEnumeration();
            } else {
                return new JHashtableEnumeratorImpl(this,type, false);
            }
        }

        JIterator* JHashtable::getIterator(jint type) {
            if (table->size()== 0) {
                return JCollections::emptyIterator();
            } else {
                return new JHashtableEnumeratorImpl(this,type, true);
            }
        }

        JHashtable::~JHashtable(){
        }
    }
}
