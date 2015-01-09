#ifndef JCPP_LANG_REFLECT_JCONSTRUCTOR_H
#define JCPP_LANG_REFLECT_JCONSTRUCTOR_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/reflect/JExecutable.h"

using namespace std;
using namespace jcpp::lang;

namespace jcpp{
    namespace util{
        class JList;
    }
    namespace lang{
        class JString;
        class JStringBuilder;
        namespace reflect{

            class JCPP_EXPORT JConstructor : public JExecutable{
            public:
                typedef JObject* (*instantiator)(jcpp::util::JList* args);

            protected:
                instantiator inst;
                virtual void specificToStringHeader(JStringBuilder* sb);

            public:
                JConstructor(jcpp::lang::JClass* declaringClass,jint modifiers,instantiator inst);
                
                static jcpp::lang::JClass* getClazz();

                virtual JConstructor* addAnnotation(JAnnotation* ann);

                virtual JConstructor* addParameterType(jcpp::lang::JClass* type);
                
                virtual JConstructor* addParameterAnnotation(jint index,JAnnotation* ann);

                virtual jbool equals(JObject* obj);

                virtual jint hashCode();

                virtual JObject* newInstance(jcpp::util::JList* initargs);

                virtual JString* toString();

                virtual ~JConstructor();
            };
        }
    }
}

#endif
