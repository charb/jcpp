#include "jcpp/nio/JByteOrder.h"



namespace jcpp {
	namespace nio {

	const JByteOrder* JByteOrder::JBIG_ENDIAN = new JByteOrder(new JString("BIG_ENDIAN"));
	const JByteOrder* JByteOrder::JLITTLE_ENDIAN = new JByteOrder(new JString("LITTLE_ENDIAN"));

	JByteOrder::JByteOrder(JString* name) : JObject(getClazz())
	{
		this->name = name;
	}

	JByteOrder* JByteOrder::nativerOrder()
	{
		if (NativeEndian::isBigEndian()){
			return const_cast<JByteOrder*>(JBIG_ENDIAN);
		}else{
			return const_cast<JByteOrder*>(JLITTLE_ENDIAN);
		}
	}

	JString* JByteOrder::toString()
	{
		return this->name;
	}

	JByteOrder::~JByteOrder()
	{	}


	}
}
