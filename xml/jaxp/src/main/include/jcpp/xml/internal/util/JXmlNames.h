#ifndef JCPP_XML_INTERNAL_UTIL_XMLNAMES_H
#define JCPP_XML_INTERNAL_UTIL_XMLNAMES_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace util{            

            	// @Class(canonicalName="javax.xml.internal.util.XmlNames", simpleName="XmlNames");
                class JCPP_EXPORT JXmlNames : public JInterface{
                public:
                    static JClass* getClazz();

                    static JString* SPEC_XML_URI;
    
                    static JString* SPEC_XMLNS_URI;

                    static jbool isName(JString* value);

                    static jbool isUnqualifiedName(JString* value);

                    static jbool isQualifiedName(JString* value);

                    static jbool isNmtoken(JString* token);

                    static jbool isNCNmtoken(JString* token);

                    static JString* getPrefix(JString* qualifiedName);

                    static JString* getLocalPart(JString* qualifiedName);

                    virtual ~JXmlNames();
                };
            }
        }
    }
}

#endif
