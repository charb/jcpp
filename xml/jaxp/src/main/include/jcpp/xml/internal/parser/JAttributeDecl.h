#ifndef JCPP_XML_INTERNAL_PARSER_ATTRIBUTE_DECL_H
#define JCPP_XML_INTERNAL_PARSER_ATTRIBUTE_DECL_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace parser{

            	// @Class(canonicalName="javax.xml.internal.parser.AttributeDecl", simpleName="AttributeDecl");
                class JCPP_EXPORT JAttributeDecl : public JObject{
                public:
                    JString* name;
                    JString*  type;
                    JPrimitiveObjectArray*  values;
                    JString*  defaultValue;
                    jbool isRequired;
                    jbool isFixed;
                    jbool isFromInternalSubset;
                    JString* valueDefault;
                    
                    static JString* CDATA;
                    static JString* ID;
                    static JString* IDREF;
                    static JString* IDREFS;
                    static JString* ENTITY;
                    static JString* ENTITIES;
                    static JString* NMTOKEN;
                    static JString* NMTOKENS;
                    static JString* NOTATION;
                    static JString* ENUMERATION;
                    static JString* IMPLIED;
                    static JString* REQUIRED;
                    static JString* FIXED;
    
                    JAttributeDecl(JString* s);

                    static JClass* getClazz();

                    virtual ~JAttributeDecl();
                };
            }
        }
    }
}

#endif
