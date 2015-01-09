#ifndef JCPP_XML_INTERNAL_PARSER_ATTRIBUTES_EX_IMPL_H
#define JCPP_XML_INTERNAL_PARSER_ATTRIBUTES_EX_IMPL_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/xml/internal/parser/JAttributesEx.h"
#include "org/xml/sax/helpers/JAttributesImpl.h"
#include "jcpp/util/JVector.h"

using namespace org::xml::sax::helpers;

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace parser{

            	// @Class(canonicalName="javax.xml.internal.parser.AttributesExImpl", simpleName="AttributesExImpl");
                class JCPP_EXPORT JAttributesExImpl : public JAttributesImpl, public virtual JAttributesEx{
                protected:
                    JVector* specified;
                    JVector* defaults;
                    JString* idAttributeName;

                public:
                    JAttributesExImpl();

                    static JClass* getClazz();

                    virtual void clear();

                    virtual void addAttribute(JString* uri, JString* localName, JString* qName,JString* type, JString* value, JString* defaultValue,jbool isSpecified);

                    virtual jbool isSpecified(jint i);

                    virtual JString* getDefault(jint i);

                    virtual JString* getIdAttributeName();

                    virtual void setIdAttributeName(JString* name);

                    virtual ~JAttributesExImpl();
                };
            }
        }
    }
}

#endif
