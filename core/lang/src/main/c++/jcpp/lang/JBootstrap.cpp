#include "jcpp/lang/JBootstrap.h"
#include "jcpp/lang/JThread.h"

namespace jcpp{
    namespace lang{

        JBootstrap::JBootstrap(): JObject(getClazz()) {
            classpaths=new JArrayList();
            arguments=null;
            classLoader=null;
        }

        void JBootstrap::addClassPath(JFile* file){
            classpaths->add(file);
        }

        void JBootstrap::setArguments(JPrimitiveObjectArray* args){
            arguments=args;
        }

        void JBootstrap::setMainClass(JString* mainClass){
            this->mainClass=mainClass;
        }

        void JBootstrap::start(){
            JClassLoader::init();
            classLoader=new JURLClassLoader(classpaths,null);
            JThread::currentThread()->setContextClassLoader(classLoader);
            JClass* mainClazz=classLoader->loadClass(mainClass);

            JArrayList* pa=new JArrayList();
            pa->add(JPrimitiveObjectArray::getClazz(JString::getClazz()));
            JMethod* mainMethod=mainClazz->getMethod(new JString("main"),pa);

            JArrayList* args=new JArrayList();
            args->add(arguments);
            mainMethod->invoke(null,args);
        }

        void JBootstrap::finalize(){
        }

        JBootstrap::~JBootstrap() {
        }
    }
}
