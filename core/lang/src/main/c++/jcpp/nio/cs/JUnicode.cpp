#include "jcpp/nio/cs/JUnicode.h"
#include "jcpp/nio/cs/JUTF_8.h"


namespace jcpp {
	namespace nio {
		namespace cs {

	JUnicode::JUnicode(jcpp::lang::JClass* _class, JString* name, JPrimitiveObjectArray* aliases)
		: JCharset(_class, name, aliases)
	{	}

	jbool JUnicode::contains(JCharset* cs)
	{
		//TODO add other Unicode encodings later
		return ( //(cs->isInstanceOf(US_ASCII))
//				|| (cs->isInstanceOf(ISO_8859_1))
//				|| (cs->isInstanceOf(ISO_8859_15))
//				|| (cs->isInstanceOf(MS1252))
				 (cs->isInstanceOf(JUTF_8::getClazz()))
//				|| (cs->isInstanceOf(UTF_16))
//				|| (cs->isInstanceOf(UTF_16BE))
//				|| (cs->isInstanceOf(UTF_16LE))
//				|| (cs->isInstanceOf(UTF_16LE_BOM))
//				|| (cs->getName()->equals(new JString("GBK")))
//				|| (cs->getName()->equals(new JString("GB18030")))
//				|| (cs->getName()->equals(new JString("ISO-8859-2")))
//				|| (cs->getName()->equals(new JString("ISO-8859-3")))
//				|| (cs->getName()->equals(new JString("ISO-8859-4")))
//				|| (cs->getName()->equals(new JString("ISO-8859-5")))
//				|| (cs->getName()->equals(new JString("ISO-8859-6")))
//				|| (cs->getName()->equals(new JString("ISO-8859-7")))
//				|| (cs->getName()->equals(new JString("ISO-8859-8")))
//				|| (cs->getName()->equals(new JString("ISO-8859-9")))
//				|| (cs->getName()->equals(new JString("ISO-8859-13")))
//				|| (cs->getName()->equals(new JString("JIS_X0201")))
//				|| (cs->getName()->equals(new JString("x-JIS0208")))
//				|| (cs->getName()->equals(new JString("JIS_X0212-1990")))
//				|| (cs->getName()->equals(new JString("GB2312")))
//				|| (cs->getName()->equals(new JString("EUC-KR")))
//				|| (cs->getName()->equals(new JString("x-EUC-TW")))
//				|| (cs->getName()->equals(new JString("EUC-JP")))
//				|| (cs->getName()->equals(new JString("x-euc-jp-linux")))
//				|| (cs->getName()->equals(new JString("KOI8-R")))
//				|| (cs->getName()->equals(new JString("TIS-620")))
//				|| (cs->getName()->equals(new JString("x-ISCII91")))
//				|| (cs->getName()->equals(new JString("windows-1251")))
//				|| (cs->getName()->equals(new JString("windows-1253")))
//				|| (cs->getName()->equals(new JString("windows-1254")))
//				|| (cs->getName()->equals(new JString("windows-1255")))
//				|| (cs->getName()->equals(new JString("windows-1256")))
//				|| (cs->getName()->equals(new JString("windows-1257")))
//				|| (cs->getName()->equals(new JString("windows-1258")))
//				|| (cs->getName()->equals(new JString("windows-932")))
//				|| (cs->getName()->equals(new JString("x-mswin-936")))
//				|| (cs->getName()->equals(new JString("x-windows-949")))
//				|| (cs->getName()->equals(new JString("x-windows-950")))
//				|| (cs->getName()->equals(new JString("windows-31j")))
//				|| (cs->getName()->equals(new JString("Big5")))
//				|| (cs->getName()->equals(new JString("Big5-HKSCS")))
//				|| (cs->getName()->equals(new JString("x-MS950-HKSCS")))
//				|| (cs->getName()->equals(new JString("ISO-2022-JP")))
//				|| (cs->getName()->equals(new JString("ISO-2022-KR")))
//				|| (cs->getName()->equals(new JString("x-ISO-2022-CN-CNS")))
//				|| (cs->getName()->equals(new JString("x-ISO-2022-CN-GB")))
//				|| (cs->getName()->equals(new JString("Big5-HKSCS")))
//				|| (cs->getName()->equals(new JString("x-Johab")))
//				|| (cs->getName()->equals(new JString("Shift_JIS")))
				);
	}

	JUnicode::~JUnicode()
	{	}


		}
	}
}
