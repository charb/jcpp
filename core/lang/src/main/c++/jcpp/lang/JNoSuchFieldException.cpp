#include "jcpp/lang/JNoSuchFieldException.h"
#include "jcpp/lang/JSystem.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{
        class JNoSuchFieldExceptionClass : public jcpp::lang::JClass{
        protected:
            static JObject* createJNoSuchFieldException(jcpp::util::JList* args){
                return new JNoSuchFieldException();
            }

        public:
            JNoSuchFieldExceptionClass():jcpp::lang::JClass(){
                canonicalName=new JString("java.lang.NoSuchFieldException");
                name=new JString("java.lang.NoSuchFieldException");
                simpleName=new JString("NoSuchFieldException");
                serialVersionUID=-6143714805279938260ULL;
            }

            virtual void initialize(){
                addConstructor(new JConstructor(JNoSuchFieldException::getClazz(),JModifier::PUBLIC,createJNoSuchFieldException));
            }

            virtual jcpp::lang::JClass* getSuperclass(){
                return JReflectiveOperationException::getClazz();
            }
        };

        static jcpp::lang::JClass* clazz;

        jcpp::lang::JClass* JNoSuchFieldException::getClazz(){
            if (clazz==null){
                clazz=new JNoSuchFieldExceptionClass();
            }
            return clazz;
        }

        JNoSuchFieldException::JNoSuchFieldException():JReflectiveOperationException(getClazz()){
        }

        JNoSuchFieldException::JNoSuchFieldException(JString* message):JReflectiveOperationException(getClazz()){
            setMessage(message);
        }

        JNoSuchFieldException::~JNoSuchFieldException(){
        }
    }
}
