#ifndef JCPP_XML_INTERNAL_PARSER_ATTRIBUTES_EX_H
#define JCPP_XML_INTERNAL_PARSER_ATTRIBUTES_EX_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "org/xml/sax/JAttributes.h"

using namespace org::xml::sax;

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace parser{

            	// @Class(canonicalName="javax.xml.internal.parser.AttributesEx", simpleName="AttributesEx");
                class JCPP_EXPORT JAttributesEx : public virtual JAttributes{
                public:
                    static JClass* getClazz();

                    virtual jbool isSpecified(jint i)=0;

                    virtual JString* getDefault(jint i)=0;

                    virtual JString* getIdAttributeName()=0;

                    virtual ~JAttributesEx();
                };
            }
        }
    }
}

#endif
