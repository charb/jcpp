#include "jcpp/lang/info/JObjectInfoGroupVisitorResultTest.h"

#include "jcpp/gc/GarbageCollector.h"
#include "jcpp/io/JFile.h"
#include "jcpp/io/JFileOutputStream.h"
#include "jcpp/io/JPrintStream.h"
#include "jcpp/io/JPrintWriter.h"
#include "jcpp/lang/info/JFieldInfo.h"
#include "jcpp/lang/info/JObjectInfo.h"
#include "jcpp/lang/info/JObjectInfoGroupVisitor.h"
#include "jcpp/lang/JException.h"
#include "jcpp/lang/JPrimitiveLong.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "jcpp/lang/JSystem.h"
#include "jcpp/native/api/NativeInclude.h"
#include "jcpp/util/JArrayList.h"
#include "jcpp/util/JHashSet.h"
#include "jcpp/lang/JEnum.h"
#include "jcpp/lang/JPrimitiveArray.h"

using namespace jcpp::gc;
using namespace jcpp::gc::info;
using namespace jcpp::lang;
using namespace jcpp::util;
using namespace jcpp::io;
using namespace jcpp::lang;
using namespace junit::framework;
using namespace jcpp;

namespace jcpp {
	namespace lang {
		namespace info {

			JObjectInfoGroupVisitorResultTest::JObjectInfoGroupVisitorResultTest() :
					JTestCase(getClazz(), new JString("test")){
			}

			void JObjectInfoGroupVisitorResultTest::test(){
				try{
					GarbageCollector* myGC = GarbageCollector::getGarbageCollector();

					JObjectInfoGroupVisitor* oigVisitor = new JObjectInfoGroupVisitor();
					myGC->acceptObjectVisitor(oigVisitor);
					JArrayList* result = new JArrayList(oigVisitor->getResult());

					JPrintWriter* pw = new JPrintWriter(new JFileOutputStream(new JFile(new JString("heap.txt"))), true);

					JObjectInfo* currentOI = null;
					JFieldInfo* currentFI = null;
					pw->print(result->size());
					pw->println();
					for (jint i = 0; i < result->size(); i++){
						currentOI = dynamic_cast<JObjectInfo*>(result->get(i));
						pw->write(currentOI->getClassName());
						void * myObject;
						if(currentOI->getClassName()->endsWith(new JString("JEnumClass"))){
							myObject = (void *)currentOI->getAddress()->get();
							JEnum::JEnumClass* myEnum = reinterpret_cast<JEnum::JEnumClass*>(myObject);
							pw->write(new JString("."));
							pw->write(myEnum->getName());
							pw->write(new JString("::JEnumClass"));
						}


						if(currentOI->getClassName()->endsWith(new JString("JPrimitiveArrayClass"))){
							myObject = (void *)currentOI->getAddress()->get();
							JClass* myParray = reinterpret_cast<JClass*>(myObject);
							pw->write(new JString("."));
							pw->write(myParray->getCanonicalName());
							pw->write(new JString("::JPrimitiveArrayClass"));
						}

						if(currentOI->getClassName()->endsWith(new JString("JClass"))){
							myObject = (void *)currentOI->getAddress()->get();
							JClass* myParray = reinterpret_cast<JClass*>(myObject);
							pw->write(new JString("."));
							pw->write(myParray->getSimpleName());
							pw->write(new JString("::JClass"));
						}


						pw->write(new JString(": "));
						pw->print(currentOI->getAddress()->get());
						pw->print(new JString(" "));
						JArrayList* refsArray = new JArrayList(currentOI->getReferences());
						pw->print(refsArray->size());
						pw->println();
						for (jint j = 0; j < refsArray->size(); j++){
							currentFI = dynamic_cast<JFieldInfo*>(refsArray->get(j));
							pw->write(new JString("    "));
							if (currentFI == null){
								JSystem::out->println(currentOI->getClassName());
								continue;
							}

							pw->write(currentFI->getName());
							pw->write(new JString(": "));
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
			JObjectInfoGroupVisitorResultTest::~JObjectInfoGroupVisitorResultTest(){

			}
		}
	}
}
