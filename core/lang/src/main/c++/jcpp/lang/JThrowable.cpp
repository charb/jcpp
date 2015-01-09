#include "jcpp/lang/JThrowable.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/util/JArrayList.h"
#include "jcpp/lang/JStringBuilder.h"
#include "jcpp/lang/JSystem.h"
#include "jcpp/io/JPrintStream.h"
#include "jcpp/io/JPrintWriter.h"
#include "jcpp/lang/JStringBuilder.h"
#include "jcpp/lang/JException.h"
#include "jcpp/lang/JNullPointerException.h"
#include "jcpp/lang/JIllegalArgumentException.h"
#include "jcpp/lang/JIndexOutOfBoundsException.h"
#include "jcpp/lang/JIllegalStateException.h"
#include "jcpp/io/JIOException.h"
#include "jcpp/io/JFileNotFoundException.h"
#include "jcpp/net/JSocketException.h"
#include "jcpp/net/JUnknownHostException.h"
#include "jcpp/lang/JInterruptedException.h"
#include "jcpp/lang/JOutOfMemoryError.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;
using namespace jcpp::io;
using namespace jcpp::net;

namespace jcpp{
    namespace lang{
        class JThrowableClass : public jcpp::lang::JClass{
        protected:
            static JObject* createJThrowable(jcpp::util::JList* args){
                return new JThrowable();
            }

            static JObject* staticGetDetailMessage(JObject* object){
                JThrowable* th=dynamic_cast<JThrowable*>(object);
                return th->getMessage();
            }

            static void staticSetDetailMessage(JObject* object,JObject* value){
                JThrowable* th=dynamic_cast<JThrowable*>(object);
                th->setMessage((JString*)value);
            }

            static JObject** adrDetailMessage(JObject* object){
                JThrowable* th=dynamic_cast<JThrowable*>(object);
                return (JObject**)&th->message;
            }

            static JObject* staticGetCause(JObject* object){
                JThrowable* th=dynamic_cast<JThrowable*>(object);
                return th->getCause();
            }

            static void staticSetCause(JObject* object,JObject* value){
                JThrowable* th=dynamic_cast<JThrowable*>(object);
                th->setCause((JThrowable*)value);
            }

            static JObject** adrCause(JObject* object){
                JThrowable* th=dynamic_cast<JThrowable*>(object);
                return (JObject**)&th->cause;
            }

            static JObject* staticGetStackTrace(JObject* object){
                JThrowable* th=dynamic_cast<JThrowable*>(object);
                return th->getStackTrace();
            }

            static void staticSetStackTrace(JObject* object,JObject* value){
                JThrowable* th=dynamic_cast<JThrowable*>(object);
                th->setStackTrace((JPrimitiveObjectArray*)value);
            }

            static JObject** adrStackTrace(JObject* object){
                JThrowable* th=dynamic_cast<JThrowable*>(object);
                return (JObject**)&th->stackTrace;
            }

            static JObject* staticGetSuppressedExceptions(JObject* object){
                JThrowable* th=dynamic_cast<JThrowable*>(object);
                return dynamic_cast<JObject*>(th->getSuppressedExceptions());
            }

            static void staticSetSuppressedExceptions(JObject* object,JObject* value){
                JThrowable* th=dynamic_cast<JThrowable*>(object);
                th->suppressedExceptions=dynamic_cast<JList*>(value);
            }

            static JObject** adrSuppressedExceptions(JObject* object){
                JThrowable* th=dynamic_cast<JThrowable*>(object);
                return (JObject**)&th->suppressedExceptions;
            }

        public :
            JThrowableClass():jcpp::lang::JClass(){
                this->canonicalName=new JString("java.lang.Throwable");
                this->name=new JString("java.lang.Throwable");
                this->simpleName=new JString("Throwable");
                this->serialVersionUID=-3042686055658047285ULL;
            }

