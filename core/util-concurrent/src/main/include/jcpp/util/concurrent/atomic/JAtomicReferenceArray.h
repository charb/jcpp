#ifndef JCPP_UTIL_CONCURRENT_ATOMIC_JATOMIC_REFERENCE_ARRAY_H
#define JCPP_UTIL_CONCURRENT_ATOMIC_JATOMIC_REFERENCE_ARRAY_H

#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "jcpp/io/JSerializable.h"
#include "jcpp/io/JObjectInputStream.h"

using namespace jcpp::io;
using namespace jcpp::lang;

namespace jcpp{
    namespace util{
        namespace concurrent{
            namespace atomic{

            	// @Class(canonicalName="java.util.concurrent.atomic.AtomicReferenceArray", simpleName="AtomicReferenceArray");
                class JCPP_EXPORT JAtomicReferenceArray : public JObject, public JSerializable{
                	private:
                		static const jlong serialVersionUID = -6209656149925076980LL;

                	protected:
                        JPrimitiveObjectArray* array;
                        friend class JAtomicReferenceArrayClass;

                    public:
                        JAtomicReferenceArray();

                        JAtomicReferenceArray(jint length);

                        static JClass* getClazz();

                        virtual jint length();

                        virtual JObject* get(jint);

                        virtual void set(jint index,JObject* value);

                        virtual void lazySet(jint index,JObject* value);

                        virtual JObject* getAndSet(jint index,JObject* value);

                        virtual jbool compareAndSet(jint index,JObject* expect,JObject* update);

                        virtual jbool weakCompareAndSet(jint index,JObject* expect, JObject* update);

                        virtual JString* toString();

                        virtual ~JAtomicReferenceArray();
                };
            }
        }
    }
}
#endif
