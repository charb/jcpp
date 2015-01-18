#ifndef JCPP_UTIL_JARRAYS_H
#define JCPP_UTIL_JARRAYS_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JPrimitiveByteArray.h"
#include "jcpp/lang/JPrimitiveCharArray.h"
#include "jcpp/lang/JPrimitiveIntArray.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "jcpp/lang/JPrimitiveLongArray.h"
#include "jcpp/lang/JPrimitiveFloatArray.h"
#include "jcpp/lang/JPrimitiveShortArray.h"
#include "jcpp/lang/JPrimitiveBooleanArray.h"
#include "jcpp/lang/JPrimitiveDoubleArray.h"
#include "jcpp/util/JComparator.h"
#include "jcpp/util/JList.h"

namespace jcpp{
    namespace util{

    	// @Class(canonicalName="java.util.Arrays", simpleName="Arrays");
        class JCPP_EXPORT JArrays : public JObject{
        public:
            static jcpp::lang::JClass* getClazz();

            static JList* asList(JPrimitiveObjectArray* a);

            static JPrimitiveByteArray* copyOf(JPrimitiveByteArray* a, jint size);

            static JPrimitiveCharArray* copyOf(JPrimitiveCharArray* a, jint size);

            static JPrimitiveObjectArray* copyOf(JPrimitiveObjectArray* a, jint size);

            static JPrimitiveObjectArray* copyOf(JPrimitiveObjectArray* a, jint size,jcpp::lang::JClass* newType);

            static jbool equals(JPrimitiveObjectArray* a1, JPrimitiveObjectArray* a2);

            static jbool equals(JPrimitiveBooleanArray* a1, JPrimitiveBooleanArray* a2);            

            static jbool equals(JPrimitiveByteArray* a1, JPrimitiveByteArray* a2);            

            static jbool equals(JPrimitiveCharArray* a1, JPrimitiveCharArray* a2);            

            static jbool equals(JPrimitiveIntArray* a1, JPrimitiveIntArray* a2);     

            static jbool equals(JPrimitiveLongArray* a1, JPrimitiveLongArray* a2);            

            static jbool equals(JPrimitiveFloatArray* a1, JPrimitiveFloatArray* a2);            

            static jbool equals(JPrimitiveShortArray* a1, JPrimitiveShortArray* a2);

            static jbool equals(JPrimitiveDoubleArray* a1, JPrimitiveDoubleArray* a2);

            static void sort(JPrimitiveObjectArray* a);

            static void sort(JPrimitiveObjectArray* a, JComparator* c);

            static void fill(JPrimitiveIntArray* a,jint v);

            static void fill(JPrimitiveCharArray* a,jchar v);

            static void fill(JPrimitiveObjectArray* a,jint start,jint end,JObject* val);

            virtual ~JArrays();
        };
    }
}

#endif
