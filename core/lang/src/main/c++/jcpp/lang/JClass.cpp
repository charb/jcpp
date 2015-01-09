#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClassLoader.h"
#include "jcpp/io/JSerializable.h"
#include "jcpp/lang/JEnum.h"
#include "jcpp/util/JList.h"
#include "jcpp/util/JMap.h"
#include "jcpp/util/JArrayList.h"
#include "jcpp/util/JHashMap.h"
#include "jcpp/lang/reflect/JPackage.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JNoSuchFieldException.h"
#include "jcpp/lang/JNoSuchMethodException.h"
#include "jcpp/lang/JIllegalArgumentException.h"
#include "jcpp/lang/JPrimitiveArray.h"
#include "jcpp/lang/JPrimitiveBoolean.h"
#include "jcpp/lang/JPrimitiveByte.h"
#include "jcpp/lang/JPrimitiveChar.h"
#include "jcpp/lang/JPrimitiveDouble.h"
#include "jcpp/lang/JPrimitiveFloat.h"
#include "jcpp/lang/JPrimitiveInt.h"
#include "jcpp/lang/JPrimitiveLong.h"
#include "jcpp/lang/JPrimitiveShort.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/JInternalError.h"
#include "jcpp/lang/JNullPointerException.h"
#include "jcpp/lang/JString.h"
#include "jcpp/lang/JInstantiationException.h"
#include "jcpp/lang/JSystem.h"
#include "jcpp/io/JObjectStreamField.h"

using namespace jcpp::util;
using namespace jcpp::io;

namespace jcpp{
    namespace lang{

        class JClassClass : public JClass{
        protected:
            static JObject* staticGetserialPersistentFields(JObject*){
                return JClass::getSerialPersistentFields();
            }

            static JObject** adrSerialPersistentFields(JObject*){
                return (JObject**)&JClass::serialPersistentFields;
            }

        public:
            JClassClass():JClass(){
                this->canonicalName=new JString("java.lang.Class");
                this->name=new JString("java.lang.Class");
                this->simpleName=new JString("Class");
                this->serialVersionUID=3206093459760846163ULL;
            }

            virtual void initialize(){
                addField(new JField(new JString("serialPersistentFields"),JPrimitiveArray::getClazz(JObjectStreamField::getClazz()),this,staticGetserialPersistentFields,null,adrSerialPersistentFields));
            }

            JClassLoader* getClassLoader(){
                return JClassLoader::getBootClassLoader();
            }

            virtual JClass* getSuperclass(){
                return JObject::getClazz();
            }

            void fillInterfaces(){
                addInterface(JSerializable::getClazz());
            }
        };

        static JClass* clazz;

        JClass* JClass::getClazz(){
            if (clazz==null){
                clazz=new JClassClass();
            }
            return clazz;
        }

        JPrimitiveObjectArray* JClass::serialPersistentFields = null;

        JPrimitiveObjectArray* JClass::getSerialPersistentFields(){
            if (serialPersistentFields==null){
                serialPersistentFields=new JPrimitiveObjectArray(JObjectStreamField::getClazz(),0);
            }
            return serialPersistentFields;
        }

        JClass::JClass(JClassLoader* classLoader):JObject(){
            init(classLoader);
        }

        JClass::JClass():JObject(){
            init(null);
        }

        void JClass::init(JClassLoader* cl){
            this->name=null;
            this->simpleName=null;
            this->canonicalName=null;
            this->package=null;
            this->classLoader=cl;
            this->serialVersionUID=0;
            this->signature=null;
            this->bIsArray=false;
            this->bIsAnnotation=false;
            this->bIsAnonymousClass=false;
            this->bIsProxy=false;
            this->bIsEnum=false;
            this->bIsInterface=false;
            this->bIsPrimitive=false;
            this->bIsLocalClass=false;
            this->bIsMemberClass=false;
            this->bIsPackage=false;
            this->componentType=null;
            this->initialized=false;
            this->defaultConstructor=null;
            this->modifier=0;
        }

