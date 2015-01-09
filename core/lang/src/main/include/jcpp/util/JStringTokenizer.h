#ifndef JCPP_UTIL_JSTRING_TOKENIZER_H
#define JCPP_UTIL_JSTRING_TOKENIZER_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JPrimitiveIntArray.h"
#include "jcpp/util/JEnumeration.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace util{
        class JCPP_EXPORT JStringTokenizer : public JObject, public JEnumeration{
        protected:
        	jint currentPosition;
    		jint newPosition;
    		jint maxPosition;
    		JString* str;
    		JString* delimiters;
    		jbool retDelims;
    		jbool delimsChanged;
			jint maxDelimCodePoint;
			jbool hasSurrogates;
			JPrimitiveIntArray* delimiterCodePoints;
			virtual void setMaxDelimCodePoint();
			virtual jint skipDelimiters(jint startPos);
			virtual jint scanToken(jint startPos);
			virtual jbool isDelimiter(jint codePoint);

        public:
        	JStringTokenizer(JString* str, JString* delim, jbool returnDelims);

        	JStringTokenizer(JString* str, JString* delim);

        	JStringTokenizer(JString* str);

            static jcpp::lang::JClass* getClazz();

            virtual jbool hasMoreTokens();

            virtual JString* nextToken();

            virtual JString* nextToken(JString* delim);

            virtual jbool hasMoreElements();

            virtual JObject* nextElement();

            virtual jint countTokens();

            virtual ~JStringTokenizer();
        };
    }
}


#endif
