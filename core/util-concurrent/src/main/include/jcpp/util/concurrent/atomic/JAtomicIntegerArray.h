#ifndef JCPP_UTIL_CONCURRENT_ATOMIC_JATOMIC_INTEGER_ARRAY_H
#define JCPP_UTIL_CONCURRENT_ATOMIC_JATOMIC_INTEGER_ARRAY_H

#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JNumber.h"
#include "jcpp/lang/JPrimitiveInt.h"
#include "jcpp/lang/JPrimitiveIntArray.h"
#include "jcpp/io/JSerializable.h"

using namespace jcpp::io;
using namespace jcpp::lang;

namespace jcpp{
    namespace util{
        namespace concurrent{
            namespace atomic{

            	// @Class(canonicalName="java.util.concurrent.atomic.AtomicIntegerArray", simpleName="AtomicIntegerArray");
                class JCPP_EXPORT JAtomicIntegerArray : public JObject, public JSerializable{
                	private:
                	static const jlong serialVersionUID = 2862133569453604235LL;

                	protected:
                        JPrimitiveIntArray* value;
                        friend class JAtomicIntegerArrayClass;

                    public:
                        JAtomicIntegerArray(jint length);

                        static JClass* getClazz();

                        virtual jint length();

                        virtual jint get(jint);

                        virtual void set(jint index,jint value);

                        virtual void lazySet(jint index,jint value);

                        virtual jint getAndSet(jint index,jint value);

                        virtual jbool compareAndSet(jint index,jint expect,jint update);

                        virtual jbool weakCompareAndSet(jint index,jint expect, jint update);

                        virtual jint getAndIncrement(jint index);

                        virtual jint getAndDecrement(jint index);

                        virtual jint getAndAdd(jint index,jint delta);

                        virtual jint incrementAndGet(jint index);                        

                        virtual jint decrementAndGet(jint index);

                        virtual jint addAndGet(jint index,jint delta);

                        virtual JString* toString();

                        virtual ~JAtomicIntegerArray();
                };
            }
        }
    }
}
#endif
