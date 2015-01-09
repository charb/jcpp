#ifndef JCPP_UTIL_CONCURRENT_ATOMIC_JATOMIC_INTEGER_H
#define JCPP_UTIL_CONCURRENT_ATOMIC_JATOMIC_INTEGER_H

#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JNumber.h"
#include "jcpp/lang/JPrimitiveInt.h"
#include "jcpp/io/JSerializable.h"

using namespace jcpp::io;
using namespace jcpp::lang;

namespace jcpp{
    namespace util{
        namespace concurrent{
            namespace atomic{

            	// @Class(canonicalName="java.util.concurrent.atomic.AtomicInteger", simpleName="AtomicInteger");
                class JCPP_EXPORT JAtomicInteger : public JNumber{
                	private:
                		static const jlong serialVersionUID = 6214790243416807050LL;

                	protected:
                        JPrimitiveInt* value;
                        friend class JAtomicIntegerClass;

                    public:
                        JAtomicInteger();

                        JAtomicInteger(jint value);

                        static JClass* getClazz();

                        virtual jint get();

                        virtual void set(jint value);

                        virtual void lazySet(jint value);

                        virtual jint getAndSet(jint value);

                        virtual jbool compareAndSet(jint expect,jint update);

                        virtual jbool weakCompareAndSet(jint expect, jint update);

                        virtual jint getAndIncrement();

                        virtual jint getAndDecrement();

                        virtual jint getAndAdd(jint delta);

                        virtual jint incrementAndGet();                        

                        virtual jint decrementAndGet();

                        virtual jint addAndGet(jint delta);

                        virtual JString* toString();

                        virtual jint intValue();

                        virtual jlong longValue();

                        virtual jfloat floatValue();

                        virtual jdouble doubleValue();

                        virtual ~JAtomicInteger();
                };
            }
        }
    }
}
#endif