        void JClass::initInternal(){
            if (!initialized){
                initialized=true;
                this->annotations=new JArrayList();
                this->enumConstants=new JArrayList();
                this->fields=new JHashMap();
                this->fieldsList=new JArrayList();
                this->declaredFields=new JHashMap();
                this->declaredFieldsList=new JArrayList();
                this->constructors=new JHashMap();
                this->constructorsList=new JArrayList();
                this->declaredConstructors=new JHashMap();
                this->declaredConstructorsList=new JArrayList();
                this->methods=new JHashMap();
                this->methodsList=new JArrayList();
                this->declaredMethods=new JHashMap();
                this->declaredMethodsList=new JArrayList();
                this->interfaces=new JArrayList();
                this->publicClasses=new JArrayList();
                this->inheritedPublicClasses=new JArrayList();
                this->declaredClasses=new JArrayList();
                initialize();
            }
        }

        void JClass::initialize(){
        }

        void JClass::initFields(){
            initInternal();
            if (fieldsList->size()==0){
                JClass* current=this;
                while (current!=null){
                    for (jint i=0;i<current->declaredFieldsList->size();i++){
                        JField* f=dynamic_cast<JField*>(current->declaredFieldsList->get(i));
                        fieldsList->add(f);
                        fields->put(f->getName(),f);
                    }
                    current=current->getSuperclass();
                }
            }
        }

        void JClass::initConstructors(){
            initInternal();
            if (constructorsList->size()==0){
                JClass* current=this;
                while (current!=null){
                    current->initDeclaredConstructors();
                    for (jint i=0;i<current->declaredConstructorsList->size();i++){
                        JConstructor* c=dynamic_cast<JConstructor*>(current->declaredConstructorsList->get(i));
                        constructorsList->add(c);
                        constructors->put(dynamic_cast<JObject*>(c->getParameterTypes()),c);
                    }
                    JList* interf=current->getInterfaces();
                    for (jint i=0;i<interf->size();i++){
                        JClass* c=dynamic_cast<JClass*>(interf->get(i));
                        c->initDeclaredConstructors();
                        for (jint j=0;j<c->declaredConstructorsList->size();j++){
                            JConstructor* ctr=dynamic_cast<JConstructor*>(c->declaredConstructorsList->get(j));
                            constructorsList->add(ctr);
                            constructors->put(dynamic_cast<JObject*>(ctr->getParameterTypes()),ctr);
                        }
                    }
                    current=current->getSuperclass();
                }
            }
        }

        void JClass::initDeclaredConstructors(){
            initInternal();
            if (declaredConstructors->size()==0){
                fillDeclaredConstructors();
            }
        }
        
        void JClass::initMethods(){
            initInternal();
            if (methodsList->size()==0){
                JClass* current=this;
                while (current!=null){
                    current->initDeclaredMethods();
                    for (jint i=0;i<current->declaredMethodsList->size();i++){
                        JMethod* m=dynamic_cast<JMethod*>(current->declaredMethodsList->get(i));
                        methodsList->add(m);
                        methods->put(m->getName(),m);//TODO add parameterTypes as addition key with the method name
                    }
                    JList* interf=current->getInterfaces();
                    for (jint i=0;i<interf->size();i++){
                        JClass* c=dynamic_cast<JClass*>(interf->get(i));
                        c->initDeclaredMethods();
                        for (jint j=0;j<c->declaredMethodsList->size();j++){
                            JMethod* m=dynamic_cast<JMethod*>(c->declaredMethodsList->get(j));
                            methodsList->add(m);
                            methods->put(m->getName(),m);//TODO add parameterTypes as addition key with the method name
                        }
                    }
                    current=current->getSuperclass();
                }
            }
        }

        void JClass::initDeclaredMethods(){
            initInternal();
            if (declaredMethods->size()==0){
                fillDeclaredMethods();
        }
        }

