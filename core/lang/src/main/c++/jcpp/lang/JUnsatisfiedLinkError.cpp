#include "jcpp/lang/JUnsatisfiedLinkError.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{
        class JUnsatisfiedLinkErrorClass : public jcpp::lang::JClass{
        protected:
            static JObject* createJUnsatisfiedLinkError(jcpp::util::JList* args){
                return new JUnsatisfiedLinkError();
            }

        public:
            JUnsatisfiedLinkErrorClass():jcpp::lang::JClass(){
                canonicalName=new JString("java.lang.UnsatisfiedLinkError");
                name=new JString("java.lang.UnsatisfiedLinkError");
                simpleName=new JString("UnsatisfiedLinkError");
                serialVersionUID=-4019343241616879428LL;
            }

            virtual void initialize(){
                addConstructor(new JConstructor(JUnsatisfiedLinkError::getClazz(),JModifier::PUBLIC,createJUnsatisfiedLinkError));
            }

            virtual jcpp::lang::JClass* getSuperclass(){
                return JLinkageError::getClazz();
            }
        };

        static jcpp::lang::JClass* clazz;

        jcpp::lang::JClass* JUnsatisfiedLinkError::getClazz(){
            if (clazz==null){
                clazz=new JUnsatisfiedLinkErrorClass();
            }
            return clazz;
        }

        JUnsatisfiedLinkError::JUnsatisfiedLinkError():JLinkageError(getClazz()){
        }

        JUnsatisfiedLinkError::JUnsatisfiedLinkError(jcpp::lang::JClass* _class):JLinkageError(_class){
        }

        JUnsatisfiedLinkError::JUnsatisfiedLinkError(JString* message):JLinkageError(getClazz()){
            this->message = message;
        }

        JUnsatisfiedLinkError::~JUnsatisfiedLinkError(){
        }
    }
}

