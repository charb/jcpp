#ifndef JCPP_XML_INTERNAL_PARSER_ENTITY_DECL_H
#define JCPP_XML_INTERNAL_PARSER_ENTITY_DECL_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace parser{            

            	// @Class(canonicalName="javax.xml.internal.parser.EntityDecl", simpleName="EntityDecl");
            	class JCPP_EXPORT JEntityDecl : public JObject{
                protected:
                    JEntityDecl(JClass* _class);
                public:
                    JString* name;
                    jbool isFromInternalSubset;
                    jbool isPE;
    
                    JEntityDecl();

                    static JClass* getClazz();

                    virtual ~JEntityDecl();
                };
            }
        }
    }
}

#endif
