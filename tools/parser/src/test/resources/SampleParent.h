#ifndef SAMPLEPARENT_H_
#define SAMPLEPARENT_H_

#include "SampleGrandParent.h"

class SampleParent: public helloGrandParent::SampleGrandParent {
public:
	SampleParent();
	virtual ~SampleParent();
};

#endif /* SAMPLEPARENT_H_ */
