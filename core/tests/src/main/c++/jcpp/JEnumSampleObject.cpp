#include "jcpp/JEnumSampleObject.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JField.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JStringBuilder.h"

using namespace jcpp::lang::reflect;
using namespace jcpp::lang;

namespace jcpp{

    JEnumSampleObject::JEnumSampleObject(JString* strField, JPrimitiveInt* i, JString* name, JPrimitiveInt* ordinal):JEnum(dynamic_cast<JEnumClass*>(getClazz()),name,ordinal){
        this->strField=strField;
        this->iField=i;
    }

    JEnumSampleObject* JEnumSampleObject::ENUM1 = new JEnumSampleObject(new JString("ENUM1"),new JPrimitiveInt(1),new JString("ENUM1"),new JPrimitiveInt(0));

    JEnumSampleObject* JEnumSampleObject::ENUM2 = new JEnumSampleObject(new JString("ENUM2"),new JPrimitiveInt(2),new JString("ENUM2"),new JPrimitiveInt(1));

    JEnumSampleObject* JEnumSampleObject::ENUM3 = new JEnumSampleObject(new JString("ENUM3"),new JPrimitiveInt(3),new JString("ENUM3"),new JPrimitiveInt(2));

    JEnumSampleObject* JEnumSampleObject::ENUM4 = new JEnumSampleObject(new JString("ENUM4"),new JPrimitiveInt(4),new JString("ENUM4"),new JPrimitiveInt(3));

    JEnumSampleObject* JEnumSampleObject::ENUM5 = new JEnumSampleObject(new JString("ENUM5"),new JPrimitiveInt(5),new JString("ENUM5"),new JPrimitiveInt(4));

    JString* JEnumSampleObject::getStringField(){
        return strField;
    }

    jint JEnumSampleObject::getIntField(){
        return iField->get();
    }

    JString* JEnumSampleObject::toString(){
        JStringBuilder* builder=new JStringBuilder();
        builder->append(JEnum::toString());
        builder->append("[StrField:")->append(strField)
               ->append(",IField:")->append(iField->get())
               ->append(']');
        return builder->toString();
    }

    JEnumSampleObject::~JEnumSampleObject(){
    }
}
