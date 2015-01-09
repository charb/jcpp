#include "jcpp/util/JArrays.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/util/JArrayList.h"
#include <vector>
#include <algorithm>

namespace jcpp{
    namespace util{
        class JArraysClass : public jcpp::lang::JClass{
        public:
            JArraysClass():jcpp::lang::JClass(){
                this->canonicalName=new JString("java.util.Arrays");
                this->name=new JString("java.util.Arrays");
                this->simpleName=new JString("Arrays");
            }

            virtual jcpp::lang::JClass* getSuperclass(){
                return JObject::getClazz();
            }
        };

        static jcpp::lang::JClass* clazz;

        jcpp::lang::JClass* JArrays::getClazz(){
            if (clazz==null){
                clazz=new JArraysClass();
            }
            return clazz;
        }

        JList* JArrays::asList(JPrimitiveObjectArray* a){
            JList* args=new JArrayList();
            if (a!=null){
                for (jint i=0;i<a->size();i++){
                    args->add(a->get(i));
                }
            }
            return args;
        }

        JPrimitiveByteArray* JArrays::copyOf(JPrimitiveByteArray* a, jint size){
            JPrimitiveByteArray* newa=new JPrimitiveByteArray(size);
            jint m=(a->size()<size ? a->size() : size);
            for (jint i=0;i<m;i++){
                newa->setByte(i,a->getByte(i));
            }
            return newa;
        }

        JPrimitiveCharArray* JArrays::copyOf(JPrimitiveCharArray* a, jint size){
            JPrimitiveCharArray* newa=new JPrimitiveCharArray(size);
            jint m=(a->size()<size ? a->size() : size);
            for (jint i=0;i<m;i++){
                newa->setChar(i,a->getChar(i));
            }
            return newa;
        }

        JPrimitiveObjectArray* JArrays::copyOf(JPrimitiveObjectArray* a, jint size){
            JPrimitiveObjectArray* newa=new JPrimitiveObjectArray(a->getComponentType(),size);
            jint m=(a->size()<size ? a->size() : size);
            for (jint i=0;i<m;i++){
                newa->set(i,a->get(i));
            }
            return newa;
        }

        JPrimitiveObjectArray* JArrays::copyOf(JPrimitiveObjectArray* a, jint size,jcpp::lang::JClass* newType){
            JPrimitiveObjectArray* newa=new JPrimitiveObjectArray(newType,size);
            jint m=(a->size()<size ? a->size() : size);
            for (jint i=0;i<m;i++){
                newa->set(i,a->get(i));
            }
            return newa;
        }

        static jbool compareFunc(JObject* f1,JObject* f2) {
            JComparable* comp=dynamic_cast<JComparable*>(f1);
            return comp->compareTo(f2)<0;
        }

        void JArrays::sort(JPrimitiveObjectArray* a){
            vector<JObject*> fields;
            for (jint  i=0;i<a->size();i++){
                JObject* o=a->get(i);
                fields.push_back(o);
            }
            std::sort(fields.begin(),fields.end(),compareFunc);
            for (jint i = 0; i < fields.size(); i++) {
                JObject* o=fields.at(i);
                a->set(i,o);
            }
        }

        class SortUsingComaparatorClass{
        protected:
            JComparator* c;
        public:
            SortUsingComaparatorClass(JComparator* c){
                this->c=c;
            }

            jbool operator()(JObject* f1, JObject* f2){
                return c->compare(f1,f2)<0;
            }
        };

        void JArrays::sort(JPrimitiveObjectArray* a, JComparator* c){
            vector<JObject*> fields;
            for (jint  i=0;i<a->size();i++){
                JObject* o=a->get(i);
                fields.push_back(o);
            }
            SortUsingComaparatorClass compClass(c);
            std::sort(fields.begin(),fields.end(),compClass);
            for (jint i = 0; i < fields.size(); i++) {
                JObject* o=fields.at(i);
                a->set(i,o);
            }
        }

        void JArrays::fill(JPrimitiveIntArray* a,jint v){
            for (jint i=0;i<a->size();i++){
                a->setInt(i,v);
            }
        }

        void JArrays::fill(JPrimitiveCharArray* a,jchar v){
            for (jint i=0;i<a->size();i++){
                a->setChar(i,v);
            }
        }

        void JArrays::fill(JPrimitiveObjectArray* a,jint start,jint end,JObject* val){
            for (jint i=start;i<end;i++){
                a->set(i,val);
            }
        }

        JArrays::~JArrays(){
        }
    }
}
