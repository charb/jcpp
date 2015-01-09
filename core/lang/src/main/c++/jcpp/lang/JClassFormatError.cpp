#include "jcpp/lang/JClassFormatError.h"
#include "jcpp/lang/reflect/JField.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{
        class JClassFormatErrorClass : public JClass{
        protected:
            static JObject* createJClassFormatError(jcpp::util::JList* args){
                return new JClassFormatError();
            }

        public:
            JClassFormatErrorClass():jcpp::lang::JClass(){
                canonicalName=new JString("java.lang.ClassFormatError");
                name=new JString("java.lang.ClassFormatError");
                simpleName=new JString("ClassFormatError");
                serialVersionUID=-8420114879011949195LL;
            }

            virtual void initialize(){
                JConstructor* cons=addConstructor(new JConstructor(JClassFormatError::getClazz(),JModifier::PUBLIC,createJClassFormatError));
            }

            virtual JClass* getSuperclass(){
                return JLinkageError::getClazz();
            }
        };

        static JClass* clazz;

        JClass* JClassFormatError::getClazz(){
            if (clazz==null){
                clazz=new JClassFormatErrorClass();
            }
            return clazz;
        }

        JClassFormatError::JClassFormatError():JLinkageError(getClazz()){
        }

        JClassFormatError::JClassFormatError(JClass* _class):JLinkageError(_class){
        }

        JClassFormatError::JClassFormatError(JString* message):JLinkageError(getClazz()){
            this->message = message;
        }

        JClassFormatError::~JClassFormatError(){
        }
    }
}

