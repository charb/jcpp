#ifndef JCPP_LANG_REFLECT_JPROXY_H
#define JCPP_LANG_REFLECT_JPROXY_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/reflect/JInvocationHandler.h"
#include "jcpp/util/JList.h"
#include "jcpp/lang/reflect/JMethod.h"

namespace jcpp{
    namespace lang{
        namespace reflect{

        	// @IgnoreReflection()
            class JCPP_EXPORT JProxy : public JObject{
            public:
            	// @IgnoreReflection()
                class JCPP_EXPORT JProxyClass : public jcpp::lang::JClass{
                protected:
                    static JObject** staticAdrInvocationHandler(JObject* obj);
                public:
                    JProxyClass();

                    virtual void initialize();

                    virtual jcpp::lang::JClass* getSuperclass();
                };

            protected:

                JInvocationHandler *invocationHandler;

                JProxy(jcpp::lang::JClass* _class);
                friend class JProxyClass;

            public:
                JProxy();

                JProxy(JInvocationHandler* i);

                static jcpp::lang::JClass* getClazz();

                static jcpp::lang::JClass* getProxyClass(JClassLoader* loader,JList* interfaces);

                static JProxy* newProxyInstance(JClassLoader* loader,JList* interfaces, JInvocationHandler* i);

                static jbool isProxyClass(jcpp::lang::JClass* cl);

                static JInvocationHandler* getInvocationHandler(JObject* proxy);

                virtual JInvocationHandler* getInvocationHandler();

                virtual void setInvocationHandler(JInvocationHandler* invocationHandler);

                virtual JObject* invoke(JString* methodName,JList* argTypes, JList* args);

                virtual jint hashCode();

                virtual jbool equals(JObject *o);

                virtual JString* toString();

                virtual ~JProxy();
            };
        }
    }
}

#endif
