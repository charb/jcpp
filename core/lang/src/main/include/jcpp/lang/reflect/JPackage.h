#ifndef JCPP_LANG_REFLECT_JPACKAGE_H
#define JCPP_LANG_REFLECT_JPACKAGE_H

#include "jcpp/lang/JString.h"
#include "jcpp/native/api/NativeInclude.h"

using namespace std;
using namespace jcpp::lang;

namespace jcpp{
    namespace util{
        class JList;
    }
    namespace lang{
        class JObject;
        class JClass;

        namespace reflect{

            class JCPP_EXPORT JPackage : public JObject{
                protected:
                    JString* name;
                    jcpp::util::JList* classes;
                    jcpp::util::JList* packages;
                    
                    JPackage(JString* name,jcpp::lang::JClass* _class);
                    JPackage* addClass(jcpp::lang::JClass* c);
                    JPackage* addPackage(JPackage* p);

                public:
                    static jcpp::lang::JClass* getClazz();

                    virtual JPackage* getSuperPackage()=0;

                    virtual jcpp::util::JList* getPackages()=0;
                    
                    virtual JString* toString();
                    
                    virtual jcpp::util::JList* getClasses();

                    virtual ~JPackage();
            };
        }
    }
}

#endif
