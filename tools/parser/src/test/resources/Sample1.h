#ifndef SAMPLE1_H_
#define SAMPLE1_H_

#include "SampleParent.h"
#include "SampleParent2.h"

char* strGlobal1;
char* strGlobal2 = (char*) 0;

namespace helloNamespace {
	class UndefindedClass;
	char* strHelloGlobal = (char*) 0;
	namespace internal {
		char * internalHello = (char*) 0;
		namespace emptyns {}
	}
}

/*
 * @MetadataAnnotation(meta1="hello world", meta2="3", meta3="")
 * @AnotherMetadataAnnotation(meta1=hello world, meta2=3, meta3=)
 */
//@EmptyAnnotation()
class Sample1 : public SampleParent, SampleParent2 {
public:
	Sample1();
	virtual ~Sample1();

	void addValue(Sample1* object);
	void addValue(Sample1* objectA, Sample1* objectB);
	Sample1* getCopy();

private:
	int value;
	char *strField;
	static char *strStaticField; 

};

namespace sampleNs {
	class Sample2 {
		public:
			Sample2();
			virtual ~Sample2();
			char* sayHello(char *strMessage);
		private:
			char *strInternal;
		public:
			class SampleChild {
				public:
					SampleChild();
					virtual ~SampleChild();

					int childValue;
			};
	};
}

#endif
