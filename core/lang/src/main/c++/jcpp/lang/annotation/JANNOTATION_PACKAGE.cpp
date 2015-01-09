#include "jcpp/lang/annotation/JANNOTATION_PACKAGE.h"
#include "jcpp/lang/JLANG_PACKAGE.h"
#include "jcpp/lang/annotation/JAnnotation.h"

namespace jcpp{
    namespace lang{
        namespace reflect{
            JANNOTATION_PACKAGE::JANNOTATION_PACKAGE():JPackage(new JString("java.lang.annotation"),JPackage::getClazz()){
                addClass(JAnnotation::getClazz());
            }

            JPackage* JANNOTATION_PACKAGE::getSuperPackage(){
                return JLANG_PACKAGE::getPackage();
            }

            JList* JANNOTATION_PACKAGE::getPackages(){
                return packages;
            }

            static JANNOTATION_PACKAGE* jreflect=null;

            JANNOTATION_PACKAGE* JANNOTATION_PACKAGE::getPackage(){
                if (jreflect==null){
                    jreflect=new JANNOTATION_PACKAGE();
                }
                return jreflect;
            }

            JANNOTATION_PACKAGE::~JANNOTATION_PACKAGE(){
            }
        }
    }
}
