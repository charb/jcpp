#ifndef JCPP_RMI_SERVER_CONNECTION_JCONNECTIONEXCEPTION_H
#define JCPP_RMI_SERVER_CONNECTION_JCONNECTIONEXCEPTION_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JException.h"

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace connection{
            // @Class(canonicalName="jcpp.rmi.server.connection.ConnectionException", simpleName="ConnectionException");
                class JCPP_EXPORT JConnectionException : public JException{
            	private:
            		static const jlong serialVersionUID = 1470950606719849553LL;

                protected:
                    JConnectionException(JClass* _class);

                public:
                    JConnectionException();

                    JConnectionException(JString* message);

                    JConnectionException(JString* message,JThrowable* cause);

                    static JClass* getClazz();

                    virtual ~JConnectionException();
                };
            }
        }
    }
}

#endif
