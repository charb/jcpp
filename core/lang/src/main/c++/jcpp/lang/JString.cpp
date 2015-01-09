#include "jcpp/lang/JString.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JBoolean.h"
#include "jcpp/lang/JFloat.h"
#include "jcpp/lang/JDouble.h"
#include "jcpp/lang/JLong.h"
#include "jcpp/lang/JInteger.h"
#include "jcpp/lang/JCharacter.h"
#include "jcpp/lang/JPrimitiveByteArray.h"
#include "jcpp/lang/JPrimitiveCharArray.h"
#include "jcpp/io/JSerializable.h"
#include "jcpp/util/JMap.h"
#include "jcpp/util/JHashMap.h"
#include "jcpp/util/JComparator.h"
#include "jcpp/lang/JStringIndexOutOfBoundsException.h"
#include "jcpp/lang/JStringCoding.h"

using namespace jcpp::io;
using namespace jcpp::util;
using namespace jcpp::native::api;

namespace jcpp{
    namespace lang{

        class JStringClass : public jcpp::lang::JClass{
        public:
            JStringClass():jcpp::lang::JClass(){
                this->canonicalName=new JString("java.lang.String");
                this->name=new JString("java.lang.String");
                this->simpleName=new JString("String");
                this->serialVersionUID=-6849794470754667710ULL;
            }

            virtual void initialize(){
                addInterface(JSerializable::getClazz());
                addInterface(JComparable::getClazz());
                addInterface(JCloneable::getClazz());
                addInterface(JCharSequence::getClazz());
            }

            virtual jcpp::lang::JClass* getSuperclass(){
                return JObject::getClazz();
            }
        };

        static jcpp::lang::JClass* clazz;

        jcpp::lang::JClass* JString::getClazz(){
            if (clazz==null){
                clazz=new JStringClass();
            }
            return clazz;
        }

        static JMap* internStrings = null;

        JString* JString::staticIntern(JString* s){
            synchronized(getClazz(),{
                if (internStrings==null){
                    internStrings=new JHashMap();
                }
                JString* js=dynamic_cast<JString*>(internStrings->get(s));
                if (js==null){
                    js=new JString(s);
                    internStrings->put(js,js);
                }
                return js;
            })
        }

        jint JString::hashCode(JString* s){
            jint h=0;
            for (jint i=0;i<s->length();i++){
                h=31*h+(jint)s->charAt(i);
            }
            return h;
        }

        jint JString::compare(JString* s1,JString* s2){
            jint len1 = s1->length();
            jint len2 = s2->length();
            jint lim = (len1<len2?len1:len2);

            jint k = 0;
            while (k < lim) {
                jchar c1 = s1->charAt(k);
                jchar c2 = s1->charAt(k);
                if (c1 != c2) {
                    return c1 - c2;
                }
                k++;
            }
            return len1 - len2;
        }

        JString* JString::NULL_STRING = new JString("null");

        JString* JString::valueOf(JObject* obj){
            return (obj==null ? NULL_STRING : obj->toString());
        }

        JString* JString::valueOf(JPrimitiveCharArray* data){
            return new JString(data);
        }

        JString* JString::valueOf(JPrimitiveCharArray* data, jint offset, jint count){
            return new JString(data,offset,count);
        }

        JString* JString::valueOf(jbool b){
            return (b ? JBoolean::TRUE_STRING : JBoolean::FALSE_STRING);
        }

        JString* JString::valueOf(jchar c){
            return new JString(c);
        }

        JString* JString::valueOf(jint i){
            return JInteger::toString(i);
        }

        JString* JString::valueOf(jlong l){
            return JLong::toString(l);
        }

        JString* JString::valueOf(jfloat f){
            return JFloat::toString(f);
        }

        JString* JString::valueOf(jdouble d){
            return JDouble::toString(d);
        }

        JString::JString(const NativeString& string): JObject(false), nativeString(string){
        }

        JString::JString(): JObject(false), nativeString(){
        }

        JString::JString(string str): JObject(false), nativeString(str){
        }

        JString::JString(JString* str): JObject(false), nativeString(str->nativeString){
        }

        JString::JString(const char* c): JObject(false), nativeString(c){
        }

        JString::JString(JPrimitiveCharArray* chars):JObject(false), nativeString(){
        	jint size = chars->size();
        	jchar* jcharArray = new jchar[size];
        	for(jint i = 0; i < size; i++) {
        		jcharArray[i] = chars->getChar(i);
        	}
        	nativeString = NativeString(jcharArray, 0, size);
        	delete jcharArray;
        }

        JString::JString(JPrimitiveCharArray* chars,jint off,jint length):JObject(false), nativeString(){
			jchar* jcharArray = new jchar[length];
			for(jint i = 0; i < length; i++) {
				jcharArray[i] = chars->getChar(off + i);
			}
			nativeString = NativeString(jcharArray, 0, length);
			delete jcharArray;
        }

        JString::JString(JPrimitiveByteArray* bytes):JObject(false), nativeString(){
        	JPrimitiveCharArray* ca = JStringCoding::decode(bytes, 0, bytes->size());
        	nativeString = NativeString(ca->getArray(), 0, ca->size());
        }

