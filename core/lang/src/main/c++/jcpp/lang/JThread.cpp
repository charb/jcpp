#include "jcpp/lang/JThread.h"
#include "jcpp/lang/JClassLoader.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "jcpp/lang/JStringBuilder.h"
#include "jcpp/lang/JIllegalArgumentException.h"
#include "jcpp/native/api/NativeFactory.h"

using namespace jcpp::native::api;

namespace jcpp{
    namespace lang{

    	JThread::JState* JThread::JState::NEW = new JState(new JString("NEW"),new JPrimitiveInt(0));
    	JThread::JState* JThread::JState::RUNNABLE = new JState(new JString("RUNNABLE"),new JPrimitiveInt(1));
    	JThread::JState* JThread::JState::TERMINATED = new JState(new JString("TERMINATED"),new JPrimitiveInt(2));

    	JThread::JState::JState(JString* name, JPrimitiveInt* ordinal) : JEnum(dynamic_cast<JEnumClass*>(getClazz()),name,ordinal){
        }

    	JThread::JState::~JState(){
    	}

        JThread* JThread::mainJThread = new JThread(NativeFactory::getNativeThreadFactory()->mainThread());

        JThread* JThread::currentThread() {
        	return (JThread *)NativeFactory::getNativeThreadFactory()->currentThread()->getAttachment();
        }

        JThread* JThread::mainThread() {
        	return mainJThread;
        }

		void JThread::yield() {
			NativeFactory::getNativeThreadFactory()->currentThread()->yield();
		}

		void JThread::sleep(jlong millis) {
			NativeFactory::getNativeThreadFactory()->currentThread()->sleep(millis);
		}

		JPrimitiveObjectArray* JThread::enumerate() {
			std::vector<NativeThread *> threads;
			NativeFactory::getNativeThreadFactory()->getAllThreads(threads);

			JPrimitiveObjectArray* array = new JPrimitiveObjectArray(JThread::getClazz(), threads.size());

			jint index = 0;
			for(std::vector<NativeThread*>::iterator it = threads.begin(); it != threads.end(); ++it) {
				void* attachment = (*it)->getAttachment();
				if(attachment != null) {
					array->set(index++, (JThread*)attachment);
				}
			}

			if(array->size() > index) {
				JPrimitiveObjectArray* tempArray = new JPrimitiveObjectArray(JThread::getClazz(), index);
				for(jint i = 0; i < index; i++) {
					tempArray->set(i, array->get(i));
				}
				array = tempArray;
			}

			return array;
		}

		JThread::JThread(NativeThread* mainThread) : JObject(getClazz()) {
			bDaemon=false;
			nativeThread = mainThread;
			nativeThread->setAttachment((void*) this);
			target = null;
		}

		JThread::JThread(jcpp::lang::JClass* _class) : JObject(_class) {
			bDaemon=false;
			nativeThread = NativeFactory::getNativeThreadFactory()->createNativeThread(this);
			nativeThread->setAttachment((void*) this);
			target = null;
		}

		JThread::JThread(): JObject(getClazz()) {
			bDaemon=false;
			nativeThread = NativeFactory::getNativeThreadFactory()->createNativeThread(this);
			nativeThread->setAttachment((void*) this);
			target = null;
		}

		JThread::JThread(JRunnable* target): JObject(getClazz()) {
			bDaemon=false;
			nativeThread = NativeFactory::getNativeThreadFactory()->createNativeThread(this);
			nativeThread->setAttachment((void*) this);
			this->target = target;
		}

		JThread::JThread(JString* name): JObject(getClazz()) {
			bDaemon=false;
			nativeThread = NativeFactory::getNativeThreadFactory()->createNativeThread(this);
			nativeThread->setAttachment((void*) this);
			target = null;
			setName(name);
		}

		JThread::JThread(JRunnable* target, JString* name): JObject(getClazz()) {
			bDaemon=false;
			this->target = target;
			nativeThread = NativeFactory::getNativeThreadFactory()->createNativeThread(this);
			nativeThread->setAttachment((void*) this);
			setName(name);
		}

        JClassLoader* JThread::getContextClassLoader(){
        	if (contextClassLoader==null){
        		contextClassLoader=JClassLoader::getBootClassLoader();
        	}
        	return contextClassLoader;
        }

        void JThread::setContextClassLoader(JClassLoader* c){
        	this->contextClassLoader=c;
        }

        JThread::JState* JThread::getState() {
			switch(nativeThread->getState()) {
				case NTH_NEW:
					return JThread::JState::NEW;
				case NTH_RUNNABLE:
					return JThread::JState::RUNNABLE;
				case NTH_TERMINATED:
					return JThread::JState::TERMINATED;
				default:
					return JThread::JState::TERMINATED;
			}
		}

		void JThread::start() {
			setContextClassLoader(JThread::currentThread()->getContextClassLoader());
			nativeThread->start();
		}

		jbool JThread::isAlive() {
			return nativeThread->isRunning();
		}

		void JThread::suspend() {
			nativeThread->suspend();
		}

		void JThread::resume() {
			nativeThread->resume();
		}

		void JThread::setPriority(jint priority) {
			if (priority > MAX_PRIORITY || priority < MIN_PRIORITY) {
				throw new JIllegalArgumentException();
			}
			switch(priority) {
				case MIN_PRIORITY:
					nativeThread->setPriority(LOWEST);
					break;
				case 2:
				case 3:
				case 4:
					nativeThread->setPriority(LOW);
					break;
				case NORM_PRIORITY:
					nativeThread->setPriority(NORMAL);
					break;
				case 6:
				case 7:
				case 8:
				case 9:
					nativeThread->setPriority(HIGH);
					break;
				case MAX_PRIORITY:
					nativeThread->setPriority(HIGHEST);
					break;
				default:
					nativeThread->setPriority(NORMAL);
					break;
			}
		}

		jint JThread::getPriority() {
			return nativeThread->getPriority();
		}

		void JThread::setName(JString* name) {
			NativeString nameStr = name->getNativeString();
			nativeThread->setName(nameStr);
		}

		JString* JThread::getName() {
			return new JString(nativeThread->getName());
		}

		void JThread::join(jlong millis) {
			nativeThread->join(millis);
		}

		void JThread::join() {
			nativeThread->join();
		}

		void JThread::setDaemon(jbool bDaemon){
			this->bDaemon=bDaemon;
		}

        jbool JThread::isDaemon(){
        	return bDaemon;
        }

		jlong JThread::getId() {
			return nativeThread->getId();
		}

		void JThread::run() {
			if(target != null) {
				target->run();
			}
		}

		JString* JThread::toString() {
			JStringBuilder* builder = new JStringBuilder();
			builder->append("Thread[")->append(getName())->append(",")->append(getPriority())->append("]");
			return builder->toString();
		}


		jbool JThread::equals(JObject* other) {
			if((other == null) || other->getClass() != getClazz()) {
				return false;
			}
			JThread* otherThread = dynamic_cast<JThread*>(other);
			return getId() == otherThread->getId();
		}

		jint JThread::hashCode() {
			return nativeThread->getId();
		}

		void JThread::finalize(){
			if(nativeThread->isRunning()) {
				nativeThread->setAttachment(null);
				nativeThread->setDeleteOnFinish(true);
			} else {
				delete nativeThread;
			}
		}

        JThread::~JThread(){
        }
    }
}
