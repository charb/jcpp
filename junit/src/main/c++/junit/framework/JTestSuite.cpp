#include "junit/framework/JTestSuite.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JString.h"
#include "jcpp/lang/JStringBuilder.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/JNoSuchMethodException.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/util/JArrayList.h"
#include "jcpp/util/JIterator.h"
#include "junit/framework/JTestCase.h"
#include "jcpp/io/JStringWriter.h"
#include "jcpp/io/JPrintWriter.h"
#include "jcpp/lang/JSystem.h"

using namespace jcpp::lang;
using namespace jcpp::io;

namespace junit{
    namespace framework{

        JTestSuite::JTestSuite(JClass* _class,jbool root):JObject(_class){
            fName=null;
            fTests=new JArrayList();
        }

        JTestSuite::JTestSuite(JClass* _class,JClass* theClass,jbool root):JObject(_class){
            fName=null;
            fTests=new JArrayList();
            addTestsFromTestCase(theClass);
        }

        JTestSuite::JTestSuite(JClass* _class,JClass* theClass, JString* name,jbool root):JObject(_class){
            setName(name);
            fTests=new JArrayList();
            addTestsFromTestCase(theClass);
        }
        
        JTestSuite::JTestSuite(JClass* _class,JString* name,jbool root):JObject(_class){
            fName=name;
            fTests=new JArrayList();
        }

        JTestSuite::JTestSuite(JClass* _class,JList* classes,jbool root):JObject(_class){
            fName=null;
            fTests=new JArrayList();
            for (jint i=0;i<classes->size();i++){
                JClass* c=dynamic_cast<JClass*>(classes->get(i));
                addTest(testCaseForClass(c));
            }
        }

        JTestSuite::JTestSuite(JClass* _class,JList* classes, JString* name,jbool root):JObject(_class){
            fName=name;
            fTests=new JArrayList();
            for (jint i=0;i<classes->size();i++){
                JClass* c=dynamic_cast<JClass*>(classes->get(i));
                addTest(testCaseForClass(c));
            }
        }

        JTestSuite::JTestSuite():JObject(getClazz()){
            fName=null;
            fTests=new JArrayList();
        }

        JTestSuite::JTestSuite(JClass* theClass):JObject(getClazz()){
            fName=null;
            fTests=new JArrayList();
            addTestsFromTestCase(theClass);
        }

        JTestSuite::JTestSuite(JClass* theClass, JString* name):JObject(getClazz()){
            setName(name);
            fTests=new JArrayList();
            addTestsFromTestCase(theClass);
        }
        
        JTestSuite::JTestSuite(JString* name):JObject(getClazz()){
            fName=name;
            fTests=new JArrayList();
        }

        JTestSuite::JTestSuite(JList* classes):JObject(getClazz()){
            fName=null;
            fTests=new JArrayList();
            for (jint i=0;i<classes->size();i++){
                JClass* c=dynamic_cast<JClass*>(classes->get(i));
                addTest(testCaseForClass(c));
            }
        }

        JTestSuite::JTestSuite(JList* classes, JString* name):JObject(getClazz()){
            fName=name;
            fTests=new JArrayList();
            for (jint i=0;i<classes->size();i++){
                JClass* c=dynamic_cast<JClass*>(classes->get(i));
                addTest(testCaseForClass(c));
            }
        }

        JString* JTestSuite::exceptionToString(JThrowable* e){
            JStringWriter* stringWriter = new JStringWriter();
            JPrintWriter* writer = new JPrintWriter(stringWriter);
            e->printStackTrace(writer);
            return stringWriter->toString();
        }

        void JTestSuite::addTestsFromTestCase(JClass* theClass){
            fName = theClass->getName();
            try {
                getTestConstructor(theClass);
            } catch (JNoSuchMethodException* e) {
                JStringBuilder* builder=new JStringBuilder();
                builder->append(new JString("Class "))->append(theClass->getName());
                builder->append(new JString(" has no public constructor TestCase(String name) or TestCase()"));
                addTest(warning(builder->toString()));
                return;
            }

            if (!JModifier::isPublic(theClass->getModifiers())) {
                JStringBuilder* builder=new JStringBuilder();
                builder->append(new JString("Class "))->append(theClass->getName())->append(new JString(" is not public"));
                addTest(warning(builder->toString()));
                return;
            }

            JClass* superClass = theClass;
            JList* names = new JArrayList();
            while (JTest::getClazz()->isAssignableFrom(superClass)) {
                JList* methods=superClass->getDeclaredMethods();
                for (jint i=0;i<methods->size() ; i++) {
                    JMethod* m = dynamic_cast<JMethod*>(methods->get(i));
                    addTestMethod(m, names, theClass);
                }
                superClass = superClass->getSuperclass();
            }
            if (fTests->size() == 0) {
                JStringBuilder* builder=new JStringBuilder();
                builder->append(new JString("No tests found in "))->append(theClass->getName());
                addTest(warning(builder->toString()));
            }
        }

