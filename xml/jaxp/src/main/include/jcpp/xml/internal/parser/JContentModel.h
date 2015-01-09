#ifndef JCPP_XML_INTERNAL_PARSER_CONTENT_MODEL_H
#define JCPP_XML_INTERNAL_PARSER_CONTENT_MODEL_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/util/JHashtable.h"

using namespace jcpp::util;

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace parser{

            	// @Class(canonicalName="javax.xml.internal.parser.ContentModel", simpleName="ContentModel");
                class JCPP_EXPORT JContentModel : public JObject{
                public:
                    jchar type;
                    JObject* content;
                    JContentModel* next;
                    JHashtable* cache;
    
                    JContentModel(JString* element);

                    JContentModel(jchar type, JContentModel* content);

                    static JClass* getClazz();

                    virtual jbool empty();

                    virtual jbool first(JString* token);

                    virtual JString* toString();

                    virtual JString* contentString();

                    virtual JString* toString(jbool isOuter);

                    virtual ~JContentModel();
                };
            }
        }
    }
}

#endif
