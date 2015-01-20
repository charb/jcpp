#include "jcpp/nio/cs/JUTF_8.h"


namespace jcpp {
	namespace nio {
		namespace cs {

			JUTF_8::JUTF_8() : JUnicode(getClazz(), new JString("UTF-8"), null) {
			}

			JString* JUTF_8::historicalName() {
				return new JString("UTF8");
			}

			JCharsetEncoder* JUTF_8::newEncoder() {
				return new JUTF_8::JEncoder(this);
			}

			JCharsetDecoder* JUTF_8::newDecoder() {
				return new JUTF_8::JDecoder(this);
			}

			void JUTF_8::updatePositions(JBuffer* src, jint sp, JBuffer* dst, jint dp) {
				src->position(sp - src->arrayOffset());
				dst->position(dp - dst->arrayOffset());
			}

			JUTF_8::~JUTF_8() {
			}

			JUTF_8::JEncoder::JEncoder(JCharset* cs) : JCharsetEncoder(getClazz(), cs, 1.1f, 3.0f) {
			}

			JCoderResult* JUTF_8::JEncoder::overflow(JCharBuffer* src, jint sp, JByteBuffer* dst, jint dp) {
				updatePositions(src, sp, dst, dp);
				return JCoderResult::JOVERFLOW;
			}

			JCoderResult* JUTF_8::JEncoder::overflow(JCharBuffer* src, jint mark) {
				src->position(mark);
				return JCoderResult::JOVERFLOW;
			}

			JCoderResult* JUTF_8::JEncoder::encodeArrayLoop(JCharBuffer* src, JByteBuffer* dst) {
				JPrimitiveCharArray* sa = reinterpret_cast<JPrimitiveCharArray*>(src->array());
				jint sp = src->arrayOffset() + src->position();
				jint sl = src->arrayOffset() + src->limit();

				JPrimitiveByteArray* da = reinterpret_cast<JPrimitiveByteArray*>(dst->array());
				jint dp = dst->arrayOffset() + dst->position();
				jint dl = dst->arrayOffset() + dst->limit();
				jint dlASCII = dp + min(sl-sp, dl-dp);

				//ASCII only loop
				while (dp < dlASCII && sa->getChar(sp) < 0x0080 )
					da->setByte(dp++, (jbyte)sa->getChar(sp++));
				while (sp < sl) {
					jchar c = sa->getChar(sp);
					if ( c < 0x80 ) {
						if (dp >= dl)
							return overflow(src, sp, dst, dp);
						da->setByte(dp++, jbyte(c));
					} else if (c < 0x800) {
						if (dl-dp < 2)
							return overflow(src, sp, dst, dp);
						da->setByte(dp++, jbyte(0xc0 | (c >> 6)));
						da->setByte(dp++, jbyte(0x80 | (c & 0x3f)));
					} else if (JCharacter::isSurrogate(c)) {
						if (sgp == null)
							sgp = new JSurrogate::JParser();
						jint uc = sgp->parse(c, sa, sp, sl);
						if (uc < 0){
							updatePositions(src, sp, dst, dp);
							return sgp->error();
						}
						if (dl - dp < 4)
							return overflow(src, sp, dst, dp);
						da->setByte(dp++, jbyte(0xf0 | ((uc>>18))));
						da->setByte(dp++, jbyte(0x80 | ((uc>>12) & 0x3f)));
						da->setByte(dp++, jbyte(0x80 | ((uc>>6) & 0x3f)));
						da->setByte(dp++, jbyte(0x80 | (uc & 0x3f)));
						sp++;
					} else {
						if (dl-dp < 3)
							return overflow(src, sp, dst, dp);
						da->setByte(dp++, jbyte(0xe0 | ((c>>12))));
						da->setByte(dp++, jbyte(0x80 | ((c>>6) & 0x3f)));
						da->setByte(dp++, jbyte(0x80 | (c & 0x3f)));
					}
					sp++;
				}
				updatePositions(src, sp, dst, dp);
				return JCoderResult::JUNDERFLOW;
			}

