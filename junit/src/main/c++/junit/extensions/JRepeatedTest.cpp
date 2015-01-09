#include "junit/extensions/JRepeatedTest.h"
#include "junit/extensions/JTestDecorator.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JString.h"
#include "jcpp/lang/JStringBuilder.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JIllegalArgumentException.h"

namespace junit{
    namespace extensions{

        JRepeatedTest::JRepeatedTest(JTest* test, jint repeat):JTestDecorator(getClazz(),test){
            if (repeat < 0) {
                throw new JIllegalArgumentException(new JString("Repetition count must be >= 0"));
            }
            fTimesRepeat = repeat;
        }
        
        jint JRepeatedTest::countTestCases(){
            return JTestDecorator::countTestCases() * fTimesRepeat;
        }
        
        void JRepeatedTest::run(JTestResult* result){
            for (jint i = 0; i < fTimesRepeat; i++) {
                if (result->shouldStop()) {
                    break;
                }
                JTestDecorator::run(result);
            }
        }

        JString* JRepeatedTest::toString(){
            JStringBuilder* builder=new JStringBuilder();
            builder->append(JTestDecorator::toString())->append(new JString("(repeated)"));
            return builder->toString();
        }

        JRepeatedTest::~JRepeatedTest(){
        }
    }
}

