#include "jcpp/lang/JStringCoding.h"

namespace jcpp {
	namespace lang {

	JStringCoding::JStringCoding():JObject(getClazz())
	{	}

	JStringCoding::~JStringCoding()
	{	}

	JPrimitiveByteArray* JStringCoding::safeTrim(JPrimitiveByteArray* ba, jint len, JCharset* cs, jbool isTrusted)
	{
		if ( len == ba->size() && isTrusted )
			return ba;
		else
			return JArrays::copyOf(ba, len);
	}

	JPrimitiveCharArray* JStringCoding::safeTrim(JPrimitiveCharArray* ca, jint len, JCharset* cs, jbool isTrusted)
	{
		if (len == ca->size() && isTrusted)
			return ca;
		else
			return JArrays::copyOf(ca, len);
	}

	jint JStringCoding::scale(jint len, jfloat expansionFactor)
	{
		return (jint)(len * (jdouble)expansionFactor);
	}

	JCharset* JStringCoding::lookupCharset(JString* csn)
	{
		if (JCharset::isSupported(csn)){
			try{
				return JCharset::forName(csn);
			}catch(JUnsupportedCharsetException* x){
				throw new JError(new JString("Unsupported Charset"),(JException*)x);
			}
		}
		return null;
	}

	JPrimitiveCharArray* JStringCoding::decode(JString* charsetName, JPrimitiveByteArray* ba, jint off, jint len)
	{
		JStringDecoder* sd = null;
		JString* csn = (charsetName == null)? new JString("ISO-8859-1") : charsetName;
		if ((sd == null) || !(csn->equals((JObject*)sd->requestedCharsetName())
				|| csn->equals(sd->charsetName()))) {
			sd = null;
			try {
				JCharset* cs = lookupCharset(csn);
				if (cs != null)
					sd = new JStringDecoder(cs, csn);
			} catch (JIllegalCharsetNameException* x){}
			if (sd == null)
				throw new JUnsupportedEncodingException(csn);
		}
		return sd->decode(ba, off, len);
	}

	JPrimitiveCharArray* JStringCoding::decode(JPrimitiveByteArray* ba, jint off, jint len)
	{
		JString* csn = new JString("UTF-8"); //TODO Charset.defaultCharset().name();
		try {
			return decode(csn, ba, off, len);
		} catch(JUnsupportedEncodingException* x){
			// warUnsupportedCharset(csn);
		}
		try {
			return decode(new JString("ISO-8859-1"), ba, off, len);
		}	catch (JUnsupportedEncodingException* x){
			// MessageUtils.err("ISO-8859-1 charset not available: "
			//+ x.toString());
			// exit(1); Throw Exception keep commaent of exit
			throw new JRuntimeException(new JString("ISO-8859-1 encoding not supported"));
			return null;
		}
	}

	JPrimitiveByteArray* JStringCoding::encode(JString* charsetName, JPrimitiveCharArray* ca, jint off, jint len){
		JStringEncoder* se = null;
		JString* csn = (charsetName == null)? new JString("ISO-8859-1") : charsetName;

		if ((se==null) || !(csn->equals(se->requestedCharsetName()))
				|| csn->equals(se->charsetName()))
		{
			se = null;
			try {
				JCharset* cs = lookupCharset(csn);
				if (cs != null)
					se = new JStringEncoder(cs, csn);
			} catch(JIllegalCharsetNameException* x){}
			if (se == null)
				throw new JUnsupportedEncodingException(csn);
		}
		return se->encode(ca, off, len);
	}


	JPrimitiveByteArray* JStringCoding::encode(JPrimitiveCharArray* ca, jint off, jint len){
		JString* csn = new JString("UTF-8");
		try{
			return encode(csn, ca, off, len);
		} catch(JUnsupportedEncodingException* x){
			// warnUnsupportedCharset(csn)
		}
		try{
			return encode(new JString("ISO-8859-1"), ca, off, len);
		} catch (JUnsupportedEncodingException* x){
			// MessageUtils.err("ISO-8859-1 charset not available: "
            //+ x.toString());
			// exit(1); Throw Exception keep commaent of exit
			throw new JRuntimeException(new JString("ISO-8859-1 encoding not supported"));
			return null;
		}

	}


