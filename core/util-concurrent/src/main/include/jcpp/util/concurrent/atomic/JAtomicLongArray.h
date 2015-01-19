#ifndef JCPP_UTIL_CONCURRENT_ATOMIC_JATOMIC_LONG_ARRAY_H
#define JCPP_UTIL_CONCURRENT_ATOMIC_JATOMIC_LONG_ARRAY_H

#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JNumber.h"
#include "jcpp/lang/JPrimitiveLong.h"
#include "jcpp/lang/JPrimitiveLongArray.h"
#include "jcpp/io/JSerializable.h"

using namespace jcpp::io;
using namespace jcpp::lang;

namespace jcpp{
    namespace util{
        namespace concurrent{
            namespace atomic{

            	// @Class(canonicalName="java.util.concurrent.atomic.AtomicLongArray", simpleName="AtomicLongArray");
                class JCPP_EXPORT JAtomicLongArray : public JObject, public JSerializable{
                	private:
                		static const jlong serialVersionUID = -2308431214976778248LL;

                	protected:
                        JPrimitiveLongArray* array;
                        friend class JAtomicLongArrayClass;

                    public:
                        JAtomicLongArray();

                        JAtomicLongArray(jint length);

                        static JClass* getClazz();

                        virtual jint length();

                        virtual jlong get(jint index);

                        virtual void set(jint index,jlong value);

                        virtual void lazySet(jint index,jlong value);

                        virtual jlong getAndSet(jint index,jlong value);

                        virtual jbool compareAndSet(jint index,jlong expect,jlong update);

                        virtual jbool weakCompareAndSet(jint index,jlong expect, jlong update);

                        virtual jlong getAndIncrement(jint index);

                        virtual jlong getAndDecrement(jint index);

                        virtual jlong getAndAdd(jint index,jlong delta);

                        virtual jlong incrementAndGet(jint index);                        

                        virtual jlong decrementAndGet(jint index);

                        virtual jlong addAndGet(jint index,jlong delta);

                        virtual JString* toString();

                        virtual ~JAtomicLongArray();
                };
            }
        }
    }
}
#endif
