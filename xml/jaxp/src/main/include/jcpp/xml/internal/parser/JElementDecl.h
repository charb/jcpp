#ifndef JCPP_XML_INTERNAL_PARSER_ELEMENT_DECL_H
#define JCPP_XML_INTERNAL_PARSER_ELEMENT_DECL_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/util/JHashtable.h"
#include "jcpp/xml/internal/parser/JElementValidator.h"
#include "jcpp/xml/internal/parser/JContentModel.h"

using namespace jcpp::util;

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace parser{            

            	// @Class(canonicalName="javax.xml.internal.parser.ElementDecl", simpleName="ElementDecl");
            	class JCPP_EXPORT JElementDecl : public JObject{
                public:
                    JString* name;
                    JString* id;
                    JString* contentType;
                    JElementValidator* validator;
                    JContentModel*    model;
                    jbool ignoreWhitespace;
                    jbool isFromInternalSubset;
                    JHashtable* attributes;
    
                    JElementDecl(JString* s);

                    static JClass* getClazz();

                    virtual ~JElementDecl();
                };
            }
        }
    }
}

#endif
