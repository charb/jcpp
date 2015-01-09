#include "junit/framework/JTestFailure.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JString.h"
#include "jcpp/lang/JStringBuilder.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/io/JStringWriter.h"
#include "jcpp/io/JPrintWriter.h"

using namespace jcpp::io;

namespace junit{
    namespace framework{

        JTestFailure::JTestFailure(JTest* failedTest, JThrowable* thrownException):JObject(getClazz()){
            this->fFailedTest=failedTest;
            this->fThrownException=thrownException;
        }

        JTest* JTestFailure::failedTest(){
            return fFailedTest;
        }

        JThrowable* JTestFailure::thrownException(){
            return fThrownException;
        }

        JString* JTestFailure::trace(){
            JStringWriter* stringWriter = new JStringWriter();
            JPrintWriter* writer = new JPrintWriter(stringWriter);
            thrownException()->printStackTrace(writer);
            return stringWriter->toString();
        }

        JString* JTestFailure::exceptionMessage(){
            return thrownException()->getMessage();
        }

        jbool JTestFailure::isFailure(){
            return thrownException()->isInstanceOf(JAssertionFailedError::getClazz());
        }

        JString* JTestFailure::toString(){
            JStringBuilder* builder=new JStringBuilder();
            builder->append(fFailedTest)->append(": ")->append(fThrownException->getMessage());
            return builder->toString();
        }

        JTestFailure::~JTestFailure(){
        }
    }
}