        JString::JString(JPrimitiveByteArray* bytes,jint off,jint length):JObject(false), nativeString(){
        	checkBounds(bytes, off, length);
        	JPrimitiveCharArray* ca = JStringCoding::decode(bytes, off, length);
        	nativeString = NativeString(ca->getArray(), 0, ca->size());
        }

        JString::JString(JPrimitiveByteArray* bytes, jint off, jint length, JString* charsetName):JObject(getClazz()), nativeString(){
        	checkBounds(bytes, off, length);
        	JPrimitiveCharArray* ca = JStringCoding::decode(charsetName, bytes, off, length);
        	nativeString = NativeString(ca->getArray(), 0, ca->size());
        }

        JString::JString(jchar c):JObject(false), nativeString(&c, 0, 1){
        }

        jcpp::lang::JClass* JString::getClass(){
            return JString::getClazz();
        }

        jint JString::length(){
            return nativeString.length();
        }

        jbool JString::isEmpty(){
            return nativeString.isEmpty();
        }

        jchar JString::charAt(jint index){
        	if ((index < 0) || (index >= nativeString.length())) {
        		throw new JStringIndexOutOfBoundsException(new JString(NativeString::valueOf(index)));
        	}
            return nativeString[index];
        }

        //TODO sevag to review
        jint JString::codePointAt(jint index){
            if ((index < 0) || (index >= nativeString.length())) {
                throw new JStringIndexOutOfBoundsException(new JString(NativeString::valueOf(index)));
            }
            return (jint)nativeString[index];
        }

        jint JString::indexOf(JString* str){
            return nativeString.indexOf(str->nativeString);
        }

        jint JString::indexOf(JString* str,jint from){
            return nativeString.indexOf(str->nativeString, from);
        }

        jint JString::lastIndexOf(JString* str){
        	return nativeString.lastIndexOf(str->nativeString);
        }

        jint JString::lastIndexOf(JString* str,jint from){
            return nativeString.lastIndexOf(str->nativeString, from);
        }

        JString* JString::reverse(){
        	return new JString(nativeString.reverse());
        }

        void JString::getChars(jint srcBegin, jint srcEnd, JPrimitiveCharArray* dst, jint dstBegin){
        	if (srcBegin < 0) {
        		throw new JStringIndexOutOfBoundsException(new JString(NativeString::valueOf(srcBegin)));
			}
			if (srcEnd > nativeString.length()) {
				throw new JStringIndexOutOfBoundsException(new JString(NativeString::valueOf(srcEnd)));
			}
			if (srcBegin > srcEnd) {
				throw new JStringIndexOutOfBoundsException(new JString(NativeString::valueOf(srcEnd - srcBegin)));
			}
        	for(jint i = srcBegin; i < srcEnd; i++) {
        		dst->setChar(dstBegin++, nativeString[i]);
        	}
        }

        JPrimitiveByteArray* JString::getBytes(){
        	JPrimitiveCharArray* ca = new JPrimitiveCharArray(nativeString.length());
        	jchar* cstr = nativeString.getChars();
        	for (int i=0; i < nativeString.length(); i++){
        		ca->setChar(i, cstr[i]);
        	}
            return JStringCoding::encode(ca, 0, nativeString.length());
        }

        jbool JString::contentEquals(JCharSequence* cs){
        	jint length = nativeString.length();
        	if((cs != null) && (length == cs->length())) {
        		for(jint i = 0; i < length; i++) {
        			if(nativeString[i] != cs->charAt(i)) {
        				return false;
        			}
        		}
        	}
            return false;
        }

        jbool JString::equalsIgnoreCase(JString* anotherString){
            return nativeString.equalsIgnoreCase(anotherString->nativeString);
        }

        jbool JString::startsWith(JString* prefix, jint toffset){
            return nativeString.startsWith(prefix->nativeString, toffset);
        }

        jbool JString::startsWith(JString* prefix){
            return nativeString.startsWith(prefix->nativeString);
        }

        jbool JString::endsWith(JString* prefix){
            return nativeString.endsWith(prefix->nativeString);
        }

        jint JString::indexOf(jchar c){
            return nativeString.indexOf(c);
        }

        jint JString::indexOf(jchar c,jint fromIndex){
            return nativeString.indexOf(c, fromIndex);
        }

        jint JString::lastIndexOf(jchar c){
            return nativeString.lastIndexOf(c);
        }

        jint JString::lastIndexOf(jchar c,jint fromIndex){
            return nativeString.lastIndexOf(c, fromIndex);
        }

        JString* JString::replace(jchar oldchar,jchar newchar){
            return new JString(nativeString.replace(oldchar, newchar));
        }

        JString* JString::substring(jint start){
        	if (start < 0) {
        		throw new JStringIndexOutOfBoundsException(new JString(NativeString::valueOf(start)));
			}
			jint subLen = nativeString.length() - start;
			if (subLen < 0) {
				throw new JStringIndexOutOfBoundsException(new JString(NativeString::valueOf(subLen)));
			}
            return new JString(nativeString.substring(start));
        }

