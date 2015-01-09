#ifndef JCPP_LANG_REFLECT_JEXECUTABLE_H
#define JCPP_LANG_REFLECT_JEXECUTABLE_H

#include "jcpp/lang/reflect/JAccessibleObject.h"
#include "jcpp/lang/reflect/JMember.h"
#include "jcpp/lang/annotation/JAnnotation.h"

using namespace jcpp::lang::annotation;

namespace jcpp{
    namespace util{
        class JList;
    }
    namespace lang{
        class JObject;
        class JString;
        class JStringBuilder;
        class JClass;

        namespace reflect{
            class JCPP_EXPORT JExecutable: public JAccessibleObject, public JMember{
            protected:
                jint modifiers;
                JString* name;
                jcpp::lang::JClass* declaringClass;
                jcpp::util::JList* annotations;
                jcpp::util::JList* parameterTypes;
                jcpp::util::JList* parameterAnnotations;
                JExecutable* addAnnotation(JAnnotation* ann);
                JExecutable* addParameterType(jcpp::lang::JClass* type);
                JExecutable* addParameterAnnotation(jint index,JAnnotation* ann);
                jbool equalParamTypes(jcpp::util::JList* params1, jcpp::util::JList* params2);
                void checkArguments(jcpp::util::JList* arguments);
                void separateWithCommas(jcpp::util::JList* types, JStringBuilder* sb);
                void printModifiersIfNonzero(JStringBuilder* sb, jbool isDefault);
                JString* sharedToString(jbool isDefault,jcpp::util::JList* parameterTypes);
                virtual void specificToStringHeader(JStringBuilder* sb)=0;

                JExecutable();
                JExecutable(jcpp::lang::JClass* _class);
                friend class jcpp::lang::JClass;

            public:

                virtual void setFinal();
                virtual void setNative();
                virtual void setAbstract();

                static jcpp::lang::JClass* getClazz();
                
                virtual void setPublic();
                virtual void setPrivate();
                virtual void setProtected();
                virtual void setStatic();

                virtual JAnnotation* getAnnotation(jcpp::lang::JClass* annotationClass);

                virtual jcpp::util::JList* getAnnotations();

                virtual jcpp::lang::JClass* getDeclaringClass();

                virtual jint getModifiers();

                virtual JString* getName();

                virtual jcpp::util::JList* getParameterAnnotations();

                virtual jint getParameterCount();

                virtual jcpp::util::JList* getParameterTypes();

                virtual ~JExecutable();
            };
        }
    }
}

#endif
