#include "org/xml/sax/helpers/JLocatorImpl.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JArrayIndexOutOfBoundsException.h"
#include "jcpp/lang/JSystem.h"

namespace org{
    namespace xml{
        namespace sax{
            namespace helpers{

                JLocatorImpl::JLocatorImpl(JClass* _class):JObject(_class){
                    publicId=null;
                    systemId=null;
                    lineNumber=0;
                    columnNumber=0;
                }

                JLocatorImpl::JLocatorImpl(JClass* _class,JLocator* locator):JObject(_class){
                    publicId=null;
                    systemId=null;
                    lineNumber=0;
                    columnNumber=0;
                    setPublicId(locator->getPublicId());
                    setSystemId(locator->getSystemId());
                    setLineNumber(locator->getLineNumber());
                    setColumnNumber(locator->getColumnNumber());
                }

                JLocatorImpl::JLocatorImpl():JObject(getClazz()){
                    publicId=null;
                    systemId=null;
                    lineNumber=0;
                    columnNumber=0;
                }

                JLocatorImpl::JLocatorImpl(JLocator* locator):JObject(getClazz()){
                    publicId=null;
                    systemId=null;
                    lineNumber=0;
                    columnNumber=0;
                    setPublicId(locator->getPublicId());
                    setSystemId(locator->getSystemId());
                    setLineNumber(locator->getLineNumber());
                    setColumnNumber(locator->getColumnNumber());
                }

                JString* JLocatorImpl::getPublicId(){
                    return publicId;
                }

                JString* JLocatorImpl::getSystemId(){
                    return systemId;
                }

                jint JLocatorImpl::getLineNumber(){
                    return lineNumber;
                }

                jint JLocatorImpl::getColumnNumber(){
                    return columnNumber;
                }

                void JLocatorImpl::setPublicId(JString* publicId){
                    this->publicId = publicId;
                }

                void JLocatorImpl::setSystemId(JString* systemId){
                    this->systemId = systemId;
                }

                void JLocatorImpl::setLineNumber(jint lineNumber){
                    this->lineNumber = lineNumber;
                }

                void JLocatorImpl::setColumnNumber(jint columnNumber){
                    this->columnNumber = columnNumber;
                }

                JLocatorImpl::~JLocatorImpl(){
                }
            }
        }
    }
}
