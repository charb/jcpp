#include "jcpp/nio/charset/JCHARSET_PACKAGE.h"
#include "jcpp/nio/JNIO_PACKAGE.h"
#include "jcpp/nio/charset/JCharacterCodingException.h"
#include "jcpp/nio/charset/JCharset.h"
#include "jcpp/nio/charset/JCharsetDecoder.h"
#include "jcpp/nio/charset/JCharsetEncoder.h"
#include "jcpp/nio/charset/JCoderMalfunctionError.h"
#include "jcpp/nio/charset/JCoderResult.h"
#include "jcpp/nio/charset/JCodingErrorAction.h"
#include "jcpp/nio/charset/JMalformedInputException.h"
#include "jcpp/nio/charset/JUnmappableCharacterException.h"
#include "jcpp/nio/charset/JUnsupportedCharsetException.h"

#include "jcpp/lang/reflect/JPackage.h"
#include "jcpp/util/JList.h"

using namespace jcpp::lang::reflect;
using namespace jcpp::util;

namespace jcpp{
	namespace nio{
		namespace charset{

		JCHARSET_PACKAGE::JCHARSET_PACKAGE():JPackage(new JString("charset"),JPackage::getClazz()){
			addClass(JCharacterCodingException::getClazz());
			addClass(JCharset::getClazz());
			addClass(JCharsetDecoder::getClazz());
			addClass(JCharsetEncoder::getClazz());
			addClass(JCoderMalfunctionError::getClazz());
			addClass(JCoderResult::getClazz());
			addClass(JCodingErrorAction::getClazz());
			addClass(JMalformedInputException::getClazz());
			addClass(JUnmappableCharacterException::getClazz());
			addClass(JUnsupportedCharsetException::getClazz());
		}

		static JCHARSET_PACKAGE* jcharset=null;

		JCHARSET_PACKAGE* JCHARSET_PACKAGE::getPackage(){
			if (jcharset==null){
				jcharset=new JCHARSET_PACKAGE();
			}
			return jcharset;
		}

		JPackage* JCHARSET_PACKAGE::getSuperPackage(){
			return JNIO_PACKAGE::getPackage();
		}


		JList* JCHARSET_PACKAGE::getPackages(){
			return packages;
		}

		JCHARSET_PACKAGE::~JCHARSET_PACKAGE(){
		}

		}
	}
}

