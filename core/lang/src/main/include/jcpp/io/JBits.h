#ifndef JCPP_IO_JBITS_H
#define JCPP_IO_JBITS_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JPrimitiveByteArray.h"

using namespace jcpp::lang;



namespace jcpp{
    namespace io{

        //@Class(canonicalName="java.io.Bits", simpleName="Bits");
        class JCPP_EXPORT JBits : public JObject{
        public:
            static jcpp::lang::JClass* getClazz();

            static jbool getBoolean(JPrimitiveByteArray* b, jint off) {
                return (b->getByte(off) != 0);
            }

            static jchar getChar(JPrimitiveByteArray* b, jint off, jbool bigEndian){
            	if(bigEndian){
            		 return (jchar)(((b->getByte(off + 1) & 0xFF)) +
            		                               ((b->getByte(off + 0)) << 8));
            	}else{
            		 return (jchar)(((b->getByte(off + 0) & 0xFF)) +
            		                               ((b->getByte(off + 1)) << 8));
            	}
            }

            static jchar getChar(JPrimitiveByteArray* b,jint off){
                return getChar(b,off,true);
            }

            static jshort getShort(JPrimitiveByteArray* b, jint off) {
                return (jshort) (((b->getByte(off + 1) & 0xFF)) + 
                                 ((b->getByte(off + 0)) << 8));
            }

            static jint getInt(JPrimitiveByteArray* b, jint off) {
                return ((b->getByte(off + 3) & (jint) 0xFF)) +
                        ((b->getByte(off + 2) & (jint) 0xFF) << 8) +
                        ((b->getByte(off + 1) & (jint) 0xFF) << 16) +
                        (b->getByte(off + 0) << 24);
            }

            static jfloat getFloat(JPrimitiveByteArray* b, jint off) {
                jint i = ((b->getByte(off + 3) & (jint) 0xFF)) +
                         ((b->getByte(off + 2) & (jint) 0xFF) << 8) +
                         ((b->getByte(off + 1) & (jint) 0xFF) << 16) +
                          (b->getByte(off + 0) << 24);
                return *(reinterpret_cast<jfloat*> (&i));
            }

            static jlong getLong(JPrimitiveByteArray *b, jint off) {
                    return ((b->getByte(off + 7) & (jlong) 0xFFL)) +
                           ((b->getByte(off + 6) & (jlong) 0xFFL) << 8) +
                           ((b->getByte(off + 5) & (jlong) 0xFFL) << 16) +
                           ((b->getByte(off + 4) & (jlong) 0xFFL) << 24) +
                           ((b->getByte(off + 3) & (jlong) 0xFFL) << 32) +
                           ((b->getByte(off + 2) & (jlong) 0xFFL) << 40) +
                           ((b->getByte(off + 1) & (jlong) 0xFFL) << 48) +
                           (((jlong) b->getByte(off + 0)) << 56);
            }

            static jdouble getDouble (JPrimitiveByteArray *b, jint off) {
                jlong j = ((b->getByte(off + 7) & (jlong)0xFFL)) +
                          ((b->getByte(off + 6) & (jlong)0xFFL) << 8) +
                          ((b->getByte(off + 5) & (jlong)0xFFL) << 16) +
                          ((b->getByte(off + 4) & (jlong)0xFFL) << 24) +
                          ((b->getByte(off + 3) & (jlong)0xFFL) << 32) +
                          ((b->getByte(off + 2) & (jlong)0xFFL) << 40) +
                          ((b->getByte(off + 1) & (jlong)0xFFL) << 48) +
                          (((jlong) b->getByte(off + 0)) << 56);
                return *(reinterpret_cast<jdouble*> (&j));
            }

            static void putBoolean(JPrimitiveByteArray* b, jint off, jbool val) {
                b->setByte(off, (jbyte) (val ? 1 : 0));
            }

            static void putChar(JPrimitiveByteArray* b, jint off, jchar val, jbool bigEndian){
            	if (bigEndian){
            		b->setByte(off + 1, (jbyte) (val ));
            		b->setByte(off + 0, (jbyte) (val >> 8));
            	}else{
            		b->setByte(off + 0, (jbyte) (val ));
            		b->setByte(off + 1, (jbyte) (val >> 8));
            	}
            }

            static void putChar(JPrimitiveByteArray* b, jint off, jchar val) {
                putChar(b, off, val, true);
            }

            static void putShort(JPrimitiveByteArray* b, jint off, jshort val) {
                b->setByte(off + 1, (jbyte) (val    ));
                b->setByte(off + 0, (jbyte) (val >> 8));
            }

            static void putInt(JPrimitiveByteArray* b, jint off, jint val) {
                b->setByte(off + 3, (jbyte) (val));
                b->setByte(off + 2, (jbyte) (val >> 8));
                b->setByte(off + 1, (jbyte) (val >> 16));
                b->setByte(off + 0, (jbyte) (val >> 24));
            }

            static void putFloat(JPrimitiveByteArray* b, jint off, jfloat val) {
                jint* i = reinterpret_cast<jint*>(&val);
                b->setByte(off + 3, (jbyte) (*i));
                b->setByte(off + 2, (jbyte) (*i >> 8));
                b->setByte(off + 1, (jbyte) (*i >> 16));
                b->setByte(off + 0, (jbyte) (*i >> 24));
            }

            static void putLong(JPrimitiveByteArray* b, jint off, jlong val) {
                b->setByte(off + 7, (jbyte) (val));
                b->setByte(off + 6, (jbyte) (val >> 8));
                b->setByte(off + 5, (jbyte) (val >> 16));
                b->setByte(off + 4, (jbyte) (val >> 24));
                b->setByte(off + 3, (jbyte) (val >> 32));
                b->setByte(off + 2, (jbyte) (val >> 40));
                b->setByte(off + 1, (jbyte) (val >> 48));
                b->setByte(off + 0, (jbyte) (val >> 56));
            }

            static void putDouble(JPrimitiveByteArray* b, jint off, jdouble val) {
                jlong* j = reinterpret_cast<jlong*>(&val);
                b->setByte(off + 7, (jbyte) (*j));
                b->setByte(off + 6, (jbyte) (*j >> 8));
                b->setByte(off + 5, (jbyte) (*j >> 16));
                b->setByte(off + 4, (jbyte) (*j >> 24));
                b->setByte(off + 3, (jbyte) (*j >> 32));
                b->setByte(off + 2, (jbyte) (*j >> 40));
                b->setByte(off + 1, (jbyte) (*j >> 48));
                b->setByte(off + 0, (jbyte) (*j >> 56));
            }
        };
    }
}

#endif
