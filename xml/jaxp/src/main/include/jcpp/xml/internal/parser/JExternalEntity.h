#ifndef JCPP_XML_INTERNAL_PARSER_EXTERNAL_ENTITY_DECL_H
#define JCPP_XML_INTERNAL_PARSER_EXTERNAL_ENTITY_DECL_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/xml/internal/parser/JEntityDecl.h"
#include "org/xml/sax/JEntityResolver.h"
#include "org/xml/sax/JInputSource.h"
#include "org/xml/sax/JLocator.h"
#include "org/xml/sax/JSAXException.h"

using namespace org::xml::sax;

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace parser{            

            	// @Class(canonicalName="javax.xml.internal.parser.ExternalEntity", simpleName="ExternalEntity");
            	class JCPP_EXPORT JExternalEntity : public JEntityDecl{
                public:
                    JString* systemId;
                    JString* publicId;
                    JString* notation;
                    JString* verbatimSystemId;
    
                    JExternalEntity(JLocator* l);

                    static JClass* getClazz();

                    virtual JInputSource* getInputSource(JEntityResolver* r);

                    virtual ~JExternalEntity();
                };
            }
        }
    }
}

#endif
