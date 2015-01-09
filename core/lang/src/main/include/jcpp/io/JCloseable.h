#ifndef JCPP_IO_JCLOSEABLE_H
#define JCPP_IO_JCLOSEABLE_H

#include "jcpp/lang/JAutoCloseable.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{

    	//@Class(canonicalName="java.io.Closeable", simpleName="Closeable");
        class JCPP_EXPORT JCloseable : public JAutoCloseable  {
        public:
            static jcpp::lang::JClass* getClazz();

            virtual void close()=0;

            virtual ~JCloseable();
        };
    }
}

#endif
