#include "jcpp/lang/reflect/JREFLECT_PACKAGE.h"
#include "jcpp/lang/JLANG_PACKAGE.h"
#include "jcpp/lang/reflect/JAccessibleObject.h"
#include "jcpp/lang/reflect/JAnnotatedElement.h"
#include "jcpp/lang/reflect/JAnnotatedType.h"
#include "jcpp/lang/reflect/JArray.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JExecutable.h"
#include "jcpp/lang/reflect/JField.h"
#include "jcpp/lang/reflect/JInvocationHandler.h"
#include "jcpp/lang/reflect/JInvocationTargetException.h"
#include "jcpp/lang/reflect/JMalformedParameterizedTypeException.h"
#include "jcpp/lang/reflect/JMalformedParametersException.h"
#include "jcpp/lang/reflect/JMember.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/reflect/JPackage.h"
#include "jcpp/lang/reflect/JProxy.h"
#include "jcpp/lang/reflect/JUndeclaredThrowableException.h"

namespace jcpp{
    namespace lang{
        namespace reflect{
            JREFLECT_PACKAGE::JREFLECT_PACKAGE():JPackage(new JString("java.lang.reflect"),JPackage::getClazz()){
                addClass(JAccessibleObject::getClazz());
                addClass(JAnnotatedElement::getClazz());
                addClass(JAnnotatedType::getClazz());
                addClass(JArray::getClazz());
                addClass(JConstructor::getClazz());
                addClass(JExecutable::getClazz());
                addClass(JField::getClazz());
                addClass(JInvocationHandler::getClazz());
                addClass(JInvocationTargetException::getClazz());
                addClass(JMalformedParameterizedTypeException::getClazz());
                addClass(JMalformedParametersException::getClazz());
                addClass(JMember::getClazz());
                addClass(JMethod::getClazz());
                addClass(JModifier::getClazz());
                addClass(JPackage::getClazz());
                addClass(JProxy::getClazz());
                addClass(JUndeclaredThrowableException::getClazz());
            }

            JPackage* JREFLECT_PACKAGE::getSuperPackage(){
                return JLANG_PACKAGE::getPackage();
            }

            JList* JREFLECT_PACKAGE::getPackages(){
                return packages;
            }

            static JREFLECT_PACKAGE* jreflect=null;

            JREFLECT_PACKAGE* JREFLECT_PACKAGE::getPackage(){
                if (jreflect==null){
                    jreflect=new JREFLECT_PACKAGE();
                }
                return jreflect;
            }

            JREFLECT_PACKAGE::~JREFLECT_PACKAGE(){
            }
        }
    }
}