	JStringCoding::JStringEncoder::JStringEncoder(JCharset* cs, JString* rcn) : JObject(getClazz()){
		this->reqCharsetName = rcn;
		this->cs = cs;
		this->ce = cs->newEncoder()->onMalformedInput(JCodingErrorAction::REPLACE)->
										onUnmappableCharacter(JCodingErrorAction::REPLACE);
		this->isTrusted = true;
	}

	JString* JStringCoding::JStringEncoder::charsetName() {
		return this->cs->getName();
	}

	JString* JStringCoding::JStringEncoder::requestedCharsetName() {
		return reqCharsetName;
	}

	JPrimitiveByteArray* JStringCoding::JStringEncoder::encode (JPrimitiveCharArray* ca, jint off, jint len){
		jint en = scale(len, ce->getMaxBytesPerChar());
		JPrimitiveByteArray* ba = new JPrimitiveByteArray(en);
		if (len == 0)
			return ba;

		if (ce->isInstanceOf(JArrayEncoder::getClazz())) {
			jint blen = dynamic_cast<JArrayEncoder*>(ce)->encode(ca, off, len, ba);
			return safeTrim(ba, blen, cs, isTrusted);
        } else {
			ce->reset();
			JByteBuffer* bb = JByteBuffer::wrap(ba);
			JCharBuffer* cb = JCharBuffer::wrap(ca, off, len);
			try{
				JCoderResult* cr = ce->encode(cb, bb, true);
				if (!cr->isUnderflow())
					cr->throwException();
				cr = ce->flush(bb);
				if (!cr->isUnderflow())
					cr->throwException();
			} catch(JCharacterCodingException* x){
				throw new JError(new JString("Character Coding Exception"),(JThrowable*)x);
			}
			return safeTrim(ba, bb->position(), cs, isTrusted);
        }
	}


	JStringCoding::JStringDecoder::JStringDecoder(JCharset* cs, JString* rcn){
		this->reqCharsetName = rcn;
		this->cs = cs;
		this->cd = cs->newDecoder()->onMalformedInput(JCodingErrorAction::REPLACE)
									->onUnmappableCharacter(JCodingErrorAction::REPLACE);
		this->isTrusted = true;
	}

	JString* JStringCoding::JStringDecoder::charsetName() {
		return this->cs->getName();
	}

	JString* JStringCoding::JStringDecoder::requestedCharsetName(){
		return this->reqCharsetName;
	}

	JPrimitiveCharArray* JStringCoding::JStringDecoder::decode(JPrimitiveByteArray* ba,jint off, jint len) {
		jint en = scale(len, cd->getMaxCharsPerByte());
		JPrimitiveCharArray* ca = new JPrimitiveCharArray(en);
		if (len == 0)
			return ca;

		if (cd->isInstanceOf(JArrayEncoder::getClazz())){
			jint clen = dynamic_cast<JArrayDecoder*>(cd)->decode(ba, off, len, ca);
			return safeTrim(ca, clen, cs, isTrusted);
		} else {
			cd->reset();
			JByteBuffer* bb = JByteBuffer::wrap(ba, off, len);
			JCharBuffer* cb = JCharBuffer::wrap(ca);
			try{
				JCoderResult* cr = cd->decode(bb, cb, true);
				if (!cr->isUnderflow())
					cr->throwException();
				cr = cd->flush(cb);
				if (!cr->isUnderflow())
					cr->throwException();
			}catch(JCharacterCodingException* x){
				throw new JError(new JString("Character Coding Exception"), (JThrowable*)x);
			}
			return safeTrim(ca, cb->position(), cs, isTrusted);
		}
	}


	}
}