			JCoderResult* JUTF_8::JEncoder::encodeBufferLoop(JCharBuffer* src, JByteBuffer* dst) {
				jint mark = src->position();
				while (src->hasRemaining()) {
					jchar c = src->get();
					if (c < 0x80) {
						if (!dst->hasRemaining())
							return overflow(src, mark);
						dst->put((jbyte)c);
					} else if (c < 0x800){
						if (dst->remaining() < 2)
							return overflow(src, mark);
						dst->put((jbyte)(0xc0 | (c>>6)));
						dst->put((jbyte)(0x80 | (c&0x3f)));
					} else if (JCharacter::isSurrogate(c)) {
						if (sgp==null)
							sgp = new JSurrogate::JParser();
						jint uc = sgp->parse(c, src);
						if (uc < 0) {
							src->position(mark);
							return sgp->error();
						}
						if (dst->remaining() < 4)
							return overflow(src, mark);
						dst->put((jbyte)(0xf0 | ((uc >> 18))));
						dst->put((jbyte)(0x80 | ((uc >> 12) & 0x3f)));
						dst->put((jbyte)(0x80 | ((uc >> 6) & 0x3f)));
						dst->put((jbyte)(0x80 | (uc & 0x3f)));
						mark++;
					} else {
						if (dst->remaining() < 3)
							return overflow(src, mark);
						dst->put((jbyte)(0xe0 | ((c >> 12))));
						dst->put((jbyte)(0x80 | ((c >> 6) & 0x3f)));
						dst->put((jbyte)(0x80 | (c & 0x3f)));
					}
					mark++;
				}
				src->position(mark);
				return JCoderResult::JUNDERFLOW;
			}

			JCoderResult* JUTF_8::JEncoder::encodeLoop(JCharBuffer* src, JByteBuffer* dst) {
				if (src->hasArray() && dst->hasArray())
					return encodeArrayLoop(src, dst);
				else
					return encodeBufferLoop(src, dst);
			}

			jint JUTF_8::JEncoder::encode(JPrimitiveCharArray* sa, jint sp, jint len, JPrimitiveByteArray* da) {
				jint sl = sp + len;
				jint dp = 0;
				jint dlASCII = dp + min(len, da->size());

				while (dp < dlASCII && sa->getChar(sp) < 0x0080)
					da->setByte(dp++, (jbyte)sa->getChar(sp++));

				while ( sp < sl ){
					jchar c = sa->getChar(sp++);
					if (c < 0x80) {
						da->setByte(dp++, (jbyte)c);
					}else if ( c < 0x800) {
						da->setByte(dp++, (jbyte)(0xc0 | (c >> 6)));
						da->setByte(dp++, (jbyte)(0x80 | (c & 0x3f)));
					} else if (JCharacter::isSurrogate(c)) {
						if (sgp == null)
							sgp  = new JSurrogate::JParser();
						jint uc = sgp->parse(c, sa, sp-1, sl);
						if (uc < 0) {
							if (this->getMalformedInputAction() != JCodingErrorAction::REPLACE)
								return -1;
							da->setByte(dp++, getReplacement()->getByte(0));
						}else {
							da->setByte(dp++, (jbyte)(0xf0 | ((uc >> 18))));
							da->setByte(dp++, (jbyte)(0x80 | ((uc >> 12) & 0x3f)));
							da->setByte(dp++, (jbyte)(0x80 | ((uc >> 6) & 0x3f)));
							da->setByte(dp++, (jbyte)(0x80 | (uc & 0x3f)));
							sp++;
						}
					} else {
						da->setByte(dp++, (jbyte)(0xe0 | ((c >> 12))));
						da->setByte(dp++, (jbyte)(0x80 | ((c >> 6) & 0x3f)));
						da->setByte(dp++, (jbyte)(0x80 | (c & 0x3f)));
					}
				}
				return dp;
			}

			jbool JUTF_8::JEncoder::canEncode(jchar c) {
				return !JCharacter::isSurrogate(c);
			}

			jbool JUTF_8::JEncoder::isLegalReplacement(JPrimitiveByteArray* repl){
				return ((repl->size()==1 && repl->getByte(0) >= 0) ||
						JCharsetEncoder::isLegalReplacement(repl));
			}

			JUTF_8::JEncoder::~JEncoder() {
			}


			JUTF_8::JDecoder::JDecoder(JCharset* cs) : JCharsetDecoder(getClazz(), cs, 1.0f, 1.0f) {
			}

			jbool JUTF_8::JDecoder::isNotContinuation(jint b){
				return (b & 0xc0) != 0x80;
			}

			jbool JUTF_8::JDecoder::isMalformed2(jint b1, jint b2){
				return (b1 & 0x1e) == 0x0 || (b2 & 0xc0) != 0x80;
			}

			jbool JUTF_8::JDecoder::isMalformed3(jint b1, jint b2, jint b3){
				return (b1 == (jbyte)0xe0 && (b2 & 0xe0) == 0x80) ||
						(b2 & 0xc0) != 0x80 || (b3 & 0xc0) != 0x80;
			}

