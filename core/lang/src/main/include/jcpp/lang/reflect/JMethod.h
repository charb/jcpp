#ifndef JCPP_LANG_REFLECT_JMETHOD_H
#define JCPP_LANG_REFLECT_JMETHOD_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/reflect/JExecutable.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace util{
        class JList;
    }
    namespace lang{
        class JString;
        class JStringBuilder;
        class JClass;
        
        namespace reflect{

            class JCPP_EXPORT JMethod : public JExecutable{
            public:
                typedef JObject* (*invocation)(JObject* objet,jcpp::util::JList* args);

            protected:
                jcpp::lang::JClass* returnType;
                invocation inv;
                virtual void specificToStringHeader(JStringBuilder* sb);
                friend class jcpp::lang::JClass;

            public:
                JMethod(JString* name,jcpp::lang::JClass* declaringClass,jcpp::lang::JClass* returnType,invocation inv);

                virtual void setPublic();
                virtual void setPrivate();
                virtual void setProtected();
                virtual void setStatic();

                static jcpp::lang::JClass* getClazz();

                virtual JMethod* addAnnotation(JAnnotation* ann);

                virtual JMethod* addParameterType(jcpp::lang::JClass* type);

                virtual JMethod* addParameterAnnotation(jint index,JAnnotation* ann);

                virtual jbool equals(JObject* o);

                virtual jcpp::lang::JClass* getReturnType();

                virtual jint hashCode();

                virtual JObject* invoke(JObject* object, jcpp::util::JList* args); 

                virtual JString* toString();
                
                virtual ~JMethod();
            };
        }
    }
}

#endif
