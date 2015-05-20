#ifndef JCPP_LANG_JClassLoader_H
#define JCPP_LANG_JClassLoader_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JString.h"
#include "jcpp/lang/reflect/JPackage.h"
#include "jcpp/util/JMap.h"

using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{

    	// @IgnoreReflection()
        class JCPP_EXPORT JClassLoader : public JObject{
        private:
            JClassLoader(jbool root);
            static jcpp::lang::JClass* clazz;
            static JClassLoader* bootClassLoader;
            static jbool initialized;
        protected:
            JClassLoader* parent;
            JMap* classes;
            jbool bIsBootClassLoader;
            static JString* SIG_I;
            static JString* SIG_B;
            static JString* SIG_J;
            static JString* SIG_F;
            static JString* SIG_D;
            static JString* SIG_S;
            static JString* SIG_C;
            static JString* SIG_Z;
            static JString* SIG_V;
            JClassLoader(jcpp::lang::JClass* _class,JClassLoader* parent);
            void initClasses(JPackage* p);
            virtual void addClass(jcpp::lang::JClass* jClass);
            static jcpp::lang::JClass* getClazz(JClassLoader* classLoader);

        public:
            static void init();

            static JClassLoader* getBootClassLoader();

            static jcpp::lang::JClass* getClazz();

            virtual JClassLoader* getParent();
            
            virtual jbool isBootClassLoader();
            
            virtual jcpp::lang::JClass* loadClass(JString* name);
            
            virtual jcpp::lang::JClass* loadClassBySignature(JString* name);
                        
            virtual ~JClassLoader();
        };
    }
}

#endif
