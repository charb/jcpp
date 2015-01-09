#ifndef JCPP_IO_JFLUSHABLE_H
#define JCPP_IO_JFLUSHABLE_H

#include "jcpp/lang/JInterface.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{

    	//@Class(canonicalName="java.io.Flushable", simpleName="Flushable");
       class JCPP_EXPORT JFlushable : public JInterface {
            public:
                static jcpp::lang::JClass* getClazz();

                virtual void flush()=0;

                virtual ~JFlushable();
        };
    }
}

#endif 
