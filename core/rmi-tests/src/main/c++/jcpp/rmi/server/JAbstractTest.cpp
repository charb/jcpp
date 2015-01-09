#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/rmi/server/JAbstractTest.h"

using namespace jcpp::io;

namespace jcpp{
    namespace rmi{
        namespace server{

            JAbstractTest::JAbstractTest(JClass* _class,JString* name):JTestCase(_class,name){
            }

            JFile* JAbstractTest::createOutputFile(JClass* c){
                JStringBuilder* builder=new JStringBuilder();
                builder->append(new JString("../java-tests-results/"))
                       ->append(c->getName()->replace('.','/'))
                       ->append(new JString(".ser"));
                return new JFile(builder->toString());
            }

            JFile* JAbstractTest::createOutputFile(JClass* c,JString* name){
                JStringBuilder* builder=new JStringBuilder();
                builder->append(new JString("../java-tests-results/"))
                       ->append(c->getName()->replace('.','/'))
                       ->append(name)
                       ->append(new JString(".ser"));
                return new JFile(builder->toString());
            }

            JAbstractTest::~JAbstractTest(){
            }
        }
    }
}