        void JClass::initInheritedPublicClasses(){
            initInternal();
            if (inheritedPublicClasses->size()==0){
                JClass* current=this;
                while (current!=null){
                    JList* members=current->getDeclaredClasses();
                    for (jint i=0;members->size();i++){
                        JClass* c=dynamic_cast<JClass*>(members->get(i));
                        if (JModifier::isPublic(c->getModifiers())){
                            inheritedPublicClasses->add(c);
                        }
                    }
                    current=current->getSuperclass();
                }
            }
        }

        void JClass::initEnumConstants(){
            initInternal();
            if (enumConstants->size()==0){
                fillEnumConstants();
            }
        }

        void JClass::initInterfaces(){
            initInternal();
            if (interfaces->size()==0){
                fillInterfaces();
            }
        }

        void JClass::setPublic(){
            modifier|=JModifier::PUBLIC;
        }
            
        void JClass::setPackage(JPackage* p){
            this->package=p;
        }

        JEnum* JClass::addEnumConstant(JEnum* enumConstant){
            initInternal();
            enumConstants->add(enumConstant);
            return enumConstant;
        }

        JField* JClass::addField(JField* field){
            initInternal();
            declaredFieldsList->add(field);
            declaredFields->put(field->getName(),field);
            return field;
        }

        JConstructor* JClass::addConstructor(JConstructor* constructor){
            initInternal();
            if (constructor->getParameterTypes()->size()==0){
                defaultConstructor=constructor;
            }
            declaredConstructorsList->add(constructor);
            declaredConstructors->put(dynamic_cast<JObject*>(constructor->getParameterTypes()),constructor);
            return constructor;
        }

        void JClass::setPublic(JConstructor* c){
            c->setPublic();
        }
        
        JMethod* JClass::addMethod(JMethod* method){
            initInternal();
            declaredMethodsList->add(method);
            declaredMethods->put(method->getName(),method);
            return method;
        }

        void JClass::setPublic(JMethod* m){
            m->setPublic();
        }
         
        void JClass::setStatic(JMethod* m){
            m->setStatic();
        }

        void JClass::addInterface(JClass* inter){
            initInternal();
            if (!inter->isInterface()){
                JStringBuilder* builder=new JStringBuilder();
                builder->append("class ")->append(inter->getName())->append(" is not typed as an interface");
                throw new JIllegalArgumentException(builder->toString());
            }
            if (!inter->getSuperclass()->isInterface()){
                JStringBuilder* builder=new JStringBuilder();
                builder->append("class ")->append(inter->getName());
                builder->append(" doesnt not declare ")->append(JInterface::getClazz()->getName())->append(" as its parent class");
                throw new JIllegalArgumentException(builder->toString());
            }
            interfaces->add(inter);
        }

        void JClass::addDeclaredClass(JClass* c){
            initInternal();
            if (c->getDeclaringClass()!=this){
                JStringBuilder* builder=new JStringBuilder();
                builder->append("Declaring class of ")->append(c->getName())->append(" is not ");
                builder->append(getName())->append(". It is ")->append(c->getDeclaringClass()->getName());
                throw new JIllegalArgumentException(builder->toString());
            }
            declaredClasses->add(c);
        }
        
        void JClass::fillDeclaredMethods(){
        }

        void JClass::fillDeclaredConstructors(){
        }

        void JClass::fillDeclaredClasses(){
        }

        void JClass::fillEnumConstants(){
        }

        void JClass::fillInterfaces(){
        }

        
        JClass* JClass::forName(JString* name){
            return forName(name,JClassLoader::getBootClassLoader());
        }

        JClass* JClass::forName(JString* name,JClassLoader* loader){
            return loader->loadClass(name);
        }

        JClass* JClass::getClass(){
            if (_class==null){
                this->_class=JClass::getClazz();
            }
            return _class;
        }

