#include "org/w3c/dom/JUserDataHandler.h"
#include "jcpp/lang/JClass.h"

namespace org{
    namespace w3c{
        namespace dom{

            jshort JUserDataHandler::NODE_CLONED = 1;
            jshort JUserDataHandler::NODE_IMPORTED = 2;
            jshort JUserDataHandler::NODE_DELETED = 3;
            jshort JUserDataHandler::NODE_RENAMED = 4;
            jshort JUserDataHandler::NODE_ADOPTED = 5;

            JUserDataHandler::~JUserDataHandler(){
            }
        }
    }
}
