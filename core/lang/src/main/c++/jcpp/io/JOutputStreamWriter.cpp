#include "jcpp/io/JOutputStreamWriter.h"
#include "jcpp/lang/JClass.h"

namespace jcpp{
    namespace io{

        JOutputStreamWriter::JOutputStreamWriter(jcpp::lang::JClass* _class,JOutputStream* out):JWriter(_class, out){
        	try {
        		se = JStreamEncoder::forOutputStreamWriter(out, this, (JString*)null);
        	} catch (JUnsupportedEncodingException* e){
        		throw new JError(new JString("Unsupported Encoding"),e);
        	}
        }

        JOutputStreamWriter::JOutputStreamWriter(JOutputStream* out,JString* encoding):JWriter(getClazz(), out){
        	if (encoding == null)
        		throw new JNullPointerException(new JString("charsetName"));
        	se = JStreamEncoder::forOutputStreamWriter(out, this, encoding);
        }

        JOutputStreamWriter::JOutputStreamWriter(JOutputStream* out):JWriter(getClazz(), out){
        	try {
        		se = JStreamEncoder::forOutputStreamWriter(out, this, (JString*)null);
        	} catch (JUnsupportedEncodingException* e){
        		throw new JError(new JString("Unsupported Encoding"),e);
        	}
        }

        void JOutputStreamWriter::write(jint c){
        	se->write(c);
        }

        void JOutputStreamWriter::write(JPrimitiveCharArray* c,jint offset,jint length){
        	se->write(c, offset, length);
        }

        void JOutputStreamWriter::write(JString* c,jint offset,jint length){
            se->write(c, offset, length);
        }

        void JOutputStreamWriter::flush(){
            se->flush();
        }

        void JOutputStreamWriter::close(){
            se->close();
        }

        JOutputStreamWriter::~JOutputStreamWriter(){
        }
    }
}
