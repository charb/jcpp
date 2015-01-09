#ifndef ORG_W3C_DOM_USER_DATA_HANDLER_H
#define ORG_W3C_DOM_USER_DATA_HANDLER_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "org/w3c/dom/JNode.h"

namespace org{
    namespace w3c{
        namespace dom{

        	// @Class(canonicalName="org.w3c.dom.UserDataHandler", simpleName="UserDataHandler");
            class JCPP_EXPORT JUserDataHandler : public JInterface{
            public:
                static JClass* getClazz();

                static jshort NODE_CLONED;
                static jshort NODE_IMPORTED;
                static jshort NODE_DELETED;
                static jshort NODE_RENAMED;
                static jshort NODE_ADOPTED;

                virtual void handle(jshort operation,JString* key,JObject* data,JNode* src,JNode* dst)=0;

                virtual ~JUserDataHandler();
            };
        }
    }
}

#endif
