#ifndef JCPP_RMI_SERVER_CONNECTION_JOBJECTPOINTER_H
#define JCPP_RMI_SERVER_CONNECTION_JOBJECTPOINTER_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/io/JSerializable.h"
#include "jcpp/rmi/server/transport/JEndPoint.h"

using namespace jcpp::io;
using namespace jcpp::rmi::server::transport;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace connection{
                // @Class(canonicalName="jcpp.rmi.server.connection.ObjectPointer", simpleName="ObjectPointer");
                class JCPP_EXPORT JObjectPointer : public JObject, public JSerializable{
                    protected:
                        JString* id;
                        JEndPoint* endPoint;
                        static const jlong serialVersionUID = 1L;

                    public:
                        JObjectPointer();
                        
                        JObjectPointer(JEndPoint* endPoint, JString* id);
                        
                        static JClass* getClazz();
                        
                        virtual JEndPoint* getEndPoint();
                        
                        virtual void setEndPoint(JEndPoint* endPoint);
                        
                        virtual JString* getId();
                        
                        virtual void setId(JString* id);
                        
                        virtual jbool equals(JObject* other);
                        
                        virtual jint hashCode();
                        
                        virtual JString* toString();
                        
                        virtual ~JObjectPointer();
                };
            }
        }
    }
}

#endif
