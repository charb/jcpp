#ifndef JCPP_NIO_CHANNELS_JCHANNEL_H
#define JCPP_NIO_CHANNELS_JCHANNEL_H

#include "jcpp/io/JCloseable.h"

using namespace jcpp::io;

namespace jcpp {
	namespace nio {
		namespace channels {

		// @Class(canonicalName="java.nio.channels.Channel", simpleName="Channel");
		class JCPP_EXPORT JChannel : public JCloseable {
		public:
			static JClass* getClazz();

			virtual jbool isOpen() = 0;

			virtual void close() = 0;

			virtual ~JChannel();
		};

		}
	}
}



#endif /* JCHANNEL_H_ */
