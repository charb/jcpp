#ifndef JCPP_LANG_JCLASS_H
#define JCPP_LANG_JCLASS_H

#include "jcpp/native/api/NativeInclude.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JField.h"
#include "jcpp/lang/JString.h"
#include "jcpp/lang/annotation/JAnnotation.h"
#include "jcpp/lang/reflect/JAnnotatedType.h"
#include "jcpp/lang/reflect/JConstructor.h"

using namespace jcpp::lang::reflect;
using namespace jcpp::lang::annotation;

namespace jcpp{
    
    namespace util{
        class JList;
        class JMap;
    }

    namespace lang{
        class JEnum;
        class JClassLoader;
        class JPrimitiveObjectArray;

        namespace reflect{
            class JPackage;
        }

        class JCPP_EXPORT JClass : public JObject{
        private:
            jbool initialized;
            void init(JClassLoader* cl);
            void initInternal();
            void initFields();
            void initConstructors();
            void initDeclaredConstructors();
            void initMethods();
            void initDeclaredMethods();
            void initInheritedPublicClasses();
            void initEnumConstants();
            void initInterfaces();

        protected:
            static JPrimitiveObjectArray* serialPersistentFields;
            static JPrimitiveObjectArray* getSerialPersistentFields();
            jcpp::lang::reflect::JPackage* package;
            JString* canonicalName;
            JString* name;
            JString* simpleName;
            JString* signature;
            JClassLoader* classLoader;
            JClass* componentType;
            jcpp::util::JList* annotations;
            jcpp::util::JList* enumConstants;
            jcpp::util::JMap* fields;
            jcpp::util::JList* fieldsList;
            jcpp::util::JMap* declaredFields;
            jcpp::util::JList* declaredFieldsList;
            JConstructor* defaultConstructor;
            jcpp::util::JMap* constructors;
            jcpp::util::JList* constructorsList;
            jcpp::util::JMap* declaredConstructors;
            jcpp::util::JList* declaredConstructorsList;
            jcpp::util::JMap* methods;
            jcpp::util::JList* methodsList;
            jcpp::util::JMap* declaredMethods;
            jcpp::util::JList* declaredMethodsList;
            jcpp::util::JList* interfaces;
            jcpp::util::JList* publicClasses;
            jcpp::util::JList* inheritedPublicClasses;
            jcpp::util::JList* declaredClasses;
            jbool bIsArray;
            jbool bIsAnnotation;
            jbool bIsAnonymousClass;
            jbool bIsProxy;
            jbool bIsEnum;
            jbool bIsInterface;
            jbool bIsLocalClass;
            jbool bIsMemberClass;
            jbool bIsPrimitive;
            jbool bIsPackage;
            jlong serialVersionUID;
            jint modifier;
            JClass(JClassLoader* classLoader);
            JClass();

            void setPublic();
            void setPackage(jcpp::lang::reflect::JPackage* p);
            JEnum* addEnumConstant(JEnum* enumConstant);
            JField* addField(JField* field);
            JConstructor* addConstructor(JConstructor* constructor);
            void setPublic(JConstructor* m);
            JMethod* addMethod(JMethod* method);
            void setPublic(JMethod* m);
            void setStatic(JMethod* m);
            void addInterface(JClass* inter);
            void addDeclaredClass(JClass* c);
            virtual void initialize();
            virtual void fillDeclaredMethods();
            virtual void fillDeclaredConstructors();
            virtual void fillDeclaredClasses();
            virtual void fillEnumConstants();
            virtual void fillInterfaces();
            friend class JClassLoader;
            friend class jcpp::lang::reflect::JPackage;

         public:

            static JClass* getClazz();

            static JClass* forName(JString* name);

            static JClass* forName(JString* name,JClassLoader* loader);

            virtual JClass* getClass();
            
            virtual JAnnotation* getAnnotation(JClass* annotationClass);

            virtual jcpp::util::JList* getAnnotations();

            virtual JString* getSignature();
            
            virtual JString* getCanonicalName();
            
            virtual jcpp::util::JList* getClasses();
            
            virtual JClassLoader* getClassLoader();
            
            virtual JClass* getComponentType();

            virtual JConstructor* getConstructor(jcpp::util::JList* parameterTypes);

            virtual jcpp::util::JList* getConstructors();

            virtual jcpp::util::JList* getDeclaredClasses();

            virtual JConstructor* getDeclaredConstructor(jcpp::util::JList* parameterTypes);

            virtual jcpp::util::JList* getDeclaredConstructors();
            
            virtual JField* getDeclaredField(JString* name);

            virtual jcpp::util::JList* getDeclaredFields();
                        
            virtual JMethod* getDeclaredMethod(JString* name, jcpp::util::JList* parameterTypes);

            virtual jcpp::util::JList* getDeclaredMethods();

            virtual JClass* getDeclaringClass();

            virtual JClass* getEnclosingClass();

            virtual JConstructor* getEnclosingConstructor();

            virtual JMethod* getEnclosingMethod();

            virtual jcpp::util::JList* getEnumConstants();

            virtual JField* getField(JString* name);
            
            virtual jcpp::util::JList* getFields();

            virtual jcpp::util::JList* getInterfaces();

            virtual JMethod* getMethod(JString* name, jcpp::util::JList* parameterTypes);

            virtual jcpp::util::JList* getMethods();

            virtual jint getModifiers();

            virtual JString* getName();

            virtual jcpp::lang::reflect::JPackage* getPackage();

            virtual JString* getSimpleName();

            virtual jlong getSerialVersionUID();

            virtual JClass* getSuperclass()=0;

            virtual JString* getTypeName();

            virtual jbool hasDeclaredField(JString* name);
            
            virtual jbool hasConstructor(jcpp::util::JList* parameterTypes);
                        
            virtual jbool hasDeclaredConstructor(jcpp::util::JList* parameterTypes);

            virtual jbool hasMethod(JString* name, jcpp::util::JList* parameterTypes);
                        
            virtual jbool hasDeclaredMethod(JString* name, jcpp::util::JList* parameterTypes);

            virtual jbool isProxy();
            
            virtual jbool isPackage();

            virtual jbool isAnnotation();

            virtual jbool isAnnotationPresent(JClass* annotationClass);

            virtual jbool isAnonymousClass();

            virtual jbool isArray();

            virtual jbool isAssignableFrom(JClass* clazz);

            virtual jbool isEnum();

            virtual jbool isInstance(JObject* o);

            virtual jbool isInterface();

            virtual jbool isLocalClass();

            virtual jbool isMemberClass();

            virtual jbool isPrimitive();

            virtual JObject* newInstance();

            virtual JString* toString();

            virtual JEnum* valueOf(JString* value);
            
            virtual ~JClass();
        };
    }
}

#endif
