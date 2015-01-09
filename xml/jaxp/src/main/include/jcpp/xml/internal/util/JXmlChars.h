#ifndef JCPP_XML_INTERNAL_UTIL_XMLCHARS_H
#define JCPP_XML_INTERNAL_UTIL_XMLCHARS_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace util{            

            	// @Class(canonicalName="javax.xml.internal.util.XmlChars", simpleName="XmlChars");
            	class JCPP_EXPORT JXmlChars : public JInterface{
                public:
                    static JClass* getClazz();

                    static jbool isChar(jint ucs4char);

                    static jbool isNameChar(jchar c);

                    static jbool isNCNameChar(jchar c);

                    static jbool isSpace(jchar c);

                    static jbool isLetter(jchar c);

                    static jbool isCompatibilityChar(jchar c);

                    static jbool isLetter2(jchar c);

                    static jbool isDigit(jchar c);

                    static jbool isExtender(jchar c);

                    virtual ~JXmlChars();
                };
            }
        }
    }
}

#endif