            virtual void initialize(){
                this->addInterface(JSerializable::getClazz());

                addConstructor(new JConstructor(JThrowable::getClazz(),JModifier::PUBLIC,createJThrowable));

                this->addField(new JField(new JString("detailMessage"),JString::getClazz(),this,staticGetDetailMessage,staticSetDetailMessage,adrDetailMessage));
                this->addField(new JField(new JString("cause"),this,this,staticGetCause,staticSetCause,adrCause));
                this->addField(new JField(new JString("stackTrace"),JPrimitiveObjectArray::getClazz(JStackTraceElement::getClazz()),this,staticGetStackTrace,staticSetStackTrace,adrStackTrace));
                this->addField(new JField(new JString("suppressedExceptions"),JList::getClazz(),this,staticGetSuppressedExceptions,staticSetSuppressedExceptions,adrSuppressedExceptions));
            }

            virtual jcpp::lang::JClass* getSuperclass(){
                return JObject::getClazz();
            }
        };


        static jcpp::lang::JClass* clazz = null;

        jcpp::lang::JClass* JThrowable::getClazz(){
            if (clazz==null){
                clazz=new JThrowableClass();
            }
            return clazz;
        }

        JThrowable::JThrowable(jcpp::lang::JClass* _class):JObject(_class){
            this->message=null;
            this->cause=null;
            this->stackTrace=null;
            this->suppressedExceptions=null;
        }

        JThrowable::JThrowable():JObject(getClazz()){
            this->message=null;
            this->cause=null;
            this->stackTrace=null;
            this->suppressedExceptions=null;
        }

        JThrowable::JThrowable(JString* message):JObject(getClazz()){
            this->message = message;
            this->cause=null;
            this->stackTrace=null;
            this->suppressedExceptions=null;
        }

        JThrowable::JThrowable(JString* message, JThrowable *cause):JObject(getClazz()){
            this->message = message;
            this->cause = cause;
            this->stackTrace=null;
            this->suppressedExceptions=null;
        }

        jbool JThrowable::equals(JObject* o){
            if ((o == null) || !getClazz()->isAssignableFrom(o->getClass())){
                return false;
            }
            JThrowable* other=dynamic_cast<JThrowable*>(o);
            jbool eq=true;
            if (other->message!=null && message!=null){
                eq=other->message->equals(message);
            }else{
                eq=other->message==null && message==null;
            }
            if (!eq){
                return false;
            }
            if (other->cause!=null && cause!=null){
                eq=other->cause->equals(cause);
            }else{
                eq=other->cause==null && cause==null;
            }
            if (!eq){
                return false;
            }
            if (other->stackTrace!=null && stackTrace!=null){
                eq=other->stackTrace->equals(stackTrace);
            }else{
                eq=other->stackTrace==null && stackTrace==null;
            }
            return eq;
        }

        JThrowable *JThrowable::getCause() {
            return cause;
        }

        void JThrowable::setCause(JThrowable* cause) {
            this->cause=cause;
        }

        void JThrowable::setMessage(JString* message){
            this->message = message;
        }

        JString* JThrowable::getMessage(){
            return this->message;
        }

        JPrimitiveObjectArray* JThrowable::getStackTrace(){
            return stackTrace;
        }

        void JThrowable::setStackTrace(JPrimitiveObjectArray* stackTrace){
            this->stackTrace=stackTrace;
        }

        void JThrowable::printStackTrace(JPrintStream* ps){
            ps->println(toString());
            if (stackTrace!=null){
                for (jint i=0;i<stackTrace->size();i++){
                    JStackTraceElement* s=dynamic_cast<JStackTraceElement*>(stackTrace->get(i));
                    ps->print(new JString("\tat "));
                    ps->println(s->toString());
                }
                if (getCause()!=null && getCause()!=this){
                    ps->println(new JString("Caused by:"));
                    getCause()->printStackTrace(ps);
                }
            }
            ps->flush();
        }

