#ifndef JCPP_IO_JOPTIONALDATAEXCEPTION_H
#define JCPP_IO_JOPTIONALDATAEXCEPTION_H

#include "jcpp/io/JObjectStreamException.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JPrimitiveInt.h"
#include "jcpp/lang/JPrimitiveBoolean.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{

    	//@Class(canonicalName="java.io.OptionalDataException", simpleName="OptionalDataException");
        class JCPP_EXPORT JOptionalDataException : public JObjectStreamException{
        private:
       				static const jlong serialVersionUID = -8011121865681257820LL;
        protected:
            JPrimitiveInt* length;
            JPrimitiveBoolean* eof;

            JOptionalDataException(jcpp::lang::JClass* _clazz);

            JPrimitiveInt* getPLength();
            void setPLength(JPrimitiveInt* l);

            JPrimitiveBoolean* getPEOF();
            void setPEOF(JPrimitiveBoolean* eof);
            

        public:
            JOptionalDataException();
            JOptionalDataException(JString* message);
            JOptionalDataException(jbool end);

            static jcpp::lang::JClass* getClazz();

            jint getLength();

            void setLength(jint l);

            jbool getEOF();

            void setEOF(jbool eof);

            virtual ~JOptionalDataException();
        };
    }
}

#endif
