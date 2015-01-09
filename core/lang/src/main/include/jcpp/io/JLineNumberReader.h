#ifndef JCPP_IO_JLINENUMBERREADER_H
#define JCPP_IO_JLINENUMBERREADER_H

#include "jcpp/lang/JString.h"
#include "jcpp/io/JBufferedReader.h"
#include "jcpp/lang/JPrimitiveCharArray.h"

using namespace jcpp::lang;

namespace jcpp {
	namespace io {

		//@Class(canonicalName="java.io.LineNumberReader", simpleName="LineNumberReader");
		class JCPP_EXPORT JLineNumberReader: public JBufferedReader {
		protected:
			jint lineNumber;
			jint markedLineNumber;
			jbool skipLF;
			jbool markedSkipLF;
			JPrimitiveCharArray* skipBuffer;

		public:
			JLineNumberReader(JReader* in, jint sz);

			JLineNumberReader(JReader* in);

			static jcpp::lang::JClass* getClazz();

			virtual void setLineNumber(jint lineNumber);

			virtual jint getLineNumber();

			virtual jint read();

			virtual jint read(JPrimitiveCharArray* cbuf, jint off, jint len);

			virtual JString* readLine();

			virtual jlong skip(jlong n);

			virtual void mark(jint m);

			virtual void reset();

			virtual ~JLineNumberReader();
		};
	}
}

#endif
