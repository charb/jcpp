#include "jcpp/util/JHashSet.h"
#include "jcpp/util/JList.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace util{
        static JObject* PRESENT = new JObject();

        JHashSet::JHashSet():JAbstractSet(getClazz()){
            this->map=new JHashMap();
        }

        JHashSet::JHashSet(jint initialCapacity, jfloat loadFactor):JAbstractSet(getClazz()){
            this->map=new JHashMap(initialCapacity,loadFactor);
        }

        JHashSet::JHashSet(JCollection* c):JAbstractSet(getClazz()){
            this->map=new JHashMap();
            addAll(c);
        }

        JIterator* JHashSet::iterator(){
            return map->keySet()->iterator();
        }

        jint JHashSet::size(){
            return map->size();
        }

        JPrimitiveObjectArray* JHashSet::toArray(){
            return JAbstractSet::toArray();
        }

        jbool JHashSet::containsAll(JCollection* c){
            return JAbstractSet::containsAll(c);
        }

        jbool JHashSet::addAll(JCollection* c){
            return JAbstractSet::addAll(c);
        }

        jbool JHashSet::removeAll(JCollection* c){
            return JAbstractSet::removeAll(c);
        }

        jbool JHashSet::retainAll(JCollection* c){
            return JAbstractSet::retainAll(c);
        }

        jbool JHashSet::equals(JObject* c){
            return JAbstractSet::equals(c);
        }

        jint JHashSet::hashCode(){
            return JAbstractSet::hashCode();
        }

        jbool JHashSet::isEmpty(){
            return map->isEmpty();
        }

        jbool JHashSet::contains(JObject* o){
            return map->containsKey(o);
        }

        jbool JHashSet::add(JObject* item){
            return map->put(item,PRESENT)==null;
        }

        jbool JHashSet::remove(JObject* e){
            return map->remove(e)==PRESENT;
        }

        void JHashSet::clear(){
            map->clear();
        }

        JHashSet* JHashSet::clone(){
            return new JHashSet(dynamic_cast<JAbstractCollection*>(this));
        }

        void JHashSet::writeObject(JObjectOutputStream* out){
            out->defaultWriteObject();

            out->writeInt(map->capacity());
            out->writeFloat(map->loadFactor->get());
            out->writeInt(map->size());

            JIterator* iterator=map->keySet()->iterator();
            while (iterator->hasNext()){
                JObject* e=iterator->next();
                out->writeObject(e);
            }
        }

        void JHashSet::readObject(JObjectInputStream* in){
            in->defaultReadObject();

            jint capacity=in->readInt();
            jfloat loadFactor=in->readFloat();

            jint size = in->readInt();
            for (jint i=0; i<size; i++) {
                JObject* e= in->readObject();
                map->put(e, PRESENT);
            }
        }

        JHashSet::~JHashSet(){
        }
    }
}
