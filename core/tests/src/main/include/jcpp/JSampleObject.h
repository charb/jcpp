#ifndef JCPP_TEST_SAMPLE_OBJECT_H
#define JCPP_TEST_SAMPLE_OBJECT_H

#include "jcpp/lang/JString.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JPrimitiveInt.h"
#include "jcpp/lang/JPrimitiveLong.h"
#include "jcpp/lang/JPrimitiveShort.h"
#include "jcpp/lang/JPrimitiveFloat.h"
#include "jcpp/lang/JPrimitiveDouble.h"
#include "jcpp/lang/JPrimitiveBoolean.h"
#include "jcpp/lang/JPrimitiveChar.h"
#include "jcpp/lang/JPrimitiveByte.h"
#include "jcpp/io/JSerializable.h"

using namespace jcpp::lang;
using namespace jcpp::io;

namespace jcpp{

    //@Class(canonicalName="jcpp.SampleObject", simpleName="SampleObject");
    class JCPP_EXPORT JSampleObject : public JObject, public JSerializable{
    protected:
    	JPrimitiveInt* i;
    	JPrimitiveLong* l;
    	JPrimitiveShort* s;
    	JPrimitiveFloat* f;
    	JPrimitiveDouble* d;
    	JPrimitiveBoolean* bo;
    	JPrimitiveChar* c;
    	JPrimitiveByte* by;

    public:
        JSampleObject();

        JSampleObject(jint i,jlong l,jshort s,jfloat f,jdouble d,jbool bo,jchar c,jbyte by);

        static JClass* getClazz();

        virtual jint getInt();

        virtual void setInt(jint i);

        virtual jlong getLong();

        virtual void setLong(jlong l);

        virtual jshort getShort();

        virtual void setShort(jshort s);

        virtual jfloat getFloat();

        virtual void setFloat(jfloat f);

        virtual jdouble getDouble();

        virtual void setDouble(jdouble d);

        virtual jbool getBoolean();

        virtual void setBoolean(jbool b);

        virtual jchar getChar();

        virtual void setChar(jchar c);

        virtual jbyte getByte();

        virtual void setByte(jbyte b);

        virtual JString* toString();

        virtual jbool equals(JObject* obj);

        virtual ~JSampleObject();
    };
}
#endif
