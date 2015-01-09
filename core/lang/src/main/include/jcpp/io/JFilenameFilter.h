#ifndef JCPP_IO_JFILENAMEFILTER_H
#define JCPP_IO_JFILENAMEFILTER_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JString.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{
        class JFile;

        //@Class(canonicalName="java.io.FilenameFilter", simpleName="FilenameFilter");
        class JCPP_EXPORT JFilenameFilter : public JInterface  {
            public:
                static jcpp::lang::JClass* getClazz();

                virtual jbool accept(JFile* dir, JString* name)=0;

                virtual ~JFilenameFilter();
        };
    }
}

#endif
