#include "jcpp/lang/JInterruptedException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{
        class JInterruptedExceptionClass : public jcpp::lang::JClass{
        protected:
            static JObject* createJInterruptedException(jcpp::util::JList* args){
                return new JInterruptedException();
            }

        public:
            JInterruptedExceptionClass():jcpp::lang::JClass(){
                canonicalName=new JString("java.lang.InterruptedException");
                name=new JString("java.lang.InterruptedException");
                simpleName=new JString("InterruptedException");
                serialVersionUID=6700697376100628473LL;
            }

            virtual void initialize(){
                addConstructor(new JConstructor(JInterruptedException::getClazz(),JModifier::PUBLIC,createJInterruptedException));
            }

            virtual jcpp::lang::JClass* getSuperclass(){
                return JException::getClazz();
            }
        };

        static jcpp::lang::JClass* clazz;

        jcpp::lang::JClass* JInterruptedException::getClazz(){
            if (clazz==null){
                clazz=new JInterruptedExceptionClass();
            }
            return clazz;
        }

        JInterruptedException::JInterruptedException():JException(getClazz()){
        }

        JInterruptedException::JInterruptedException(JString* message):JException(getClazz()){
            setMessage(message);
        }

        JInterruptedException::~JInterruptedException(){
        }
    }
}

