#include "org/xml/sax/helpers/JXMLReaderFactory.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JArrayIndexOutOfBoundsException.h"
#include "jcpp/lang/JSystem.h"
#include "jcpp/lang/JThread.h"
#include "jcpp/lang/JClassLoader.h"

namespace org{
    namespace xml{
        namespace sax{
            namespace helpers{

                JXMLReader* JXMLReaderFactory::createXMLReader(){
                    return createXMLReader(new JString("javax.xml.internal.parser.XMLReaderImpl"));
                }

                JXMLReader* JXMLReaderFactory::createXMLReader(JString* className){
                    JClass* c=JThread::currentThread()->getContextClassLoader()->loadClass(className);
                    return dynamic_cast<JXMLReader*>(c->newInstance());
                }

                JXMLReaderFactory::~JXMLReaderFactory(){
                }
            }
        }
    }
}
