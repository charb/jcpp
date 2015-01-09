#ifndef JCPP_XML_INTERNAL_PARSER_RESOLVER_H
#define JCPP_XML_INTERNAL_PARSER_RESOLVER_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JClassLoader.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "jcpp/util/JHashtable.h"
#include "jcpp/io/JInputStream.h"
#include "org/xml/sax/JEntityResolver.h"
#include "org/xml/sax/JInputSource.h"
#include "jcpp/io/JFile.h"

using namespace org::xml::sax;
using namespace jcpp::util;
using namespace jcpp::io;

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace parser{            

            	// @Class(canonicalName="javax.xml.internal.parser.Resolver", simpleName="Resolver");
            	class JCPP_EXPORT JResolver : public JObject, public JEntityResolver{
                protected:
                    jbool ignoringMIME;
                    JHashtable* id2uri;
                    JHashtable* id2resource;
                    JHashtable* id2loader;
                    static JPrimitiveObjectArray* types;
                    static JPrimitiveObjectArray* getTypes();

                public:
                    JResolver();

                    static JClass* getClazz();

                    static JInputSource* createInputSource(JString* contentType,JInputStream* stream, jbool checkType,JString* scheme);

                    static JInputSource* createInputSource(JFile* file);

                    virtual JInputSource* resolveEntity(JString* name, JString* uri);

                    virtual jbool isIgnoringMIME();

                    virtual void setIgnoringMIME(jbool value);

                    virtual JString* name2uri(JString* publicId);

                    virtual void registerCatalogEntry(JString* publicId,JString* uri);

                    virtual JInputStream* mapResource(JString* publicId);

                    virtual void registerCatalogEntry(JString* publicId,JString* resourceName,JClassLoader* loader);

                    virtual ~JResolver();
                };
            }
        }
    }
}

#endif
