#include "jcpp/util/JStringTokenizer.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JCharacter.h"
#include "jcpp/lang/JInstantiationException.h"
#include "jcpp/lang/JNullPointerException.h"
#include "jcpp/util/JNoSuchElementException.h"

namespace jcpp{
    namespace util{

        JStringTokenizer::JStringTokenizer(JString* str, JString* delim, jbool returnDelims):JObject(getClazz()){
            currentPosition = 0;
            newPosition = -1;
            maxPosition = str->length();
            this->str = str;
            delimiters = delim;
            retDelims = returnDelims;
            delimsChanged = false;
            maxDelimCodePoint=0;
            hasSurrogates=false;
            delimiterCodePoints=null;
            setMaxDelimCodePoint();
        }

        JStringTokenizer::JStringTokenizer(JString* str, JString* delim):JObject(getClazz()){
            currentPosition = 0;
            newPosition = -1;
            maxPosition = str->length();
            this->str = str;
            delimiters = delim;
            retDelims = false;
            delimsChanged = false;
            maxDelimCodePoint=0;
            hasSurrogates=false;
            delimiterCodePoints=null;
            setMaxDelimCodePoint();
        }

        JStringTokenizer::JStringTokenizer(JString* str):JObject(getClazz()){
            currentPosition = 0;
            newPosition = -1;
            maxPosition = str->length();
            this->str = str;
            delimiters = new JString(" \t\n\r\f");
            retDelims = false;
            delimsChanged = false;
            maxDelimCodePoint=0;
            hasSurrogates=false;
            delimiterCodePoints=null;
            setMaxDelimCodePoint();
        }

        void JStringTokenizer::setMaxDelimCodePoint(){
            if (delimiters == null) {
                maxDelimCodePoint = 0;
                return;
            }

            jint m = 0;
            jint c=0;
            jint count = 0;
            for (jint i = 0; i < delimiters->length(); i += JCharacter::charCount(c)) {
                c = delimiters->charAt(i);
                if (c >= JCharacter::MIN_HIGH_SURROGATE && c <= JCharacter::MAX_LOW_SURROGATE) {
                    c = delimiters->codePointAt(i);
                    hasSurrogates = true;
                }
                if (m < c){
                    m = c;
                }
                count++;
            }
            maxDelimCodePoint = m;

            if (hasSurrogates) {
                delimiterCodePoints = new JPrimitiveIntArray(count);
                for (jint i = 0, j = 0; i < count; i++, j += JCharacter::charCount(c)) {
                    c = delimiters->codePointAt(j);
                    delimiterCodePoints->setInt(i, c);
                }
            }
        }

        jint JStringTokenizer::skipDelimiters(jint startPos){
            if (delimiters == null){
                throw new JNullPointerException();
            }

            jint position = startPos;
            while (!retDelims && position < maxPosition) {
                if (!hasSurrogates) {
                    jchar c = str->charAt(position);
                    if ((c > maxDelimCodePoint) || (delimiters->indexOf(c) < 0)){
                        break;
                    }
                    position++;

                } else {
                    jint c = str->codePointAt(position);
                    if ((c > maxDelimCodePoint) || !isDelimiter(c)) {
                        break;
                    }
                    position += JCharacter::charCount(c);
                }
            }
            return position;
        }

        jint JStringTokenizer::scanToken(jint startPos){
            jint position = startPos;
            while (position < maxPosition) {
                if (!hasSurrogates) {
                    jchar c = str->charAt(position);
                    if ((c <= maxDelimCodePoint) && (delimiters->indexOf(c) >= 0)){
                        break;
                    }
                    position++;

                } else {
                    jint c = str->codePointAt(position);
                    if ((c <= maxDelimCodePoint) && isDelimiter(c)){
                        break;
                    }
                    position += JCharacter::charCount(c);
                }
            }

            if (retDelims && (startPos == position)) {
                if (!hasSurrogates) {
                    jchar c = str->charAt(position);
                    if ((c <= maxDelimCodePoint) && (delimiters->indexOf(c) >= 0)){
                        position++;
                    }

                } else {
                    jint c = str->codePointAt(position);
                    if ((c <= maxDelimCodePoint) && isDelimiter(c))
                        position += JCharacter::charCount(c);
                }
            }
            return position;
        }

        jbool JStringTokenizer::isDelimiter(jint codePoint){
            for (jint i = 0; i < delimiterCodePoints->size(); i++) {
                if (delimiterCodePoints->getInt(i) == codePoint) {
                    return true;
                }
            }
            return false;
        }

        jbool JStringTokenizer::hasMoreTokens(){
            newPosition = skipDelimiters(currentPosition);
            return (newPosition < maxPosition);
        }

        JString* JStringTokenizer::nextToken(){
            currentPosition = (newPosition >= 0 && !delimsChanged) ? newPosition : skipDelimiters(currentPosition);

            delimsChanged = false;
            newPosition = -1;

            if (currentPosition >= maxPosition){
                throw new JNoSuchElementException();
            }
            jint start = currentPosition;
            currentPosition = scanToken(currentPosition);
            return str->substring(start, currentPosition);
        }

        JString* JStringTokenizer::nextToken(JString* delim){
            delimiters = delim;
            delimsChanged = true;
            setMaxDelimCodePoint();
            return nextToken();
        }

        jbool JStringTokenizer::hasMoreElements(){
            return hasMoreTokens();
        }

        JObject* JStringTokenizer::nextElement(){
            return nextToken();
        }

        jint JStringTokenizer::countTokens(){
            jint count = 0;
            jint currpos = currentPosition;
            while (currpos < maxPosition) {
                currpos = skipDelimiters(currpos);
                if (currpos >= maxPosition){
                    break;
                }
                currpos = scanToken(currpos);
                count++;
            }
            return count;
        }

        JStringTokenizer::~JStringTokenizer(){
        }
    }
}
