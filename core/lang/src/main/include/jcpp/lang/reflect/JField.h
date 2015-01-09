#ifndef JCPP_LANG_REFLECT_JFIELD_H
#define JCPP_LANG_REFLECT_JFIELD_H

#include "jcpp/lang/reflect/JAccessibleObject.h"
#include "jcpp/lang/reflect/JMember.h"
#include "jcpp/lang/reflect/JAnnotatedType.h"
#include "jcpp/lang/annotation/JAnnotation.h"

using namespace jcpp::lang::annotation;

namespace jcpp{
    namespace util{
        class JList;
    }
    namespace lang{
        class JObject;
        class JString;
        class JClass;

        namespace reflect{
            class JCPP_EXPORT JField: public JAccessibleObject, public JMember{
            public:
                typedef JObject* (*getter)(JObject* objet);
                typedef void (*setter)(JObject* object,JObject* value);
                typedef JObject** (*adressReference)(JObject*);

            protected:
                JString* name;
                jcpp::lang::JClass* type;
                getter g;
                setter s;
                adressReference adr;
                jint iModifiers;
                jcpp::lang::JClass* declaringClass;
                jcpp::util::JList* annotations;

				friend class jcpp::lang::JClass;

            public:
                JField(JString* name,jcpp::lang::JClass* type,jcpp::lang::JClass* declaringClass,getter g,setter s, adressReference adr);

                static jcpp::lang::JClass* getClazz();

                virtual void setPublic();
                virtual void setPrivate();
                virtual void setProtected();
                virtual void setStatic();
                virtual void setFinal();

                virtual JField* addAnnotation(JAnnotation* ann);

                virtual jbool equals(JObject* o);

                virtual JObject* get(JObject* object);

                virtual JAnnotation* getAnnotation(jcpp::lang::JClass* annotationClass);

                virtual jcpp::util::JList* getAnnotations();

                virtual jbool getBoolean(JObject* obj);

                virtual jbyte getByte(JObject* obj);

                virtual jchar getChar(JObject* obj);

                virtual jcpp::lang::JClass* getDeclaringClass();

                virtual jdouble getDouble(JObject* obj);

                virtual jfloat getFloat(JObject* obj);

                virtual jint getInt(JObject* obj);

                virtual jlong getLong(JObject* obj);

                virtual jint getModifiers();

                virtual JString* getName();

                virtual jshort getShort(JObject* obj);
                
                virtual jcpp::lang::JClass* getType();
                
                virtual jint hashCode();

                virtual jbool isEnumConstant();
                
                virtual void set(JObject* object, JObject* value);
                
                virtual void setBoolean(JObject* obj, jbool z);

                virtual void setByte(JObject* obj, jbyte b);

                virtual void setChar(JObject* obj, jchar c);

                virtual void setDouble(JObject* obj, jdouble d);

                virtual void setFloat(JObject* obj, jfloat f);

                virtual void setInt(JObject* obj, jint i);

                virtual void setLong(JObject* obj, jlong l);

                virtual void setShort(JObject* obj, jshort s);
                
                virtual JString* toString();
                
                virtual ~JField();
            };
        }
    }
}

#endif
