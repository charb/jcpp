#include "jcpp/lang/JStringBuffer.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JPrimitiveArray.h"
#include "jcpp/lang/JPrimitiveCharArray.h"
#include "jcpp/lang/JPrimitiveChar.h"
#include "jcpp/lang/JInteger.h"
#include "jcpp/lang/JBoolean.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/util/JList.h"
#include "jcpp/io/JObjectStreamField.h"
#include "jcpp/io/JObjectInputStream.h"
#include "jcpp/io/JObjectOutputStream.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang::reflect;
using namespace jcpp::io;

namespace jcpp{
    namespace lang{

        JPrimitiveObjectArray* JStringBuffer::serialPersistentFields = null;

        JPrimitiveObjectArray* JStringBuffer::getSerialPersistentFields(){
            if (serialPersistentFields==null){
                serialPersistentFields=new JPrimitiveObjectArray(JObjectStreamField::getClazz(),3);
                serialPersistentFields->set(0,new JObjectStreamField(new JString("value"),JPrimitiveCharArray::getClazz()));
                serialPersistentFields->set(1,new JObjectStreamField(new JString("count"),JPrimitiveInt::getClazz()));
                serialPersistentFields->set(2,new JObjectStreamField(new JString("shared"),JBoolean::TYPE));
            }
            return serialPersistentFields;
        }

        JStringBuffer::JStringBuffer():JAbstractStringBuilder(getClazz()){
        }

        JStringBuffer::JStringBuffer(JString* str):JAbstractStringBuilder(getClazz()){
            append(str);
        }

        JStringBuffer::JStringBuffer(JCharSequence* cs):JAbstractStringBuilder(getClazz()){
            append(cs);
        }

        jint JStringBuffer::length(){
            synchronized(this,{
                jint i=JAbstractStringBuilder::length();
                return i;
            })
        }

        jint JStringBuffer::capacity(){
            synchronized(this,{
                jint i=JAbstractStringBuilder::capacity();
                return i;
            })
        }

        void JStringBuffer::ensureCapacity(jint c){
            synchronized(this,{
                JAbstractStringBuilder::ensureCapacity(c);
            })
        }

        void JStringBuffer::trimToSize(){
            synchronized(this,{
                JAbstractStringBuilder::trimToSize();
            })
        }

        void JStringBuffer::setLength(jint l){
            synchronized(this,{
                JAbstractStringBuilder::setLength(l);
            })
        }

        jchar JStringBuffer::charAt(jint index){
            synchronized(this,{
                jchar c=JAbstractStringBuilder::charAt(index);
                return c;
            })
        }

        void JStringBuffer::getChars(jint srcBegin,jint srcEnd,JPrimitiveCharArray* dst,jint dstBegin){
            synchronized(this,{
                JAbstractStringBuilder::getChars(srcBegin,srcEnd,dst,dstBegin);
            })
        }

        void JStringBuffer::setCharAt(jint index,jchar c){
            synchronized(this,{
                JAbstractStringBuilder::setCharAt(index,c);
            })
        }

        JStringBuffer* JStringBuffer::append(JObject* o){
            synchronized(this,{
                JAbstractStringBuilder::append(o);
                return this;
            })
        }

        JStringBuffer* JStringBuffer::append(JString* o){
            synchronized(this,{
                JAbstractStringBuilder::append(o);
                return this;
            })
        }

        JStringBuffer* JStringBuffer::append(JStringBuffer* sb){
            synchronized(this,{
                JAbstractStringBuilder::append(sb);
                return this;
            })
        }

        JStringBuffer* JStringBuffer::append(JCharSequence* s){
            synchronized(this,{
                JAbstractStringBuilder::append(s);
                return this;
            })
        }

        JStringBuffer* JStringBuffer::append(JCharSequence* s,jint start,jint end){
            synchronized(this,{
                JAbstractStringBuilder::append(s,start,end);
                return this;
            })
        }

        JStringBuffer* JStringBuffer::append(JPrimitiveCharArray* str,jint offset,jint length){
            synchronized(this,{
                JAbstractStringBuilder::append(str,offset,length);
                return this;
            })
        }

        JStringBuffer* JStringBuffer::append(jbool b){
            synchronized(this,{
                JAbstractStringBuilder::append(b);
                return this;
            })
        }

        JStringBuffer* JStringBuffer::append(jchar c){
            synchronized(this,{
                JAbstractStringBuilder::append(c);
                return this;
            })
        }

        JStringBuffer* JStringBuffer::append(jint i){
            synchronized(this,{
                JAbstractStringBuilder::append(i);
                return this;
            })
        }

        JStringBuffer* JStringBuffer::append(jlong l){
            synchronized(this,{
                JAbstractStringBuilder::append(l);
                return this;
            })
        }

        JStringBuffer* JStringBuffer::append(jfloat f){
            synchronized(this,{
                JAbstractStringBuilder::append(f);
                return this;
            })
        }

        JStringBuffer* JStringBuffer::append(jdouble d){
            synchronized(this,{
                JAbstractStringBuilder::append(d);
                return this;
            })
        }

        JStringBuffer* JStringBuffer::append(JString* str,jint offset,jint length){
            synchronized(this,{
                JAbstractStringBuilder::append(str,offset,length);
                return this;
            })
        }

        JStringBuffer* JStringBuffer::append(const char * str) {
        	synchronized(this,{
				JAbstractStringBuilder::append(str);
				return this;
			})
        }

        JStringBuffer* JStringBuffer::append(const wchar_t* wstr) {
        	synchronized(this,{
				JAbstractStringBuilder::append(wstr);
				return this;
			})
        }

