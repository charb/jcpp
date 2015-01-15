#ifndef JCPP_LANG_JSTACK_TRACE_ELEMENT_H
#define JCPP_LANG_JSTACK_TRACE_ELEMENT_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JString.h"
#include "jcpp/io/JSerializable.h"
#include "jcpp/lang/JPrimitiveInt.h"

using namespace jcpp::io;

namespace jcpp{
    namespace lang{

    	// @Class(canonicalName="java.lang.StackTraceElement", simpleName="StackTraceElement");
        class JCPP_EXPORT JStackTraceElement: public JObject, public JSerializable {
        private:
        	static const jlong serialVersionUID = 6992337162326171013LL;

            JString* declaringClass;
            JString* methodName;
            JString* fileName;
            JPrimitiveInt* lineNumber;
            JPrimitiveInt* getPLineNumber();
            void setPLineNumber(JPrimitiveInt* lineNumber);

        public:
            JStackTraceElement();

            JStackTraceElement(JString* declaringClass,JString* methodName,JString* fileName,jint lineNumber);

            static jcpp::lang::JClass* getClazz();

            virtual JString* getDeclaringClass();

            virtual void setDeclaringClass(JString* declaringClass);

            virtual JString* getMethodName();

            virtual void setMethodName(JString* methodName);

            virtual JString* getFileName();

            virtual void setFileName(JString* fileName);

            virtual jint getLineNumber();

            virtual void setLineNumber(jint lineNumber);

            virtual jbool equals(JObject* other);

            virtual jint hashCode();

            virtual JString* toString();

            virtual ~JStackTraceElement();
        };
    }
}


#endif
