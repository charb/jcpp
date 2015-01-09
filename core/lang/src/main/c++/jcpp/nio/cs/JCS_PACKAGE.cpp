#include "jcpp/nio/cs/JCS_PACKAGE.h"
#include "jcpp/nio/JNIO_PACKAGE.h"
#include "jcpp/nio/cs/JArrayDecoder.h"
#include "jcpp/nio/cs/JArrayEncoder.h"
#include "jcpp/nio/cs/JHistoricallyNamedCharset.h"
#include "jcpp/nio/cs/JIllegalCharsetNameException.h"
#include "jcpp/nio/cs/JStreamEncoder.h"
#include "jcpp/nio/cs/JSurrogate.h"
#include "jcpp/nio/cs/JUnicode.h"
#include "jcpp/nio/cs/JUTF_8.h"


namespace jcpp{
	namespace nio{
		namespace cs{

		JCS_PACKAGE::JCS_PACKAGE():JPackage(new JString("cs"),JPackage::getClazz()){
			addClass(JArrayDecoder::getClazz());
			addClass(JArrayEncoder::getClazz());
			addClass(JHistoricallyNamedCharset::getClazz());
			addClass(JIllegalCharsetNameException::getClazz());
			addClass(JStreamEncoder::getClazz());
			addClass(JSurrogate::getClazz());
			addClass(JUnicode::getClazz());
			addClass(JUTF_8::getClazz());
		}

		static JCS_PACKAGE* cs=null;

		JCS_PACKAGE* JCS_PACKAGE::getPackage(){
			if (cs==null){
				cs=new JCS_PACKAGE();
			}
			return cs;
		}

		JPackage* JCS_PACKAGE::getSuperPackage(){
			return JNIO_PACKAGE::getPackage();
		}

		JList* JCS_PACKAGE::getPackages(){
			return packages;
		}

		JCS_PACKAGE::~JCS_PACKAGE(){
		}

		}
	}
}
