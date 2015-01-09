#include "jcpp/lang/JBootstrapMethodError.h"
#include "jcpp/lang/reflect/JField.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{
        class JBootstrapMethodErrorClass : public jcpp::lang::JClass{
        protected:
            static JObject* createJBootstrapMethodError(jcpp::util::JList* args){
                return new JBootstrapMethodError();
            }
        public:
            JBootstrapMethodErrorClass():jcpp::lang::JClass(){
                canonicalName=new JString("java.lang.BootstrapMethodError");
                name=new JString("java.lang.BootstrapMethodError");
                simpleName=new JString("BootstrapMethodError");
                serialVersionUID=292L;
            }

            virtual void initialize(){
                JConstructor* cons=addConstructor(new JConstructor(JBootstrapMethodError::getClazz(),JModifier::PUBLIC,createJBootstrapMethodError));
            }

            virtual jcpp::lang::JClass* getSuperclass(){
                return JLinkageError::getClazz();
            }
        };

        static jcpp::lang::JClass* clazz;

        jcpp::lang::JClass* JBootstrapMethodError::getClazz(){
            if (clazz==null){
                clazz=new JBootstrapMethodErrorClass();
            }
            return clazz;
        }

        JBootstrapMethodError::JBootstrapMethodError():JLinkageError(getClazz()){
        }

        JBootstrapMethodError::JBootstrapMethodError(jcpp::lang::JClass* _class):JLinkageError(_class){
        }

        JBootstrapMethodError::JBootstrapMethodError(JString* message):JLinkageError(getClazz()){
            this->message = message;
        }

        JBootstrapMethodError::~JBootstrapMethodError(){
        }
    }
}

