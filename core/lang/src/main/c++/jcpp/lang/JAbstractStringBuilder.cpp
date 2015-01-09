#include "jcpp/lang/JAbstractStringBuilder.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JStringBuffer.h"
#include "jcpp/lang/JPrimitiveChar.h"
#include "jcpp/lang/JOutOfMemoryError.h"
#include "jcpp/lang/JIndexOutOfBoundsException.h"
#include "jcpp/lang/JStringIndexOutOfBoundsException.h"
#include "jcpp/lang/JArrayIndexOutOfBoundsException.h"

#include <sstream>
#include <string.h>

using namespace std;

using jcpp::native::api::NativeString;

namespace jcpp{
    namespace lang{
        class JAbstractStringBuilderClass : public jcpp::lang::JClass{
            public:
                JAbstractStringBuilderClass():jcpp::lang::JClass(){
                    this->canonicalName=new JString("java.lang.AbstractStringBuilder");
                    this->name=new JString("java.lang.AbstractStringBuilder");
                    this->simpleName=new JString("AbstractStringBuilder");
                }

                virtual void initialize(){
                    addInterface(JAppendable::getClazz());
                    addInterface(JCharSequence::getClazz());
                }

                virtual jcpp::lang::JClass* getSuperclass(){
                    return JObject::getClazz();
                }
        };

        static jcpp::lang::JClass* clazz;

        jcpp::lang::JClass* JAbstractStringBuilder::getClazz(){
            if (clazz==null){
                clazz=new JAbstractStringBuilderClass();
            }
            return clazz;
        }

        JAbstractStringBuilder::JAbstractStringBuilder(jcpp::lang::JClass* _class):JObject(_class){
        	count = new JPrimitiveInt(0);
        	bufferCapacity = 16;
        	value = new JPrimitiveCharArray(bufferCapacity);
        }

        jint JAbstractStringBuilder::length(){
            return count->get();
        }

        jint JAbstractStringBuilder::capacity(){
            return bufferCapacity;
        }

        void JAbstractStringBuilder::ensureCapacityInternal(jint minimumCapacity){
			if(minimumCapacity - bufferCapacity > 0) {
				jint newCapacity = bufferCapacity * 2 + 2;
				if(newCapacity - minimumCapacity < 0) {
					newCapacity = minimumCapacity;
				}
				if (newCapacity < 0) {
					if (minimumCapacity < 0) {
						throw new JOutOfMemoryError();
					}
					newCapacity = JINT_MAX;
				}
				JPrimitiveCharArray * newValue = new JPrimitiveCharArray(newCapacity);
				for(jint i = 0; i < count->get(); i++) {
					newValue->setChar(i, value->getChar(i));
				}
				value = newValue;
				bufferCapacity = newCapacity;
			}
		}

        void JAbstractStringBuilder::ensureCapacity(jint minimumCapacity){
        	if(minimumCapacity > 0) {
        		ensureCapacityInternal(minimumCapacity);
        	}
        }

        void JAbstractStringBuilder::trimToSize(){
        	if(count->get() < bufferCapacity) {
        		JPrimitiveCharArray * newValue = new JPrimitiveCharArray(count->get());
				for(jint i = 0; i < count->get(); i++) {
					newValue->setChar(i,value->getChar(i));
				}
				value = newValue;
				bufferCapacity = count->get();
        	}
        }

        void JAbstractStringBuilder::setLength(jint newLength){
        	if(newLength < 0) {
        		throw new JStringIndexOutOfBoundsException();
        	}
        	ensureCapacityInternal(newLength);
        	if(count->get() < newLength) {
        		for(; count->get() < newLength; count->set(count->get()+1)) {
        			value->setChar(count->get(), 0);
        		}
        	} else {
        		count->set(newLength);
        	}
        }

        jchar JAbstractStringBuilder::charAt(jint index){
            if ((index < 0) || (index >= count->get())) {
                throw new JStringIndexOutOfBoundsException();
            }
            return value->getChar(index);
        }

