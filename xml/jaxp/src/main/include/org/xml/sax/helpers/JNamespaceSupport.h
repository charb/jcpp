#ifndef ORG_XML_SAX_HELPERS_NAMESPACE_SUPPORT_H
#define ORG_XML_SAX_HELPERS_NAMESPACE_SUPPORT_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JPrimitiveCharArray.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "org/xml/sax/JEntityResolver.h"
#include "org/xml/sax/JDTDHandler.h"
#include "org/xml/sax/JContentHandler.h"
#include "org/xml/sax/JErrorHandler.h"
#include "org/xml/sax/JInputSource.h"
#include "org/xml/sax/JLocator.h"
#include "org/xml/sax/JSAXParseException.h"
#include "org/xml/sax/JAttributes.h"
#include "jcpp/util/JVector.h"
#include "jcpp/util/JHashtable.h"
#include "jcpp/util/JEnumeration.h"

using namespace jcpp::util;
using namespace org::xml::sax;

namespace org{
    namespace xml{
        namespace sax{
            namespace helpers{

            	// @Class(canonicalName="org.xml.sax.helpers.NamespaceSupport", simpleName="NamespaceSupport");
                class JCPP_EXPORT JNamespaceSupport : public JObject{
                protected:
                    static JEnumeration* EMPTY_ENUMERATION;

                    // @Class(canonicalName="org.xml.sax.helpers.NamespaceSupport$Context", simpleName="NamespaceSupport$Context");
                    class JCPP_EXPORT JContext : public JObject {
                    protected:
                        JNamespaceSupport* support;
                        JHashtable* prefixTable;
                        JHashtable* uriTable;
                        JHashtable* elementNameTable;
                        JHashtable* attributeNameTable;
                        JString* defaultNS;
                        JVector* declarations;
                        jbool declSeen;
                        JContext* parent;
                        virtual void copyTables();

                    public:
                        JContext(JNamespaceSupport* support);

                        static JClass* getClazz();

                        virtual void setParent(JContext* parent);

                        virtual void clear();

                        virtual void declarePrefix(JString* prefix, JString* uri);

                        virtual JPrimitiveObjectArray* processName(JString* qName, jbool isAttribute);

                        virtual JString* getURI(JString* prefix);

                        virtual JString* getPrefix(JString* uri);

                        virtual JEnumeration* getDeclaredPrefixes();

                        virtual JEnumeration* getPrefixes();

                        virtual ~JContext();
                    };

                    JPrimitiveObjectArray* contexts;
                    JContext* currentContext;
                    jint contextPos;
                    jbool namespaceDeclUris;
                    friend class JContext;
                
                public:
                    static JString* XMLNS ;
                    static JString* NSDECL ;

                    JNamespaceSupport();

                    static JClass* getClazz();

                    virtual void reset();

                    virtual void pushContext();

                    virtual void popContext();

                    virtual jbool declarePrefix(JString* prefix, JString* uri);

                    virtual JPrimitiveObjectArray* processName(JString* qName, JPrimitiveObjectArray* parts,jbool isAttribute);

                    virtual JString* getURI(JString* prefix);

                    virtual JEnumeration* getPrefixes();

                    virtual JString* getPrefix(JString* uri);

                    virtual JEnumeration* getPrefixes(JString* uri);

                    virtual JEnumeration* getDeclaredPrefixes();

                    virtual void setNamespaceDeclUris(jbool value);

                    virtual jbool isNamespaceDeclUris();

                    virtual ~JNamespaceSupport();
                };
            }
        }
    }
}

#endif
