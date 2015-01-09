#ifndef JCPP_IO_JSTREAMCORRUPTEDEXCEPTION_H
#define JCPP_IO_JSTREAMCORRUPTEDEXCEPTION_H

#include "jcpp/io/JObjectStreamException.h"
#include "jcpp/lang/JClass.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{

    	//@Class(canonicalName="java.io.StreamCorruptedException", simpleName="StreamCorruptedException");
        class JCPP_EXPORT JStreamCorruptedException : public JObjectStreamException{
        private:
        	static const jlong serialVersionUID = 8983558202217591746LL;
        protected:
            JStreamCorruptedException(jcpp::lang::JClass* _clazz);

        public:
            JStreamCorruptedException();
            
            JStreamCorruptedException(JString* message);

            static jcpp::lang::JClass* getClazz();

            virtual ~JStreamCorruptedException();
        };
    }
}

#endif
