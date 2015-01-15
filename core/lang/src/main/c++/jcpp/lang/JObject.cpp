#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JIllegalArgumentException.h"
#include "jcpp/lang/JCloneNotSupportedException.h"
#include "jcpp/lang/JCloneable.h"
#include "jcpp/lang/JNullPointerException.h"
#include "jcpp/lang/JString.h"
#include "jcpp/lang/JStringBuilder.h"
#include "jcpp/native/api/NativeFactory.h"

using namespace jcpp::native::api;
using namespace jcpp::native::api::nthread;

namespace jcpp{
    namespace lang{

        JObject::JObject(){
            this->_class=null;
            NativeThreadFactory * threadFactory = NativeFactory::getNativeThreadFactory();
            TRY_CATCH_NATIVE_EXCEPTION( mutex = threadFactory->createNativeMutex(); )
            TRY_CATCH_NATIVE_EXCEPTION( condition = threadFactory->createNativeCondition(mutex); )
        }

        JObject::JObject(jcpp::lang::JClass* _class){
            this->_class=_class;
            NativeThreadFactory * threadFactory = NativeFactory::getNativeThreadFactory();
            TRY_CATCH_NATIVE_EXCEPTION( mutex = threadFactory->createNativeMutex(); )
            TRY_CATCH_NATIVE_EXCEPTION( condition = threadFactory->createNativeCondition(mutex); )
        }

        jcpp::lang::JClass* JObject::getClass(){
            if (this->_class==null){
                this->_class=JObject::getClazz();
            }
            return this->_class;
        }

        jbool JObject::isInstanceOf(jcpp::lang::JClass* c){
            if (c==null){
                throw new JNullPointerException();
            }
            return c->isAssignableFrom(getClass());
        }

        JString* JObject::toString(){
            JStringBuilder* builder=new JStringBuilder();
            builder->append(getClass()->getName())->append("@")->append((jlong)this);
            return builder->toString();
        }

        void JObject::internalLock(){
        	TRY_CATCH_NATIVE_EXCEPTION( mutex->lock(); )
        }


        jbool JObject::internalTryLock(){
            jbool b;
            TRY_CATCH_NATIVE_EXCEPTION(b=mutex->tryLock();)
            return b;
        }

        jbool JObject::internalTryLock(jlong l){
            jbool b;
            TRY_CATCH_NATIVE_EXCEPTION(b=mutex->tryLock(l);)
            return b;
        }

        void JObject::internalUnlock(){
        	TRY_CATCH_NATIVE_EXCEPTION( mutex->unlock(); )
        }

        void JObject::wait(){
        	TRY_CATCH_NATIVE_EXCEPTION( condition->wait(); )
        }

        void JObject::wait(jlong time){
        	TRY_CATCH_NATIVE_EXCEPTION( condition->wait(time); )
        }

        void JObject::notify(){
        	TRY_CATCH_NATIVE_EXCEPTION( condition->notify(); )
        }

        void JObject::notifyAll(){
        	TRY_CATCH_NATIVE_EXCEPTION( condition->notifyAll(); )
        }

        void JObject::finalize(){
        	delete condition;
			condition = null;

			delete mutex;
			mutex = null;
        }

        jbool JObject::equals(JObject* o){
            if (o==null || getClass()!=o->getClass()){
                return false;
            }
            return this==o;
        }

        jint JObject::hashCode(){
        	//TODO loss of data, hashCode collision is possible
            return (jint)(jlong)this;
        }

        JObject* JObject::clone(){
            JStringBuilder* builder=new JStringBuilder();
            builder->append("not clonable ")->append(toString());
            throw new JCloneNotSupportedException(builder->toString());
        }

        JObject::~JObject(){
        }

        ScopedObjectLock::ScopedObjectLock(JObject* obj){
            this->obj=obj;
            obj->internalLock();
        }

        ScopedObjectLock::~ScopedObjectLock(){
            obj->internalUnlock();
        }
    }
}
