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

