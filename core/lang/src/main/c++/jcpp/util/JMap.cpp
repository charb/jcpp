#include "jcpp/util/JMap.h"
#include "jcpp/lang/JClass.h"

namespace jcpp{
    namespace util{

        class JMapClass : public jcpp::lang::JClass{
        public:
            JMapClass():jcpp::lang::JClass(){
                this->canonicalName=new JString("java.util.Map");
                this->name=new JString("java.util.Map");
                this->simpleName=new JString("Map");
                this->bIsInterface=true;
            }

            virtual jcpp::lang::JClass* getSuperclass(){
                return JInterface::getClazz();
            }

            virtual void fillDeclaredClasses();
        };

        static jcpp::lang::JClass* clazz;

        jcpp::lang::JClass* JMap::getClazz(){
            if (clazz==null){
                clazz=new JMapClass();
            }
            return clazz;
        }

        class JEntryMapClass : public jcpp::lang::JClass{
        public:
            JEntryMapClass():jcpp::lang::JClass(){
                this->canonicalName=new JString("java.util.Map$Entry");
                this->name=new JString("java.util.Map$Entry");
                this->simpleName=new JString("Map$Entry");
                this->bIsInterface=true;
            }

            virtual jcpp::lang::JClass* getSuperclass(){
                return JInterface::getClazz();
            }

            virtual jcpp::lang::JClass* getDeclaringClass(){
                return JMap::getClazz();
            }
        };

        static jcpp::lang::JClass* entryClazz;

        jcpp::lang::JClass* JMap::JEntry::getClazz(){
            if (entryClazz==null){
                entryClazz=new JEntryMapClass();
            }
            return entryClazz;
        }

        JMap::JEntry::~JEntry(){
        }

        void JMapClass::fillDeclaredClasses(){
            addDeclaredClass(JMap::JEntry::getClazz());
        }

        JMap::~JMap(){
        }
    }
}
