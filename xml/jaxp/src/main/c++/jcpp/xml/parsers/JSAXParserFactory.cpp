#include "jcpp/xml/parsers/JSAXParserFactory.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JThread.h"
#include "jcpp/lang/JUnsupportedOperationException.h"
#include "jcpp/lang/JIllegalArgumentException.h"

namespace jcpp{
    namespace xml{
        namespace parsers{

            JSAXParserFactory::JSAXParserFactory(JClass* _class):JObject(_class){
                validating = false;
                namespaceAware = false;
            }

            JSAXParserFactory* JSAXParserFactory::newInstance(){
                return newInstance(new JString("javax.xml.internal.jaxp.SAXParserFactoryImpl"),JThread::currentThread()->getContextClassLoader());
            }

            JSAXParserFactory* JSAXParserFactory::newInstance(JString* factoryClassName, JClassLoader* classLoader){
                JClass* c=classLoader->loadClass(factoryClassName);
                return dynamic_cast<JSAXParserFactory*>(c->newInstance());
            }
      
            void JSAXParserFactory::setNamespaceAware(jbool awareness){
                this->namespaceAware = awareness;
            }

            void JSAXParserFactory::setValidating(jbool validating){
                this->validating = validating;
            }

            jbool JSAXParserFactory::isNamespaceAware(){
                return namespaceAware;
            }

            jbool JSAXParserFactory::isValidating(){
                return validating;
            }

            void JSAXParserFactory::setXIncludeAware(jbool state){
                if (state) {
                    throw new JUnsupportedOperationException();
                }
            }

            jbool JSAXParserFactory::isXIncludeAware(){
                throw new JUnsupportedOperationException();
            }

            JSAXParserFactory::~JSAXParserFactory(){
            }
        }
    }
}
