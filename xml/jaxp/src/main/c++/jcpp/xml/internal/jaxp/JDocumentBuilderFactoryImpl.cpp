#include "jcpp/xml/internal/jaxp/JDocumentBuilderFactoryImpl.h"
#include "jcpp/xml/internal/parser/JXMLReaderImpl.h"
#include "jcpp/lang/JClass.h"
#include "org/xml/sax/helpers/JDefaultHandler.h"
#include "jcpp/lang/JIllegalArgumentException.h"
#include "jcpp/xml/internal/jaxp/JDocumentBuilderImpl.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;
using namespace jcpp::xml::internal::parser;

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace jaxp{

                JDocumentBuilderFactoryImpl::JDocumentBuilderFactoryImpl():JDocumentBuilderFactory(getClazz()){
                }

                JDocumentBuilder* JDocumentBuilderFactoryImpl::newDocumentBuilder(){
                    return new JDocumentBuilderImpl(this);
                }
                
                void JDocumentBuilderFactoryImpl::setAttribute(JString* name, JObject* value){
                    throw new JIllegalArgumentException(new JString("No attributes are implemented"));
                }

                JObject* JDocumentBuilderFactoryImpl::getAttribute(JString* name){
                    throw new JIllegalArgumentException(new JString("No attributes are implemented"));
                }

                void JDocumentBuilderFactoryImpl::setFeature(JString* name, jbool value){
                    throw new JIllegalArgumentException(new JString("No attributes are implemented"));
                }

                jbool JDocumentBuilderFactoryImpl::getFeature(JString* name){
                    throw new JIllegalArgumentException(new JString("No attributes are implemented"));
                }

                JDocumentBuilderFactoryImpl::~JDocumentBuilderFactoryImpl(){
                }
            }
        }
    }
}
