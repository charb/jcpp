#ifndef ORG_XML_SAX_HELPERS_ATTRIBUTES_IMPL_H
#define ORG_XML_SAX_HELPERS_ATTRIBUTES_IMPL_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "org/xml/sax/JAttributes.h"

using namespace org::xml::sax;

namespace org{
    namespace xml{
        namespace sax{
            namespace helpers{

            	// @Class(canonicalName="org.xml.sax.helpers.AttributesImpl", simpleName="AttributesImpl");
                class JCPP_EXPORT JAttributesImpl : public JObject, public virtual JAttributes{
                protected:
                    jint length;
                    JPrimitiveObjectArray* data;
                    JAttributesImpl(JClass* _class);
                    JAttributesImpl(JClass* _class, JAttributes* atts);
                    void ensureCapacity(jint n);
                    void badIndex(jint index);

                public:
                    JAttributesImpl();

                    JAttributesImpl(JAttributes* atts);

                    static JClass* getClazz();

                    virtual jint getLength();

                    virtual JString* getURI(jint index);

                    virtual JString* getLocalName(jint index);

                    virtual JString* getQName(jint index);

                    virtual JString* getType(jint index);

                    virtual JString* getValue(jint index);

                    virtual jint getIndex(JString* uri, JString* localName);

                    virtual jint getIndex(JString* qName);

                    virtual JString* getType(JString* uri, JString* localName);

                    virtual JString* getType(JString* qName);

                    virtual JString* getValue(JString* uri, JString* localName);

                    virtual JString* getValue(JString* qName);

                    virtual void clear();

                    virtual void setAttributes(JAttributes* atts);

                    virtual void addAttribute(JString* uri, JString* localName, JString* qName,JString* type, JString* value);

                    virtual void setAttribute(jint index, JString* uri, JString* localName,JString* qName, JString* type, JString* value);

                    virtual void removeAttribute(jint index);

                    virtual void setURI(jint index, JString* uri);

                    virtual void setLocalName(jint index, JString* localName);

                    virtual void setQName(jint index, JString* qName);

                    virtual void setType(jint index, JString* type);

                    virtual void setValue(jint index, JString* value);

                    virtual ~JAttributesImpl();
                };
            }
        }
    }
}

#endif
