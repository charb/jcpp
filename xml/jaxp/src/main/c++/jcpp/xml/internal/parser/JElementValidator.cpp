#include "jcpp/xml/internal/parser/JElementValidator.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JInternalError.h"
#include "jcpp/lang/JStringBuilder.h"
#include "jcpp/lang/JBoolean.h"

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace parser{
    
                JElementValidator* JElementValidator::ANY = new JElementValidator();

                JElementValidator::JElementValidator(JClass* _class):JObject(_class){
                }

                JElementValidator::JElementValidator():JObject(getClazz()){
                }

                void JElementValidator::consume(JString* type){
                }

                void JElementValidator::text(){
                }

                void JElementValidator::done(){
                }

                JElementValidator::~JElementValidator(){
                }
            }
        }
    }
}
