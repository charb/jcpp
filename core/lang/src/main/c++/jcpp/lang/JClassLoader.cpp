#include "jcpp/lang/JClassLoader.h"
#include "jcpp/util/JHashMap.h"
#include "jcpp/util/JList.h"
#include "jcpp/JCPP_PACKAGE.h"
#include "jcpp/lang/JClassNotFoundException.h"
#include "jcpp/lang/JIllegalArgumentException.h"
#include "jcpp/lang/JPrimitiveByte.h"
#include "jcpp/lang/JPrimitiveLong.h"
#include "jcpp/lang/JPrimitiveFloat.h"
#include "jcpp/lang/JPrimitiveDouble.h"
#include "jcpp/lang/JPrimitiveShort.h"
#include "jcpp/lang/JPrimitiveChar.h"
#include "jcpp/lang/JPrimitiveBoolean.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/JInternalError.h"
#include "jcpp/lang/JStringBuilder.h"
#include "jcpp/lang/JSystem.h"

using namespace jcpp::util;

namespace jcpp{
    namespace lang{
        class JClassLoaderClass : public jcpp::lang::JClass{
          public:
            JClassLoaderClass():jcpp::lang::JClass(){
                this->canonicalName=new JString("java.lang.ClassLoader");
                this->name=new JString("java.lang.ClassLoader");
                this->simpleName=new JString("ClassLoader");
            }

            JClassLoaderClass(JClassLoader* classLoader):jcpp::lang::JClass(){
                this->canonicalName=new JString("java.lang.ClassLoader");
                this->name=new JString("java.lang.ClassLoader");
                this->simpleName=new JString("ClassLoader");
                this->classLoader=classLoader;
            }

            virtual JClassLoader* getClassLoader(){
                if (classLoader==null){
                    classLoader=JClassLoader::getBootClassLoader();
                }
                return classLoader;
            }

            virtual jcpp::lang::JClass* getSuperclass(){
                return JObject::getClazz();
            }
        };

        static jcpp::lang::JClass* clazz;

        jcpp::lang::JClass* JClassLoader::getClazz(){
            if (clazz==null){
                clazz=new JClassLoaderClass();
            }
            return clazz;
        }

        jcpp::lang::JClass* JClassLoader::getClazz(JClassLoader* classLoader){
            if (clazz==null){
                clazz=new JClassLoaderClass(classLoader);
            }
            return clazz;
        }


        static JClassLoader* bootClassLoader;

        JClassLoader* JClassLoader::getBootClassLoader(){
            if (bootClassLoader==null){
                bootClassLoader=new JClassLoader(true);
            }
            return bootClassLoader;
        }

        static jbool initialized=false;
        void JClassLoader::init(){
            if (!initialized){
                initialized=true;
                getBootClassLoader()->initClasses(JCPP_PACKAGE::getPackage());
            }
        }

        JString* JClassLoader::SIG_I = new JString("I");
        
        JString* JClassLoader::SIG_B = new JString("B");

        JString* JClassLoader::SIG_J =new JString("J");

        JString* JClassLoader::SIG_F = new JString("F");

        JString* JClassLoader::SIG_D = new JString("D");

        JString* JClassLoader::SIG_S = new JString("S");

        JString* JClassLoader::SIG_C = new JString("C");

        JString* JClassLoader::SIG_Z = new JString("Z");

        JString* JClassLoader::SIG_V = new JString("V");

        JClassLoader::JClassLoader(jcpp::lang::JClass* _class,JClassLoader* parent):JObject(_class){
            this->classes=new JHashMap();
            this->bIsBootClassLoader=false;
            this->parent=(parent!=null ? parent : getBootClassLoader());
        }

        JClassLoader::JClassLoader(jbool root):JObject(){
            this->classes=new JHashMap();
            this->_class=getClazz(this);
            this->bIsBootClassLoader=root;
            this->parent=null;
        }

        jbool JClassLoader::isBootClassLoader(){
            return bIsBootClassLoader;
        }

        JClassLoader* JClassLoader::getParent(){
            return parent;
        }

