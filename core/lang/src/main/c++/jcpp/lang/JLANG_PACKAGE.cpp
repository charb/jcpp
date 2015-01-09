#include "jcpp/lang/JLANG_PACKAGE.h"
#include "jcpp/lang/JAbstractMethodError.h"
#include "jcpp/lang/JAbstractStringBuilder.h"
#include "jcpp/lang/JAppendable.h"
#include "jcpp/lang/JArithmeticException.h"
#include "jcpp/lang/JArrayIndexOutOfBoundsException.h"
#include "jcpp/lang/JArrayStoreException.h"
#include "jcpp/lang/JAssertionError.h"
#include "jcpp/lang/JAutoCloseable.h"
#include "jcpp/lang/JBoolean.h"
#include "jcpp/lang/JBootstrap.h"
#include "jcpp/lang/JBootstrapMethodError.h"
#include "jcpp/lang/JByte.h"
#include "jcpp/lang/JCharacter.h"
#include "jcpp/lang/JCharSequence.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JClassCastException.h"
#include "jcpp/lang/JClassCircularityError.h"
#include "jcpp/lang/JClassFormatError.h"
#include "jcpp/lang/JClassLoader.h"
#include "jcpp/lang/JClassNotFoundException.h"
#include "jcpp/lang/JCloneable.h"
#include "jcpp/lang/JCloneNotSupportedException.h"
#include "jcpp/lang/JComparable.h"
#include "jcpp/lang/JDouble.h"
#include "jcpp/lang/JEnum.h"
#include "jcpp/lang/JEnumConstantNotPresentException.h"
#include "jcpp/lang/JError.h"
#include "jcpp/lang/JException.h"
#include "jcpp/lang/JFloat.h"
#include "jcpp/lang/JIllegalAccessError.h"
#include "jcpp/lang/JIllegalAccessException.h"
#include "jcpp/lang/JIllegalArgumentException.h"
#include "jcpp/lang/JIllegalMonitorStateException.h"
#include "jcpp/lang/JIllegalStateException.h"
#include "jcpp/lang/JIllegalThreadStateException.h"
#include "jcpp/lang/JIncompatibleClassChangeError.h"
#include "jcpp/lang/JIndexOutOfBoundsException.h"
#include "jcpp/lang/JInstantiationError.h"
#include "jcpp/lang/JInstantiationException.h"
#include "jcpp/lang/JInteger.h"
#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JInternalError.h"
#include "jcpp/lang/JInterruptedException.h"
#include "jcpp/lang/JIterable.h"
#include "jcpp/lang/JLinkageError.h"
#include "jcpp/lang/JLong.h"
#include "jcpp/lang/JNegativeArraySizeException.h"
#include "jcpp/lang/JNoClassDefFoundError.h"
#include "jcpp/lang/JNoSuchFieldError.h"
#include "jcpp/lang/JNoSuchFieldException.h"
#include "jcpp/lang/JNoSuchMethodError.h"
#include "jcpp/lang/JNoSuchMethodException.h"
#include "jcpp/lang/JNullPointerException.h"
#include "jcpp/lang/JNumber.h"
#include "jcpp/lang/JNumberFormatException.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JOutOfMemoryError.h"
#include "jcpp/lang/JProcessBuilder.h"
#include "jcpp/lang/JPrimitiveBoolean.h"
#include "jcpp/lang/JPrimitiveBooleanArray.h"
#include "jcpp/lang/JPrimitiveByte.h"
#include "jcpp/lang/JPrimitiveByteArray.h"
#include "jcpp/lang/JPrimitiveChar.h"
#include "jcpp/lang/JPrimitiveCharArray.h"
#include "jcpp/lang/JPrimitiveDouble.h"
#include "jcpp/lang/JPrimitiveDoubleArray.h"
#include "jcpp/lang/JPrimitiveFloat.h"
#include "jcpp/lang/JPrimitiveFloatArray.h"
#include "jcpp/lang/JPrimitiveInt.h"
#include "jcpp/lang/JPrimitiveIntArray.h"
#include "jcpp/lang/JPrimitiveLong.h"
#include "jcpp/lang/JPrimitiveLongArray.h"
#include "jcpp/lang/JPrimitiveShort.h"
#include "jcpp/lang/JPrimitiveShortArray.h"
#include "jcpp/lang/JPrimitiveVoid.h"
#include "jcpp/lang/JReadable.h"
#include "jcpp/lang/JReflectiveOperationException.h"
#include "jcpp/lang/JRuntimeException.h"
#include "jcpp/lang/JSecurityException.h"
#include "jcpp/lang/JShort.h"
#include "jcpp/lang/JStackOverflowError.h"
#include "jcpp/lang/JStackTraceElement.h"
#include "jcpp/lang/JString.h"
#include "jcpp/lang/JStringBuffer.h"
#include "jcpp/lang/JStringBuilder.h"
#include "jcpp/lang/JStringIndexOutOfBoundsException.h"
#include "jcpp/lang/JSystem.h"
#include "jcpp/lang/JThread.h"
#include "jcpp/lang/JThrowable.h"
#include "jcpp/lang/JTypeNotPresentException.h"
#include "jcpp/lang/JUnknownError.h"
#include "jcpp/lang/JUnsatisfiedLinkError.h"
#include "jcpp/lang/JUnsupportedClassVersionError.h"
#include "jcpp/lang/JUnsupportedOperationException.h"
#include "jcpp/lang/JVerifyError.h"
#include "jcpp/lang/JVirtualMachineError.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/JString.h"
#include "jcpp/JCPP_PACKAGE.h"
#include "jcpp/lang/annotation/JANNOTATION_PACKAGE.h"
#include "jcpp/lang/reflect/JREFLECT_PACKAGE.h"

