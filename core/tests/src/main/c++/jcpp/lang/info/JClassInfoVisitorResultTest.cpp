#include "jcpp/lang/info/JClassInfoVisitorResultTest.h"
#include "jcpp/gc/GarbageCollector.h"
#include "jcpp/io/JFile.h"
#include "jcpp/io/JFileOutputStream.h"
#include "jcpp/io/JPrintStream.h"
#include "jcpp/io/JPrintWriter.h"
#include "jcpp/lang/info/JClassInfoVisitor.h"
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

			JClassInfoVisitorResultTest::JClassInfoVisitorResultTest() :
					JTestCase(getClazz(), new JString("test")){

			}

			void JClassInfoVisitorResultTest::test(){
				try{
					GarbageCollector* myGC = GarbageCollector::getGarbageCollector();

					JClassInfoVisitor* ciVisitor = new JClassInfoVisitor();
					myGC->acceptClassVisitor(ciVisitor);

					JArrayList* result = new JArrayList(ciVisitor->getResult());

					JPrintWriter* pw = new JPrintWriter(new JFileOutputStream(new JFile(new JString("classInfos.txt"))), true);

					JClassInfo* currentCI = null;
					JFieldInfo* currentFI = null;
					pw->println(result->size());
					for (jint i = 0; i < result->size(); i++){
						currentCI = dynamic_cast<JClassInfo*>(result->get(i));
						pw->print(currentCI->getClassName());

						JArrayList* staticFieldInfos = new JArrayList(currentCI->getStaticFieldInfos());
						pw->print(new JString(" "));
						pw->print(staticFieldInfos->size());
						pw->println();
						for (jint j = 0; j < staticFieldInfos->size(); j++){
							currentFI = dynamic_cast<JFieldInfo*>(staticFieldInfos->get(j));
							pw->print(new JString("    "));
							if (currentFI == null){
								JSystem::out->println(currentFI->getName());
								continue;
							}

							pw->print(currentFI->getName());
							pw->print(new JString(": "));

							pw->print(currentFI->isStaticField());

							pw->print(new JString(": "));
							pw->print(currentFI->getAddress()->get());
							pw->println();
						}
						pw->println();
					}
					pw->close();
				} catch (JException* e){
					e->printStackTrace();
				}

			}
			JClassInfoVisitorResultTest::~JClassInfoVisitorResultTest(){

			}
		}
	}
}
