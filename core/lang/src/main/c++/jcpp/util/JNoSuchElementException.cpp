#include "jcpp/util/JNoSuchElementException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace util{
        class JNoSuchElementExceptionClass : public jcpp::lang::JClass{
        protected:
            static JObject* createJNoSuchElementException(jcpp::util::JList* args){
                return new JNoSuchElementException();
            }

        public:
            JNoSuchElementExceptionClass():jcpp::lang::JClass(){
                canonicalName=new JString("java.util.NoSuchElementException");
                name=new JString("java.util.NoSuchElementException");
                simpleName=new JString("NoSuchElementException");
                serialVersionUID=6769829250639411880ULL;
            }

            virtual void initialize(){
                JConstructor* cons=addConstructor(new JConstructor(JNoSuchElementException::getClazz(),JModifier::PUBLIC,createJNoSuchElementException));
            }

            virtual jcpp::lang::JClass* getSuperclass(){
                return JRuntimeException::getClazz();
            }
        };

        static jcpp::lang::JClass* clazz;

        jcpp::lang::JClass* JNoSuchElementException::getClazz(){
            if (clazz==null){
                clazz=new JNoSuchElementExceptionClass();
            }
            return clazz;
        }

        JNoSuchElementException::JNoSuchElementException():JRuntimeException(getClazz()){
        }

        JNoSuchElementException::JNoSuchElementException(JString* message):JRuntimeException(getClazz()){
            this->message=message;
        }

        JNoSuchElementException::~JNoSuchElementException(){
        }
    }
}

