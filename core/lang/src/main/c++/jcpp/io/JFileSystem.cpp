#include "jcpp/io/JFileSystem.h"
#include "jcpp/lang/JClass.h"

namespace jcpp{
    namespace io{


        JFileSystem::JFileSystem(jcpp::lang::JClass* _class):JObject(_class){
        }

        jint JFileSystem::BA_EXISTS = 0x01;
        jint JFileSystem::BA_REGULAR = 0x02;
        jint JFileSystem::BA_DIRECTORY = 0x04;
        jint JFileSystem::BA_HIDDEN = 0x08;

        jint JFileSystem::ACCESS_READ = 0x04;
        jint JFileSystem::ACCESS_WRITE = 0x02;
        jint JFileSystem::ACCESS_EXECUTE = 0x01;

        jint JFileSystem::SPACE_TOTAL = 0;
        jint JFileSystem::SPACE_FREE = 1;
        jint JFileSystem::SPACE_USABLE = 2;

        JFileSystem::~JFileSystem(){
        }
    }
}
