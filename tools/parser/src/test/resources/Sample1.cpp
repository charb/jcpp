#include "Sample1.h"

Sample1* globalSample = new Sample1();

namespace helloNamespace2 {
	namespace internal {
		char* strHelloGlobal2 = (char*) 0;
	}
}

char * Sample1::strStaticField = 0;

Sample1::Sample1() : strField(0) {
	value = 0;
}

Sample1::~Sample1() {
}

void Sample1::addValue(Sample1* object) {
    Sample1* anotherObject = new Sample1();
	value += object->value;
	for (char c[] = {'a','b','c','\0'}; *c == 0; c++) {
		*c = 'x';
	}
}

// @MethodDefinitionAnnotation(meta1=hello , meta2= "world", isDefinition=true)
// @AnotherMethodDefinitionAnnotation(meta1=hello , meta2 = "world", isDefinition=true)
void Sample1::addValue(Sample1* objectA, Sample1* objectB) {
    Sample1* someOtherObject = new Sample1();
	value += objectA->value;
	value += objectB->value;
}

Sample1* Sample1::getCopy() {
	Sample1* newObject = new Sample1();
	return newObject;
}

void* someFunction(Sample1* object, char* strParam) {
	Sample1* anotherObject = new Sample1();
	object->strField = strParam;
	return 0;
}

namespace sampleNs {
	Sample2::Sample2() : strInternal(0) {
	}
	
	Sample2::~Sample2() {
	}

	char* Sample2::sayHello(char *strMessage) {
		char* tmp = strMessage;
		return tmp;
	}

	Sample2::SampleChild::SampleChild() : childValue(0) {
	}

	Sample2::SampleChild::~SampleChild() {
	}
}