			jbool JUTF_8::JDecoder::isMalformed4(jint b2, jint b3, jint b4) {
				return (b2 & 0xc0) != 0x80 || (b3 & 0xc0) != 0x80 ||
						(b4 & 0xc0) != 0x80;
			}

			JCoderResult* JUTF_8::JDecoder::lookupN(JByteBuffer* src, jint n) {
				for (jint i=1; i < n; i++) {
					if (isNotContinuation(src->get()))
						return JCoderResult::malformedForLength(i);
				}
				return JCoderResult::malformedForLength(n);
			}

			JCoderResult* JUTF_8::JDecoder::malformedN(JByteBuffer* src, jint nb){
				jint b1;
				jint b2;
				switch(nb) {
				case 1:
					b1 = src->get();
					if ((b1 >> 2) == -2) {
						if (src->remaining() < 4)
							return JCoderResult::JUNDERFLOW;
						return lookupN(src, 5);
					}
					if ((b1 >> 1) == -2) {
						if (src->remaining() < 5)
							return JCoderResult::JUNDERFLOW;
						return lookupN(src, 6);
					}
					return JCoderResult::malformedForLength(1);
				case 2:
					return JCoderResult::malformedForLength(1);
				case 3:
					b1 = src->get();
					b2 = src->get();
					return JCoderResult::malformedForLength(
							((b1 == (jbyte)0xe0 && (b2 & 0xe0) == 0x80) ||
							 isNotContinuation(b2))?1:2);
				case 4:
					b1 = src->get() & 0xff;
					b2 = src->get() & 0xff;
					if (b1 > 0xf4 ||
						(b1 == 0xf0 && (b2 < 0x90 || b2 > 0xbf)) ||
						(b1 == 0xf4 && (b2 & 0xf0) != 0x80) ||
						isNotContinuation(b2))
						return JCoderResult::malformedForLength(1);
					if (isNotContinuation(src->get()))
						return JCoderResult::malformedForLength(2);
					return JCoderResult::malformedForLength(3);
				default:
					assert(false);
					return null;
				}
			}

			JCoderResult* JUTF_8::JDecoder::malformed(JByteBuffer* src, jint sp, JCharBuffer* dst, jint dp, jint nb) {
				src->position(sp - src->arrayOffset());
				JCoderResult* cr = malformedN(src, nb);
				updatePositions(src, sp, dst, dp);
				return cr;
			}

			JCoderResult* JUTF_8::JDecoder::malformed(JByteBuffer* src, jint mark, jint nb) {
				src->position(mark);
				JCoderResult* cr = malformedN(src, nb);
				src->position(mark);
				return cr;
			}

			JCoderResult* JUTF_8::JDecoder::xflow(JBuffer* src, jint sp, jint sl, JBuffer* dst, jint dp, jint nb) {
				updatePositions(src, sp, dst, dp);
				return  (nb == 0 || sl - sp < nb) ? JCoderResult::JUNDERFLOW : JCoderResult::JOVERFLOW;
			}

			JCoderResult* JUTF_8::JDecoder::xflow(JBuffer* src, jint mark, jint nb) {
				JCoderResult* cr = (nb == 0 || src->remaining() < (nb -1)) ? JCoderResult::JUNDERFLOW : JCoderResult::JOVERFLOW;
				src->position(mark);
				return cr;
			}

