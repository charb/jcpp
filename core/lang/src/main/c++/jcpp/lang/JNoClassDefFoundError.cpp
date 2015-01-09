#include "jcpp/lang/JNoClassDefFoundError.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{
        class JNoClassDefFoundErrorClass : public jcpp::lang::JClass{
        protected:
            static JObject* createJNoClassDefFoundError(jcpp::util::JList* args){
                return new JNoClassDefFoundError();
            }

        public:
            JNoClassDefFoundErrorClass():jcpp::lang::JClass(){
                canonicalName=new JString("java.lang.NoClassDefFoundError");
                name=new JString("java.lang.NoClassDefFoundError");
                simpleName=new JString("NoClassDefFoundError");
                serialVersionUID=9095859863287012458LL;
            }

            virtual void initialize(){
                addConstructor(new JConstructor(JNoClassDefFoundError::getClazz(),JModifier::PUBLIC,createJNoClassDefFoundError));
            }

            virtual jcpp::lang::JClass* getSuperclass(){
                return JLinkageError::getClazz();
            }
        };

        static jcpp::lang::JClass* clazz;

        jcpp::lang::JClass* JNoClassDefFoundError::getClazz(){
            if (clazz==null){
                clazz=new JNoClassDefFoundErrorClass();
            }
            return clazz;
        }

        JNoClassDefFoundError::JNoClassDefFoundError():JLinkageError(getClazz()){
        }

        JNoClassDefFoundError::JNoClassDefFoundError(jcpp::lang::JClass* _class):JLinkageError(_class){
        }

        JNoClassDefFoundError::JNoClassDefFoundError(JString* message):JLinkageError(getClazz()){
            this->message = message;
        }

        JNoClassDefFoundError::JNoClassDefFoundError(JString* message, JThrowable *cause):JLinkageError(getClazz()){
            this->message = message;
            this->cause = cause;
        }

        JNoClassDefFoundError::~JNoClassDefFoundError(){
        }
    }
}

