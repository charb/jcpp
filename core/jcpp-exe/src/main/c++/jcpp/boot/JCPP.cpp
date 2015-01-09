#include "jcpp/net/JURLClassLoader.h"
#include "jcpp/lang/reflect/JPackageLoader.h"
#include "jcpp/lang/JPrimitiveArray.h"
#include "jcpp/lang/JString.h"
#include "jcpp/lang/JClassLoader.h"
#include "jcpp/io/JFile.h"
#include "jcpp/util/JArrayList.h"
#include "jcpp/lang/JThrowable.h"
#include "jcpp/lang/JBootstrap.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JSystem.h"
#include "jcpp/lang/JNullPointerException.h"
#include "org/apache/commons/cli/JOption.h"
#include "org/apache/commons/cli/JCommandLineParser.h"
#include "org/apache/commons/cli/JDefaultParser.h"
#include "org/apache/commons/cli/JOptions.h"
#include "org/apache/commons/cli/JHelpFormatter.h"

using namespace jcpp::util;
using namespace jcpp::lang;
using namespace jcpp::lang::reflect;
using namespace jcpp::io;
using namespace jcpp::net;
using namespace org::apache::commons::cli;


int main(int argc, char* argv[]){

    class MainExitListener : public JSystem::ExitListener{
    protected:
        JObject* lock;
        jbool set;
        jint code;
    public:
        MainExitListener(){
            lock=new JObject();
            set=false;
            code=0;
        }

        virtual void exit(jint code){
            synchronized(lock,{
                this->code=code;
                set=true;
                lock->notifyAll();
            })
        }

        jint waitExit(){
            synchronized(lock,{
                while (!set){
                    lock->wait();
                }
                return code;
            })
        }
    };

    MainExitListener* mainExitListener=new MainExitListener();
    JSystem::exitListener=mainExitListener;
    try{
        JCommandLineParser* parser = new JDefaultParser();
        JOptions* options = new JOptions();
        options->addOption(JOption::builder(new JString("classpath"))
                                             ->longOpt(new JString("classpath"))
                                             ->argName(new JString("classpath"))
                                             ->desc(new JString(" class search path of libraries" ))
                                             ->valueSeparator(';')
                                             ->hasArgs()
                                             ->build());
        options->addOption(JOption::builder(new JString("classname"))
                                             ->longOpt(new JString("classname"))
                                             ->argName(new JString("classname"))
                                             ->desc(new JString(" main class name" ))
                                             ->hasArg(true)
                                             ->build());
        options->addOption(new JString("help"),false,new JString(" print this help" ));
        options->addOption(JOption::builder(new JString("D"))
                                             ->argName(new JString("name=value"))
                                             ->numberOfArgs(2)
                                             ->valueSeparator()
                                             ->desc(new JString(" set a system property"))
                                             ->build());

        JPrimitiveObjectArray* arguments=new JPrimitiveObjectArray(JString::getClazz(),argc-1);
        for (jint i=0;i<arguments->size();i++){
            arguments->set(i,new JString(argv[i+1]));
        }
        JCommandLine* line = parser->parse(options, arguments);

        //setting system property
        JMap* properties=line->getOptionProperties(new JString("D"));
        if (properties!=null){
            JIterator* it=properties->keySet()->iterator();
            while (it->hasNext()){
                JString* key=dynamic_cast<JString*>(it->next());
                JString* value=dynamic_cast<JString*>(properties->get(key));
                JSystem::setProperty(key,value);
            }
        }

        if (line->hasOption(new JString("help"))){
            JHelpFormatter* formatter=new JHelpFormatter();
            formatter->printHelp(new JString("jcpp"),options);
            return 0;
        }

        JBootstrap* bootstrap=new JBootstrap();

        JPrimitiveObjectArray* cps=line->getOptionValues(new JString("classpath"));
        for (jint i=0;i<cps->size();i++){
            bootstrap->addClassPath(new JFile(dynamic_cast<JString*>(cps->get(i))));
        }

        JString* mainClass=line->getOptionValue(new JString("classname"));
        bootstrap->setMainClass(mainClass);
        bootstrap->setArguments(arguments);
        bootstrap->start();

        return 0;
        //TODO return mainExitListener->waitExit(); //activate once we can get all the threads

    }catch(JThrowable* th){
        th->printStackTrace();
        throw th;
    }catch(exception& e){
        cout << "Standard exception: " << e.what() << endl;
        cout.flush();
        throw e;
    }catch(...){
        cout<<"error"<<endl;
        cout.flush();
    }
}



