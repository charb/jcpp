#include "jcpp/nio/channels/JFileLock.h"
#include "jcpp/lang/JIllegalArgumentException.h"

namespace jcpp {
	namespace nio {
		namespace channels {

		JFileLock::JFileLock(JFileChannel* channel, jlong position, jlong size, jbool shared) {
			if (position < 0)
				throw new JIllegalArgumentException(new JString("Negative position"));
			if (size < 0)
				throw new JIllegalArgumentException(new JString("Negative size"));
			if (position + size < 0)
				throw new JIllegalArgumentException(new JString("Negative position + size"));
			this->_channel = channel;
			this->_position = position;
			this->_size = size;
			this->shared = shared;
		}

		JFileChannel* JFileLock::channel() {
			return _channel;
		}

		jlong JFileLock::position() {
			return _position;
		}

		jlong JFileLock::size() {
			return _size;
		}

		jbool JFileLock::isShared() {
			return shared;
		}

		jbool JFileLock::overlaps(jlong position, jlong size) {
			if (position + size <= this->_position)
				return false;
			if (this->_position + this->_size <= position)
				return false;
			return true;
		}

		JString* JFileLock::toString() {
			JStringBuilder* sb = new JStringBuilder();
			sb->append(getClazz()->getName());
			sb->append("["); sb->append(this->_position);
			sb->append(":"); sb->append(this->_size);
			sb->append(" "); sb->append(shared? "shared" : "exclusive");
			sb->append(" "); sb->append(isValid()? "valid" : "invalid");
			sb->append("]");
			return sb->toString();
		}

		JFileLock::~JFileLock() {
		}

		}
	}
}
