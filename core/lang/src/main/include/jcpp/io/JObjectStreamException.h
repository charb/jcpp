#ifndef JCPP_IO_JOBJECTSTREAMEXCEPTION_H
#define JCPP_IO_JOBJECTSTREAMEXCEPTION_H

#include "jcpp/io/JIOException.h"
#include "jcpp/lang/JClass.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{

    	//@Class(canonicalName="java.io.ObjectStreamException", simpleName="ObjectStreamException");
        class JCPP_EXPORT JObjectStreamException : public JIOException{
        private:
       		static const jlong serialVersionUID = 7260898174833392607LL;

        protected:
            JObjectStreamException(jcpp::lang::JClass* _clazz);

        public:
            JObjectStreamException();

            JObjectStreamException(JString* message);

            static jcpp::lang::JClass* getClazz();

            virtual ~JObjectStreamException();
        };
    }
}

#endif
