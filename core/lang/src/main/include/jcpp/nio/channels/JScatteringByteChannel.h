#ifndef JSCATTERINGBYTECHANNEL_H
#define JSCATTERINGBYTECHANNEL_H

#include "jcpp/nio/channels/JReadableByteChannel.h"

namespace jcpp {
	namespace nio {
		namespace channels {

		// @Class(canonicalName="java.nio.channels.ScatteringByteChannel", simpleName="ScatteringByteChannel");
		class JCPP_EXPORT JScatteringByteChannel : public JReadableByteChannel {
		public:
			static JClass* getClazz();

			jlong read(JPrimitiveObjectArray* dsts, jint offset, jint length);

			jlong read(JPrimitiveObjectArray* dsts);

			virtual ~JScatteringByteChannel();
		};

		}
	}
}



#endif /* JSCATTERINGBYTECHANNEL_H_ */