        JAnnotation* JClass::getAnnotation(JClass* annotationClass){
            initInternal();
            for (jint i=0;i<annotations->size();i++){
                JAnnotation* ann=dynamic_cast<JAnnotation*>(annotations->get(i));
                if (ann->annotationType()->equals(annotationClass)){
                    return ann;
                }
            }
            return null;
        }

        JList* JClass::getAnnotations(){
            initInternal();
            return annotations;
        }

        JString* JClass::getSignature(){
            if (signature==null){
                JStringBuilder* builder=new JStringBuilder();
                JClass* _class=this;
                while (_class->isArray()){
                    builder->append((jchar)'[');
                    _class=_class->getComponentType();
                }
                if (_class->isPrimitive()){
                    if (_class== JPrimitiveInt::getClazz()) {
                        builder->append((jchar)'I');

                    }else if (_class == JPrimitiveByte::getClazz()) {
                        builder->append((jchar)'B');

                    } else if (_class == JPrimitiveLong::getClazz()) {
                        builder->append((jchar)'J');

                    } else if (_class == JPrimitiveFloat::getClazz()) {
                        builder->append((jchar)'F');

                    } else if (_class == JPrimitiveDouble::getClazz()) {
                        builder->append((jchar)'D');

                    } else if (_class == JPrimitiveShort::getClazz()) {
                        builder->append((jchar)'S');

                    } else if (_class == JPrimitiveChar::getClazz()) {
                        builder->append((jchar)'C');

                    } else if (_class == JPrimitiveBoolean::getClazz()) {
                        builder->append((jchar)'Z');

                    } else if (_class == JVoid::TYPE) {
                        builder->append((jchar)'V');

                    } else {
                        throw new JInternalError();
                    }
                }else{
                    JString* name=_class->getName();
                    JString* newName=name->replace('/','.');
                    builder->append((jchar)'L');
                    builder->append(newName);
                    builder->append((jchar)';');
                }
                signature=builder->toString();
            }
            return signature;
        }

        JString* JClass::getCanonicalName(){
            return canonicalName;
        }
            
        JList* JClass::getClasses(){
            initInternal();
            initInheritedPublicClasses();
            return inheritedPublicClasses;
        }
            
        JClassLoader* JClass::getClassLoader(){
            if (classLoader==null){
                classLoader=JClassLoader::getBootClassLoader();
            }
            return classLoader;
        }
            
        JClass* JClass::getComponentType(){
            return componentType;
        }

        JConstructor* JClass::getConstructor(JList* parameterTypes){
            initInternal();
            initConstructors();
            if (parameterTypes==null){//TODO use static empty list
                parameterTypes=new JArrayList();
            }
            JConstructor* cons=dynamic_cast<JConstructor*>(constructors->get(dynamic_cast<JObject*>(parameterTypes)));
            if (cons==null){
                throw new JNoSuchMethodException(new JString("<init>"));
            }
            return cons;
        }

        JList* JClass::getConstructors(){
            initInternal();
            return constructorsList;
        }

        JList* JClass::getDeclaredClasses(){
            initInternal();
            if (declaredClasses->size()==0){
                fillDeclaredClasses();
            }
            return declaredClasses;
        }

        JConstructor* JClass::getDeclaredConstructor(JList* parameterTypes){
            initInternal();
            initDeclaredConstructors();
            if (parameterTypes==null){//TODO use static empty list
                parameterTypes=new JArrayList();
            }
            JConstructor* cons=dynamic_cast<JConstructor*>(declaredConstructors->get(dynamic_cast<JObject*>(parameterTypes)));
            if (cons==null){
                throw new JNoSuchMethodException(new JString("<init>"));
            }
            return cons;
        }

        JList* JClass::getDeclaredConstructors(){
            initInternal();
            initDeclaredConstructors();
            return declaredConstructorsList;
        }
            
        JField* JClass::getDeclaredField(JString* name){
            initInternal();
            initFields();
            JField* field=dynamic_cast<JField*>(declaredFields->get(name));
            if (field==null){
                JStringBuilder* builder=new JStringBuilder();
                builder->append("field ")->append(name)->append(" not delared in ")->append(getName());
                throw new JNoSuchFieldException(builder->toString());
            }
            return field;
        }

