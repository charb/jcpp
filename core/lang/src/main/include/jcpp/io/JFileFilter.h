#ifndef JCPP_IO_JFILEFILTER_H
#define JCPP_IO_JFILEFILTER_H

#include "jcpp/lang/JInterface.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{
        class JFile;
        //@Class(canonicalName="java.io.FileFilter", simpleName="FileFilter");
        class JCPP_EXPORT JFileFilter : public JInterface  {
            public:
                static jcpp::lang::JClass* getClazz();

                virtual jbool accept(JFile* file)=0;

                virtual ~JFileFilter();
        };
    }
}

#endif
