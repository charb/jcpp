#include "jcpp/io/JInputStreamReader.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JNullPointerException.h"

namespace jcpp{
    namespace io{

        JInputStreamReader::JInputStreamReader(jcpp::lang::JClass* _class,JInputStream* in):JReader(_class,in){
            try {
            	sd = JStreamDecoder::forInputStreamReader(in, this, (JString*)null);
            } catch(JUnsupportedCharsetException* e){
            	throw new JError(new JString("Default Charset Unsupported !!!"), e);
            }
        }

        JInputStreamReader::JInputStreamReader(JInputStream* in):JReader(getClazz(),in){
            try {
            	sd = JStreamDecoder::forInputStreamReader(in, this, (JString*)null);
            } catch(JUnsupportedCharsetException* e){
            	throw new JError(new JString("Default Charset Unsupported !!!"), e);
            }
        }

        JInputStreamReader::JInputStreamReader(JInputStream* in, JString* charsetName):JReader(getClazz(), in){
        	if (charsetName == null)
        		throw new JNullPointerException(new JString("charsetName"));
        	sd = JStreamDecoder::forInputStreamReader(in, this, charsetName);
        }

        JInputStreamReader::JInputStreamReader(JInputStream* in, JCharset* cs):JReader(getClazz(), in){
        	if (cs == null)
        		throw new JNullPointerException(new JString("charset"));
        	sd = JStreamDecoder::forInputStreamReader(in, this, cs);
        }

        JInputStreamReader::JInputStreamReader(JInputStream* in, JCharsetDecoder* dec):JReader(getClazz(), in){
        	if (dec == null)
        		throw new JNullPointerException(new JString("charset decoder"));
        	sd = JStreamDecoder::forInputStreamReader(in, this, dec);
        }

        JString* JInputStreamReader::getEncoding(){
        	return sd->getEncoding();
        }

        jint JInputStreamReader::read(){
            return sd->read();
        }

        jint JInputStreamReader::read(JPrimitiveCharArray* b,jint offset, jint length){
        	return sd->read(b, offset, length);
        }

        jbool JInputStreamReader::ready(){
            return sd->ready();
        }

        void JInputStreamReader::close(){
        	sd->close();
        }

        JInputStreamReader::~JInputStreamReader(){
        }
    }
}
