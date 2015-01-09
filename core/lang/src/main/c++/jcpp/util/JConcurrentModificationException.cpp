#include "jcpp/util/JConcurrentModificationException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace util{
        class JConcurrentModificationExceptionClass : public jcpp::lang::JClass{
        protected:
            static JObject* createJConcurrentModificationException(jcpp::util::JList* args){
                return new JConcurrentModificationException();
            }

        public:
            JConcurrentModificationExceptionClass():jcpp::lang::JClass(){
                canonicalName=new JString("java.util.ConcurrentModificationException");
                name=new JString("java.util.ConcurrentModificationException");
                simpleName=new JString("ConcurrentModificationException");
                serialVersionUID=3666751008965953603ULL;
            }

            virtual void initialize(){
                JConstructor* cons=addConstructor(new JConstructor(JConcurrentModificationException::getClazz(),JModifier::PUBLIC,createJConcurrentModificationException));
            }

            virtual jcpp::lang::JClass* getSuperclass(){
                return JRuntimeException::getClazz();
            }
        };

        static jcpp::lang::JClass* clazz;

        jcpp::lang::JClass* JConcurrentModificationException::getClazz(){
            if (clazz==null){
                clazz=new JConcurrentModificationExceptionClass();
            }
            return clazz;
        }

        JConcurrentModificationException::JConcurrentModificationException(jcpp::lang::JClass* _class):JRuntimeException(_class){
        }

        JConcurrentModificationException::JConcurrentModificationException():JRuntimeException(getClazz()){
        }

        JConcurrentModificationException::JConcurrentModificationException(JString* message):JRuntimeException(getClazz()){
            this->message=message;
        }

        JConcurrentModificationException::~JConcurrentModificationException(){
        }
    }
}


