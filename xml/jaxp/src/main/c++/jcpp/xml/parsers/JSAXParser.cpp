#include "jcpp/xml/parsers/JSAXParser.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JUnsupportedOperationException.h"
#include "jcpp/lang/JIllegalArgumentException.h"

namespace jcpp{
    namespace xml{
        namespace parsers{

            JSAXParser::JSAXParser(JClass* _class):JObject(_class){
            }

            void JSAXParser::reset(){
                throw new JUnsupportedOperationException();
            }

            void JSAXParser::parse(JInputStream* is, JHandlerBase* hb){
                if (is == null) {
                    throw new JIllegalArgumentException(new JString("InputStream cannot be null"));
                }

                JInputSource* input = new JInputSource(is);
                parse(input, hb);
            }

            void JSAXParser::parse(JInputStream* is,JHandlerBase* hb,JString* systemId){
                if (is == null) {
                    throw new JIllegalArgumentException(new JString("InputStream cannot be null"));
                }

                JInputSource* input = new JInputSource(is);
                input->setSystemId(systemId);
                parse(input, hb);
            }

            void JSAXParser::parse(JInputStream* is, JDefaultHandler* dh){
                if (is == null) {
                    throw new JIllegalArgumentException(new JString("InputStream cannot be null"));
                }

                JInputSource* input = new JInputSource(is);
                parse(input, dh);
            }

            void JSAXParser::parse(JInputStream* is, JDefaultHandler* dh, JString* systemId){
                if (is == null) {
                    throw new JIllegalArgumentException(new JString("InputStream cannot be null"));
                }

                JInputSource* input = new JInputSource(is);
                input->setSystemId(systemId);
                parse(input, dh);
            }

            void JSAXParser::parse(JString* uri, JHandlerBase* hb){
                if (uri == null) {
                    throw new JIllegalArgumentException(new JString("uri cannot be null"));
                }

                JInputSource* input = new JInputSource(uri);
                parse(input, hb);
            }

            void JSAXParser::parse(JString* uri, JDefaultHandler* dh){
                if (uri == null) {
                    throw new JIllegalArgumentException(new JString("uri cannot be null"));
                }

                JInputSource* input = new JInputSource(uri);
                parse(input, dh);
            }

            void JSAXParser::parse(JFile* f, JHandlerBase* hb){
                if (f == null) {
                    throw new JIllegalArgumentException(new JString("File cannot be null"));
                }

                JInputSource* input = new JInputSource(f->getAbsolutePath());
                parse(input, hb);
            }

            void JSAXParser::parse(JFile* f, JDefaultHandler* dh){
                if (f == null) {
                    throw new JIllegalArgumentException(new JString("File cannot be null"));
                }

                JInputSource* input = new JInputSource(f->getAbsolutePath());
                parse(input, dh);
            }

            void JSAXParser::parse(JInputSource* is, JHandlerBase* hb){
                if (is == null) {
                    throw new JIllegalArgumentException(new JString("InputSource cannot be null"));
                }

                JParser* parser = getParser();
                if (hb != null) {
                    parser->setDocumentHandler(hb);
                    parser->setEntityResolver(hb);
                    parser->setErrorHandler(hb);
                    parser->setDTDHandler(hb);
                }
                parser->parse(is);
            }

            void JSAXParser::parse(JInputSource* is, JDefaultHandler* dh){
                if (is == null) {
                    throw new JIllegalArgumentException(new JString("InputSource cannot be null"));
                }

                JXMLReader* reader = getXMLReader();
                if (dh != null) {
                    reader->setContentHandler(dh);
                    reader->setEntityResolver(dh);
                    reader->setErrorHandler(dh);
                    reader->setDTDHandler(dh);
                }
                reader->parse(is);
            }

            jbool JSAXParser::isXIncludeAware(){
                throw new JUnsupportedOperationException();
            }

            JSAXParser::~JSAXParser(){
            }
        }
    }
}
