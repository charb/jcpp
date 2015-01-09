#ifndef JCPP_NET_JURLCLASSLOADER_H
#define JCPP_NET_JURLCLASSLOADER_H

#include "jcpp/security/JSecureClassLoader.h"
#include "jcpp/io/JFile.h"
#include "jcpp/util/JList.h"
#include "jcpp/native/api/library/NativeLibrary.h"

using namespace jcpp::security;
using namespace jcpp::io;
using namespace jcpp::util;
using namespace jcpp::native::api::library;

namespace jcpp{
    namespace net{

		//@Class(canonicalName="java.net.URLClassLoader", simpleName="URLClassLoader");
        class JCPP_EXPORT JURLClassLoader : public JSecureClassLoader{
        protected:
            JList* files;
            NativeLibrary** libraries;
            void loadClasses();

        public:
            JURLClassLoader(JList* files,JClassLoader* parent);

            static jcpp::lang::JClass* getClazz();

            virtual void finalize();

            virtual ~JURLClassLoader();
        };
    }
}
#endif