        void JAbstractStringBuilder::getChars(jint srcBegin,jint srcEnd,JPrimitiveCharArray* dst,jint dstBegin){
            if (srcBegin < 0)
                throw new JStringIndexOutOfBoundsException(new JString(NativeString::valueOf(srcBegin)));
            if ((srcEnd < 0) || (srcEnd > count->get()))
                throw new JStringIndexOutOfBoundsException(new JString(NativeString::valueOf(srcEnd)));
            if (srcBegin > srcEnd)
                throw new JStringIndexOutOfBoundsException(new JString("srcBegin > srcEnd"));

        	for(jint i = srcBegin; i < srcEnd; i++) {
        		dst->setChar(dstBegin++, value->getChar(i));
        	}
        }

        void JAbstractStringBuilder::setCharAt(jint index,jchar c){
        	 if ((index < 0) || (index >= count->get()))
        		 throw new JStringIndexOutOfBoundsException(new JString(NativeString::valueOf(index)));
        	 value->setChar(index, c);
        }

        JAbstractStringBuilder* JAbstractStringBuilder::append(JObject* o){
            return append(JString::valueOf(o));
        }

        JAbstractStringBuilder* JAbstractStringBuilder::append(JString* str){
        	if(str == null) {
        		str = new JString("null");
        	}
        	jint len = str->length();
        	ensureCapacityInternal(count->get() + len);
        	str->getChars(0, len, value, count->get());
        	count->set(count->get()+ len);
            return this;
        }

        JAbstractStringBuilder* JAbstractStringBuilder::append(JStringBuffer* sb){
        	if (sb == null) {
        		return append(new JString("null"));
        	}
        	jint len = sb->length();
        	ensureCapacityInternal(count->get() + len);
        	sb->getChars(0, len, value, count->get());
        	count->set(count->get()+len);
            return this;
        }

        JAbstractStringBuilder* JAbstractStringBuilder::append(JCharSequence* s){
            return append(s,0,s->length());
        }

        JAbstractStringBuilder* JAbstractStringBuilder::append(JCharSequence* s,jint start,jint end){
        	if(s == null) {
        		s = new JString("null");
        	}
        	if ((start < 0) || (start > end) || (end > s->length())) {
        		throw new JIndexOutOfBoundsException(new JString(NativeString("start ") + start + NativeString(", end ") + end + NativeString(", s.length() ") + s->length()));
        	}
        	jint len = end - start;
        	ensureCapacityInternal(count->get() + len);
        	for(jint i = start, j = count->get(); i < end; i++, j++) {
        		value->setChar(j, s->charAt(i));
        	}
        	count->set(count->get()+ len);
            return this;
        }

        JAbstractStringBuilder* JAbstractStringBuilder::append(JPrimitiveCharArray* str,jint offset,jint length){
        	if(length < 0) {
        		throw new JArrayIndexOutOfBoundsException(new JString(NativeString::valueOf(length)));
        	}
        	if(length > 0) {
        		ensureCapacityInternal(count->get() + length);
        		jint end = offset + length;
        		for(jint i = offset; i < end; i++) {
					value->setChar(count->get(), str->getChar(i));
                    count->set(count->get()+1);
				}
        	}
            return this;
        }

        JAbstractStringBuilder* JAbstractStringBuilder::append(JString* s,jint offset,jint length){
        	if(s == null) {
				s = new JString("null");
			}
        	if(length < 0) {
				throw new JArrayIndexOutOfBoundsException(new JString(NativeString::valueOf(length)));
			}
        	if(length > 0) {
				ensureCapacityInternal(count->get() + length);
				s->getChars(offset, offset + length, value, count->get());
				count->set(count->get()+ length);
			}
			return this;
        }

        JAbstractStringBuilder* JAbstractStringBuilder::append(const char * str)  {
        	jint length = strlen(str);
        	jint currentCount = count->get();
			ensureCapacityInternal(currentCount + length);
			for(jint i = 0; i < length; i++) {
				value->setChar(currentCount++, str[i]);
			}
        	count->set(currentCount);
        	return this;
        }

        JAbstractStringBuilder* JAbstractStringBuilder::append(const wchar_t* wstr) {
        	jint length = wcslen(wstr);
			jint currentCount = count->get();
			ensureCapacityInternal(currentCount + length);
			for(jint i = 0; i < length; i++) {
				value->setChar(currentCount++, wstr[i]);
			}
			count->set(currentCount);
			return this;
        }

