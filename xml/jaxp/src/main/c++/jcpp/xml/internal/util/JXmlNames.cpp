#include "jcpp/xml/internal/util/JXmlNames.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/xml/internal/util/JXmlChars.h"

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace util{

                JString* JXmlNames::SPEC_XML_URI = new JString("http://www.w3.org/XML/1998/namespace");
    
                
                JString* JXmlNames::SPEC_XMLNS_URI = new JString("http://www.w3.org/2000/xmlns/");

                jbool JXmlNames::isName(JString* value){
                    if (value == null || (new JString(""))->equals(value)){
                        return false;
                    }

                    jchar c = value->charAt(0);
                    if (!JXmlChars::isLetter(c) && c != '_' && c != ':'){
                        return false;
                    }
                    for (jint i = 1; i < value->length (); i++){
                        if (!JXmlChars::isNameChar(value->charAt(i))){
                            return false;
                        }
                    }
                    return true;
                }

                jbool JXmlNames::isUnqualifiedName(JString* value){
                    if (value == null || value->length() == 0){
                        return false;
                    }

                    jchar c = value->charAt(0);
                    if (!JXmlChars::isLetter(c) && c != '_'){
                        return false;
                    }
                    for (jint i = 1; i < value->length(); i++){
                        if (!JXmlChars::isNCNameChar(value->charAt(i))){
                            return false;
                        }
                    }
                    return true;
                }

                jbool JXmlNames::isQualifiedName(JString* value){
                    if (value == null){
                        return false;
                    }

                    jint first = value->indexOf(':');

                    if (first <= 0){
                        return isUnqualifiedName(value);
                    }

                    jint last = value->lastIndexOf(':');
                    if (last != first){
                        return false;
                    }
                    
                    return isUnqualifiedName(value->substring(0, first))
                        && isUnqualifiedName(value->substring(first + 1));
                }

                jbool JXmlNames::isNmtoken(JString* token){
                    jint length = token->length();

                    for (jint i = 0; i < length; i++){
                        if (!JXmlChars::isNameChar(token->charAt(i))){
                            return false;
                        }
                    }
                    return true;
                }

                jbool JXmlNames::isNCNmtoken(JString* token){
                    return isNmtoken(token) && token->indexOf(':') < 0;
                }

                JString* JXmlNames::getPrefix(JString* qualifiedName){
                    jint index = qualifiedName->indexOf(':');
                    return index <= 0 ? null : qualifiedName->substring(0, index);
                }

                JString* JXmlNames::getLocalPart(JString* qualifiedName){
                    jint index = qualifiedName->indexOf(':');
                    if (index < 0) {
                        return qualifiedName;
                    }

                    if (index == qualifiedName->length() - 1) {
                        return null;
                    }

                    return qualifiedName->substring(index + 1);
                }

                JXmlNames::~JXmlNames(){
                }
            }
        }
    }
}