        void JClassLoader::addClass(jcpp::lang::JClass* jClass){
            jcpp::lang::JClass* tmp=dynamic_cast<jcpp::lang::JClass*>(classes->get(jClass->getName()));
            if (tmp!=null && tmp!=jClass){
                JStringBuilder* builder=new JStringBuilder();
                builder->append("class ")->append(jClass->toString())->append(" already defined in classlaoder ");
                builder->append(toString());
                throw new JIllegalArgumentException(builder->toString());
            }
            classes->put(jClass->getName(),jClass);
            jClass->classLoader=this;
        }

        void JClassLoader::initClasses(JPackage* p){
            for (jint i=0;i<p->getClasses()->size();i++){
                jcpp::lang::JClass* c=dynamic_cast<jcpp::lang::JClass*>(p->getClasses()->get(i));
                addClass(c);
                JList* dc=c->getDeclaredClasses();
                for (jint j=0;j<dc->size();j++){
                    addClass(dynamic_cast<jcpp::lang::JClass*>(dc->get(j)));
                }
            }
            for (jint i=0;i<p->getPackages()->size();i++){
                initClasses(dynamic_cast<JPackage*>(p->getPackages()->get(i)));
            }
        }

        jcpp::lang::JClass* JClassLoader::loadClass(JString* name){
            if (name->charAt(0)=='['){
                return loadClassBySignature(name);
            }
            jcpp::lang::JClass* jClass=null;
            if (!bIsBootClassLoader){
                if (parent!=null){
                    try{
                        jClass=parent->loadClass(name);
                    }catch(JClassNotFoundException* e1){
                    }
                }else{
                    try{
                        jClass=getBootClassLoader()->loadClass(name);
                    }catch(JClassNotFoundException* e1){
                    }
                }
            }
            if (jClass==null){
                jClass=dynamic_cast<jcpp::lang::JClass*>(classes->get(name));
                if (jClass==null){
                    JStringBuilder* builder=new JStringBuilder();
                    builder->append("class ")->append(name)->append(" not found");
                    throw new JClassNotFoundException(builder->toString());
                }
            }
            return jClass;
        }

        jcpp::lang::JClass* JClassLoader::loadClassBySignature(JString* name){
            if (name->charAt(0)=='['){
                int nbArray=0;
                JString* classname;
                for (jint i=0;i<name->length();i++){
                    if (name->charAt(i)=='['){
                        nbArray++;
                    }else{
                        classname=name->substring(i,name->length());
                        break;
                    }
                }
                jcpp::lang::JClass* componentClass;
                if (classname->equals(SIG_I)){
                    componentClass= JPrimitiveInt::getClazz();

                }else if (classname->equals(SIG_B)){
                    componentClass= JPrimitiveByte::getClazz();

                }else if (classname->equals(SIG_J)){
                    componentClass= JPrimitiveLong::getClazz();

                }else if (classname->equals(SIG_F)){
                    componentClass= JPrimitiveFloat::getClazz();

                }else if (classname->equals(SIG_D)){
                    componentClass= JPrimitiveDouble::getClazz();

                }else if (classname->equals(SIG_S)){
                    componentClass= JPrimitiveShort::getClazz();

                }else if (classname->equals(SIG_C)){
                    componentClass= JPrimitiveChar::getClazz();

                }else if (classname->equals(SIG_Z)){
                    componentClass= JPrimitiveBoolean::getClazz();

                }else if (classname->equals(SIG_V)){
                    componentClass= JVoid::TYPE;

                }else if (classname->charAt(0)=='L'){
                    classname=classname->substring(1,classname->length()-1);//remove ;
                    classname=classname->replace('/','.');
                    componentClass=loadClass(classname);

                }else{
                    throw new JInternalError();
                }
                jcpp::lang::JClass* current=componentClass;
                for (jint i=0;i<nbArray;i++){
                    current=JPrimitiveArray::getClazz(current);
                }
                return current;
            }
            throw new JInternalError();
        }

        JClassLoader::~JClassLoader() {
        }
    }
}