        JAbstractStringBuilder* JAbstractStringBuilder::append(jbool b){
        	jint currentCount = count->get();
        	if (b) {
        		ensureCapacityInternal(currentCount + 4);
				value->setChar(currentCount++, 't');
				value->setChar(currentCount++, 'r');
				value->setChar(currentCount++, 'u');
				value->setChar(currentCount++, 'e');
			} else {
				ensureCapacityInternal(currentCount + 5);
				value->setChar(currentCount++, 'f');
				value->setChar(currentCount++, 'a');
				value->setChar(currentCount++, 'l');
				value->setChar(currentCount++, 's');
				value->setChar(currentCount++, 'e');
			}
        	count->set(currentCount);
			return this;
        }

        JAbstractStringBuilder* JAbstractStringBuilder::append(jchar c){
        	ensureCapacityInternal(count->get() + 1);
			value->setChar(count->get(), c);
            count->set(count->get()+1);
			return this;
        }

        inline void JAbstractStringBuilder::append(const std::string& str) {
        	jint length = str.length();
        	jint currentCount = count->get();
        	ensureCapacityInternal(currentCount + length);
        	for(jint i = 0; i < length; i++) {
        		value->setChar(currentCount++, str[i]);
        	}
        	count->set(currentCount);
        }

        JAbstractStringBuilder* JAbstractStringBuilder::append(jint i){
        	std::stringstream out;
        	out << i;
        	append(out.str());
            return this;
        }

        JAbstractStringBuilder* JAbstractStringBuilder::append(jlong l){
        	std::stringstream out;
			out << l;
			append(out.str());
        	return this;
        }

        JAbstractStringBuilder* JAbstractStringBuilder::append(jfloat f){
        	std::stringstream out;
			out << f;
			append(out.str());
        	return this;
        }

        JAbstractStringBuilder* JAbstractStringBuilder::append(jdouble d){
        	std::stringstream out;
			out << d;
			append(out.str());
        	return this;
        }

        JAbstractStringBuilder* JAbstractStringBuilder::deleteChar(jint start,jint end){
        	if (start < 0)
				throw new JStringIndexOutOfBoundsException(new JString(NativeString::valueOf(start)));
			if (end > count->get())
				end = count->get();
			if (start > end)
				throw new JStringIndexOutOfBoundsException();
			jint len = end - start;
			if (len > 0) {
				for(jint i = start + len; i < count->get(); i++) {
					value->setChar(i - len, value->getChar(i));
				}
				count->set(count->get()- len);
			}
			return this;
        }

        JAbstractStringBuilder* JAbstractStringBuilder::deleteCharAt(jint index){
        	if ((index < 0) || (index >= count->get()))
				throw new JStringIndexOutOfBoundsException(new JString(NativeString::valueOf(index)));
        	for(jint i = index + 1; i < count->get(); i++) {
        		value->setChar(i - 1, value->getChar(i));
        	}
			count->set(count->get()-1);
			return this;
        }

        JAbstractStringBuilder* JAbstractStringBuilder::replace(jint start,jint end,JString* str){
        	if (start < 0)
				throw new JStringIndexOutOfBoundsException(new JString(NativeString::valueOf(start)));
			if (start > count->get())
				throw new JStringIndexOutOfBoundsException(new JString("start > length()"));
			if (start > end)
				throw new JStringIndexOutOfBoundsException(new JString("start > end"));

			if (end > count->get()){
				end = count->get();
            }
			jint len = str->length();

			jint lengthToReplace = (end - start);
			jint newCount = count->get() + len - lengthToReplace;
			ensureCapacityInternal(newCount);

			if(lengthToReplace != len) {
				if(lengthToReplace < len) {
					jint dif = len - lengthToReplace;
					for(jint i = count->get() - 1; i >= end; i--) {
						value->setChar(i + dif, value->getChar(i));
					}
				} else {
					jint dif = lengthToReplace - len;
					for(jint i = end; i < count->get(); i++) {
						value->setChar(i - dif, value->getChar(i));
					}
				}
			}

			str->getChars(0, len, value, start);
			count->set(newCount);
			return this;
        }

        JString* JAbstractStringBuilder::substring(jint start){
            return substring(start, count->get());
        }

        JCharSequence* JAbstractStringBuilder::subSequence(jint start,jint end){
        	return substring(start, end);
        }

