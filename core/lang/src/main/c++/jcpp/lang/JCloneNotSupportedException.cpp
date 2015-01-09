#include "jcpp/lang/JCloneNotSupportedException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{
        class JCloneNotSupportedExceptionClass : public jcpp::lang::JClass{
        protected:
            static JObject* createJCloneNotSupportedException(jcpp::util::JList* args){
                return new JCloneNotSupportedException();
            }

        public:
            JCloneNotSupportedExceptionClass():jcpp::lang::JClass(){
                canonicalName=new JString("java.lang.CloneNotSupportedException");
                name=new JString("java.lang.CloneNotSupportedException");
                simpleName=new JString("CloneNotSupportedException");
                serialVersionUID=5195511250079656443ULL;
            }

            virtual void initialize(){
                JConstructor* cons=addConstructor(new JConstructor(JCloneNotSupportedException::getClazz(),JModifier::PUBLIC,createJCloneNotSupportedException));
            }

            virtual jcpp::lang::JClass* getSuperclass(){
                return JException::getClazz();
            }
        };

        static jcpp::lang::JClass* clazz;

        jcpp::lang::JClass* JCloneNotSupportedException::getClazz(){
            if (clazz==null){
                clazz=new JCloneNotSupportedExceptionClass();
            }
            return clazz;
        }

        JCloneNotSupportedException::JCloneNotSupportedException():JException(getClazz()){
        }

        JCloneNotSupportedException::JCloneNotSupportedException(jcpp::lang::JClass* _class):JException(_class){
        }

        JCloneNotSupportedException::JCloneNotSupportedException(JString* message):JException(getClazz()){
            setMessage(message);
        }

        JCloneNotSupportedException::JCloneNotSupportedException(JString* message,JThrowable* cause):JException(getClazz()){
            setMessage(message);
            setCause(cause);
        }

        JCloneNotSupportedException::~JCloneNotSupportedException(){
        }
    }
}


