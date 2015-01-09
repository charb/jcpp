#include "jcpp/io/JInputHandleTable.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JInternalError.h"
#include "jcpp/io/JInputHandleList.h"
#include "jcpp/io/JObjectInputStream.h"
#include "jcpp/lang/JSystem.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"

namespace jcpp{
    namespace io{

    	JInputHandleTable::JInputHandleTable(jint initialCapacity) :JObject(getClazz()){
            lowDep = -1;
            size = 0;
            status = new JPrimitiveByteArray(initialCapacity);
            entries = new JPrimitiveObjectArray(JObject::getClazz(),initialCapacity);
            deps = new JPrimitiveObjectArray(JInputHandleList::getClazz(),initialCapacity);
        }

        jint JInputHandleTable::assign(JObject *obj) {
            if (size >= entries->size()) {
                grow();
            }
            status->setByte(size,STATUS_UNKNOWN);
            entries->set(size,obj);
            return size++;
        }

        void JInputHandleTable::markDependency(jint dependent, jint target) {
            if (dependent == NULL_HANDLE || target == NULL_HANDLE) {
                return;
            }
            switch (status->getByte(dependent)) {
                case STATUS_UNKNOWN:
                    switch (status->getByte(target)) {
                        case STATUS_OK:
                            break;

                        case STATUS_EXCEPTION:
                            markException(dependent,dynamic_cast<JClassNotFoundException*>(entries->get(target)));
                            break;

                        case STATUS_UNKNOWN:{
                            JInputHandleList* l=dynamic_cast<JInputHandleList*>(deps->get(target));
                            if (l == null) {
                                l=new JInputHandleList();
                                deps->set(target, l);
                            }
                            l->add(dependent);
                            
                            if (lowDep < 0 || lowDep > target) {
                                lowDep = target;
                            }
                            break;
                        }

                        default:{
                            throw new JInternalError();
                        }
                    }
                    break;

                case STATUS_EXCEPTION:
                    break;

                default:
                    throw new JInternalError();
                }
        }

        void JInputHandleTable::markException(jint handle, JClassNotFoundException* ex) {
            switch (status->getByte(handle)) {
                case STATUS_UNKNOWN:{
                    status->setByte(handle, STATUS_EXCEPTION);
                    entries->set(handle,ex);

                    JInputHandleList *dlist = dynamic_cast<JInputHandleList*>(deps->get(handle));
                    if (dlist != null) {
                        jint ndeps = dlist->getSize();
                        for (jint i = 0; i < ndeps; ++i) {
                            markException(dlist->get(i), ex);
                        }
                        deps->set(handle,null);
                    }
                }
                break;

                case STATUS_EXCEPTION:
                    break;

                default:
                    throw new JInternalError();
            }
        }

        void JInputHandleTable::finish(jint handle) {
            jint end = 0;
            if (lowDep < 0) {
                end = handle + 1;
            } else if (lowDep >= handle) {
                end = size;
                lowDep = -1;
            } else {
                return;
            }

            for (jint i = handle; i < end; i++) {
                switch (status->getByte(i)) {
                    case STATUS_UNKNOWN:
                        status->setByte(i, STATUS_OK);
                        deps->set(i,null);
                        break;

                    case STATUS_OK:
                    case STATUS_EXCEPTION:
                        break;

                    default:
                        throw new JInternalError();
                }
            }
        }

        void JInputHandleTable::setObject(jint handle, JObject* obj) {
            switch (status->getByte(handle)) {
                case STATUS_UNKNOWN:
                case STATUS_OK:
                    entries->set(handle,obj);
                    break;

                case STATUS_EXCEPTION:
                    break;

                default:
                    throw new JInternalError();
            }
        }

        JObject* JInputHandleTable::lookupObject(jint handle) {
            JObject* obj=(handle != NULL_HANDLE && status->getByte(handle) != STATUS_EXCEPTION) ? entries->get(handle) : null;
            return obj;
        }

        JClassNotFoundException* JInputHandleTable::lookupException(jint handle) {
            return (handle != NULL_HANDLE && status->getByte(handle) == STATUS_EXCEPTION) ? dynamic_cast<JClassNotFoundException*> (entries->get(handle)) : null;
        }

        void JInputHandleTable::clear() {
            for (jint i = 0; i < size; ++i) {
                status->setByte(i,(jbyte) 0);
                entries->set(i,null);
                deps->set(i,null);
            }
            lowDep = -1;
            size = 0;
        }

        jint JInputHandleTable::getSize(){
            return size;
        }

        void JInputHandleTable::grow() {
            jint newCapacity = (entries->size()*2) +1;

            JPrimitiveByteArray *newStatus = new JPrimitiveByteArray(newCapacity);
            JPrimitiveObjectArray *newEntries = new JPrimitiveObjectArray(JObject::getClazz(),newCapacity);
            JPrimitiveObjectArray *newDeps = new JPrimitiveObjectArray(JInputHandleList::getClazz(),newCapacity);

            JSystem::arraycopy(status, 0, newStatus, 0, size);
            JSystem::arraycopy(entries, 0, newEntries, 0, size);
            JSystem::arraycopy(deps, 0, newDeps, 0, size);

            status = newStatus;
            entries = newEntries;
            deps = newDeps;
        }

        JInputHandleTable::~JInputHandleTable() {
        }
    }
}