        JString* JAbstractStringBuilder::substring(jint start,jint end){
        	if (start < 0)
				throw new JStringIndexOutOfBoundsException(new JString(NativeString::valueOf(start)));
			if (end > count->get())
				throw new JStringIndexOutOfBoundsException(new JString(NativeString::valueOf(end)));
			if (start > end)
				throw new JStringIndexOutOfBoundsException(new JString(NativeString::valueOf(end - start)));
			return new JString(value, start, end - start);
        }

        JAbstractStringBuilder* JAbstractStringBuilder::insert(jint index,JPrimitiveCharArray* str,jint offset,jint len){
            if ((index < 0) || (index > length()))
                throw new JStringIndexOutOfBoundsException(new JString(NativeString::valueOf(index)));
            if ((offset < 0) || (len < 0) || (offset > str->size() - len))
                throw new JStringIndexOutOfBoundsException(new JString(NativeString("offset ") + offset + NativeString(", len ") + len + NativeString(", str.length ") + str->size()));

            ensureCapacityInternal(count->get() + len);

            for(jint i = count->get() -1; i >= index; i--) {
            	value->setChar(i + len, value->getChar(i));
            }

            for(jint i = 0; i < len; i++) {
            	value->setChar(index + i, str->getChar(offset + i));
            }
			count->set(count->get()+ len);
            return this;
        }

        JAbstractStringBuilder* JAbstractStringBuilder::insert(jint offset,JObject* o){
            return insert(offset,JString::valueOf(o));
        }

        JAbstractStringBuilder* JAbstractStringBuilder::insert(jint offset,JString* str){
        	if ((offset < 0) || (offset > length()))
				throw new JStringIndexOutOfBoundsException(new JString(NativeString::valueOf(offset)));
			if (str == null)
				str = new JString("null");
			jint len = str->length();
			ensureCapacityInternal(count->get() + len);

			for(jint i = count->get() -1; i >= offset; i--) {
				value->setChar(i + len, value->getChar(i));
			}
			str->getChars(0, len, value, offset);
			count->set(count->get()+ len);
			return this;
        }

        JAbstractStringBuilder* JAbstractStringBuilder::insert(jint offset,JCharSequence* s){
        	return s == null ? insert(offset , new JString("null")) : insert(offset,s,0,s->length());
        }

        JAbstractStringBuilder* JAbstractStringBuilder::insert(jint offset,JCharSequence* s,jint start,jint end){
            if (s == null) {
                s = new JString("null");
            }
            if ((offset < 0) || (offset > count->get()))
                throw new JIndexOutOfBoundsException(new JString(NativeString::valueOf(offset)));
            if ((start < 0) || (end < 0) || (start > end) || (end > s->length()))
                throw new JIndexOutOfBoundsException(new JString(NativeString("offset ") + offset + NativeString(", len ") + (end - start) + NativeString(", str.length ") + s->length()));
            jint len = end - start;
            ensureCapacityInternal(count->get() + len);

            for(jint i = count->get() -1; i >= offset; i--) {
            	value->setChar(i + len, value->getChar(i));
            }

            for (jint i=start; i<end; i++) {
                value->setChar(offset++, s->charAt(i));
            }
            count->set(count->get()+ len);

            return this;
        }

        JAbstractStringBuilder* JAbstractStringBuilder::insert(jint offset,const char * str) {
        	if ((offset < 0) || (offset > count->get()))
				throw new JIndexOutOfBoundsException(new JString(NativeString::valueOf(offset)));
			jint len = strlen(str);
			jint currentCount = count->get();
			ensureCapacityInternal(currentCount + len);
			for(jint i = currentCount -1; i >= offset; i--) {
				value->setChar(i + len, value->getChar(i));
			}
			for(jint i = 0; i < len; i++) {
				value->setChar(offset++, str[i]);
			}
			count->set(count->get()+ len);
			return this;
        }

        JAbstractStringBuilder* JAbstractStringBuilder::insert(jint offset,const wchar_t* wstr) {
        	if ((offset < 0) || (offset > count->get()))
				throw new JIndexOutOfBoundsException(new JString(NativeString::valueOf(offset)));
			jint len = wcslen(wstr);
			jint currentCount = count->get();
			ensureCapacityInternal(currentCount + len);
			for(jint i = currentCount -1; i >= offset; i--) {
				value->setChar(i + len, value->getChar(i));
			}
			for(jint i = 0; i < len; i++) {
				value->setChar(offset++, wstr[i]);
			}
			count->set(count->get()+ len);
			return this;
        }

