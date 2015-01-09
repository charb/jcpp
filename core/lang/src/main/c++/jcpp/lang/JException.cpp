#include "jcpp/lang/JException.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{
        class JExceptionClass : public jcpp::lang::JClass{
        protected:
            static JObject* createJException(jcpp::util::JList* args){
                return new JException();
            }

        public:
            JExceptionClass():jcpp::lang::JClass(){
                canonicalName=new JString("java.lang.Exception");
                name=new JString("java.lang.Exception");
                simpleName=new JString("Exception");
                serialVersionUID=-3387516993124229948ULL;
            }

            virtual void initialize(){
                addConstructor(new JConstructor(JException::getClazz(),JModifier::PUBLIC,createJException));
            }

            virtual jcpp::lang::JClass* getSuperclass(){
                return JThrowable::getClazz();
            }
        };

        static jcpp::lang::JClass* clazz;

        jcpp::lang::JClass* JException::getClazz(){
            if (clazz==null){
                clazz=new JExceptionClass();
            }
            return clazz;
        }

        JException::JException():JThrowable(getClazz()){
        }

        JException::JException(jcpp::lang::JClass* _class):JThrowable(_class){
        }

        JException::JException(JString* message):JThrowable(getClazz()){
            setMessage(message);
        }

        JException::JException(JString* message, JThrowable *cause):JThrowable(getClazz()){
            setMessage(message);
            setCause(cause);
        }

        JException::~JException(){
        }
    }
}