        JStringBuffer* JStringBuffer::deleteChar(jint start,jint end){
            synchronized(this,{
                JAbstractStringBuilder::deleteChar(start,end);
                return this;
            })
        }

        JStringBuffer* JStringBuffer::deleteCharAt(jint index){
            synchronized(this,{
                JAbstractStringBuilder::deleteCharAt(index);
                return this;
            })
        }

        JStringBuffer* JStringBuffer::replace(jint start,jint end,JString* str){
            synchronized(this,{
                JAbstractStringBuilder::replace(start,end,str);
                return this;
            })
        }

        JString* JStringBuffer::substring(jint start){
            synchronized(this,{
                JString* str=JAbstractStringBuilder::substring(start);
                return str;
            })
        }

        JCharSequence* JStringBuffer::subSequence(jint start,jint end){
            synchronized(this,{
                JCharSequence* s=JAbstractStringBuilder::subSequence(start,end);
                return s;
            })
        }

        JString* JStringBuffer::substring(jint start,jint end){
            synchronized(this,{
                JString* str=JAbstractStringBuilder::substring(start,end);
                return str;
            })
        }

        JStringBuffer* JStringBuffer::insert(jint index,JPrimitiveCharArray* str,jint offset,jint len){
            synchronized(this,{
                JAbstractStringBuilder::insert(index,str,offset,len);
                return this;
            })
        }

        JStringBuffer* JStringBuffer::insert(jint offset,JObject* o){
            synchronized(this,{
                JAbstractStringBuilder::insert(offset,o);
                return this;
            })
        }

        JStringBuffer* JStringBuffer::insert(jint offset,JString* str){
            synchronized(this,{
                JAbstractStringBuilder::insert(offset,str);
                return this;
            })
        }

        JStringBuffer* JStringBuffer::insert(jint offset,JCharSequence* s){
            synchronized(this,{
                JAbstractStringBuilder::insert(offset,s);
                return this;
            })
        }

        JStringBuffer* JStringBuffer::insert(jint offset,JCharSequence* s,jint start,jint end){
            synchronized(this,{
                JAbstractStringBuilder::insert(offset,s,start,end);
                return this;
            })
        }

        JStringBuffer* JStringBuffer::insert(jint offset,const char * str) {
        	synchronized(this,{
				JAbstractStringBuilder::insert(offset,str);
				return this;
			})
        }

        JStringBuffer* JStringBuffer::insert(jint offset,const wchar_t* wstr) {
        	synchronized(this,{
				JAbstractStringBuilder::insert(offset,wstr);
				return this;
			})
        }

        JStringBuffer* JStringBuffer::insert(jint offset,jbool b){
            synchronized(this,{
                JAbstractStringBuilder::insert(offset,b);
                return this;
            })
        }

        JStringBuffer* JStringBuffer::insert(jint offset,jchar c){
            synchronized(this,{
                JAbstractStringBuilder::insert(offset,c);
                return this;
            })
        }

        JStringBuffer* JStringBuffer::insert(jint offset,jint i){
            synchronized(this,{
                JAbstractStringBuilder::insert(offset,i);
                return this;
            })
        }

        JStringBuffer* JStringBuffer::insert(jint offset,jlong l){
            synchronized(this,{
                JAbstractStringBuilder::insert(offset,l);
                return this;
            })
        }

        JStringBuffer* JStringBuffer::insert(jint offset,jfloat f){
            synchronized(this,{
                JAbstractStringBuilder::insert(offset,f);
                return this;
            })
        }

        JStringBuffer* JStringBuffer::insert(jint offset,jdouble d){
            synchronized(this,{
                JAbstractStringBuilder::insert(offset,d);
                return this;
            })
        }

        jint JStringBuffer::indexOf(JString* str){
            synchronized(this,{
                jint i=JAbstractStringBuilder::indexOf(str);
                return i;
            })
        }

        jint JStringBuffer::indexOf(JString* str,jint fromIndex){
            synchronized(this,{
                jint i=JAbstractStringBuilder::indexOf(str,fromIndex);
                return i;
            })
        }

        jint JStringBuffer::lastIndexOf(JString* str){
            synchronized(this,{
                jint i=JAbstractStringBuilder::lastIndexOf(str);
                return i;
            })
        }

        jint JStringBuffer::lastIndexOf(JString* str,jint fromIndex){
            synchronized(this,{
                jint i=JAbstractStringBuilder::lastIndexOf(str,fromIndex);
                return i;
            })
        }

        JStringBuffer* JStringBuffer::reverse(){
            synchronized(this,{
                JAbstractStringBuilder::reverse();
                return this;
            })
        }

        JString* JStringBuffer::toString(){
            synchronized(this,{
                JString* str=JAbstractStringBuilder::toString();
                return str;
            })
        }

        void JStringBuffer::writeObject(JObjectOutputStream* out){
            JObjectOutputStream::JPutField* fields = out->putFields();
            fields->put(new JString("value"), value);
            fields->put(new JString("count"), count->get());
            fields->put(new JString("shared"), false);
            out->writeFields();
        }

        void JStringBuffer::readObject(JObjectInputStream* in){
            JObjectInputStream::JGetField* fields = in->readFields();
            value=dynamic_cast<JPrimitiveCharArray*>(fields->get(new JString("value"), (JObject*)null));
            count=new JPrimitiveInt(fields->get(new JString("count"), (jint)0));
        }

        JStringBuffer::~JStringBuffer(){
        }
    }
}