        JList* JClass::getDeclaredFields(){
            initInternal();
            initFields();
            return declaredFieldsList;
        }
                        
        JMethod* JClass::getDeclaredMethod(JString* name, JList* parameterTypes){
            initInternal();
            initDeclaredMethods();
            JMethod* method=dynamic_cast<JMethod*>(declaredMethods->get(name));
            if (method==null){
                JStringBuilder* builder=new JStringBuilder();
                builder->append("method ")->append(name)->append(" not delared in ")->append(getName());
                throw new JNoSuchMethodException(builder->toString());
            }
            return method;
        }

        JList* JClass::getDeclaredMethods(){
            initInternal();
            initDeclaredMethods();
            return declaredMethodsList;
        }

        JClass* JClass::getDeclaringClass(){
            return null;//TODO maybe better filled automaticaly using C++ parser
        }

        JClass* JClass::getEnclosingClass(){
            return null;//TODO maybe better filled automaticaly using C++ parser
        }

        JConstructor* JClass::getEnclosingConstructor(){
            return null;//TODO maybe better filled automaticaly using C++ parser
        }

        JMethod* JClass::getEnclosingMethod(){
            return null;//TODO maybe better filled automaticaly using C++ parser
        }

        JList* JClass::getEnumConstants(){
            initInternal();
            initEnumConstants();
            return enumConstants;
        }

        JField* JClass::getField(JString* name){
            initInternal();
            initFields();
            JField* field=dynamic_cast<JField*>(fields->get(name));
            if (field==null){
                JStringBuilder* builder=new JStringBuilder();
                builder->append("field ")->append(name)->append(" not delared in ")->append(getName());
                throw new JNoSuchFieldException(builder->toString());
            }
            return field;
        }
            
        JList* JClass::getFields(){
            initInternal();
            initFields();
            return fieldsList;
        }

        JList* JClass::getInterfaces(){
            initInternal();
            initInterfaces();
            return interfaces;
        }
    
        JMethod* JClass::getMethod(JString* name, JList* parameterTypes){
            initInternal();
            initMethods();
            JMethod* method=dynamic_cast<JMethod*>(methods->get(name));
            if (method==null){
                JStringBuilder* builder=new JStringBuilder();
                builder->append("method ")->append(name)->append(" not delared in ")->append(getName());
                throw new JNoSuchMethodException(builder->toString());
            }
            return method;
        }

        JList* JClass::getMethods(){
            initInternal();
            initMethods();
            return methodsList;
        }

        jint JClass::getModifiers(){
            return modifier;
        }

        JString* JClass::getName(){
            return name;
        }

        JPackage* JClass::getPackage(){
            return package;
        }

        JString* JClass::getSimpleName(){
            return simpleName;
        }

        jlong JClass::getSerialVersionUID(){
            return serialVersionUID;
        }

        JString* JClass::getTypeName(){
            if (isArray()) {
                try {
                    JClass* cl = this;
                    jint dimensions = 0;
                    while (cl->isArray()) {
                        dimensions++;
                        cl = cl->getComponentType();
                    }
                    JStringBuilder* sb = new JStringBuilder();
                    sb->append(cl->getName());
                    for (jint i = 0; i < dimensions; i++) {
                        sb->append("[]");
                    }
                    return sb->toString();
                } catch (JThrowable* e) {
                }
            }
            return getName();
        }

        jbool JClass::hasDeclaredField(JString* name){
            initInternal();
            initFields();
            JField* field=dynamic_cast<JField*>(declaredFields->get(name));
            return (field!=null);
        }
            
        jbool JClass::hasConstructor(JList* parameterTypes){
            initInternal();
            initConstructors();
            if (parameterTypes==null){//TODO use static empty list
                parameterTypes=new JArrayList();
            }
            JConstructor* cons=dynamic_cast<JConstructor*>(constructors->get(dynamic_cast<JObject*>(parameterTypes)));
            return (cons!=null);
        }

