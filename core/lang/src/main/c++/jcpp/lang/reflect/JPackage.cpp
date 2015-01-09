#include "jcpp/lang/reflect/JPackage.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/util/JList.h"
#include "jcpp/util/JArrayList.h"
#include "jcpp/lang/JStringBuilder.h"

using namespace jcpp::lang;
using namespace jcpp::util;

namespace jcpp{
    namespace lang{
        namespace reflect{
            class JPackageClass : public jcpp::lang::JClass{
                public:
                    JPackageClass():jcpp::lang::JClass(){
                        canonicalName=new JString("java.lang.Package");
                        name=new JString("java.lang.Package");
                        simpleName=new JString("Package");
                        bIsPackage=true;
                    }

                    virtual jcpp::lang::JClass* getSuperclass(){
                        return null;
                    }
            };

            static jcpp::lang::JClass* clazz;

            jcpp::lang::JClass* JPackage::getClazz(){
                if (clazz==null){
                    clazz=new JPackageClass();
                }
                return clazz;
            }

            JPackage::JPackage(JString* name,jcpp::lang::JClass* _class):JObject(_class){
                this->name=name;
                this->classes=new JArrayList();
                this->packages=new JArrayList();
            }

            JPackage* JPackage::addClass(jcpp::lang::JClass* c){
                classes->add(c);
                c->setPackage(this);
                return this;
            }

            JPackage* JPackage::addPackage(JPackage* p){
                packages->add(p);
                return this;
            }

            JString* JPackage::toString(){
                JStringBuilder* builder=new JStringBuilder();
                builder->append("package ")->append(name);
                return builder->toString();
            }

            JList* JPackage::getClasses(){
                return classes;
            }

            JList* JPackage::getPackages(){
                return packages;
            }

            JPackage::~JPackage() {
            }
        }
    }
}