			JCoderResult* JUTF_8::JDecoder::decodeArrayLoop(JByteBuffer* src, JCharBuffer* dst) {
				JPrimitiveByteArray* sa = reinterpret_cast<JPrimitiveByteArray*>(src->array());
				jint sp = src->arrayOffset() + src->position();
				jint sl = src->arrayOffset() + src->limit();

				JPrimitiveCharArray* da = reinterpret_cast<JPrimitiveCharArray*>(dst->array());
				jint dp = dst->arrayOffset() + dst->position();
				jint dl = dst->arrayOffset() + dst->limit();
				jint dlASCII = dp + min(sl - sp, dl - dp);

				while (dp < dlASCII && sa->getByte(sp) >= 0)
					da->setChar(dp++, sa->getByte(sp++));

				while (sp < sl) {
					jint b1 = sa->getByte(sp);
					if (b1 >= 0) {
						if (dp >= dl)
							return xflow(src, sp, sl, dst, dp, 1);
						da->setChar(dp++, (jchar)b1);
						sp++;
					} else if ((b1 >> 5) == -2){
						if (sl - sp < 2 || dp >= dl)
							return xflow(src, sp, sl, dst, dp, 2);
						jint b2 = sa->getByte(sp+1);
						if (isMalformed2(b1, b2))
							return malformed(src, sp, dst, dp, 2);
						da->setChar(dp ++, (jchar) (((b1 << 6) ^ b2)
												^(((jbyte) 0xC0 << 6)
												^((jbyte) 0x80 << 0 ))));
						sp += 2;
					} else if ((b1 >> 4) == -2){
						if (sl - sp <3 || dp >= dl)
							return xflow(src, sp, sl, dst, dp, 3);
						jint b2 = sa->getByte(sp+1);
						jint b3 = sa->getByte(sp+2);
						if (isMalformed3(b1, b2, b3))
							return malformed(src, sp, dst, dp, 3);
						da->setChar(dp++, (jchar)
								((b1 << 12) ^
								 (b2 <<  6) ^
								 (b3 ^
								  (((jbyte) 0xE0 << 12) ^
								   ((jbyte) 0x80 <<  6) ^
								   ((jbyte) 0x80 <<  0)))));
						sp += 3;
					} else if ((b1 >> 3) == -2) {
						if (sl - sp < 4 || dl-dp < 2)
							return xflow(src, sp, sl, dst, dp, 4);
						jint b2 = sa->getByte(sp+1);
						jint b3 = sa->getByte(sp+2);
						jint b4 = sa->getByte(sp+3);
						jint uc = ((b1 << 18) ^
								   (b2 << 12) ^
								   (b3 <<  6) ^
								   (b4 ^
									(((jbyte) 0xF0 << 18) ^
									 ((jbyte) 0x80 << 12) ^
									 ((jbyte) 0x80 <<  6) ^
									 ((jbyte) 0x80 <<  0))));
						if (isMalformed4(b2, b3, b4) ||
							!JCharacter::isSupplementaryCodePoint(uc)){
							return malformed(src, sp, dst, dp, 4);
						}
						da->setChar(dp++, JCharacter::highSurrogate(uc));
						da->setChar(dp++, JCharacter::lowSurrogate(uc));
						sp += 4;
					} else
						return malformed(src, sp, dst, dp , 1);
				}
				return xflow(src, sp, sl, dst, dp, 0);
			}

			JCoderResult* JUTF_8::JDecoder::decodeBufferLoop(JByteBuffer* src, JCharBuffer* dst) {
				jint mark = src->position();
				jint limit = src->limit();
				while (mark < limit) {
					jint b1 = src->get();
					if (b1 >= 0) {
						if (dst->remaining() < 1)
							return xflow(src, mark, 1);
						dst->put((jchar)b1);
						mark++;
					} else if ((b1 >> 5) == -2) {
						if (limit - mark < 2 || dst->remaining() < 1)
							return xflow(src, mark, 2);
						jint b2 = src->get();
						if (isMalformed2(b1, b2))
							return malformed(src, mark, 2);
						dst->put((jchar)(((b1 << 6) ^ b2)
										^ (((jbyte) 0xC0 << 6) ^
										   ((jbyte) 0x80 << 0))));
						mark += 2;
					} else if ((b1 >> 4) == -2) {
						if (limit - mark < 3 || dst->remaining() < 1)
							return xflow(src, mark, 3);
						jint b2 = src->get();
						jint b3 = src->get();
						if (isMalformed3(b1, b2, b3))
							return malformed(src, mark, 3);
						dst->put((jchar)
								 ((b1 << 12) ^
								  (b2 <<  6) ^
								  (b3 ^
								   (((jbyte) 0xE0 << 12) ^
									((jbyte) 0x80 <<  0)))));
						mark += 3;
					} else if ((b1 >> 3) == -2) {
						if (limit - mark < 4 || dst->remaining() < 2)
							return xflow(src, mark, 4);
						jint b2 = src->get();
						jint b3 = src->get();
						jint b4 = src->get();
						jint uc = ((b1 << 18) ^
								   (b2 << 12) ^
								   (b3 <<  6) ^
								   (b4 ^
									(((jbyte) 0xF0 << 18) ^
									 ((jbyte) 0x80 << 12) ^
									 ((jbyte) 0x80 <<  6) ^
									 ((jbyte) 0x80 <<  0))));
						if (isMalformed4(b2, b3, b4) ||
							!JCharacter::isSupplementaryCodePoint(uc)) {
							return malformed(src, mark, 4);
						}
						dst->put(JCharacter::highSurrogate(uc));
						dst->put(JCharacter::lowSurrogate(uc));
						mark += 4;
					} else {
						return malformed(src, mark, 1);
					}
				}
				return xflow(src, mark, 0);
			}

			JCoderResult* JUTF_8::JDecoder::decodeLoop(JByteBuffer* src, JCharBuffer* dst) {
				if (src->hasArray() && dst->hasArray())
					return decodeArrayLoop(src, dst);
				else
					return decodeBufferLoop(src, dst);
			}

