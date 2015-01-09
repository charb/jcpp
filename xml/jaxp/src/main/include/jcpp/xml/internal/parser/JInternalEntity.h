#ifndef JCPP_XML_INTERNAL_PARSER_INTERNAL_ENTITY_DECL_H
#define JCPP_XML_INTERNAL_PARSER_INTERNAL_ENTITY_DECL_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JPrimitiveCharArray.h"
#include "jcpp/xml/internal/parser/JEntityDecl.h"

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace parser{            

            	// @Class(canonicalName="javax.xml.internal.parser.InternalEntity", simpleName="InternalEntity");
            	class JCPP_EXPORT JInternalEntity : public JEntityDecl{
                public:
                    JPrimitiveCharArray* buf;
    
                    JInternalEntity(JString* name,JPrimitiveCharArray* value);

                    static JClass* getClazz();

                    virtual ~JInternalEntity();
                };
            }
        }
    }
}

#endif
