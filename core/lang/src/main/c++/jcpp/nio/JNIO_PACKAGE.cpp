#include "jcpp/JCPP_PACKAGE.h"
#include "jcpp/nio/JNIO_PACKAGE.h"
#include "jcpp/nio/cs/JCS_PACKAGE.h"
#include "jcpp/nio/charset/JCHARSET_PACKAGE.h"
#include "jcpp/nio/JBuffer.h"
#include "jcpp/nio/JByteBuffer.h"
#include "jcpp/nio/JByteBufferAsCharBufferB.h"
#include "jcpp/nio/JByteBufferAsCharBufferL.h"
#include "jcpp/nio/JByteOrder.h"
#include "jcpp/nio/JCharBuffer.h"
#include "jcpp/nio/JHeapByteBuffer.h"
#include "jcpp/nio/JHeapCharBuffer.h"
#include "jcpp/nio/JReadOnlyBufferException.h"
#include "jcpp/nio/JStringCharBuffer.h"


namespace jcpp{
	namespace nio{

		JNIO_PACKAGE::JNIO_PACKAGE():JPackage(new JString("nio"),JPackage::getClazz()){
			addClass(JBuffer::getClazz());
			addClass(JBufferOverflowException::getClazz());
			addClass(JBufferUnderflowException::getClazz());
			addClass(JByteBuffer::getClazz());
			addClass(JByteBufferAsCharBufferB::getClazz());
			addClass(JByteBufferAsCharBufferL::getClazz());
			addClass(JByteOrder::getClazz());
			addClass(JCharBuffer::getClazz());
			addClass(JHeapByteBuffer::getClazz());
			addClass(JHeapCharBuffer::getClazz());
			addClass(JInvalidMarkException::getClazz());
			addClass(JReadOnlyBufferException::getClazz());
			addClass(JStringCharBuffer::getClazz());
		}

		static JNIO_PACKAGE* jnio=null;

		JNIO_PACKAGE* JNIO_PACKAGE::getPackage(){
			if (jnio==null){
				jnio=new JNIO_PACKAGE();
			}
			return jnio;
		}

		JPackage* JNIO_PACKAGE::getSuperPackage(){
			return JCPP_PACKAGE::getPackage();
		}

		JList* JNIO_PACKAGE::getPackages(){
			if (packages->size()==0){
				addPackage(JCHARSET_PACKAGE::getPackage());
				addPackage(JCS_PACKAGE::getPackage());
			}
			return packages;
		}


		JNIO_PACKAGE::~JNIO_PACKAGE(){
		}

	}
}
