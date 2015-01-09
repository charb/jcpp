#include "jcpp/io/JLineNumberReader.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JIllegalArgumentException.h"

namespace jcpp {
	namespace io {

		JLineNumberReader::JLineNumberReader(JReader* in, jint sz) :
				JBufferedReader(getClazz(), in, sz) {
			lineNumber = 0;
			markedLineNumber = 0;
			skipLF = false;
			markedSkipLF = false;
			skipBuffer = null;
		}

		JLineNumberReader::JLineNumberReader(JReader* in) :
				JBufferedReader(getClazz(), in) {
			lineNumber = 0;
			markedLineNumber = 0;
			skipLF = false;
			markedSkipLF = false;
			skipBuffer = null;
		}

		void JLineNumberReader::setLineNumber(jint lineNumber) {
			this->lineNumber = lineNumber;
		}

		jint JLineNumberReader::getLineNumber() {
			return lineNumber;
		}

		jint JLineNumberReader::read() {
			synchronized(lock, {
				jint c = JBufferedReader::read();
				if (skipLF) {
					if (c == '\n') {
						c = JBufferedReader::read()
						;
					}
					skipLF = false
					;
				}
				switch (c) {
				case '\r':
					skipLF = true
					;
				case '\n':
					lineNumber++
					;
					return '\n';
				}
				return c;
			}
		)
	}

	jint JLineNumberReader::read(JPrimitiveCharArray* cbuf, jint off, jint len) {
		synchronized(lock, {
			jint n = JBufferedReader::read(cbuf, off, len);
			for (jint i = off; i < off + n; i++) {
				jint c = cbuf->getChar(i);
				if (skipLF) {
					skipLF = false
					;
					if (c == '\n') {
						continue;
					}
				}
				switch (c) {
				case '\r':
					skipLF = true
					;
				case '\n':
					lineNumber++
					;
					break;
				}
			}
			return n;
		}
	)
}

JString* JLineNumberReader::readLine() {
	synchronized(lock, { JString* l = JBufferedReader::readLine(skipLF); skipLF = false; if (l!=null){ lineNumber++; } return l; })
}

jlong JLineNumberReader::skip(jlong n) {
	if (n < 0) {
		throw new JIllegalArgumentException(new JString("skip() value is negative"));
	}
	jint nn = (n < 8192 ? n : 8192);
	synchronized(lock, { if (skipBuffer == null || skipBuffer->size() < nn){ skipBuffer = new JPrimitiveCharArray(nn); } jlong r = n; while (r > 0) { jint nc = read(skipBuffer, 0, (r < nn ? r : nn)); if (nc == -1){ break; } r -= nc; } return n - r; })
}

void JLineNumberReader::mark(jint m) {
	synchronized(lock, {
		JBufferedReader::mark(m)
		;
		markedLineNumber = lineNumber
		;
		markedSkipLF = skipLF
		;
	}
)
}

void JLineNumberReader::reset() {
synchronized(lock, {
	JBufferedReader::reset()
	;
	lineNumber = markedLineNumber
	;
	skipLF = markedSkipLF
	;
}
)
}

JLineNumberReader::~JLineNumberReader() {
}
}
}
