#include "jcpp/xml/parsers/JDocumentBuilderFactory.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JThread.h"
#include "jcpp/lang/JUnsupportedOperationException.h"
#include "jcpp/lang/JIllegalArgumentException.h"

namespace jcpp{
    namespace xml{
        namespace parsers{

            JDocumentBuilderFactory::JDocumentBuilderFactory(JClass* _class):JObject(_class){
                validating = false;
                namespaceAware = false;
                whitespace = false;
                expandEntityRef = true;
                ignoreComments = false;
                coalescing = false;
            }

            JDocumentBuilderFactory* JDocumentBuilderFactory::newInstance(){
                return newInstance(new JString("javax.xml.internal.jaxp.DocumentBuilderFactoryImpl"),JThread::currentThread()->getContextClassLoader());
            }

            JDocumentBuilderFactory* JDocumentBuilderFactory::newInstance(JString* factoryClassName, JClassLoader* classLoader){
                JClass* c=classLoader->loadClass(factoryClassName);
                return dynamic_cast<JDocumentBuilderFactory*>(c->newInstance());
            }
      
            void JDocumentBuilderFactory::setNamespaceAware(jbool awareness){
                this->namespaceAware = awareness;
            }

            void JDocumentBuilderFactory::setValidating(jbool validating){
                this->validating = validating;
            }

            void JDocumentBuilderFactory::setIgnoringElementContentWhitespace(jbool whitespace){
                this->whitespace = whitespace;
            }

            void JDocumentBuilderFactory::setExpandEntityReferences(jbool expandEntityRef){
                this->expandEntityRef = expandEntityRef;
            }

            void JDocumentBuilderFactory::setIgnoringComments(jbool ignoreComments){
                this->ignoreComments = ignoreComments;
            }

            void JDocumentBuilderFactory::setCoalescing(jbool coalescing){
                this->coalescing = coalescing;
            }

            jbool JDocumentBuilderFactory::isNamespaceAware(){
                return namespaceAware;
            }

            jbool JDocumentBuilderFactory::isValidating(){
                return validating;
            }

            jbool JDocumentBuilderFactory::isIgnoringElementContentWhitespace(){
                return whitespace;
            }

            jbool JDocumentBuilderFactory::isExpandEntityReferences(){
                return expandEntityRef;
            }

            jbool JDocumentBuilderFactory::isIgnoringComments(){
                return ignoreComments;
            }

            jbool JDocumentBuilderFactory::isCoalescing(){
                return coalescing;
            }

            void JDocumentBuilderFactory::setXIncludeAware(jbool state){
                if (state) {
                    throw new JUnsupportedOperationException();
                }
            }

            jbool JDocumentBuilderFactory::isXIncludeAware(){
                throw new JUnsupportedOperationException();
            }

            JDocumentBuilderFactory::~JDocumentBuilderFactory(){
            }
        }
    }
}
