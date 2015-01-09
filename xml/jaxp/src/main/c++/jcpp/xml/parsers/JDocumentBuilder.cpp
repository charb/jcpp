#include "jcpp/xml/parsers/JDocumentBuilder.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JUnsupportedOperationException.h"
#include "jcpp/lang/JIllegalArgumentException.h"

namespace jcpp{
    namespace xml{
        namespace parsers{

            JDocumentBuilder::JDocumentBuilder(JClass* _class):JObject(_class){
            }

            void JDocumentBuilder::reset(){
                throw new JUnsupportedOperationException();
            }

            JDocument* JDocumentBuilder::parse(JInputStream* is){
                if (is == null) {
                    throw new JIllegalArgumentException(new JString("InputStream cannot be null"));
                }

                JInputSource* in = new JInputSource(is);
                return parse(in);
            }

            JDocument* JDocumentBuilder::parse(JInputStream* is, JString* systemId){
                if (is == null) {
                    throw new JIllegalArgumentException(new JString("InputStream cannot be null"));
                }

                JInputSource* in = new JInputSource(is);
                in->setSystemId(systemId);
                return parse(in);
            }

            JDocument* JDocumentBuilder::parse(JString* uri){
                if (uri == null) {
                    throw new JIllegalArgumentException(new JString("URI cannot be null"));
                }

                JInputSource* in = new JInputSource(uri);
                return parse(in);
            }

            JDocument* JDocumentBuilder::parse(JFile* f){
                if (f == null) {
                    throw new JIllegalArgumentException(new JString("File cannot be null"));
                }

                JInputSource* in = new JInputSource(f->getAbsolutePath());
                return parse(in);
            }

            jbool JDocumentBuilder::isXIncludeAware(){
                throw new JUnsupportedOperationException();
            }

            JDocumentBuilder::~JDocumentBuilder(){
            }
        }
    }
}
