#include "jcpp/net/JURLClassLoader.h"
#include "jcpp/io/JFile.h"
#include "jcpp/lang/reflect/JPackageLoader.h"
#include "jcpp/native/api/library/NativeLibraryFactory.h"
#include "jcpp/native/api/library/NativeLibrary.h"
#include "jcpp/native/api/NativeFactory.h"

using namespace jcpp::io;
using namespace jcpp::lang::reflect;
using namespace jcpp::native::api::library;

namespace jcpp{
    namespace net{
        typedef JPackageLoader* loadPackage();

        JURLClassLoader::JURLClassLoader(JList* files,JClassLoader* parent):JSecureClassLoader(getClazz(),parent){
            this->files=files;
            loadClasses();
        }

        void JURLClassLoader::loadClasses(){
            this->libraries=new NativeLibrary*[files->size()];
            NativeLibraryFactory* libraryFactory=NativeFactory::getNativeLibraryFactory();
            NativeString name("getPackageLoader");
            for (jint i=0;i<files->size();i++){
                JFile* file=dynamic_cast<JFile*>(files->get(i)); //TODO check if isDirectory
                libraries[i]=libraryFactory->createNativeLibrary(file->getAbsolutePath()->getNativeString());
                loadPackage* loader=reinterpret_cast<loadPackage*>(libraries[i]->getFunction(name));
                if (loader!=null){
                    JPackageLoader* packageLoader=loader();
                    initClasses(packageLoader->getPackage());
                }
            }
        }

        void JURLClassLoader::finalize() {
            for (jint i=0;i<files->size();i++){
                delete libraries[i];
            }
            delete[] libraries;
        }

        JURLClassLoader::~JURLClassLoader() {
        }
    }
}
