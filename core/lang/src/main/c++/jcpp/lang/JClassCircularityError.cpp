#include "jcpp/lang/JClassCircularityError.h"
#include "jcpp/lang/reflect/JField.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{
        class JClassCircularityErrorClass : public JClass{
        protected:
            static JObject* createJClassCircularityError(jcpp::util::JList* args){
                return new JClassCircularityError();
            }
        public:
            JClassCircularityErrorClass():jcpp::lang::JClass(){
                canonicalName=new JString("java.lang.ClassCircularityError");
                name=new JString("java.lang.ClassCircularityError");
                simpleName=new JString("ClassCircularityError");
                serialVersionUID=1054362542914539689LL;
            }

            virtual void initialize(){
                JConstructor* cons=addConstructor(new JConstructor(JClassCircularityError::getClazz(),JModifier::PUBLIC,createJClassCircularityError));
            }

            virtual JClass* getSuperclass(){
                return JLinkageError::getClazz();
            }
        };

        static JClass* clazz;

        JClass* JClassCircularityError::getClazz(){
            if (clazz==null){
                clazz=new JClassCircularityErrorClass();
            }
            return clazz;
        }

        JClassCircularityError::JClassCircularityError():JLinkageError(getClazz()){
        }

        JClassCircularityError::JClassCircularityError(JClass* _class):JLinkageError(_class){
        }

        JClassCircularityError::JClassCircularityError(JString* message):JLinkageError(getClazz()){
            this->message = message;
        }

        JClassCircularityError::~JClassCircularityError(){
        }
    }
}

