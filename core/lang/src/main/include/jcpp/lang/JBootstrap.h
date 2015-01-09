#ifndef JCPP_LANG_JBOOTSTRAP_H
#define JCPP_LANG_JBOOTSTRAP_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JString.h"
#include "jcpp/io/JFile.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "jcpp/util/JList.h"
#include "jcpp/net/JURLClassLoader.h"

using namespace jcpp::io;
using namespace jcpp::util;
using namespace jcpp::net;

namespace jcpp{
    namespace lang{

        class JCPP_EXPORT JBootstrap : public JObject{
        protected:
            JList* classpaths;
            JPrimitiveObjectArray* arguments;
            JString* mainClass;
            JURLClassLoader* classLoader;

        public:
            JBootstrap();

            static jcpp::lang::JClass* getClazz();

            virtual void addClassPath(JFile* file);

            virtual void setArguments(JPrimitiveObjectArray* args);

            virtual void setMainClass(JString* mainClass);

            virtual void start();

            virtual void finalize();

            virtual ~JBootstrap();
        };
    }
}

#endif
