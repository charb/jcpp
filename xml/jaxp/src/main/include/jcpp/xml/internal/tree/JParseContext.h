#ifndef JCPP_XML_INTERNAL_TREE_PARSE_CONTEXT_H
#define JCPP_XML_INTERNAL_TREE_PARSE_CONTEXT_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/xml/internal/tree/JXmlWritable.h"
#include "org/xml/sax/JLocator.h"
#include "org/xml/sax/JErrorHandler.h"

using namespace org::xml::sax;

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace tree{            

            	// @Class(canonicalName="javax.xml.internal.tree.ParseContext", simpleName="ParseContext");
                class JCPP_EXPORT JParseContext : public JInterface{
                public:
                    static JClass* getClazz();

                    virtual JErrorHandler* getErrorHandler()=0;

                    virtual JLocator* getLocator()=0;

                    virtual ~JParseContext();
                };
            }
        }
    }
}

#endif
