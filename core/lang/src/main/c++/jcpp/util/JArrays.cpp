#include "jcpp/util/JArrays.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/util/JArrayList.h"
#include "jcpp/lang/JstringBuilder.h"
#include <vector>
#include <algorithm>

using namespace jcpp::util;

namespace jcpp{
    namespace util{

    	//--------------------
    	//	PRIVATE
    	//--------------------
    	jint JArrays::binarySearch0(JPrimitiveObjectArray* a, jint fromIndex, jint toIndex, JObject* key, JComparator* c){
    		if(c == null){
    			//TODO: check source
    		}

    		int low = fromIndex;
    		int high = toIndex - 1;

    		while(low <= high){
    			int mid = (low + high)/2;
    			JObject* midVal = a->get(mid);
    			int cmp = c->compare(midVal, key);
    			if(cmp < 0)
    			low = mid + 1;
    			else if(cmp > 0)
    				high = mid - 1;
    			else
    				return mid;
    		}
    		return -(low + 1);
    	}


    	//---------------------
    	//	PUBLIC
    	//---------------------
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

        jint JArrays::binarySearch(JPrimitiveObjectArray* a, JObject* key, JComparator* c){
        	return binarySearch0(a, 0, a->size(), key, c);
        }

        jbool JArrays::deepEquals(JPrimitiveObjectArray* a1, JPrimitiveObjectArray* a2){
        	if(a1 == a2)
        		return true;
        	if(a1 == null || a2 == null)
        		return false;
        	int length = a1->size();
        	if(a2->size() != length)
        		return false;

        	for(int i = 0; i < length; i++){
        		JObject* e1 = a1->get(i);
        		JObject* e2 = a2->get(i);

        		if(e1 == e2)
        			continue;
        		if(e1 == null)
        			return false;

        		jbool eq;
        		if((e1->getClass()->isAssignableFrom(JPrimitiveObjectArray::getClazz())) && (e2->getClass()->isAssignableFrom(JPrimitiveObjectArray::getClazz())))
        			eq = deepEquals(dynamic_cast<JPrimitiveObjectArray*>(e1), dynamic_cast<JPrimitiveObjectArray*>(e2));

        		else if((e1->getClass()->isAssignableFrom(JPrimitiveByteArray::getClazz())) && (e2->getClass()->isAssignableFrom(JPrimitiveByteArray::getClazz())))
        			eq = equals(dynamic_cast<JPrimitiveByteArray*>(e1), dynamic_cast<JPrimitiveByteArray*>(e2));

        		else if((e1->getClass()->isAssignableFrom(JPrimitiveByteArray::getClazz())) && (e2->getClass()->isAssignableFrom(JPrimitiveByteArray::getClazz())))
					eq = equals(dynamic_cast<JPrimitiveByteArray*>(e1), dynamic_cast<JPrimitiveByteArray*>(e2));

        		else if((e1->getClass()->isAssignableFrom(JPrimitiveShortArray::getClazz())) && (e2->getClass()->isAssignableFrom(JPrimitiveShortArray::getClazz())))
					eq = equals(dynamic_cast<JPrimitiveShortArray*>(e1), dynamic_cast<JPrimitiveShortArray*>(e2));

        		else if((e1->getClass()->isAssignableFrom(JPrimitiveIntArray::getClazz())) && (e2->getClass()->isAssignableFrom(JPrimitiveIntArray::getClazz())))
					eq = equals(dynamic_cast<JPrimitiveIntArray*>(e1), dynamic_cast<JPrimitiveIntArray*>(e2));

        		else if((e1->getClass()->isAssignableFrom(JPrimitiveLongArray::getClazz())) && (e2->getClass()->isAssignableFrom(JPrimitiveLongArray::getClazz())))
					eq = equals(dynamic_cast<JPrimitiveLongArray*>(e1), dynamic_cast<JPrimitiveLongArray*>(e2));

        		else if((e1->getClass()->isAssignableFrom(JPrimitiveCharArray::getClazz())) && (e2->getClass()->isAssignableFrom(JPrimitiveCharArray::getClazz())))
					eq = equals(dynamic_cast<JPrimitiveCharArray*>(e1), dynamic_cast<JPrimitiveCharArray*>(e2));

        		else if((e1->getClass()->isAssignableFrom(JPrimitiveFloatArray::getClazz())) && (e2->getClass()->isAssignableFrom(JPrimitiveFloatArray::getClazz())))
					eq = equals(dynamic_cast<JPrimitiveFloatArray*>(e1), dynamic_cast<JPrimitiveFloatArray*>(e2));

        		else if((e1->getClass()->isAssignableFrom(JPrimitiveDoubleArray::getClazz())) && (e2->getClass()->isAssignableFrom(JPrimitiveDoubleArray::getClazz())))
					eq = equals(dynamic_cast<JPrimitiveDoubleArray*>(e1), dynamic_cast<JPrimitiveDoubleArray*>(e2));

        		else if((e1->getClass()->isAssignableFrom(JPrimitiveBooleanArray::getClazz())) && (e2->getClass()->isAssignableFrom(JPrimitiveBooleanArray::getClazz())))
					eq = equals(dynamic_cast<JPrimitiveBooleanArray*>(e1), dynamic_cast<JPrimitiveBooleanArray*>(e2));

        		else
        			eq = e1->equals(e2);

        	}
        	return true;
        }

        JString* JArrays::toStringStatic(JPrimitiveObjectArray* a){
        	if(a == null)
        		return null;
        	jint iMax = a->size() - 1;
        	if(iMax == -1)
        		return new JString("[]");
        	JStringBuilder* b = new JStringBuilder();
        	b->append('[');
        	for(jint i = 0; ; i++){
        		b->append(JString::valueOf(a->get(i)));
        		if(i == iMax)
        			return b->append(']')->toString();
        		b->append(', ');
        	}
        	return null;
        }


        JArrays::~JArrays(){
        }
    }
}
