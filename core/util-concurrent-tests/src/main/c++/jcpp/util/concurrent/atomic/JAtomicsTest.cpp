#include "jcpp/util/concurrent/atomic/JAtomicsTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/util/concurrent/atomic/JAtomicBoolean.h"
#include "jcpp/util/concurrent/atomic/JAtomicInteger.h"
#include "jcpp/util/concurrent/atomic/JAtomicIntegerArray.h"
#include "jcpp/util/concurrent/atomic/JAtomicLong.h"
#include "jcpp/util/concurrent/atomic/JAtomicLongArray.h"
#include "jcpp/util/concurrent/atomic/JAtomicReference.h"
#include "jcpp/util/concurrent/atomic/JAtomicReferenceArray.h"
#include "jcpp/lang/JInteger.h"
#include "jcpp/lang/JFloat.h"
#include "jcpp/lang/JShort.h"
#include "jcpp/lang/JLong.h"
#include "jcpp/lang/JThread.h"
#include "jcpp/lang/JSystem.h"
#include "jcpp/lang/JStringBuilder.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"

using namespace jcpp::io;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace util{
        namespace concurrent{
            namespace atomic{

                JAtomicsTest::JAtomicsTest():JAbstractTest(getClazz(),new JString("test")){
                }

            	// @Class(canonicalName="jcpp.util.concurrent.atomic.AtomicsTest$ThreadWriterAtomics", simpleName="AtomicsTest$ThreadWriterAtomics");
                class JThreadWriterAtomics : public JThread{
                protected:
                    JAtomicBoolean* b;
                    JAtomicInteger* ai;
                    JAtomicIntegerArray* aia;
                    JAtomicLong* al;
                    JAtomicLongArray* ala;

                public:
                    JThreadWriterAtomics(JAtomicBoolean* b,JAtomicInteger* ai,JAtomicIntegerArray* aia,JAtomicLong* al,JAtomicLongArray* ala):JThread(getClazz()){
                        this->b=b;
                        this->ai=ai;
                        this->aia=aia;
                        this->al=al;
                        this->ala=ala;
                    }

                    static JClass* getClazz();

                    virtual void run(){
                        jint i=0;
                        while (!b->get()){
                            if (i<20){
                                JStringBuilder* builder=new JStringBuilder();
                                builder->append(JThread::currentThread())
                                       ->append(": adding value ==")
                                       ->append(ai->incrementAndGet());
                                JSystem::out->println(builder->toString());
                                al->incrementAndGet();
                                aia->incrementAndGet(0);
                                ala->incrementAndGet(0);
                            }
                            i++;
                        }
                    }
                };

                void JAtomicsTest::test(){
                    JAtomicBoolean* ab=new JAtomicBoolean(false);
                    JAtomicInteger* ai=new JAtomicInteger(0);
                    JAtomicIntegerArray* aia=new JAtomicIntegerArray(1);
                    aia->set(0,0);
                    JAtomicLong* al=new JAtomicLong(0);
                    JAtomicLongArray* ala=new JAtomicLongArray(1);
                    ala->set(0,0);

                    JPrimitiveObjectArray* array=new JPrimitiveObjectArray(JThreadWriterAtomics::getClazz(),5);
                    for (jint i=0;i<array->size();i++){
                        JThreadWriterAtomics* tw=new JThreadWriterAtomics(ab,ai,aia,al,ala);
                        tw->start();
                        array->set(i,tw);
                    }
                    JThread::sleep(5000);
                    ab->set(true);
                    for (jint i=0;i<array->size();i++){
                        JThreadWriterAtomics* tw=dynamic_cast<JThreadWriterAtomics*>(array->get(i));
                        while (tw->isAlive()){
                            JThread::sleep(1000);
                        }
                    }
                    assertEquals(ai->get(),100);
                    assertEquals(aia->get(0),100);
                    assertEquals(al->get(),(jlong)100);
                    assertEquals(ala->get(0),(jlong)100);
                }

                JAtomicsTest::~JAtomicsTest(){
                }
            }
        }
    }
}
