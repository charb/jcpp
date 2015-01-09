#ifndef JCPP_IO_JOBJECTINPUTVALIDATION_H
#define JCPP_IO_JOBJECTINPUTVALIDATION_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{

    	//@Class(canonicalName="java.io.ObjectInputValidation", simpleName="ObjectInputValidation");
        class JCPP_EXPORT JObjectInputValidation : public JInterface  {
            public:
                static jcpp::lang::JClass* getClazz();

                virtual void validateObject()=0;

                virtual ~JObjectInputValidation();
        };
    }
}

#endif
