#include "jcpp/util/concurrent/atomic/JAtomicBooleanTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/util/concurrent/atomic/JAtomicBoolean.h"
#include "jcpp/lang/JInteger.h"
#include "jcpp/lang/JFloat.h"
#include "jcpp/lang/JShort.h"
#include "jcpp/lang/JLong.h"
#include "jcpp/lang/JThread.h"

using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace util{
        namespace concurrent{
            namespace atomic{

                JAtomicBooleanTest::JAtomicBooleanTest():JSerializableTest(getClazz()){
                }

                void JAtomicBooleanTest::equals(JObject* reached, JObject* expected){
                    JAtomicBoolean* r=dynamic_cast<JAtomicBoolean*>(reached);
                    JAtomicBoolean* e=dynamic_cast<JAtomicBoolean*>(expected);
                    assertEquals(r->get(),e->get());
                }

                JObject* JAtomicBooleanTest::getSerializableObject(){
                    JAtomicBoolean* a1=new JAtomicBoolean();
                    a1->set(true);
                    return a1;
                }


            	// @Class(canonicalName="jcpp.util.concurrent.atomic.AtomicBooleanTest$ThreadWriterAtomicBoolean", simpleName="AtomicBooleanTest$ThreadWriterAtomicBoolean");
                class JThreadWriterAtomicBoolean : public JThread{
                protected:
                    JAtomicBoolean* b;

                public:
                    JThreadWriterAtomicBoolean(JAtomicBoolean* b):JThread(getClazz()){
                        this->b=b;
                    }

                    static JClass* getClazz();

                    virtual void run(){
                        while (!b->get()){
                        }
                    }
                };

                void JAtomicBooleanTest::test(){
                    JSerializableTest::test();

                    JAtomicBoolean* ab=new JAtomicBoolean(false);
                    JThreadWriterAtomicBoolean* tw=new JThreadWriterAtomicBoolean(ab);
                    tw->start();
                    JThread::sleep(3000);
                    ab->set(true);
                    while (tw->isAlive()){
                        JThread::sleep(1000);
                    }
                }

                JAtomicBooleanTest::~JAtomicBooleanTest(){
                }
            }
        }
    }
}