        void JThrowable::printStackTrace(JPrintWriter* ps){
            ps->println(toString());
            if (stackTrace!=null){
                for (jint i=0;i<stackTrace->size();i++){
                    JStackTraceElement* s=dynamic_cast<JStackTraceElement*>(stackTrace->get(i));
                    ps->print(new JString("\tat "));
                    ps->println(s->toString());
                }
                if (getCause()!=null && getCause()!=this){
                    ps->println(new JString("Caused by:"));
                    getCause()->printStackTrace(ps);
                }
            }
            ps->flush();
        }

        void JThrowable::printStackTrace(){
            printStackTrace(JSystem::out);
        }

        JList* JThrowable::getSuppressedExceptions(){
            return suppressedExceptions;
        }

        void JThrowable::addSuppressedException(JThrowable* t){
            if (suppressedExceptions==null){
                suppressedExceptions=new JArrayList();
            }
            suppressedExceptions->add(t);
        }

        JString* JThrowable::toString(){
            JStringBuilder* builder=new JStringBuilder();
            builder->append(getClass()->getName())->append(":");
            if (message!=null){
                builder->append(message);
            }
            return builder->toString();
        }

        JThrowable::~JThrowable(){
        }

        void JThrowable::throwJException(const NativeException& e) {
			JStringBuilder* builder = new JStringBuilder();

			builder->append("NativeException was thrown in class \"")->append(new JString(e.getClassName()));
			builder->append("\" method \"")->append(new JString(e.getMethodName()));
			builder->append("\" with message \"")->append(new JString(e.getMessage()));
			builder->append("\" with native type \"")->append(new JString(e.getTypeString()));

			if(e.getErrorCode() > 0) {
				builder->append("\" with error code \"")->append(e.getErrorCode());
			}

			builder->append("\"");

			JString* message = builder->toString();

			switch (e.getType()) {
				case NULL_POINTER_EXCEPTION:
					throw new JNullPointerException(message);
				case ILLEGAL_ARGUMENT_EXCEPTION:
					throw new JIllegalArgumentException(message);
				case OUT_OF_BOUND_EXCEPTION:
					throw new JIndexOutOfBoundsException(message);
				case ILLEGAL_STATE_EXCEPTION:
					throw new JIllegalStateException(message);
				case SYSTEM_EXCEPTION:
					throw new JException(message);
				case IO_EXCEPTION:
					throw new JIOException(message);
				case FILE_EXCEPTION:
					throw new JIOException(message);
				case FILE_EXISTS_EXCEPTION:
					throw new JIOException(message);
				case FILE_NOT_FOUND_EXCEPTION:
					throw new JFileNotFoundException(message);
				case FILE_READ_ONLY_EXCEPTION:
					throw new JIOException(message);
				case FILE_ACCESS_DENIED_EXCEPTION:
					throw new JIOException(message);
				case FILE_CREATE_EXCEPTION:
					throw new JIOException(message);
				case FILE_OPEN_EXCEPTION:
					throw new JIOException(message);
				case FILE_WRITE_EXCEPTION:
					throw new JIOException(message);
				case FILE_READ_EXCEPTION:
					throw new JIOException(message);
				case PATH_NOT_FOUND_EXCEPTION:
					throw new JIOException(message);
				case PATH_SYNTAX_EXCEPTION:
					throw new JIOException(message);
				case INTERRUPTED_EXCEPTION:
					throw new JInterruptedException(message);
				case UNKNOWN_HOST_EXCEPTION:
					throw new JUnknownHostException(message);
				case SOCKET_EXCEPTION:
					throw new JSocketException(message);
				case SOCKET_TIMEOUT_EXCEPTION:
					throw new JIOException(message);
				case OUT_OF_MEMORY_EXCEPTION:
					throw new JOutOfMemoryError(message);
				case BIND_EXCEPTION:
					throw new JIOException(message);
				case PROTOCOL_EXCEPTION:
					throw new JIOException(message);
				case CONNECT_EXCEPTION:
					throw new JIOException(message);
				default:
					throw new JException(message);
			}
		}

    }
}

