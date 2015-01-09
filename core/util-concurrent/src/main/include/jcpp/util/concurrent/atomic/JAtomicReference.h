#ifndef JCPP_UTIL_CONCURRENT_ATOMIC_JATOMIC_REFERENCE_H
#define JCPP_UTIL_CONCURRENT_ATOMIC_JATOMIC_REFERENCE_H

#include "jcpp/lang/JClass.h"
#include "jcpp/io/JSerializable.h"

using namespace jcpp::io;
using namespace jcpp::lang;

namespace jcpp{
    namespace util{
        namespace concurrent{
            namespace atomic{

            	// @Class(canonicalName="java.util.concurrent.atomic.AtomicReference", simpleName="AtomicReference");
                class JCPP_EXPORT JAtomicReference : public JObject, public JSerializable{
                	private:
                		static const jlong serialVersionUID = -1848883965231344442LL;

                	protected:
                        JObject* value;
                        friend class JAtomicReferenceClass;

                    public:
                        JAtomicReference(JObject* value);

                        static JClass* getClazz();

                        virtual JObject* get();

                        virtual void set(JObject* value);

                        virtual void lazySet(JObject* value);

                        virtual JObject* getAndSet(JObject* value);

                        virtual jbool compareAndSet(JObject* expect,JObject* update);

                        virtual jbool weakCompareAndSet(JObject* expect, JObject* update);

                        virtual JString* toString();

                        virtual ~JAtomicReference();
                };
            }
        }
    }
}
#endif
