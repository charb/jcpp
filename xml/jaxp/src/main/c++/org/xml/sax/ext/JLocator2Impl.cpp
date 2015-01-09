#include "org/xml/sax/ext/JLocator2Impl.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JIllegalArgumentException.h"
#include "jcpp/lang/JArrayIndexOutOfBoundsException.h"
#include "jcpp/lang/JSystem.h"

namespace org{
    namespace xml{
        namespace sax{
            namespace ext{

                JLocator2Impl::JLocator2Impl(JClass* _class):JLocatorImpl(_class){
                    encoding=null;
                    version=null;
                }

                JLocator2Impl::JLocator2Impl():JLocatorImpl(getClazz()){
                    encoding=null;
                    version=null;
                }

                JLocator2Impl::JLocator2Impl(JLocator* locator):JLocatorImpl(getClazz(),locator){
                    encoding=null;
                    version=null;
                    if (dynamic_cast<JObject*>(locator)->isInstanceOf(JLocator2::getClazz())){
                        JLocator2* l2 = dynamic_cast<JLocator2*>(locator);
                        version = l2->getXMLVersion();
                        encoding = l2->getEncoding();
                    }
                }

                JString* JLocator2Impl::getXMLVersion(){
                    return version;
                }

                JString* JLocator2Impl::getEncoding(){
                    return encoding;
                }

                void JLocator2Impl::setXMLVersion(JString* version){
                    this->version=version;
                }

                void JLocator2Impl::setEncoding(JString* encoding){
                    this->encoding=encoding;
                }

                JLocator2Impl::~JLocator2Impl(){
                }
            }
        }
    }
}
