#include "jcpp/nio/charset/JCharsetDecoder.h"


namespace jcpp {
	namespace nio {
		namespace charset {

	JCharsetDecoder::JCharsetDecoder(jcpp::lang::JClass* _class, JCharset* cs, jfloat averageCharsPerByte, jfloat maxCharsPerByte, JString* replacement)
		: JObject(_class)
	{
		construct(cs, averageCharsPerByte, maxCharsPerByte,replacement);
	}

	JCharsetDecoder::JCharsetDecoder(jcpp::lang::JClass* _class, JCharset* cs, jfloat averageCharsPerByte, jfloat maxCharsPerByte)
		: JObject(_class)
	{
		construct(cs, averageCharsPerByte, maxCharsPerByte, new JString("\uFFFD"));
	}

	JCharsetDecoder::~JCharsetDecoder()
	{	}

	void JCharsetDecoder::construct(JCharset* cs, jfloat averageCharsPerByte, jfloat maxCharsPerByte, JString* replacement) {
		this->charset = cs;
		if (averageCharsPerByte <= 0.0f)
			throw new JIllegalArgumentException(new JString("Non-positive averageCharsPerByte"));

		if (maxCharsPerByte <= 0.0f)
			throw new JIllegalArgumentException(new JString("Non-positive maxCharsPerByte"));

		if (averageCharsPerByte > maxCharsPerByte)
			throw new JIllegalArgumentException(new JString("averageCharsPerByte exceeds maxCharsPerByte"));

		this->replacement = replacement;
		this->averageCharsPerByte = averageCharsPerByte;
		this->maxCharsPerByte = maxCharsPerByte;
		replaceWith(replacement);
	}

	void JCharsetDecoder::throwIllegalStateException(jint from, jint to) {
		JStringBuilder* msgBuilder = new JStringBuilder(new JString("Current state = "));
		msgBuilder->append(getStateNameFromID(from));
		msgBuilder->append(", new state = ");
		msgBuilder->append(getStateNameFromID(to));
		throw new JIllegalStateException(msgBuilder->toString());
	}

	void JCharsetDecoder::implReplaceWith(JString* newReplacement)
	{	}

	void JCharsetDecoder::implOnMalformedInput(const JCodingErrorAction* newAction)
	{	}

	void JCharsetDecoder::implOnUnmappableCharacter(const JCodingErrorAction* newAction)
	{	}

	JCoderResult* JCharsetDecoder::implFlush(JCharBuffer* out)
	{
		return const_cast<JCoderResult*>(JCoderResult::JUNDERFLOW);
	}

	void JCharsetDecoder::implReset()
	{	}


	JCharset* JCharsetDecoder::getCharset() {
		return charset;
	}

	JString* JCharsetDecoder::getReplacement() {
		return replacement;
	}

	JCharsetDecoder* JCharsetDecoder::replaceWith(JString* newReplacement)
	{
		if (newReplacement == null)
			throw new JIllegalArgumentException(new JString("Null replacement"));
		jint len = newReplacement->length();
		if (len == 0)
			throw new JIllegalArgumentException(new JString("Empty replacement"));
		if (len > maxCharsPerByte)
			throw new JIllegalArgumentException(new JString("Replacement too long"));

		this->replacement = newReplacement;
		implReplaceWith(newReplacement);
		return this;
	}

	jfloat JCharsetDecoder::getAverageCharsPerByte() {
		return averageCharsPerByte;
	}

	jfloat JCharsetDecoder::getMaxCharsPerByte() {
		return maxCharsPerByte;
	}

	JCharsetDecoder* JCharsetDecoder::onMalformedInput(const JCodingErrorAction* newAction) {
		if (newAction == null)
			throw new JIllegalArgumentException(new JString("Null action"));
		malformedInputAction = const_cast<JCodingErrorAction*>(newAction);
		implOnMalformedInput(newAction);
		return this;
	}

	JCharsetDecoder* JCharsetDecoder::onUnmappableCharacter(const JCodingErrorAction* newAction){
		if (newAction == null)
			throw new JIllegalArgumentException(new JString("Null action"));
		unmappableCharacterAction = const_cast<JCodingErrorAction*>(newAction);
		implOnUnmappableCharacter(newAction);
		return this;
	}

	JCodingErrorAction* JCharsetDecoder::getMalformedInputAction() {
		return malformedInputAction;
	}


	JCoderResult* JCharsetDecoder::decode(JByteBuffer* in, JCharBuffer* out, jbool endOfInput)
	{
		jint newState = endOfInput? ST_END : ST_CODING;
		if ((state!=ST_RESET) && (state!=ST_CODING)
			&& !(endOfInput && (state==ST_END)))
			throwIllegalStateException(state, newState);
		state = newState;

		for(;;) {

			JCoderResult* cr;
			try {
				cr = decodeLoop(in, out);
			} catch(JBufferUnderflowException* x) {
				throw new JCoderMalfunctionError(reinterpret_cast<JException*>(x));
			} catch(JBufferOverflowException* x) {
				throw new JCoderMalfunctionError(reinterpret_cast<JException*>(x));
			}

			if (cr->isOverflow())
				return cr;

			if (cr->isUnderflow()) {
				if (endOfInput && in->hasRemaining()) {
					cr = JCoderResult::malformedForLength(in->remaining());
				} else {
					return cr;
				}
			}

			JCodingErrorAction* action = null;
			if (cr->isMalformed())
				action = malformedInputAction;
			else if (cr->isUnmappable())
				action = unmappableCharacterAction;
			else
				assert(false);

			if (action == JCodingErrorAction::REPORT)
				return cr;

			if (action == JCodingErrorAction::REPLACE) {
				if (out->remaining() < replacement->length())
					return const_cast<JCoderResult*>(JCoderResult::JOVERFLOW);
				out->put(replacement);
			}

			if ((action==JCodingErrorAction::IGNORE)
				|| (action==JCodingErrorAction::REPLACE)) {
				in->position(in->position() + cr->getLength());
				continue;
			}

			assert(false);
		}

		return null;
	}

	JCoderResult* JCharsetDecoder::flush(JCharBuffer* out)
	{
		if (state == ST_END) {
			JCoderResult* cr = implFlush(out);
			if (cr->isUnderflow())
				state = ST_FLUSHED;
			return cr;
		}

		if (state != ST_FLUSHED)
			throwIllegalStateException(state, ST_FLUSHED);

		return const_cast<JCoderResult*>(JCoderResult::JUNDERFLOW);
	}

	JCharsetDecoder* JCharsetDecoder::reset()
	{
		implReset();
		state = ST_RESET;
		return this;
	}

	JString* JCharsetDecoder::getStateNameFromID(jint id)
	{
		switch (id){
		case 0:
			return new JString("RESET");
		case 1:
			return new JString("CODING");
		case 2:
			return new JString("CODING_END");
		case 3:
			return new JString("FLUSHED");
		default:
			throw new JArrayIndexOutOfBoundsException(new JString("invalid state index"));
		}
	}


		}
	}
}

