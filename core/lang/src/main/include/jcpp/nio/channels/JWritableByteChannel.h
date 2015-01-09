#ifndef JCPP_NIO_CHANNELS_JWRITABLEBYTECHANNEL_H
#define JCPP_NIO_CHANNELS_JWRITABLEBYTECHANNEL_H

#include "jcpp/nio/channels/JChannel.h"
#include "jcpp/nio/JByteBuffer.h"

namespace jcpp {
	namespace nio {
		namespace channels {

		// @Class(canonicalName="java.nio.channels.WritableByteChannelClass", simpleName="WritableByteChannelClass");
		class JCPP_EXPORT JWritableByteChannel : public JChannel {
		public:
			static JClass* getClazz();

			virtual jint write(JByteBuffer* src) = 0;

			virtual ~JWritableByteChannel();
		};

		}
	}
}



#endif /* JWRITABLEBYTECHANNEL_H_ */