			JByteBuffer* JUTF_8::JDecoder::getByteBuffer(JByteBuffer* bb, JPrimitiveByteArray* ba, jint sp) {
				if (bb==null)
					bb = JByteBuffer::wrap(ba);
				bb->position();
				return bb;
			}

			jint JUTF_8::JDecoder::decode(JPrimitiveByteArray* sa, jint sp, jint len, JPrimitiveCharArray* da) {
				const jint sl = sp + len;
				jint dp = 0;
				jint dlASCII = min(len, da->size());
				JByteBuffer* bb = null;

				while (dp < dlASCII && sa->getByte(sp) >= 0)
					da->setChar(dp++, (jchar)sa->getByte(sp++));

				while (sp < sl) {
					jint b1 = sa->getByte(sp++);
					if (b1 >= 0) {
						da->setChar(dp++, (jchar)b1);
					} else if ((b1 >> 5) == -2) {
						if (sp < sl) {
							jint b2 = sa->getByte(sp++);
							if (isMalformed2(b1, b2)) {
								if (getMalformedInputAction() != JCodingErrorAction::REPLACE)
									return -1;
								da->setChar(dp++, getReplacement()->charAt(0));
								sp--;
							} else {
								da->setChar(dp++, (jchar)(((b1 << 6) ^ b2)^
												(((jbyte) 0xC0 << 6) ^
												 ((jbyte) 0x80 << 0))));
							}
							continue;
						}
						if (getMalformedInputAction() != JCodingErrorAction::REPLACE)
							return -1;
						da->setChar(dp++, getReplacement()->charAt(0));
						return dp;
					} else if ((b1 >> 4) == -2) {
						if (sp + 1 < sl) {
							jint b2 = sa->getByte(sp++);
							jint b3 = sa->getByte(sp++);
							if (isMalformed3(b1,b2,b3)) {
								if (getMalformedInputAction() != JCodingErrorAction::REPLACE)
									return -1;
								da->setChar(dp++, getReplacement()->charAt(0));
								sp -= 3;
								bb = getByteBuffer(bb, sa, sp);
								sp += malformedN(bb, 3)->getLength();
							} else {
								da->setChar(dp++, (jchar)((b1 << 12) ^
														  (b2 <<  6) ^
														  (b3 ^
														  (((jbyte) 0xE0 << 12) ^
														  ((jbyte) 0x80 <<  6) ^
														  ((jbyte) 0x80 <<  0)))));
							}
							continue;
						}
						if (getMalformedInputAction() != JCodingErrorAction::REPLACE)
							return -1;
						da->setChar(dp++, getReplacement()->charAt(0));
						return dp;
					} else if ((b1 >> 3) == -2) {
						if (sp + 2 < sl) {
							jint b2 = sa->getByte(sp++);
							jint b3 = sa->getByte(sp++);
							jint b4 = sa->getByte(sp++);
							jint uc = ((b1 << 18) ^
									   (b2 << 12) ^
									   (b3 <<  6) ^
									   (b4 ^
										(((jbyte) 0xF0 << 18) ^
										((jbyte) 0x80 << 12) ^
										((jbyte) 0x80 <<  6) ^
										((jbyte) 0x80 <<  0))));
							if (isMalformed4(b2,b3,b4) ||
								!JCharacter::isSupplementaryCodePoint(uc)) {
								if (getMalformedInputAction() != JCodingErrorAction::REPLACE)
									return -1;
								da->setChar(dp++, getReplacement()->charAt(0));
								sp -= 4;
								bb = getByteBuffer(bb, sa, sp);
								sp += malformedN(bb, 4)->getLength();
							} else {
								da->setChar(dp++, JCharacter::highSurrogate(uc));
								da->setChar(dp++, JCharacter::lowSurrogate(uc));
							}
							continue;
						}
						if (getMalformedInputAction() != JCodingErrorAction::REPLACE)
							return -1;
						da->setChar(dp++, getReplacement()->charAt(0));
						return dp;
					} else {
						if (getMalformedInputAction() != JCodingErrorAction::REPLACE)
							return -1;
						da->setChar(dp++, getReplacement()->charAt(0));
						sp--;
						bb = getByteBuffer(bb, sa, sp);
						JCoderResult* cr = malformedN(bb, 1);
						if (!cr->isError()){
							return dp;
						}
						sp += cr->getLength();
					}
				}
				return dp;
			}

			JUTF_8::JDecoder::~JDecoder() {
			}


		}
	}
}
