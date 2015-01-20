#include "jcpp/util/JArrays.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/util/JArrayList.h"
#include <vector>
#include <algorithm>

namespace jcpp{
    namespace util{

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

        jbool JArrays::equals(JPrimitiveObjectArray* a1, JPrimitiveObjectArray* a2){
            if (a1->size()!=a2->size()){
                return false;
            }
            for (jint i=0;i<a1->size();i++){
                if (a1->get(i)==null){
                    if (a2->get(i)!=null){
                        return false;
                    }
                }else{
                    if (a2->get(i)==null || !(a1->get(i)->equals(a2->get(i)))) {
                        return false;
                    }
                }
            }

            return true;
        }

        jbool JArrays::equals(JPrimitiveByteArray* a1, JPrimitiveByteArray* a2){
            if (a1->size()!=a2->size()){
                return false;
            }
            for (jint i=0;i<a1->size();i++){
                if (a1->getByte(i)!=a2->getByte(i)){
                    return false;
                }
            }
            return true;
        }         

        jbool JArrays::equals(JPrimitiveBooleanArray* a1, JPrimitiveBooleanArray* a2){
            if (a1->size()!=a2->size()){
                return false;
            }
            for (jint i=0;i<a1->size();i++){
                if (a1->getBoolean(i)!=a2->getBoolean(i)){
                    return false;
                }
            }
            return true;
        }   

        jbool JArrays::equals(JPrimitiveCharArray* a1, JPrimitiveCharArray* a2){
            if (a1->size()!=a2->size()){
                return false;
            }
            for (jint i=0;i<a1->size();i++){
                if (a1->getChar(i)!=a2->getChar(i)){
                    return false;
                }
            }
            return true;
        }

        jbool JArrays::equals(JPrimitiveIntArray* a1, JPrimitiveIntArray* a2){
            if (a1->size()!=a2->size()){
                return false;
            }
            for (jint i=0;i<a1->size();i++){
                if (a1->getInt(i)!=a2->getInt(i)){
                    return false;
                }
            }
            return true;
        }    

        jbool JArrays::equals(JPrimitiveLongArray* a1, JPrimitiveLongArray* a2){
            if (a1->size()!=a2->size()){
                return false;
            }
            for (jint i=0;i<a1->size();i++){
                if (a1->getLong(i)!=a2->getLong(i)){
                    return false;
                }
            }
            return true;
        }    

        jbool JArrays::equals(JPrimitiveFloatArray* a1, JPrimitiveFloatArray* a2){
            if (a1->size()!=a2->size()){
                return false;
            }
            for (jint i=0;i<a1->size();i++){
                if (a1->getFloat(i)!=a2->getFloat(i)){
                    return false;
                }
            }
            return true;
        }            

        jbool JArrays::equals(JPrimitiveShortArray* a1, JPrimitiveShortArray* a2){
            if (a1->size()!=a2->size()){
                return false;
            }
            for (jint i=0;i<a1->size();i++){
                if (a1->getShort(i)!=a2->getShort(i)){
                    return false;
                }
            }
            return true;
        }

        jbool JArrays::equals(JPrimitiveDoubleArray* a1, JPrimitiveDoubleArray* a2){
            if (a1->size()!=a2->size()){
                return false;
            }
            for (jint i=0;i<a1->size();i++){
                if (a1->getDouble(i)!=a2->getDouble(i)){
                    return false;
                }
            }
            return true;
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

        // @IgnoreReflection()
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
