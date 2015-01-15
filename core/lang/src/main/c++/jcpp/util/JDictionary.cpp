#include "jcpp/util/JDictionary.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JInstantiationException.h"

namespace jcpp{
    namespace util{

        JDictionary::JDictionary(JClass *_class):JObject(_class){
        }

        JDictionary::~JDictionary(){
        }
    }
}



