#ifndef ORG_XML_SAX_EXT_LOCATOR2_IMPL_H
#define ORG_XML_SAX_EXT_LOCATOR2_IMPL_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JPrimitiveBooleanArray.h"
#include "org/xml/sax/JAttributes.h"
#include "org/xml/sax/ext/JLocator2.h"
#include "org/xml/sax/helpers/JLocatorImpl.h"

using namespace org::xml::sax;
using namespace org::xml::sax::helpers;

namespace org{
    namespace xml{
        namespace sax{
            namespace ext{

            	// @Class(canonicalName="org.xml.sax.ext.Locator2Impl", simpleName="Locator2Impl");
                class JCPP_EXPORT JLocator2Impl : public JLocatorImpl, public virtual JLocator2{
                protected:
                    JString* encoding;
                    JString* version;
                    JLocator2Impl(JClass* _class);

                public:
                    JLocator2Impl();

                    JLocator2Impl(JLocator* locator);

                    static JClass* getClazz();

                    virtual JString* getXMLVersion();

                    virtual JString* getEncoding();

                    virtual void setXMLVersion(JString* version);

                    virtual void setEncoding(JString* encoding);

                    virtual ~JLocator2Impl();
                };
            }
        }
    }
}

#endif
