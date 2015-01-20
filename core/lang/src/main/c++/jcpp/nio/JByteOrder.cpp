#include "jcpp/nio/JByteOrder.h"



namespace jcpp {
	namespace nio {

	JByteOrder* JByteOrder::JBIG_ENDIAN = new JByteOrder(new JString("BIG_ENDIAN"));
	JByteOrder* JByteOrder::JLITTLE_ENDIAN = new JByteOrder(new JString("LITTLE_ENDIAN"));

	JByteOrder::JByteOrder(JString* name) : JObject(getClazz())
	{
		this->name = name;
	}

	JByteOrder* JByteOrder::nativerOrder()
	{
		if (NativeEndian::isBigEndian()){
			return JBIG_ENDIAN;
		}else{
			return JLITTLE_ENDIAN;
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
