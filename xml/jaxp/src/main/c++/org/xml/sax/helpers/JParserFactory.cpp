#include "org/xml/sax/helpers/JParserFactory.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JArrayIndexOutOfBoundsException.h"
#include "jcpp/lang/JSystem.h"
#include "jcpp/lang/JThread.h"
#include "jcpp/lang/JClassLoader.h"

namespace org{
    namespace xml{
        namespace sax{
            namespace helpers{

                JParser* JParserFactory::makeParser(){
                    return makeParser(new JString("TODO: create parser that use XMLReaderAdapter and XMLReaderImpl"));
                }

                JParser* JParserFactory::makeParser(JString* className){
                    JClass* c=JThread::currentThread()->getContextClassLoader()->loadClass(className);
                    return dynamic_cast<JParser*>(c->newInstance());
                }

                JParserFactory::~JParserFactory(){
                }
            }
        }
    }
}
