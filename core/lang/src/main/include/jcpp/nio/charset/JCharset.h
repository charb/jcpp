#ifndef JCPP_NIO_CHARSET_JCHARSET_H
#define JCPP_NIO_CHARSET_JCHARSET_H

#include "jcpp/lang/JComparable.h"
#include "jcpp/native/api/NativeInclude.h"
#include "jcpp/nio/charset/JUnsupportedCharsetException.h"
#include "jcpp/nio/cs/JIllegalCharsetNameException.h"
#include "jcpp/nio/charset/JCharsetEncoder.h"
#include "jcpp/nio/charset/JCharsetDecoder.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"

using namespace jcpp::nio::cs;

namespace jcpp {
	namespace nio {
		namespace charset {

		// @Class(canonicalName="java.nio.charset.Charset", simpleName="Charset");
		class JCPP_EXPORT JCharset : public JObject, public JComparable
		{
		private:
			JString* name;
			JPrimitiveObjectArray* aliases;
			static void checkName(JString* s);

			static JCharset* lookup(JString* charsetName);
			static JCharset* lookup2(JString* charsetName);

		protected:
			JCharset(jcpp::lang::JClass* _class, JString* canonicalName, JPrimitiveObjectArray* aliases);

		public:
			static jcpp::lang::JClass* getClazz();

			static JCharset* forName(JString* charsetName);
			static JCharset* defaultCharset();

			static jbool isSupported(JString* charsetName);
			JString* getName();
			virtual JCharsetEncoder* newEncoder() = 0;
			virtual JCharsetDecoder* newDecoder() = 0;
			virtual jint compareTo(JObject* that);

			virtual ~JCharset();
		};


		}
	}
}



#endif /* JCHARSET_H_ */
