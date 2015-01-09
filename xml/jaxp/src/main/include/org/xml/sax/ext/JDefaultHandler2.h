#ifndef ORG_XML_SAX_EXT_DEFAULT_HANDLER2_IMPL_H
#define ORG_XML_SAX_EXT_DEFAULT_HANDLER2_IMPL_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JPrimitiveBooleanArray.h"
#include "org/xml/sax/helpers/JDefaultHandler.h"
#include "org/xml/sax/ext/JLexicalHandler.h"
#include "org/xml/sax/ext/JDeclHandler.h"
#include "org/xml/sax/ext/JEntityResolver2.h"
#include "org/xml/sax/JInputSource.h"

using namespace org::xml::sax;
using namespace org::xml::sax::helpers;

namespace org{
    namespace xml{
        namespace sax{
            namespace ext{

            	// @Class(canonicalName="org.xml.sax.ext.DefaultHandler2", simpleName="DefaultHandler2");
                class JCPP_EXPORT JDefaultHandler2 : public JDefaultHandler, public virtual JLexicalHandler, public virtual JDeclHandler, public virtual JEntityResolver2{
                protected:
                    JDefaultHandler2(JClass* _class);

                public:
                    JDefaultHandler2();

                    static JClass* getClazz();

                    virtual void startCDATA();

                    virtual void endCDATA();
                    
                    virtual void startDTD(JString* name, JString* publicId, JString* systemId);

                    virtual void endDTD();

                    virtual void startEntity(JString* name);

                    virtual void endEntity(JString* name);

                    virtual void comment(JPrimitiveCharArray* ch, jint start, jint length);

                    virtual void attributeDecl(JString* eName, JString* aName,JString* type, JString* mode, JString* value);

                    virtual void elementDecl(JString* name, JString* model);

                    virtual void externalEntityDecl(JString* name,JString* publicId, JString* systemId);

                    virtual void internalEntityDecl(JString* name, JString* value);

                    virtual JInputSource* getExternalSubset(JString* name, JString* baseURI);

                    virtual JInputSource* resolveEntity(JString* name, JString* publicId,JString* baseURI, JString* systemId);
                    
                    virtual JInputSource* resolveEntity(JString* publicId, JString* systemId);

                    virtual ~JDefaultHandler2();
                };
            }
        }
    }
}

#endif
