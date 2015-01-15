#ifndef JGATHERINGBYTECHANNEL_H
#define JGATHERINGBYTECHANNEL_H

#include "jcpp/nio/channels/JWritableByteChannel.h"

namespace jcpp {
	namespace nio {
		namespace channels {

		// @Class(canonicalName="java.nio.channels.GatheringByteChannel", simpleName="GatheringByteChannel");
		class JCPP_EXPORT JGatheringByteChannel : public JWritableByteChannel {
		public:
			static JClass* getClazz();

			virtual jlong write(JPrimitiveObjectArray* srcs, jint offset, jint lenght) = 0;

			virtual jlong write(JPrimitiveObjectArray* srcs) = 0;

			virtual ~JGatheringByteChannel();
		};

		}
	}
}

#endif /* JGATHERINGBYTECHANNEL_H_ */
