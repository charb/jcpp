#include "jcpp/io/JOutputHandleTable.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JSystem.h"
#include "jcpp/util/JArrays.h"
#include "jcpp/io/JObjectOutputStream.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"

using namespace jcpp::util;

namespace jcpp{
    namespace io{

        JOutputHandleTable::JOutputHandleTable(jint initialCapacity, jfloat loadFactor):JObject(getClazz()){
            isize=0;
            this->loadFactor = loadFactor;
            spine = new JPrimitiveIntArray(initialCapacity);
            next = new JPrimitiveIntArray(initialCapacity);
            objs = new JPrimitiveObjectArray(JObject::getClazz(),initialCapacity);
            threshold = (jint) (initialCapacity * loadFactor);
            clear();
        }

        jint JOutputHandleTable::assign(JObject *obj){
            if (isize >= next->size()) {
                growEntries();
            }
            if (isize >= threshold) {
                growSpine();
            }
            insert(obj, isize);
            return isize++;
        }

        jint JOutputHandleTable::lookup(JObject* obj){
            if (isize == 0) {
                return -1;
            }
            jint index = hash(obj) % spine->size();
            for (jint i = spine->getInt(index); i >= 0; i = next->getInt(i)) {
                if (objs->get(i) == obj) {
                    return i;
                }
            }
            return -1;
        }

        void JOutputHandleTable::clear(){
            JArrays::fill(spine, -1);
            JArrays::fill(objs, 0, isize, (JObject*)null);
            isize = 0;
        }

        jint JOutputHandleTable::size(){
            return isize;
        }

        void JOutputHandleTable::insert(JObject* obj, jint handle) {
            jint index = hash(obj) % spine->size();
            objs->set(handle, obj);
            next->setInt(handle, spine->getInt(index));
            spine->setInt(index, handle);
        }
        
        void JOutputHandleTable::growSpine() {
            spine = new JPrimitiveIntArray((spine->size() * 2) + 1);
            threshold = (jint) (spine->size() * loadFactor);
            JArrays::fill(spine, -1);
            for (jint i = 0; i < isize; i++) {
                insert(objs->get(i), i);
            }
        }

        void JOutputHandleTable::growEntries() {
            jint newLength = (next->size() *2) + 1;
            JPrimitiveIntArray* newNext = new JPrimitiveIntArray(newLength);
            JSystem::arraycopy(next, 0, newNext, 0, isize);
            next = newNext;

            JPrimitiveObjectArray* newObjs = new JPrimitiveObjectArray(JObject::getClazz(),newLength);
            JSystem::arraycopy(objs, 0, newObjs, 0, isize);
            objs = newObjs;
        }

        jint JOutputHandleTable::hash(JObject* obj) {
            return JSystem::identityHashCode(obj) & 0x7FFFFFFF;
        }

        JOutputHandleTable::~JOutputHandleTable(){
        }
    }
}
