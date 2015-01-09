#ifndef JCPP_XML_INTERNAL_PARSER_ELEMENT_VALIDATOR_H
#define JCPP_XML_INTERNAL_PARSER_ELEMENT_VALIDATOR_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace parser{            

            	// @Class(canonicalName="javax.xml.internal.parser.ElementValidator", simpleName="ElementValidator");
            	class JCPP_EXPORT JElementValidator : public JObject{
                protected:
                    JElementValidator(JClass* _class);

                public:
                    static JElementValidator* ANY;

                    JElementValidator();

                    static JClass* getClazz();

                    virtual void consume(JString* type);

                    virtual void text();

                    virtual void done();

                    virtual ~JElementValidator();
                };
            }
        }
    }
}

#endif
