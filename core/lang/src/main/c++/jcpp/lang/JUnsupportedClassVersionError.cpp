#include "jcpp/lang/JUnsupportedClassVersionError.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{
        class JUnsupportedClassVersionErrorClass : public jcpp::lang::JClass{
        protected:
            static JObject* createJUnsupportedClassVersionError(jcpp::util::JList* args){
                return new JUnsupportedClassVersionError();
            }

        public:
            JUnsupportedClassVersionErrorClass():jcpp::lang::JClass(){
                canonicalName=new JString("java.lang.UnsupportedClassVersionError");
                name=new JString("java.lang.UnsupportedClassVersionError");
                simpleName=new JString("UnsupportedClassVersionError");
                serialVersionUID=-7123279212883497373LL;
            }

            virtual void initialize(){
                addConstructor(new JConstructor(JUnsupportedClassVersionError::getClazz(),JModifier::PUBLIC,createJUnsupportedClassVersionError));
            }

            virtual jcpp::lang::JClass* getSuperclass(){
                return jcpp::lang::JClassFormatError::getClazz();
            }
        };

        static jcpp::lang::JClass* clazz;

        jcpp::lang::JClass* JUnsupportedClassVersionError::getClazz(){
            if (clazz==null){
                clazz=new JUnsupportedClassVersionErrorClass();
            }
            return clazz;
        }

        JUnsupportedClassVersionError::JUnsupportedClassVersionError():jcpp::lang::JClassFormatError(getClazz()){
        }

        JUnsupportedClassVersionError::JUnsupportedClassVersionError(jcpp::lang::JClass* _class):jcpp::lang::JClassFormatError(_class){
        }

        JUnsupportedClassVersionError::JUnsupportedClassVersionError(JString* message):jcpp::lang::JClassFormatError(getClazz()){
            this->message = message;
        }

        JUnsupportedClassVersionError::~JUnsupportedClassVersionError(){
        }
    }
}

