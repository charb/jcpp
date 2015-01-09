#ifndef JCPP_XML_INTERNAL_PARSER_CONTENT_MODEL_STATE_H
#define JCPP_XML_INTERNAL_PARSER_CONTENT_MODEL_STATE_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/xml/internal/parser/JContentModel.h"

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace parser{

            	// @Class(canonicalName="javax.xml.internal.parser.ContentModelState", simpleName="ContentModelState");
                class JCPP_EXPORT JContentModelState : public JObject{
                public:
                    JContentModel* model;
                    jbool sawOne;
                    JContentModelState* next;
    
                    JContentModelState(JContentModel* model);

                    JContentModelState(JObject* content, JContentModelState* next);

                    static JClass* getClazz();

                    virtual jbool terminate();

                    virtual JContentModelState* advance(JString* token);

                    virtual ~JContentModelState();
                };
            }
        }
    }
}

#endif
