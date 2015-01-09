#ifndef JCPP_UTIL_CONCURRENT_ATOMIC_JATOMIC_LONG_H
#define JCPP_UTIL_CONCURRENT_ATOMIC_JATOMIC_LONG_H

#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JNumber.h"
#include "jcpp/lang/JPrimitiveLong.h"
#include "jcpp/io/JSerializable.h"

using namespace jcpp::io;
using namespace jcpp::lang;

namespace jcpp{
    namespace util{
        namespace concurrent{
            namespace atomic{

            	// @Class(canonicalName="java.util.concurrent.atomic.AtomicLong", simpleName="AtomicLong");
                class JCPP_EXPORT JAtomicLong : public JNumber{
                	private:
                		static const jlong serialVersionUID = 1927816293512124184LL;

                	protected:
                        JPrimitiveLong* value;
                        friend class JAtomicLongClass;

                    public:
                        JAtomicLong();

                        JAtomicLong(jlong value);

                        static JClass* getClazz();

                        virtual jlong get();

                        virtual void set(jlong value);

                        virtual void lazySet(jlong value);

                        virtual jlong getAndSet(jlong value);

                        virtual jbool compareAndSet(jlong expect,jlong update);

                        virtual jbool weakCompareAndSet(jlong expect, jlong update);

                        virtual jlong getAndIncrement();

                        virtual jlong getAndDecrement();

                        virtual jlong getAndAdd(jlong delta);

                        virtual jlong incrementAndGet();                        

                        virtual jlong decrementAndGet();

                        virtual jlong addAndGet(jlong delta);

                        virtual JString* toString();

                        virtual jint intValue();

                        virtual jlong longValue();

                        virtual jfloat floatValue();

                        virtual jdouble doubleValue();

                        virtual ~JAtomicLong();
                };
            }
        }
    }
}
#endif
