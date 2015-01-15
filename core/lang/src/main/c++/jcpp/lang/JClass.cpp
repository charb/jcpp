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

#include <iostream>

using namespace jcpp::util;
using namespace jcpp::io;

namespace jcpp{
    namespace lang{

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

		JList* JClass::getFieldsFromInterfaces(){

			JList* result = new JArrayList();
			JList* interfacesList = this->getInterfaces();


			for (int i = 0; i < interfacesList->size(); ++i){
				JClass* interface = dynamic_cast<JClass*>(interfacesList->get(i));
				JList *interFields = interface->getFields();
				result->addAll(interFields);
			}
			return result;
		}

		JList* JClass::getDeclaredMethodsFromInterfaces(){
			JList* declaredMethods = new JArrayList();
			JIterator* interfaceIterator = this->getInterfaces()->iterator();
			while (interfaceIterator->hasNext()){
				JClass* clas = dynamic_cast<JClass*>(interfaceIterator->next());
				if (clas != this)
					declaredMethods->addAll(clas->getDeclaredMethods());
			}
			return declaredMethods;
		}

		JMethod* JClass::searchForMethodInList(jcpp::util::JList* methods, JString* name, jcpp::util::JList* parameterTypes){
			if (parameterTypes==null)
				parameterTypes = new JArrayList();
			JIterator* methodsIterator = methods->iterator();
			while (methodsIterator->hasNext()){
				JMethod* method = dynamic_cast<JMethod*>(methodsIterator->next());
				if (method->name->equals(name) &&
						method->getParameterTypes()->equals(dynamic_cast<JObject*>(parameterTypes)))
				return method;
			}
			return null;
		}

		JConstructor* JClass::searchForConstructorInList(jcpp::util::JList* constructors, jcpp::util::JList* parameterTypes){
        	if (parameterTypes == null)
        		parameterTypes = new JArrayList();
			JIterator* constructorsIterator = constructors->iterator();
			while (constructorsIterator->hasNext()){
				JConstructor* constructor = dynamic_cast<JConstructor*>(constructorsIterator->next());
				if (constructor->getParameterTypes()->equals(dynamic_cast<JObject*>(parameterTypes)))
					return constructor;
			}
			return null;
		}


        JConstructor* JClass::getConstructorNoException(jcpp::util::JList* parameterTypes){
        	initInternal();
        	initConstructors();
        	return searchForConstructorInList(this->getConstructors(), parameterTypes);
        }

        JConstructor* JClass::getDeclaredConstructorNoException(jcpp::util::JList* parameterTypes){
        	initInternal();
        	initDeclaredConstructors();
        	if (parameterTypes == null)
        	    parameterTypes = new JArrayList();
        	return searchForConstructorInList(constructorsList, parameterTypes);
        }

        JField* JClass::searchForFieldInList(jcpp::util::JList* fields, JString* name){
        	JIterator* iterator = fields->iterator();
        	while (iterator->hasNext()){
        		JField* field = dynamic_cast<JField*>(iterator->next());
        		if (field->getName()->equals(name))
        			return field;
        	}
        	return null;
        }

        JField* JClass::getDeclaredFieldNoException(JString* name){
        	return searchForFieldInList(getDeclaredFields(), name);
        }

        JField* JClass::getFieldNoException(JString* name){
			return searchForFieldInList(getFields(), name);
		}

        JMethod* JClass::getMethodNoException(JString* name, jcpp::util::JList* parameterTypes){
			initInternal();
			initMethods();
        	return searchForMethodInList(getMethods(), name, parameterTypes);

        }

        JMethod* JClass::getDeclaredMethodNoException(JString* name, jcpp::util::JList* parameterTypes){
        	initInternal();
        	initDeclaredMethods();
			return searchForMethodInList(getDeclaredMethods(), name, parameterTypes);
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
            this->modifier=0;
        }

