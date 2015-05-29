#include  "jcpp/lang/info/JMethodCallVisitorResultTest.h"

#include "jcpp/gc/GarbageCollector.h"
#include "jcpp/io/JFile.h"
#include "jcpp/io/JFileOutputStream.h"
#include "jcpp/io/JPrintStream.h"
#include "jcpp/io/JPrintWriter.h"
#include "jcpp/lang/info/JMethodCallVisitor.h"
#include "jcpp/lang/JException.h"
#include "jcpp/lang/JPrimitiveLong.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "jcpp/lang/JSystem.h"
#include "jcpp/native/api/NativeInclude.h"
#include "jcpp/util/JArrayList.h"
#include "jcpp/util/JHashSet.h"

using namespace jcpp::gc;
using namespace jcpp::gc::info;
using namespace jcpp::lang;
using namespace jcpp::util;
using namespace jcpp::io;
using namespace junit::framework;
using namespace jcpp;

namespace jcpp {
	namespace lang {
		namespace info {

			JMethodCallVisitorResultTest::JMethodCallVisitorResultTest() :
					JTestCase(getClazz(), new JString("test")){

			}

			void JMethodCallVisitorResultTest::test(){
				try{
					GarbageCollector* myGC = GarbageCollector::getGarbageCollector();

					JMethodCallVisitor* mcVisitor = new JMethodCallVisitor();
					myGC->acceptMethodCallVisitor(mcVisitor);

					JArrayList* result = new JArrayList(mcVisitor->getResult());

					JPrintWriter* pw = new JPrintWriter(new JFileOutputStream(new JFile(new JString("stack.txt"))), true);

					JThreadInfo* currentTI = null;
					JMethodCallInfo* currentMCI = null;
					JMethodObjectInfo* currentMOI = null;

					for (jint i = 0; i < result->size(); i++){
						currentTI = dynamic_cast<JThreadInfo*>(result->get(i));
						pw->print(new JString("ThreadID"));
						pw->print(new JString(": "));
						pw->print(currentTI->getThreadID()->get());

						JArrayList* stackArray = new JArrayList(currentTI->getMethodCallInfos());
						pw->print(new JString(" "));
						pw->print(stackArray->size());
						pw->println();

						for (jint j = 0; j < stackArray->size(); j++){
							currentMCI = dynamic_cast<JMethodCallInfo*>(stackArray->get(j));
							pw->write(new JString("    "));
							//pw->write(currentMCI->getName());
							//pw->write(new JString(": "));
							//pw->print(currentMCI->getObjectInfo()->getAddress()->get());

							JArrayList* methodObjects = new JArrayList(currentMCI->getMethodObjects());
							pw->print(methodObjects->size());
							pw->println();
							for (jint k = 0; k < methodObjects->size(); k++){
								currentMOI = dynamic_cast<JMethodObjectInfo*>(methodObjects->get(k));
								pw->print(new JString("    "));
								pw->print(new JString("    "));
								pw->print(currentMOI->getAddress()->get());
								pw->println();
							}
						}
						pw->println();
					}
					pw->close();
				} catch (JException* e){
					e->printStackTrace();
				} catch (exception* e){
					printf(e->what());
					printf("\n");
				}

			}
			JMethodCallVisitorResultTest::~JMethodCallVisitorResultTest(){

			}
		}
	}
}
