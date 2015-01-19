#ifndef JCPP_RMI_SERVER_JSAMPLEOBJECT_H
#define JCPP_RMI_SERVER_JSAMPLEOBJECT_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JPrimitiveBoolean.h"
#include "jcpp/lang/JPrimitiveByte.h"
#include "jcpp/lang/JPrimitiveChar.h"
#include "jcpp/lang/JPrimitiveDouble.h"
#include "jcpp/lang/JPrimitiveFloat.h"
#include "jcpp/lang/JPrimitiveInt.h"
#include "jcpp/lang/JPrimitiveLong.h"
#include "jcpp/lang/JPrimitiveShort.h"
#include "jcpp/io/JSerializable.h"
#include "jcpp/rmi/server/JIRemoteSample.h"

using namespace jcpp::io;

namespace jcpp{
    namespace rmi{
        namespace server{
            class JIRemoteSample;

        	// @Class(canonicalName="jcpp.rmi.server.SampleObject", simpleName="SampleObject");
            class JSampleObject : public JObject, public JSerializable {
            protected:
                static const jlong serialVersionUID = 40;
                JPrimitiveBoolean* bool1;
                JPrimitiveByte* byte1;
                JPrimitiveChar* c1;
                JPrimitiveDouble* d1;
                JPrimitiveFloat* f1;
                JPrimitiveLong* l1;
                JPrimitiveShort* s1;
                JPrimitiveInt* i1;
                JIRemoteSample* rs;
                friend class JSampleObjectClass;

            public:
                JSampleObject();

                static JClass* getClazz();

                virtual JPrimitiveBoolean* getBool1();

                virtual void setBool1(JPrimitiveBoolean* bool1);

                virtual JPrimitiveByte* getByte1();

                virtual void setByte1(JPrimitiveByte* byte1);

                virtual JPrimitiveChar* getC1();

                virtual void setC1(JPrimitiveChar* c1);

                virtual JPrimitiveDouble* getD1();

                virtual void setD1(JPrimitiveDouble* d1);

                virtual JPrimitiveFloat* getF1();

                virtual void setF1(JPrimitiveFloat* f1);

                virtual JPrimitiveLong* getL1();

                virtual void setL1(JPrimitiveLong* l1);

                virtual JPrimitiveShort* getS1();

                virtual void setS1(JPrimitiveShort* s1);

                virtual JPrimitiveInt* getI1();

                virtual void setI1(JPrimitiveInt* i1);

                virtual JIRemoteSample* getRemoteSample();

                virtual void setRemoteSample(JIRemoteSample* rs);

                virtual jbool equals(JObject* other);
                
                virtual JString* toString();

                virtual ~JSampleObject();
            };
        }
    }
}

#endif
