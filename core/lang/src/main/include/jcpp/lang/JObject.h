#ifndef JCPP_LANG_JOBJECT_H
#define JCPP_LANG_JOBJECT_H

#include "jcpp/native/api/nthread/NativeMutex.h"
#include "jcpp/native/api/nthread/NativeCondition.h"
#include "jcpp/native/api/NativeInclude.h"
#include "jcpp/gc/Finalizable.h"

using namespace jcpp::native::api::nthread;
using namespace std;
using namespace jcpp::gc;

namespace jcpp{
    namespace util{
        namespace concurrent{
            class JWorker;
            namespace locks{
                class JReentrantLock;
            }
        }
    }
    namespace lang{
        class JClass;
        class JString;

        // @Class(canonicalName="java.lang.Object", simpleName="Object");
        class JCPP_EXPORT JObject : public Finalizable {
            private:
        		// @IgnoreReflection()
                NativeMutex* mutex;
                // @IgnoreReflection()
                NativeCondition* condition;

                void internalLock();
                jbool internalTryLock();
                jbool internalTryLock(jlong l);
                void internalUnlock();
                friend class ScopedObjectLock;
                friend class jcpp::util::concurrent::locks::JReentrantLock;
                friend class jcpp::util::concurrent::JWorker;

            protected:
                jcpp::lang::JClass* _class;
                JObject(jcpp::lang::JClass* _class);

            public:
                JObject();
                
                static jcpp::lang::JClass* getClazz();
                
                virtual jcpp::lang::JClass* getClass();
                                
                jbool isInstanceOf(jcpp::lang::JClass* c);

                void wait();
                
                void wait(jlong);
                
                void notify();
                
                void notifyAll();
                
                virtual void finalize();
                
                virtual jbool equals(JObject* o);
                
                virtual jint hashCode();
                
                virtual JString* toString();
                
                virtual JObject* clone();
                
                virtual ~JObject();
        };

        // @IgnoreReflection()
        // @IgnorePackageReflection()
        class JCPP_EXPORT ScopedObjectLock {
            private:
                JObject* obj;

                ScopedObjectLock(const ScopedObjectLock&);
                ScopedObjectLock& operator =(const ScopedObjectLock&);

            public:
                ScopedObjectLock(JObject* obj);
                ~ScopedObjectLock();
        };

        #define synchronized(A,B) {           \
                ScopedObjectLock __lock__(A); \
                B                             \
                }

        //TODO: this is bugged if there is an issue in B or if A use return instruction
        #define try_finally(A,B) {              \
                    try{ A                      \
                         B                      \
                    }catch(JThrowable * __th__){\
                        B                       \
                        throw __th__;           \
                    }                           \
                }
  
        /* TODO: this can be better, but the scope is an issue!
        #define try_finally(A,B) {               \
            class JCPP_EXPORT ScopedTryFinally { \
            public:                              \
                ScopedTryFinally(){              \
                }                                \
                ~ScopedTryFinally(){             \
                    B                            \
                }                                \
            };                                   \
            ScopedTryFinally __try_finally__;    \
            A                                    \
            }
        */
    }
}


#endif
