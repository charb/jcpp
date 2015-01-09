#ifndef JCPP_NIO_CHANNEL_JREADABLEBYTECHANNEL_H
#define JCPP_NIO_CHANNEL_JREADABLEBYTECHANNEL_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/nio/JByteBuffer.h"
#include "jcpp/nio/channels/JChannel.h"

using namespace jcpp::lang;

namespace jcpp {
	namespace nio {
		namespace channels {

		// @Class(canonicalName="java.nio.channels.ReadableByteChannel", simpleName="ReadableByteChannel");
		class JCPP_EXPORT JReadableByteChannel : public JChannel {
		public:
			static JClass* getClazz();

			virtual jint read(JByteBuffer* dst) = 0;

			virtual ~JReadableByteChannel();

		};


		}
	}
}



#endif /* JREADABLEBYTECHANNEL_H_ */
