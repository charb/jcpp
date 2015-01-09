#ifndef JCPP_TEST_ENUM_SAMPLE_OBJECT_H
#define JCPP_TEST_ENUM_SAMPLE_OBJECT_H

#include "jcpp/lang/JString.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JEnum.h"
#include "jcpp/lang/JPrimitiveInt.h"

using namespace jcpp::lang;
using namespace jcpp::io;

namespace jcpp{

    //@Class(canonicalName="jcpp.EnumSampleObject", simpleName="EnumSampleObject");
    class JCPP_EXPORT JEnumSampleObject : public JEnum{
    protected:

        JString* strField;
        JPrimitiveInt* iField;

        JEnumSampleObject(JString* strField, JPrimitiveInt* i, JString* name, JPrimitiveInt* ordinal);

    public:

        static JClass* getClazz();

        static JEnumSampleObject* ENUM1;

        static JEnumSampleObject* ENUM2;

        static JEnumSampleObject* ENUM3;

        static JEnumSampleObject* ENUM4;

        static JEnumSampleObject* ENUM5;

        virtual JString* getStringField();

        virtual jint getIntField();

        virtual JString* toString();

        virtual ~JEnumSampleObject();
    };
}
#endif