        JAbstractStringBuilder* JAbstractStringBuilder::insert(jint offset,jbool b){
            if ((offset < 0) || (offset > count->get()))
                throw new JIndexOutOfBoundsException(new JString(NativeString::valueOf(offset)));
            jint len = b ? 4 : 5;
            ensureCapacityInternal(count->get() + len);
			for(jint i = count->get() -1; i >= offset; i--) {
				value->setChar(i + len, value->getChar(i));
			}
			if (b) {
				value->setChar(offset++, 't');
				value->setChar(offset++, 'r');
				value->setChar(offset++, 'u');
				value->setChar(offset++, 'e');
			} else {
				value->setChar(offset++, 'f');
				value->setChar(offset++, 'a');
				value->setChar(offset++, 'l');
				value->setChar(offset++, 's');
				value->setChar(offset++, 'e');
			}
            return this;
        }

        JAbstractStringBuilder* JAbstractStringBuilder::insert(jint offset,jchar c){
            if ((offset < 0) || (offset > count->get()))
                throw new JIndexOutOfBoundsException(new JString(NativeString::valueOf(offset)));
            jint len = 1;
			ensureCapacityInternal(count->get() + len);
			for(jint i = count->get() -1; i >= offset; i--) {
				value->setChar(i + len, value->getChar(i));
			}
			value->setChar(offset, c);
			return this;
        }

        void JAbstractStringBuilder::insert(jint offset, const std::string& str) {
            if ((offset < 0) || (offset > count->get()))
                throw new JIndexOutOfBoundsException(new JString(NativeString::valueOf(offset)));
            jint len = str.length();
            ensureCapacityInternal(count->get() + len);
            for(jint i = count->get() -1; i >= offset; i--) {
            	value->setChar(i + len, value->getChar(i));
            }
            for(jint i = 0; i < len; i++) {
            	value->setChar(offset++, str[i]);
            }
            count->set(count->get()+ len);
        }

        JAbstractStringBuilder* JAbstractStringBuilder::insert(jint offset,jint i){
        	std::stringstream out;
			out << i;
        	insert(offset, out.str());
            return this;
        }

        JAbstractStringBuilder* JAbstractStringBuilder::insert(jint offset,jlong l){
        	std::stringstream out;
			out << l;
			insert(offset, out.str());
            return this;
        }

        JAbstractStringBuilder* JAbstractStringBuilder::insert(jint offset,jfloat f){
        	std::stringstream out;
			out << f;
			insert(offset, out.str());
            return this;
        }

        JAbstractStringBuilder* JAbstractStringBuilder::insert(jint offset,jdouble d){
        	std::stringstream out;
			out << d;
			insert(offset, out.str());
            return this;
        }

        jint JAbstractStringBuilder::indexOf(JString* str){
            return indexOf(str,0);
        }

        jint JAbstractStringBuilder::indexOf(JString* str,jint fromIndex){
        	return toString()->indexOf(str, fromIndex);
        }

        jint JAbstractStringBuilder::lastIndexOf(JString* str){
            return lastIndexOf(str,0);
        }

        jint JAbstractStringBuilder::lastIndexOf(JString* s,jint fromIndex){
        	return toString()->lastIndexOf(s, fromIndex);
        }

        JAbstractStringBuilder* JAbstractStringBuilder::reverse(){
        	jchar temp = 0;
        	jint index = 0;
        	for(jint i = 0; i < count->get(); i++) {
        		index = count->get() - 1 - i;
        		temp = value->getChar(index);
        		value->setChar(index, value->getChar(i));
        		value->setChar(i, temp);
        	}
            return this;
        }

        JString* JAbstractStringBuilder::toString(){
            return new JString(value, 0, count->get());
        }

        jbool JAbstractStringBuilder::equals(JObject *o){
            if ((o == null) || getClass()!=o->getClass()){
                return false;
            }
            JAbstractStringBuilder * other = dynamic_cast<JAbstractStringBuilder *>(o);
            if(count->get() != other->count->get()) {
            	return false;
            }
            for(jint i = 0; i < count->get(); i++) {
            	if(value->getChar(i) != other->value->getChar(i)) {
            		return false;
            	}
            }
            return true;
        }

        JAbstractStringBuilder::~JAbstractStringBuilder(){
        }
    }
}
