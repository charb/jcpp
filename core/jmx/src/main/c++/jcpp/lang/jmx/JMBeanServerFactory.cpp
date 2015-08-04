#include "jcpp/lang/jmx/JMBeanServerFactory.h"
#include "jcpp/lang/JException.h"
#include "jcpp/lang/JString.h"
#include "jcpp/util/JArrayList.h"
#include "jcpp/lang/jmx/JMBeanServer.h"
#include "jcpp/lang/jmx/JMBeanServerBuilder.h"

namespace jcpp{
	namespace lang{
		namespace jmx{

			/*************************************** PRIVATE *************************************/

			JMBeanServerBuilder* JMBeanServerFactory::builder = null;

			JList* JMBeanServerFactory::jmBeanServerList = new JArrayList();

			void JMBeanServerFactory::addJMBeanServer(JMBeanServer* jmbs){
				synchronized(, {
					jmBeanServerList->add(jmbs);
				})
			}

			JMBeanServerBuilder* JMBeanServerFactory::getNewJMBeanServerBuilder(){
				synchronized(,{
					checkJMBeanServerBuilder();
					return builder;
				})
			}

			void JMBeanServerFactory::checkJMBeanServerBuilder(){
				synchronized(,{
					JClass* newBuilderClass = JMBeanServerBuilder::getClazz();
					if(builder != null){
						JClass* builderClass = builder->getClass();
						if(newBuilderClass == builderClass)
							return;
					}
					builder = newBuilder(newBuilderClass);
				})
			}

			JMBeanServerBuilder* JMBeanServerFactory::newBuilder(JClass* builderClass){
				try{
					JObject* builder = builderClass->newInstance();
					return (JMBeanServerBuilder*) builder;
				}catch(JException* x){
					throw x;
				}
			}


			/*************************************** PUBLIC *************************************/

			JMBeanServer* JMBeanServerFactory::newMBeanServer(){
				JMBeanServerBuilder* mbsBuilder = getNewJMBeanServerBuilder();

				synchronized(mbsBuilder,{

					JMBeanServer* jmbeanServer = mbsBuilder->newMBeanServer(null, null);
					if(jmbeanServer == null){
						JString* msg = new JString("JMBeanServerBuilder.newJMBeanServer() returned null");
						throw new JException(msg);
					}
					return jmbeanServer;
				})
			}

			JMBeanServer* JMBeanServerFactory::createJMBeanServer(){
				JMBeanServer* jmBeanServer = newMBeanServer();
				addJMBeanServer(jmBeanServer);
				return jmBeanServer;
			}

			JMBeanServerFactory::~JMBeanServerFactory(){
			}

		}
	}
}
