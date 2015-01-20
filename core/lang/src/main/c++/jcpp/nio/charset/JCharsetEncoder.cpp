#include "jcpp/nio/charset/JCharsetEncoder.h"


namespace jcpp {
	namespace nio {
		namespace charset {

			JCharsetEncoder::JCharsetEncoder(jcpp::lang::JClass* _class, JCharset* cs, jfloat averageBytesPerChar, jfloat maxBytesPerChar, JPrimitiveByteArray* replacement) : JObject(_class) {
				construct(cs, averageBytesPerChar, maxBytesPerChar, replacement);
			}


			JCharsetEncoder::JCharsetEncoder(jcpp::lang::JClass* _class, JCharset* cs, jfloat averageBytesPerChar, jfloat maxBytesPerChar) : JObject(_class) {
				JPrimitiveByteArray* replacement = new JPrimitiveByteArray(1);
				replacement->setByte(0,(jbyte)'?');
				construct(cs, averageBytesPerChar, maxBytesPerChar, replacement);
			}

			void JCharsetEncoder::construct(JCharset* cs, jfloat averageBytesPerChar, jfloat maxBytesPerChar, JPrimitiveByteArray* replacement) {
				this->charset = cs;
				if (averageBytesPerChar <= 0.0f)
					throw new JIllegalArgumentException(new JString("Non-positive averageBytesPerChar"));

				if (maxBytesPerChar <= 0.0f)
					throw new JIllegalArgumentException(new JString("Non-positive maxBytesPerChar"));

				if (averageBytesPerChar > maxBytesPerChar)
					throw new JIllegalArgumentException(new JString("averageBytesPerChar exceeds maxBytesPerChar"));

				this->replacement = replacement;
				this->averageBytesPerChar = averageBytesPerChar;
				this->maxBytesPerChar = maxBytesPerChar;
				malformedInputAction = JCodingErrorAction::REPORT;
				unmappableCharacterAction = JCodingErrorAction::REPORT;
				state = ST_RESET;
				replaceWith(replacement);
			}


			JCharsetEncoder::~JCharsetEncoder() {
			}

			JCharset* JCharsetEncoder::getCharset(){
				return this->charset;
			}

			JPrimitiveByteArray* JCharsetEncoder::getReplacement(){
				return this->replacement;
			}

			JCharsetEncoder* JCharsetEncoder::replaceWith(JPrimitiveByteArray* newReplacement){
				if (newReplacement == null)
					throw new JIllegalArgumentException(new JString("Null replacement"));
				jint len = newReplacement->size();
				if (len == 0)
					throw new JIllegalArgumentException(new JString("Empty replacement"));

				if (len > maxBytesPerChar)
					throw new JIllegalArgumentException(new JString("Replacement too long"));

				if (!isLegalReplacement(newReplacement))
					throw new JIllegalArgumentException(new JString("Illegal replacement"));

				this->replacement = newReplacement;
				implReplaceWith(newReplacement);
				return this;
			}

			void JCharsetEncoder::implReplaceWith(JPrimitiveByteArray* newReplacement){
			}


			jbool JCharsetEncoder::isLegalReplacement(JPrimitiveByteArray* repl){
				//TODO needs Decoder, ByeBuffer, and CharBuffer
				return true;
			}


			jfloat JCharsetEncoder::getAverageBytesPerChar(){
				return this->averageBytesPerChar;
			}


			jfloat JCharsetEncoder::getMaxBytesPerChar(){
				return this->maxBytesPerChar;
			}


			JCharsetEncoder* JCharsetEncoder::onMalformedInput(JCodingErrorAction* newAction){
				if (newAction==null)
					throw new JIllegalArgumentException(new JString("Null Action"));

				this->malformedInputAction = newAction;
				implOnMalformedInput(newAction);
				return this;
			}

			void JCharsetEncoder::implOnMalformedInput(JCodingErrorAction* newAction){
			}


			JCharsetEncoder* JCharsetEncoder::onUnmappableCharacter(JCodingErrorAction* newAction){
				if (newAction==null)
					throw new JIllegalArgumentException(new JString("Null action"));

				this->unmappableCharacterAction = newAction;
				implOnUnmappableCharacter(newAction);
				return this;
			}

			JCodingErrorAction* JCharsetEncoder::getMalformedInputAction(){
				return malformedInputAction;
			}

			void JCharsetEncoder::implOnUnmappableCharacter(JCodingErrorAction* newAction){
			}

			void JCharsetEncoder::throwIllegalStateException(jint from, jint to)
			{
				JStringBuilder* msgBuilder = new JStringBuilder(new JString("Current state = "));
				msgBuilder->append(getStateNameFromID(from));
				msgBuilder->append(", new state = ");
				msgBuilder->append(getStateNameFromID(to));
				throw new JIllegalStateException(msgBuilder->toString());
			}


			JCoderResult* JCharsetEncoder::encode(JCharBuffer* in, JByteBuffer* out, jbool endOfInput) {
				jint newState = endOfInput? ST_END : ST_CODING;
				if ((state != ST_RESET) && (state != ST_CODING) && (!endOfInput && state != ST_CODING))
					throwIllegalStateException(state, newState);
				state = newState;

				for (;;) {

					JCoderResult* cr;
					try {
						cr = encodeLoop(in, out);
					} catch(JBufferUnderflowException* x){
						throw new JCoderMalfunctionError((JException*)x);
					} catch(JBufferOverflowException* x){
						throw new JCoderMalfunctionError((JException*)x);
					}

					if (cr->isOverflow())
						return cr;

					if (cr->isUnderflow()){
						if (endOfInput && in->hasRemaining()) {
							cr = JCoderResult::malformedForLength(in->remaining());
						}else {
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
						if (out->remaining() < replacement->size())
							return JCoderResult::JOVERFLOW;
						out->put(replacement);
					}

					if ((action == JCodingErrorAction::IGNORE)
						|| (action == JCodingErrorAction::REPLACE)) {
						in->position(in->position() + cr->getLength());
						continue;
					}

					assert(false);

				}
				return null;
			}

			JCoderResult* JCharsetEncoder::flush(JByteBuffer* out) {
				if (state == ST_END) {
					JCoderResult* cr = implFlush(out);
					if (cr->isUnderflow())
						state = ST_FLUSHED;
					return cr;
				}

				if (state != ST_FLUSHED)
					throwIllegalStateException(state, ST_FLUSHED);

				return JCoderResult::JUNDERFLOW;
			}

			JCoderResult* JCharsetEncoder::implFlush(JByteBuffer* out) {
				return JCoderResult::JUNDERFLOW;
			}

			JCharsetEncoder* JCharsetEncoder::reset() {
				implReset();
				state = ST_RESET;
				return this;
			}

			void JCharsetEncoder::implReset() {
			}

			JByteBuffer* JCharsetEncoder::encode(JCharBuffer* in) {
				jint n = (jint)(in->remaining() * getAverageBytesPerChar());
				JByteBuffer* out = JByteBuffer::allocate(n);

				if ((n == 0) && (in->remaining() == 0))
					return out;
				reset();
				for (;;){
					JCoderResult* cr = in->hasRemaining() ? encode(in, out, true) : JCoderResult::JUNDERFLOW;
					if (cr->isUnderflow())
						cr = flush(out);

					if (cr->isOverflow()) {
						n = 2*n + 1;
						JByteBuffer* o = JByteBuffer::allocate(n);
						out->flip();
						o->put(out);
						out = o;
						continue;
					}
					cr->throwException();
				}
				out->flip();
				return out;
			}

			JString* JCharsetEncoder::getStateNameFromID(jint id) {
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