using namespace jcpp::lang::annotation;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace lang{
        JLANG_PACKAGE::JLANG_PACKAGE():JPackage(new JString("java.lang"),JPackage::getClazz()){
            addClass(JAbstractMethodError::getClazz());
            addClass(JAbstractStringBuilder::getClazz());
            addClass(JAppendable::getClazz());
            addClass(JArithmeticException::getClazz());
            addClass(JArrayIndexOutOfBoundsException::getClazz());
            addClass(JArrayStoreException::getClazz());
            addClass(JAssertionError::getClazz());
            addClass(JAutoCloseable::getClazz());
            addClass(JBoolean::getClazz());
            addClass(JBootstrap::getClazz());
            addClass(JBootstrapMethodError::getClazz());
            addClass(JByte::getClazz());
            addClass(JCharacter::getClazz());
            addClass(JCharSequence::getClazz());
            addClass(jcpp::lang::JClass::getClazz());
            addClass(JClassCastException::getClazz());
            addClass(jcpp::lang::JClassCircularityError::getClazz());
            addClass(jcpp::lang::JClassFormatError::getClazz());
            addClass(JClassLoader::getClazz());
            addClass(JClassNotFoundException::getClazz());
            addClass(JCloneable::getClazz());
            addClass(JCloneNotSupportedException::getClazz());
            addClass(JComparable::getClazz());
            addClass(JDouble::getClazz());
            addClass(JEnum::getClazz());
            addClass(JEnumConstantNotPresentException::getClazz());
            addClass(JError::getClazz());
            addClass(JException::getClazz());
            addClass(JFloat::getClazz());
            addClass(JForkedProcess::getClazz());
            addClass(JIllegalAccessError::getClazz());
            addClass(JIllegalAccessException::getClazz());
            addClass(JIllegalArgumentException::getClazz());
            addClass(JIllegalMonitorStateException::getClazz());
            addClass(JIllegalStateException::getClazz());
            addClass(JIllegalThreadStateException::getClazz());
            addClass(JIncompatibleClassChangeError::getClazz());
            addClass(JIndexOutOfBoundsException::getClazz());
            addClass(JInstantiationError::getClazz());
            addClass(JInstantiationException::getClazz());
            addClass(JInteger::getClazz());
            addClass(JInterface::getClazz());
            addClass(JInternalError::getClazz());
            addClass(JInterruptedException::getClazz());
            addClass(JIterable::getClazz());
            addClass(JLinkageError::getClazz());
            addClass(JLong::getClazz());
            addClass(JNegativeArraySizeException::getClazz());
            addClass(JNoClassDefFoundError::getClazz());
            addClass(JNoSuchFieldError::getClazz());
            addClass(JNoSuchFieldException::getClazz());
            addClass(JNoSuchMethodError::getClazz());
            addClass(JNoSuchMethodException::getClazz());
            addClass(JNullPointerException::getClazz());
            addClass(JNumber::getClazz());
            addClass(JNumberFormatException::getClazz());
            addClass(JObject::getClazz());
            addClass(JOutOfMemoryError::getClazz());
            addClass(JProcessBuilder::getClazz());
            addClass(JProcessBuilder::JRedirect::getClazz());
            addClass(JPrimitiveBoolean::getClazz());
            addClass(JPrimitiveBooleanArray::getClazz());
            addClass(JPrimitiveByte::getClazz());
            addClass(JPrimitiveByteArray::getClazz());
            addClass(JPrimitiveChar::getClazz());
            addClass(JPrimitiveCharArray::getClazz());
            addClass(JPrimitiveDouble::getClazz());
            addClass(JPrimitiveDoubleArray::getClazz());
            addClass(JPrimitiveFloat::getClazz());
            addClass(JPrimitiveFloatArray::getClazz());
            addClass(JPrimitiveInt::getClazz());
            addClass(JPrimitiveIntArray::getClazz());
            addClass(JPrimitiveLong::getClazz());
            addClass(JPrimitiveLongArray::getClazz());
            addClass(JPrimitiveShort::getClazz());
            addClass(JPrimitiveShortArray::getClazz());
            addClass(JPrimitiveVoid::getClazz());
            addClass(JReadable::getClazz());
            addClass(JReflectiveOperationException::getClazz());
            addClass(JRuntimeException::getClazz());
            addClass(JSecurityException::getClazz());
            addClass(JShort::getClazz());
            addClass(JStackOverflowError::getClazz());
            addClass(JStackTraceElement::getClazz());
            addClass(JString::getClazz());
            addClass(JStringBuffer::getClazz());
            addClass(JStringBuilder::getClazz());
            addClass(JStringIndexOutOfBoundsException::getClazz());
            addClass(JSystem::getClazz());
            addClass(JThread::getClazz());
            addClass(JThrowable::getClazz());
            addClass(JTypeNotPresentException::getClazz());
            addClass(JUnknownError::getClazz());
            addClass(JUnsatisfiedLinkError::getClazz());
            addClass(JUnsupportedClassVersionError::getClazz());
            addClass(JUnsupportedOperationException::getClazz());
            addClass(JVerifyError::getClazz());
            addClass(JVirtualMachineError::getClazz());
            addClass(JVoid::getClazz());
        }

        JPackage* JLANG_PACKAGE::getSuperPackage(){
            return JCPP_PACKAGE::getPackage();
        }

        JList* JLANG_PACKAGE::getPackages(){
            if (packages->size()==0){
                addPackage(JREFLECT_PACKAGE::getPackage());
                addPackage(JANNOTATION_PACKAGE::getPackage());
            }
            return packages;
        }

        static JLANG_PACKAGE* jlang=null;

        JLANG_PACKAGE* JLANG_PACKAGE::getPackage(){
            if (jlang==null){
                jlang=new JLANG_PACKAGE();
            }
            return jlang;
        }

        JLANG_PACKAGE::~JLANG_PACKAGE(){
        }
    }
}