        JString* JString::substring(jint start,jint end){
        	if (start < 0) {
        		throw new JStringIndexOutOfBoundsException(new JString(NativeString::valueOf(start)));
			}
			if (end > nativeString.length()) {
				throw new JStringIndexOutOfBoundsException(new JString(NativeString::valueOf(end)));
			}
			int subLen = end - start;
			if (subLen < 0) {
				throw new JStringIndexOutOfBoundsException(new JString(NativeString::valueOf(subLen)));
			}
            return new JString(nativeString.substring(start, end));
        }

        JCharSequence* JString::subSequence(jint beginIndex, jint endIndex){
            return substring(beginIndex, endIndex);
        }

        JString* JString::concat(JString* str){
            return new JString(nativeString.concat(str->nativeString));
        }

        jbool JString::contains(JCharSequence* s){
            return nativeString.indexOf(s->toString()->nativeString) > -1;
        }

        JString* JString::toLowerCase(){
            return new JString(nativeString.toLowerCase());
        }

        JString* JString::toUpperCase(){
        	return new JString(nativeString.toUpperCase());
        }

        JString* JString::trim(){
            return new JString(nativeString.trim());
        }

        JPrimitiveCharArray* JString::toCharArray(){
        	jint length = nativeString.length();
        	JPrimitiveCharArray* array = new JPrimitiveCharArray(length);
        	for(jint i = 0; i < length; i++) {
        		array->setChar(i, nativeString[i]);
        	}
            return array;
        }

        jint JString::compareTo(JObject* o){
            JString* s=dynamic_cast<JString*>(o);
            return compare(this,s);
        }

        class JCaseInsensitiveComparatorClass : public JClass{
        public:
            JCaseInsensitiveComparatorClass():JClass(){
                this->canonicalName=new JString("java.lang.String$CaseInsensitiveComparator");
                this->name=new JString("java.lang.String$CaseInsensitiveComparator");
                this->simpleName=new JString("String$CaseInsensitiveComparator");
                this->serialVersionUID=8575799808933029326LL;
            }

            virtual void initialize(){
                addInterface(JSerializable::getClazz());
                addInterface(JComparator::getClazz());
            }

            virtual JClass* getSuperclass(){
                return JObject::getClazz();
            }
        };

        static JClass* caseInsensitiveComparatorClazz;

        class JCaseInsensitiveComparator : public JObject, public JComparator, public JSerializable {
        public:

            JCaseInsensitiveComparator():JObject(getClazz()){
            }

            static JClass* getClazz(){
                if (caseInsensitiveComparatorClazz==null){
                    caseInsensitiveComparatorClazz=new JCaseInsensitiveComparatorClass();
                }
                return caseInsensitiveComparatorClazz;
            }
    
            virtual jint compare(JObject* o1, JObject* o2) {
                JString* s1=dynamic_cast<JString*>(o1);
                JString* s2=dynamic_cast<JString*>(o2);
                jint n1 = s1->length();
                jint n2 = s2->length();
                jint min = (n1<  n2 ? n1 : n2);
                for (jint i = 0; i < min; i++) {
                    jchar c1 = s1->charAt(i);
                    jchar c2 = s2->charAt(i);
                    if (c1 != c2) {
                        c1 = JCharacter::toUpperCase(c1);
                        c2 = JCharacter::toUpperCase(c2);
                        if (c1 != c2) {
                            c1 = JCharacter::toLowerCase(c1);
                            c2 = JCharacter::toLowerCase(c2);
                            if (c1 != c2) {
                                return c1 - c2;
                            }
                        }
                    }
                }
                return n1 - n2;
            }

            virtual JObject* readResolve() {
                return dynamic_cast<JObject*>(JString::CASE_INSENSITIVE_ORDER); 
            }
        };

        jint JString::compareToIgnoreCase(JString* str){
            return JString::CASE_INSENSITIVE_ORDER->compare(this, str);
        }

        JComparator* JString::CASE_INSENSITIVE_ORDER = new JCaseInsensitiveComparator();

        JString* JString::clone(){
            return new JString(nativeString);
        }

        jbool JString::equals(JObject* other){
            if ((other != null) && (other->getClass()==getClazz())){
                JString* s=dynamic_cast<JString*>(other);
                jbool eq=nativeString == s->nativeString;
                return eq;
            }
            return false;
        }

        jint JString::hashCode(){
            return hashCode(this);
        }

        JString* JString::toString(){
            return this;
        }

        JString* JString::intern(JString* s){
            return staticIntern(s);
        }

        JString::~JString(){
        }

        NativeString JString::getNativeString() {
        	return nativeString;
        }

        void JString::checkBounds(JPrimitiveByteArray* bytes, jint offset, jint length)
        {
        	if (length < 0)
        		throw new JStringIndexOutOfBoundsException(JString::valueOf(length));
        	if (offset < 0)
        		throw new JStringIndexOutOfBoundsException(JString::valueOf(offset));
        	if (offset > bytes->size() - length)
        		throw new JStringIndexOutOfBoundsException(JString::valueOf(offset+length));
        }

    }
}
