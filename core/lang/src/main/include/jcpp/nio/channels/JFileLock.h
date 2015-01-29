#ifndef JCPP_NIO_CHANNELS_JFILELOCK_H
#define JCPP_NIO_CHANNELS_JFILELOCK_H

#include "jcpp/nio/channels/JFileChannel.h"

namespace jcpp {
	namespace nio {
		namespace channels {

		// @Class(canonicalName="java.nio.channels.FileLock", simpleName="FileLock");
		class JCPP_EXPORT JFileLock : public JObject {
		private:
			JFileChannel* _channel;
			jlong _position;
			jlong _size;
			jbool shared;

		protected:
			JFileLock(JFileChannel* channel, jlong position, jlong size, jbool shared);

		public:
			static JClass* getClazz();

			JFileChannel* channel();
			jlong position();
			jlong size();
			jbool isShared();
			jbool overlaps(jlong position, jlong size);
			virtual jbool isValid() = 0;
			virtual void release() = 0;
			JString* toString();

			virtual ~JFileLock();
		};

		}
	}
}

#endif /* JFILELOCK_H_ */