        jbool JClass::hasDeclaredConstructor(JList* parameterTypes){
            initInternal();
            initDeclaredConstructors();
            if (parameterTypes==null){//TODO use static empty list
                parameterTypes=new JArrayList();
            }
            JConstructor* cons=dynamic_cast<JConstructor*>(declaredConstructors->get(dynamic_cast<JObject*>(parameterTypes)));
            return (cons!=null);
        }

        jbool JClass::hasMethod(JString* name, JList* parameterTypes){
            initInternal();
            initMethods();
            JMethod* method=dynamic_cast<JMethod*>(methods->get(name));//TODO review key of methods map
            return (method!=null);
        }

        jbool JClass::hasDeclaredMethod(JString* name, JList* parameterTypes){
            initInternal();
            initDeclaredMethods();
            JMethod* method=dynamic_cast<JMethod*>(declaredMethods->get(name));
            return (method!=null);
        }
        
        jbool JClass::isProxy(){
            return bIsProxy;
        }
            
        jbool JClass::isPackage(){
            return bIsPackage;
        }

        jbool JClass::isAnnotation(){
            return bIsAnnotation;
        }

        jbool JClass::isAnnotationPresent(JClass* annotationClass){
            return getAnnotation(annotationClass)!=null;
        }

        jbool JClass::isAnonymousClass(){
            return bIsAnonymousClass;
        }

        jbool JClass::isArray(){
            return bIsArray;
        }

        jbool JClass::isAssignableFrom(JClass* clazz){
            JClass* current=clazz;
            while (current!=null){
                if (current==this){
                    return true;
                }
                if (current->getInterfaces()!=null){
                    for (jint i=0;i<current->getInterfaces()->size();i++){
                        JClass* interf=dynamic_cast<JClass*>(current->getInterfaces()->get(i));
                        if (this==interf){
                            return true;
                        }else{
                            if (isAssignableFrom(interf)){
                                return true;
                            }
                        }
                    }
                }
                if (current->getSuperclass()==current){
                    current=null;
                }else{
                    current=current->getSuperclass();//check also interfaces
                }
            }
            return false;
        }

        jbool JClass::isEnum(){
            return bIsEnum;
        }

        jbool JClass::isInstance(JObject* o){
            if (o==null){
                throw new JNullPointerException();
            }
            JClass* c=o->getClass();
            return isAssignableFrom(c);
        }

        jbool JClass::isInterface(){
            return bIsInterface;
        }

        jbool JClass::isLocalClass(){
            return bIsLocalClass;
        }

        jbool JClass::isMemberClass(){
            return bIsMemberClass;
        }

        jbool JClass::isPrimitive(){
            return bIsPrimitive;
        }

        JObject* JClass::newInstance(){
            if (defaultConstructor==null){
                JStringBuilder* builder=new JStringBuilder();
                builder->append("no default constructor found in class ")->append(getName());
                throw new JInstantiationException(builder->toString());
            }
            return defaultConstructor->newInstance(null);
        }

        JString* JClass::toString(){
            JStringBuilder* builder=new JStringBuilder();
            builder->append((isInterface()?"interface ":(isPrimitive()?"":"class ")))->append(getName());
            return builder->toString();
        }

        JEnum* JClass::valueOf(JString* value){
            initInternal();
            initEnumConstants();
            for (jint i=0;i<enumConstants->size();i++){
                JEnum* e=dynamic_cast<JEnum*>(enumConstants->get(i));
                if (e->getName()->equals(value)) {
                    return e;
                }
            }
            JStringBuilder* builder=new JStringBuilder();
            builder->append("No enum constant ")->append(value)->append(" in enum ")->append(getName());
            throw new JIllegalArgumentException(builder->toString());
        }

        JClass::~JClass(){
        }
    }
}
