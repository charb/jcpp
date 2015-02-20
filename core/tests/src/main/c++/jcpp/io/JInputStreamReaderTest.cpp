#include "jcpp/io/JInputStreamReaderTest.h"
#include "jcpp/io/JStringBufferInputStream.h"
#include "jcpp/lang/JSystem.h"
#include "jcpp/lang/JString.h"
#include "jcpp/lang/JStringBuilder.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{

        JInputStreamReaderTest::JInputStreamReaderTest(): JTestCase(getClazz() ,new JString("test")) {
        }

        void JInputStreamReaderTest::test() {
        	jbool ready1, ready2;

        	JStringBuilder *bu = new JStringBuilder();
        	for (int i = 0; i < 128; ++i)
        		bu->append((jchar)i);

        	JInputStream *in = new JStringBufferInputStream(bu->toString());
        	JInputStreamReader* inr = new JInputStreamReader(in);

        	ready1 = inr->ready();
        	assertTrue(new JString("Stream is not ready."), ready1);

        	jint data = inr->read();
        	JStringBuilder *bu2 = new JStringBuilder();
        	while(data != -1){
        	    jchar theChar = (jchar) data;
        	    bu2->append(theChar);
        	    data = inr->read();
        	}

        	assertEquals(new JString("Read string from stream is different from the input string"), bu->toString(), bu2->toString());

        	ready2 = inr->ready();
        	assertFalse(new JString("inconsistent ready state"), ready2);
        	inr->close();

        	JInputStream *in2 = new JStringBufferInputStream(new JString("hello"));
        	JInputStreamReader* inr2 = new JInputStreamReader(in2);

        	JPrimitiveCharArray* charArr = new JPrimitiveCharArray(2);
        	inr2->read(charArr, 0, 2);
        	assertEquals(new JString("read from windows error"), new JString(charArr), new JString("he"));

        	JString* en = inr2->getEncoding();
        	assertEquals(new JString("encoding error"), en, new JString("UTF8"));
        }

        JInputStreamReaderTest::~JInputStreamReaderTest(){
        }
    }
}
