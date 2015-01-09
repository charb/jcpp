#ifndef ORG_XML_SAX_EXT_ATTRIBUTES2_H
#define ORG_XML_SAX_EXT_ATTRIBUTES2_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "org/xml/sax/JAttributes.h"

using namespace org::xml::sax;

namespace org{
    namespace xml{
        namespace sax{
            namespace ext{

            	// @Class(canonicalName="org.xml.sax.ext.Attributes2", simpleName="Attributes2");
                class JCPP_EXPORT JAttributes2 : public virtual JAttributes{
                public:
                    static JClass* getClazz();

                    virtual jbool isDeclared(jint index)=0;

                    virtual jbool isDeclared(JString* qName)=0;

                    virtual jbool isDeclared(JString* uri, JString* localName)=0;

                    virtual jbool isSpecified(jint index)=0;

                    virtual jbool isSpecified(JString* uri, JString* localName)=0;

                    virtual jbool isSpecified(JString* qName)=0;

                    virtual ~JAttributes2();
                };
            }
        }
    }
}

#endif
