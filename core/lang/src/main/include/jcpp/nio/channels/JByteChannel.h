#ifndef JCPP_NIO_CHANNELS_JBYTECHANNEL_H
#define JCPP_NIO_CHANNELS_JBYTECHANNEL_H

#include "jcpp/nio/channels/JReadableByteChannel.h"
#include "jcpp/nio/channels/JWritableByteChannel.h"

namespace jcpp {
	namespace nio {
		namespace channels {

		// @Class(canonicalName="java.nio.channels.ByteChannel", simpleName="ByteChannel");
		class JCPP_EXPORT JByteChannel : public JReadableByteChannel, public JWritableByteChannel {
		public:
			static JClass* getClazz();

			virtual ~JByteChannel();
		};

		}
	}
}



#endif /* JBYTECHANNEL_H_ */
