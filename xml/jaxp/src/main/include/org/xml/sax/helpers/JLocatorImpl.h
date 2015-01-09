#ifndef ORG_XML_SAX_HELPERS_LOCATOR_IMPL_H
#define ORG_XML_SAX_HELPERS_LOCATOR_IMPL_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/util/JVector.h"
#include "org/xml/sax/JLocator.h"

using namespace org::xml::sax;

namespace org{
    namespace xml{
        namespace sax{
            namespace helpers{

            	// @Class(canonicalName="org.xml.sax.helpers.LocatorImpl", simpleName="LocatorImpl");
                class JCPP_EXPORT JLocatorImpl : public JObject, public virtual JLocator{
                protected:
                    JString* publicId;
                    JString* systemId;
                    jint lineNumber;
                    jint columnNumber;
                    JLocatorImpl(JClass* _class);
                    JLocatorImpl(JClass* _class, JLocator* locator);

                public:
                    JLocatorImpl();

                    JLocatorImpl(JLocator* locator);

                    static JClass* getClazz();

                    virtual JString* getPublicId();

                    virtual JString* getSystemId();

                    virtual jint getLineNumber();

                    virtual jint getColumnNumber();

                    virtual void setPublicId(JString* publicId);

                    virtual void setSystemId(JString* systemId);

                    virtual void setLineNumber(jint lineNumber);

                    virtual void setColumnNumber(jint columnNumber);

                    virtual ~JLocatorImpl();
                };
            }
        }
    }
}

#endif
