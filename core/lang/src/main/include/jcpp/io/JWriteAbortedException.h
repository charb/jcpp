#ifndef JCPP_IO_JWRITEABORTEDEXCEPTION_H
#define JCPP_IO_JWRITEABORTEDEXCEPTION_H

#include "jcpp/lang/JString.h"
#include "jcpp/lang/JThrowable.h"
#include "jcpp/lang/JException.h"
#include "jcpp/io/JObjectStreamException.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{

    	//@Class(canonicalName="java.io.WriteAbortedException", simpleName="WriteAbortedException");
        class JCPP_EXPORT JWriteAbortedException : public JObjectStreamException  {

        private:
       				static const jlong serialVersionUID = -3326426625597282442LL;
            protected:
                JException* detail;

            public:
                JWriteAbortedException();
                JWriteAbortedException(JString* message,JException* ex);

                static jcpp::lang::JClass* getClazz();

                virtual JThrowable * getCause();

                JException* getDetail();

                void setDetail(JException* e);

                virtual ~JWriteAbortedException();
        };
    }
}

#endif
