#ifndef JCPP_IO_JINPUT_HANDLELIST_H
#define JCPP_IO_JINPUT_HANDLELIST_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JPrimitiveIntArray.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{

    	//@Class(canonicalName="java.io.ObjectInputStream$HandleList", simpleName="ObjectInputStream$HandleList");
        class JInputHandleList : public JObject{
        protected:
            JPrimitiveIntArray* list;
            jint size;

        public:
            JInputHandleList();

            static jcpp::lang::JClass* getClazz();

            virtual void add(jint handle);

            virtual jint get(jint index);

            virtual jint getSize();

            virtual ~JInputHandleList();
        };
    }
}

#endif
