#include "jcpp/util/JHashSet.h"
#include "jcpp/util/JList.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace util{
        class JHashSetClass : public JClass{
            static JObject* createJHashSet(jcpp::util::JList* args){
                return new JHashSet();
            }

            static JObject* invokeWriteObject(JObject* object,JList* args){
                JHashSet* hashSet=dynamic_cast<JHashSet*>(object);
                hashSet->writeObject(dynamic_cast<JObjectOutputStream*>(args->get(0)));
                return null;
            }

            static JObject* invokeReadObject(JObject* object,JList* args){
                JHashSet* hashSet=dynamic_cast<JHashSet*>(object);
                hashSet->readObject(dynamic_cast<JObjectInputStream*>(args->get(0)));
                return null;
            }

        public:
            JHashSetClass(){
                this->canonicalName=new JString("java.util.HashSet");
                this->name=new JString("java.util.HashSet");
                this->simpleName=new JString("HashSet");
                this->serialVersionUID=-5024744406713321676ULL;
            }

            virtual void initialize(){
                addInterface(JSet::getClazz());
                addInterface(JSerializable::getClazz());
                addInterface(JCloneable::getClazz());

                addConstructor(new JConstructor(JHashSet::getClazz(),JModifier::PUBLIC,createJHashSet));

                JMethod* m=addMethod(new JMethod(new JString("readObject"),this,JVoid::TYPE,invokeReadObject));
                m->addParameterType(JObjectInputStream::getClazz());                

                m=addMethod(new JMethod(new JString("writeObject"),this,JVoid::TYPE,invokeWriteObject));
                m->addParameterType(JObjectOutputStream::getClazz());                
            }

            JClass* getSuperclass(){
                return JAbstractSet::getClazz();
            }
        };

        static JClass* clazz;

        JClass* JHashSet::getClazz(){
            if (clazz==null){
                clazz=new JHashSetClass();
            }
            return clazz;
        }

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
