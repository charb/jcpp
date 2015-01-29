#ifndef JCPP_NIO_CHANNELS_JABSTRACTINTERRUPTIBLECHANNEL_H
#define JCPP_NIO_CHANNELS_JABSTRACTINTERRUPTIBLECHANNEL_H

#include "jcpp/nio/channels/JChannel.h"
#include "jcpp/nio/channels/JInterruptibleChannel.h"

namespace jcpp {
	namespace nio {
		namespace channels {

		// @Class(canonicalName="java.nio.channels.AbstractInterruptibleChannel", simpleName="AbstractInterruptibleChannel");
		class JCPP_EXPORT JAbstractInterruptibleChannel : public JObject, public JChannel, public JInterruptibleChannel {
		private:
			JObject* closeLock;
			/*volatile*/ jbool open;
			//TODO JInterruptible interruptor;
			jbool interrupted;

		protected:
			JAbstractInterruptibleChannel(jcpp::lang::JClass* clazz);
			virtual void implCloseChannel() = 0;
			void begin();
			void end(jbool completed);

		public:
			static JClass* getClazz();

			void close();
			jbool isOpen();


		};

		}
	}
}



#endif /* JABSTRACTINTERRUPTIBLECHANNEL_H_ */
