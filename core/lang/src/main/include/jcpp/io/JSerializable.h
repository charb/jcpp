#ifndef JCPP_IO_JSERIALIZABLE_H
#define JCPP_IO_JSERIALIZABLE_H

#include "jcpp/lang/JInterface.h"

using namespace jcpp::lang;

namespace jcpp{
	namespace lang{
		class JClass;
		class JObject;
	}
    namespace io{

    	//@Class(canonicalName="java.io.Serializable", simpleName="Serializable");
        class JCPP_EXPORT JSerializable : public JInterface{
        public:
            static jcpp::lang::JClass* getClazz();

            virtual ~JSerializable();
        };
    }
}

#endif
