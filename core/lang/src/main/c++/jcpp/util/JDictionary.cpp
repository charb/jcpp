#include "jcpp/util/JDictionary.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JInstantiationException.h"

namespace jcpp{
    namespace util{
        class JDictionaryClass : public JClass{
        public:
            JDictionaryClass():JClass(){
                this->canonicalName=new JString("java.util.Dictionary");
                this->name=new JString("java.util.Dictionary");
                this->simpleName=new JString("Dictionary");
            }

            JClass* getSuperclass(){
                return JObject::getClazz();
            }
        };

        static JClass* clazz;

        JClass* JDictionary::getClazz(){
            if (clazz==null){
                clazz=new JDictionaryClass();
            }
            return clazz;
        }

        JDictionary::JDictionary(JClass *_class):JObject(_class){
        }

        JDictionary::~JDictionary(){
        }
    }
}



