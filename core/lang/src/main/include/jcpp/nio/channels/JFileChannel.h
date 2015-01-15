#ifndef JCPP_NIO_CHANNELS_JFILECHANNEL_H
#define JCPP_NIO_CHANNELS_JFILECHANNEL_H

#include "jcpp/nio/JByteBuffer.h"
#include "jcpp/lang/JString.h"
#include "jcpp/nio/channels/JAbstractInterruptibleChannel.h"
#include "jcpp/nio/channels/JByteChannel.h"
#include "jcpp/nio/channels/JGatheringByteChannel.h"
#include "jcpp/nio/channels/JScatteringByteChannel.h"


namespace jcpp {
	namespace nio {
		namespace channels {

		class JFileLock;

		// @Class(canonicalName="java.nio.channels.FileChannel", simpleName="FileChannel");
		class JCPP_EXPORT JFileChannel : public JAbstractInterruptibleChannel, public JByteChannel, public JGatheringByteChannel, public JScatteringByteChannel {
		protected:
			JFileChannel();

		public:
			static JClass* getClazz();

			virtual jint read(JByteBuffer* dst) = 0;
			virtual jlong read(JPrimitiveObjectArray* dsts, jint offset, jint length) = 0;
			virtual jlong read(JPrimitiveObjectArray* dsts);
			virtual jint write(JByteBuffer* src) = 0;
			virtual jlong write(JPrimitiveObjectArray* srcs, jint offset, jint length) = 0;
			virtual jlong write(JPrimitiveObjectArray* srcs);
			virtual jlong position() = 0;
			virtual JFileChannel* position(jlong newPosition) = 0;
			virtual jlong size() = 0;
			virtual JFileChannel* truncate(jlong size) = 0;
			virtual void force(jbool metaData) = 0;
			virtual jlong transferTo(jlong position, jlong count, JWritableByteChannel* target) = 0;
			virtual jlong transferFrom(JReadableByteChannel* src, jlong position, jlong count) = 0;
			virtual jint read(JByteBuffer* dst, jlong position) = 0;
			virtual jint write(JByteBuffer* src, jlong position) = 0;

			virtual JFileLock* lock(jlong position, jlong size, jbool shared) = 0;
			JFileLock* lock();
			virtual JFileLock* tryLock(jlong position, jlong size, jbool shared) = 0;
			JFileLock* tryLock();

			virtual ~JFileChannel();
		};

		}
	}
}



#endif /* JFILECHANNEL_H_ */
