#ifndef ORG_XML_SAX_EXT_ATTRIBUTES2_IMPL_H
#define ORG_XML_SAX_EXT_ATTRIBUTES2_IMPL_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JPrimitiveBooleanArray.h"
#include "org/xml/sax/JAttributes.h"
#include "org/xml/sax/ext/JAttributes2.h"
#include "org/xml/sax/helpers/JAttributesImpl.h"

using namespace org::xml::sax;
using namespace org::xml::sax::helpers;

namespace org{
    namespace xml{
        namespace sax{
            namespace ext{

            	// @Class(canonicalName="org.xml.sax.ext.Attributes2Impl", simpleName="Attributes2Impl");
                class JCPP_EXPORT JAttributes2Impl : public JAttributesImpl, public virtual JAttributes2{
                protected:
                    JPrimitiveBooleanArray* declared;
                    JPrimitiveBooleanArray* specified;
                    JAttributes2Impl(JClass* _class);

                public:
                    JAttributes2Impl();

                    JAttributes2Impl(JAttributes* atts);

                    static JClass* getClazz();

                    virtual jbool isDeclared(jint index);

                    virtual jbool isDeclared(JString* uri, JString* localName);

                    virtual jbool isDeclared(JString* qName);

                    virtual jbool isSpecified(jint index);

                    virtual jbool isSpecified(JString* uri, JString* localName);

                    virtual jbool isSpecified(JString* qName);

                    virtual void setAttributes(JAttributes* atts);

                    virtual void addAttribute(JString* uri, JString* localName, JString* qName,JString* type, JString* value);

                    virtual void removeAttribute(jint index);

                    virtual void setDeclared(jint index, jbool value);

                    virtual void setSpecified(jint index, jbool value);

                    virtual ~JAttributes2Impl();
                };
            }
        }
    }
}

#endif
