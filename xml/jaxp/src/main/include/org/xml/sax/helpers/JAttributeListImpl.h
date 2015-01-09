#ifndef ORG_XML_SAX_HELPERS_ATTRIBUTE_LIST_IMPL_H
#define ORG_XML_SAX_HELPERS_ATTRIBUTE_LIST_IMPL_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/util/JVector.h"
#include "org/xml/sax/JAttributeList.h"

using namespace org::xml::sax;

namespace org{
    namespace xml{
        namespace sax{
            namespace helpers{

            	// @Class(canonicalName="org.xml.sax.helpers.AttributeListImpl", simpleName="AttributeListImpl");
                class JCPP_EXPORT JAttributeListImpl : public JObject, public JAttributeList{
                protected:
                    JVector* names;
                    JVector* types;
                    JVector* values;
                    JAttributeListImpl(JClass* _class);

                public:
                    JAttributeListImpl();

                    JAttributeListImpl(JAttributeList* atts);

                    static JClass* getClazz();

                    virtual void setAttributeList(JAttributeList* atts);

                    virtual void addAttribute(JString* name, JString* type, JString* value);

                    virtual void removeAttribute(JString* name);

                    virtual void clear();

                    virtual jint getLength();

                    virtual JString* getName(jint i);

                    virtual JString* getType(jint i);
                    
                    virtual JString* getValue(jint i);

                    virtual JString* getType(JString* name);

                    virtual JString* getValue(JString* name);

                    virtual ~JAttributeListImpl();
                };
            }
        }
    }
}

#endif
