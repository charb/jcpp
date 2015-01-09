#ifndef JCPP_UTIL_CONCURRENT_ATOMIC_JATOMIC_BOOLEAN_H
#define JCPP_UTIL_CONCURRENT_ATOMIC_JATOMIC_BOOLEAN_H

#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JPrimitiveInt.h"
#include "jcpp/io/JSerializable.h"

using namespace jcpp::io;
using namespace jcpp::lang;

namespace jcpp{
    namespace util{
        namespace concurrent{
            namespace atomic{
                // @Class(canonicalName="java.util.concurrent.atomic.AtomicBoolean", simpleName="AtomicBoolean");
                class JCPP_EXPORT JAtomicBoolean : public JObject, public JSerializable{
                	private:
                		static const jlong serialVersionUID = 4654671469794556979LL;

                	protected:
                        JPrimitiveInt* value;
                        friend class JAtomicBooleanClass;

                	public:
                        JAtomicBoolean();

                        JAtomicBoolean(jbool value);

                        static JClass* getClazz();

                        virtual jbool get();

                        virtual jbool compareAndSet(jbool expect,jbool update);

                        virtual jbool weakCompareAndSet(jbool expect, jbool update);

                        virtual void set(jbool value);

                        virtual void lazySet(jbool value);

                        virtual jbool getAndSet(jbool value);

                        virtual JString* toString();                        

                        virtual ~JAtomicBoolean();
                };
            }
        }
    }
}
#endif
