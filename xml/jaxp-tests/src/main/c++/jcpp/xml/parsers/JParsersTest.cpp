#include "jcpp/xml/parsers/JParsersTest.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/JSystem.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JInteger.h"
#include "jcpp/lang/JFloat.h"
#include "jcpp/lang/JShort.h"
#include "jcpp/lang/JLong.h"
#include "jcpp/net/JInetAddress.h"
#include "jcpp/util/JList.h"
#include "jcpp/lang/JThread.h"
#include "jcpp/lang/JSystem.h"
#include "jcpp/lang/reflect/JProxy.h"
#include "jcpp/lang/JThrowable.h"
#include "jcpp/lang/JStringBuilder.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "jcpp/xml/parsers/JDocumentBuilder.h"
#include "jcpp/xml/parsers/JDocumentBuilderFactory.h"
#include "org/w3c/dom/JDocument.h"
#include "jcpp/io/JFileOutputStream.h"
#include "jcpp/xml/internal/tree/JXmlDocument.h"

using namespace jcpp::lang;
using namespace jcpp::net;
using namespace jcpp::lang::reflect;
using namespace jcpp::xml::parsers;
using namespace org::w3c::dom;
using namespace jcpp::xml::internal::tree;

namespace jcpp{
    namespace xml{
        namespace parsers{

            JParsersTest::JParsersTest():JAbstractTest(getClazz(),new JString("test")){
            }

            void JParsersTest::fill(JArrayList* list, JFile* file){
            	JSystem::out->print(new JString("Calling Fill with file path = "));
            	JSystem::out->println(file->getPath());
                if (file->isDirectory()){
                    JPrimitiveObjectArray* a=file->listFiles();
                    if (a!=null){
                        for (jint i=0;i<a->size();i++){
                            fill(list,dynamic_cast<JFile*>(a->get(i)));
                        }
                    }
                }else{
                    list->add(file);
                }
            }

            void JParsersTest::test(){
                JDocumentBuilderFactory* factory=JDocumentBuilderFactory::newInstance();
                JDocumentBuilder* builder=factory->newDocumentBuilder();

                JArrayList* files=new JArrayList();
                fill(files,new JFile(new JString("xml")));
                for (jint i=0;i<files->size();i++){
                    JFile* f=dynamic_cast<JFile*>(files->get(i));
                    JSystem::out->print(new JString("Parsing file "));
                    JSystem::out->println(f->getAbsolutePath());

                    JDocument* document=builder->parse(f);

                    JSystem::out->print(new JString("Resulted DOM == "));
                    JSystem::out->println(dynamic_cast<JObject*>(document));

                    JStringBuilder* builder=new JStringBuilder();
                    builder->append(f->getAbsolutePath())->append(new JString(".out.xml"));
                    JFile* outFile=new JFile(builder->toString());
                    JXmlDocument* xmlDocument=dynamic_cast<JXmlDocument*>(document);
                    xmlDocument->write(new JFileOutputStream(outFile));
                }
            }

            JParsersTest::~JParsersTest(){
            }
        }
    }
}
