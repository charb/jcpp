#include "jcpp/xml/internal/jaxp/JSAXParserFactoryImpl.h"
#include "jcpp/xml/internal/parser/JXMLReaderImpl.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JBoolean.h"
#include "org/xml/sax/helpers/JDefaultHandler.h"
#include "org/xml/sax/JSAXNotSupportedException.h"
#include "org/xml/sax/JSAXNotRecognizedException.h"
#include "jcpp/lang/JIllegalArgumentException.h"
#include "jcpp/xml/internal/jaxp/JSAXParserImpl.h"

using namespace jcpp::xml::internal::parser;

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace jaxp{

                JSAXParserFactoryImpl::JSAXParserFactoryImpl():JSAXParserFactory(getClazz()){
                    features=null;
                }

                JSAXParser* JSAXParserFactoryImpl::newSAXParser(){
                    return new JSAXParserImpl(this, features);
                }

                JSAXParserImpl* JSAXParserFactoryImpl::newSAXParserImpl(){
                    return new JSAXParserImpl(this, features);
                }

                void JSAXParserFactoryImpl::setFeature(JString* name,jbool value){
                    if (features == null) {
                        features = new JHashtable();
                    }
                    features->put(name, new JBoolean(value));

                    try {
                        newSAXParserImpl();
                    } catch (JSAXNotSupportedException* e) {
                        features->remove(name);
                        throw e;
                    } catch (JSAXNotRecognizedException* e) {
                        features->remove(name);
                        throw e;
                    }
                }

                jbool JSAXParserFactoryImpl::getFeature(JString* name){
                    return newSAXParserImpl()->getXMLReader()->getFeature(name);
                }

                JSAXParserFactoryImpl::~JSAXParserFactoryImpl(){
                }
            }
        }
    }
}
