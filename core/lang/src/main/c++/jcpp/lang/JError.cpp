#include "jcpp/lang/JError.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{
        class JErrorClass : public jcpp::lang::JClass{
        protected:
            static JObject* createJError(jcpp::util::JList* args){
                return new JError();
            }

        public :
            JErrorClass():jcpp::lang::JClass(){
                canonicalName=new JString("java.lang.Error");
                name=new JString("java.lang.Error");
                simpleName=new JString("Error");
                serialVersionUID=4980196508277280342ULL;
            }

            virtual void initialize(){
                addConstructor(new JConstructor(JError::getClazz(),JModifier::PUBLIC,createJError));
            }

            virtual jcpp::lang::JClass* getSuperclass(){
                return JThrowable::getClazz();
            }
        };

        static jcpp::lang::JClass* clazz;

        jcpp::lang::JClass* JError::getClazz(){
            if (clazz==null){
                clazz=new JErrorClass();
            }
            return clazz;
        }

        JError::JError():JThrowable(getClazz()){
        }

        JError::JError(jcpp::lang::JClass* _class):JThrowable(_class){
        }

        JError::JError(jcpp::lang::JClass* _class, JThrowable* cause):JThrowable(_class){
        	setCause(cause);
        }

        JError::JError(JString* message):JThrowable(getClazz()){
            setMessage(message);
        }

        JError::JError(JString* message, JThrowable *cause):JThrowable(getClazz()){
            setMessage(message);
            setCause(cause);
        }

        JError::~JError(){
        }
    }
}