        void JClass::initInternal(){
            if (!initialized){
                initialized=true;
                this->annotations=new JArrayList();
                this->enumConstants=new JArrayList();
                this->fields=new JHashMap();
                this->fieldsList=new JArrayList();
                this->constructorsList=new JArrayList();
                this->methodsList=new JArrayList();
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
        }

        void JClass::initConstructors(){
            initInternal();
        }

        void JClass::initDeclaredConstructors(){
            initInternal();
        }
        
        void JClass::initMethods(){
            initInternal();
        }

        void JClass::initDeclaredMethods(){
            initInternal();
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
            fields->put(field->getName(), field);
			fieldsList->add(field);
            return field;
        }

        JConstructor* JClass::addConstructor(JConstructor* constructor){
            	initInternal();
            	constructorsList->add(constructor);
            	return constructor;
        }

        void JClass::setPublic(JConstructor* c){
            c->setPublic();
        }
        
        JMethod* JClass::addMethod(JMethod* method){
            initInternal();
            methodsList->add(method);
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
            JClass* superClass = inter->getSuperclass();
            if (superClass != null && !superClass->isInterface()){
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
        	JConstructor* constructor = this->getConstructorNoException(parameterTypes);
        	if (constructor != null)
        		return constructor;
        	throw new JNoSuchMethodException(new JString("<init>"));
        }

        JList* JClass::getConstructors(){
            initInternal();
            JList* constructors = new JArrayList();
            JIterator* declaredConstructorsIterator = this->getDeclaredConstructors()->iterator();
            while (declaredConstructorsIterator->hasNext()){
            	JConstructor* constructor = dynamic_cast<JConstructor*>(declaredConstructorsIterator->next());
            	if (JModifier::isPublic(constructor->getModifiers()))
            		constructors->add(constructor);
            }
            return constructors;
        }

        JList* JClass::getDeclaredClasses(){
            initInternal();
            if (declaredClasses->size()==0){
                fillDeclaredClasses();
            }
            return declaredClasses;
        }

        JConstructor* JClass::getDeclaredConstructor(JList* parameterTypes){
        	JConstructor* constructor = this->getDeclaredConstructorNoException(parameterTypes);
			if (constructor != null)
				return constructor;
			throw new JNoSuchMethodException(new JString("<init>"));
        }

        JList* JClass::getDeclaredConstructors(){
			initInternal();
			initDeclaredConstructors();
			return constructorsList;
		}
            
        JField* JClass::getDeclaredField(JString* name){
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

        JList* JClass::getDeclaredFields(){
            initInternal();
            initFields();
            JList* result = new JArrayList();
            result->addAll(fieldsList);
            return result;
        }
                        
        JMethod* JClass::getDeclaredMethod(JString* name, JList* parameterTypes){
        	JMethod* method = this->getDeclaredMethodNoException(name, parameterTypes);
        	if (method != null)
        		return method;

        	JStringBuilder* builder=new JStringBuilder();
        	builder->append("method ")->append(name)->append(" not delared in ")->append(getName());
        	throw new JNoSuchMethodException(builder->toString());
        }

        JList* JClass::getDeclaredMethods(){
            initInternal();
            initDeclaredMethods();
            JList* declaredMethods = new JArrayList();
            declaredMethods->addAll(methodsList);
            return declaredMethods;
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


        	JField* field = dynamic_cast<JField*>(this->fields->get(name));
            if (field != null && JModifier::isPublic(field->getModifiers()))
            	return field;


            JList* fields = this->getFields();
            field = this->searchForFieldInList(fields, name);
            if (field != null && JModifier::isPublic(field->getModifiers()))
            	return field;

            JStringBuilder* builder=new JStringBuilder();
            builder->append("field ")->append(name)->append(" not delared in ")->append(getName());
            throw new JNoSuchFieldException(builder->toString());
        }

        JList* JClass::getFields(){
            initInternal();
            initFields();

            JList* fieldsToAdd = new JArrayList();

            JIterator* iterator = fieldsList->iterator();
            while (iterator->hasNext()){
            	JField* set = dynamic_cast<JField*>(iterator->next());
            	if (JModifier::isPublic(set->getModifiers()))
            		fieldsToAdd->add(set);
            }

            fieldsToAdd->addAll(getFieldsFromInterfaces());

            JClass* super = this->getSuperclass();
            if (super!=null)
				fieldsToAdd->addAll(super->getFields());


            return fieldsToAdd;
        }

        JList* JClass::getInterfaces(){
            initInternal();
            initInterfaces();
            return interfaces;
        }
    
        JMethod* JClass::getMethod(JString* name, JList* parameterTypes){
			JMethod* result = getMethodNoException(name, parameterTypes);
        	if (result != null)
        		return result;

			JStringBuilder* builder=new JStringBuilder();
			builder->append("method ")->append(name)->append(" not delared in ")->append(getName());
			throw new JNoSuchMethodException(builder->toString());
        }

        JList* JClass::getMethods(){
            initInternal();
            initMethods();
            JList* methods = new JArrayList();
            JList* methodsList = this->getDeclaredMethods();
            methodsList->addAll(this->getDeclaredMethodsFromInterfaces());
			JIterator* methodsIterator = methodsList->iterator();
			while (methodsIterator->hasNext()){
				JMethod* method = dynamic_cast<JMethod*>(methodsIterator->next());
				if (true||JModifier::isPublic(method->modifiers)) // TODO Remove
					methods->add(method);
			}

			JClass* superclass = this->getSuperclass();
			if (superclass != null){
				JIterator *superMethodsIterator = superclass->getMethods()->iterator();
				while (superMethodsIterator->hasNext()){
					JMethod* superMethod = dynamic_cast<JMethod*>(superMethodsIterator->next());
					JMethod* existingMethod = searchForMethodInList(methods, superMethod->getName(), superMethod->getParameterTypes());
					if (existingMethod == null)
						methods->add(superMethod);
				}
			}

			return methods;
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
            return fields->get(name) != null;
        }
            
        jbool JClass::hasConstructor(JList* parameterTypes){
        	initInternal();
        	initConstructors();
            return getConstructorNoException(parameterTypes) != null;
        }

        jbool JClass::hasDeclaredConstructor(JList* parameterTypes){
        	initInternal();
            initDeclaredConstructors();
        	return getDeclaredConstructorNoException(parameterTypes) != null;
        }

        jbool JClass::hasMethod(JString* name, JList* parameterTypes){
        	initInternal();
        	initMethods();
            return getMethodNoException(name, parameterTypes) != null;
        }

        jbool JClass::hasDeclaredMethod(JString* name, JList* parameterTypes){
        	initInternal();
        	initDeclaredMethods();
            return getDeclaredMethodNoException(name, parameterTypes) != null;
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
        	JConstructor* defaultConstructor = this->getConstructor(null);
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
