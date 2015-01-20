#ifndef JCPP_NIO_CHARSET_JCODERRESULT_H
#define JCPP_NIO_CHARSET_JCODERRESULT_H

#include "jcpp/native/api/NativeInclude.h"
#include "jcpp/lang/JString.h"
#include "jcpp/lang/JUnsupportedOperationException.h"
#include "jcpp/lang/JStringBuilder.h"
#include "jcpp/lang/JArrayIndexOutOfBoundsException.h"

namespace jcpp {
	namespace nio {
		namespace charset {

			// @Class(canonicalName="java.nio.charset.CoderResult", simpleName="CoderResult");
			class JCPP_EXPORT JCoderResult : public JObject {
			private:
				static const jint CR_UNDERFLOW = 0;
				static const jint CR_OVERFLOW = 1;
				static const jint CR_ERROR_MIN = 2;
				static const jint CR_MALFORMED = 2;
				static const jint CR_UNMAPPABLE = 3;

				const jint type;
				const jint length;

				JCoderResult(jint type, jint length);

				JString* getErrorNameFromID(jint id);

			public:
				static JCoderResult* JUNDERFLOW;
				static JCoderResult* JOVERFLOW;

				static jcpp::lang::JClass* getClazz();

				virtual JString* toString();
				jbool isUnderflow();
				jbool isOverflow();
				jbool isError();
				jbool isMalformed();
				jbool isUnmappable();
				jint getLength();

				void throwException();
				static JCoderResult* malformedForLength(jint length);

				virtual ~JCoderResult();
			};

		}
	}
}


#endif /* JCODERRESULT_H_ */
