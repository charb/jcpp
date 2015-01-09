#include "jcpp/io/JInputHandleList.h"
#include "jcpp/lang/JIndexOutOfBoundsException.h"
#include "jcpp/io/JObjectInputStream.h"
#include "jcpp/lang/JSystem.h"

namespace jcpp{
    namespace io{

        JInputHandleList::JInputHandleList() : JObject(getClazz()){
            list = new JPrimitiveIntArray(4);
            size = 0;
        }

        JInputHandleList::~JInputHandleList() {
        }

        void JInputHandleList::add(jint handle) {
            if (size >= list->size()) {
                JPrimitiveIntArray* newList = new JPrimitiveIntArray(list->size() << 1);
                JSystem::arraycopy(list, 0, newList, 0, list->size());
                list = newList;
            }
            list->setInt(size++,handle);
        }

        jint JInputHandleList::get(jint index) {
            if (index >= size || index < 0) {
                throw new JIndexOutOfBoundsException();
            }
            return list->getInt(index);
        }

        jint JInputHandleList::getSize(){
            return size;
        }
    }
}
