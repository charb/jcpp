#ifndef JCPP_NIO_CHANNELS_JINTERRUPTIBLECHANNEL_H
#define JCPP_NIO_CHANNELS_JINTERRUPTIBLECHANNEL_H

#include "jcpp/lang/JInterface.h"

using namespace jcpp::lang;

namespace jcpp {
	namespace nio {
		namespace channels {

		// @Class(canonicalName="java.nio.channels.InterruptibleChannel", simpleName="InterruptibleChannel");
		class JCPP_EXPORT JInterruptibleChannel : public JInterface {
		public:
			static JClass* getClazz();

			void close();

			~JInterruptibleChannel();
		};

		}
	}
}



#endif /* JINTERRUPTIBLECHANNEL_H_ */