        JTest* JTestSuite::testCaseForClass(JClass* each){
            if (JTestCase::getClazz()->isAssignableFrom(each)) {
                return new JTestSuite(each);
            } else {
                JStringBuilder* builder=new JStringBuilder();
                builder->append(each->getCanonicalName())->append(new JString(" does not extend TestCase"));
                return warning(builder->toString());
            }
        }

        void JTestSuite::addTestMethod(JMethod* m, JList* names, JClass* theClass){
            JString* name = m->getName();
            if (names->contains(name)) {
                return;
            }
            if (!isPublicTestMethod(m)) {
                if (isTestMethod(m)) {
                    JStringBuilder* builder=new JStringBuilder();
                    builder->append(new JString("Test method isn't public: "))->append(m->getName());
                    builder->append('(')->append(theClass->getCanonicalName())->append(')');
                    addTest(warning(builder->toString()));
                }
                return;
            }
            names->add(name);
            addTest(createTest(theClass, name));
        }

        jbool JTestSuite::isPublicTestMethod(JMethod* m){
            return isTestMethod(m) && JModifier::isPublic(m->getModifiers());
        }

        jbool JTestSuite::isTestMethod(JMethod* m){
            return m->getParameterTypes()->size() == 0 && 
                   m->getName()->startsWith(new JString("test")) &&
                   m->getReturnType()->equals(JVoid::TYPE);
        }

        JTest* JTestSuite::createTest(JClass* theClass, JString* name){
            JConstructor* constructor;
            try {
                constructor = getTestConstructor(theClass);
            } catch (JNoSuchMethodException* e) {
                JStringBuilder* builder=new JStringBuilder();
                builder->append(new JString("Class "))->append(theClass->getName());
                builder->append(new JString(" has no public constructor TestCase(String name) or TestCase()"));
                return warning(builder->toString());
            }

            JObject* test;
            try {
                if (constructor->getParameterTypes()->size() == 0) {
                    test = constructor->newInstance(null);
                    if (test->isInstanceOf(JTestCase::getClazz())) {
                        (dynamic_cast<JTestCase*>(test))->setName(name);
                    }
                } else {
                    JArrayList* list=new JArrayList();
                    list->add(name);
                    test =constructor->newInstance(list);
                }
            } catch (JThrowable* e) {
                JStringBuilder* builder=new JStringBuilder();
                builder->append(new JString("Cannot instantiate test case: "))->append(name);
                builder->append('(')->append(exceptionToString(e))->append(')');
                return warning(builder->toString());
            }
            return dynamic_cast<JTest*>(test);
        }
        
        JConstructor* JTestSuite::getTestConstructor(JClass* theClass){
            try {
                JArrayList* list=new JArrayList();
                list->add(JString::getClazz());
                return theClass->getConstructor(list);
            } catch (JNoSuchMethodException* e) {
            }
            return theClass->getConstructor(null);
        }


        // @Class(canonicalName="junit.framework.WarningTestCase", simpleName="WarningTestCase");
        class JWarningTestCase : public JTestCase{
        protected:
            JString* message;

            virtual void runTest(){
                fail(message);
            }

        public:
            JWarningTestCase(JString* name,JString* message):JTestCase(getClazz(),name){
                this->message=message;
            }

            static JClass* getClazz();
        };

        JTest* JTestSuite::warning(JString* message){
            return new JWarningTestCase(new JString("warning"),message);
        }

        void JTestSuite::addTest(JTest* test){
            fTests->add(dynamic_cast<JObject*>(test));
        }
        
        void JTestSuite::addTestSuite(JClass* testClass){
            addTest(new JTestSuite(testClass));
        }

        jint JTestSuite::countTestCases(){
            jint count = 0;
            for (jint i=0;i<fTests->size();i++) {
                JTest* each=dynamic_cast<JTest*>(fTests->get(i));
                count += each->countTestCases();
            }
            return count;
        }
        
        JString* JTestSuite::getName(){
            return fName;
        }

        void JTestSuite::run(JTestResult* result){
            for (jint i=0;i<fTests->size();i++) {
                JTest* each=dynamic_cast<JTest*>(fTests->get(i));
                if (result->shouldStop()) {
                    break;
                }
                runTest(each, result);
            }
        }

        void JTestSuite::runTest(JTest* test, JTestResult* result){
            test->run(result);
        }
        
        void JTestSuite::setName(JString* name){
            fName=name;
        }

        JTest* JTestSuite::testAt(jint index){
            return dynamic_cast<JTest*>(fTests->get(index));
        }

        jint JTestSuite::testCount(){
            return fTests->size();
        }

        JIterator* JTestSuite::tests(){
            return fTests->iterator();
        }

        JString* JTestSuite::toString(){
            if (getName() != null) {
                return getName();
            }
            return JObject::toString();
        }

        JTestSuite::~JTestSuite(){
        }
    }
}

