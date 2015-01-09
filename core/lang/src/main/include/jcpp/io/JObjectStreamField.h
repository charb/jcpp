#ifndef JCPP_IO_JOBJECTSTREAMFIELD_H
#define JCPP_IO_JOBJECTSTREAMFIELD_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/reflect/JField.h"
#include "jcpp/lang/JString.h"
#include "jcpp/lang/JComparable.h"

using namespace jcpp::lang::reflect;
using namespace jcpp::lang;

namespace jcpp{
    namespace io{

    	//@Class(canonicalName="java.io.ObjectStreamField", simpleName="ObjectStreamField");
        class JCPP_EXPORT JObjectStreamField : public JObject, public JComparable{
        private:
            JString* name;
            JString* signature;
            jcpp::lang::JClass* type;
            jbool unshared;
            JField* field;
            jint offset;
            JString* typeString;
            void setTypeString();

        public:
            JObjectStreamField();

            JObjectStreamField(JString* name,jcpp::lang::JClass* type);

            JObjectStreamField(JString* name,jcpp::lang::JClass* type,jbool unshared);

            JObjectStreamField(JString* name,JString* signature,jbool unshared);

            JObjectStreamField(JField* field,jbool unshared,jbool showType);

            static jcpp::lang::JClass* getClazz();

            virtual JString* getName();

            virtual jcpp::lang::JClass* getType();

            virtual jchar getTypeCode();

            virtual JString* getTypeString();

            virtual jint getOffset();

            virtual void setOffset(jint offset);

            virtual jbool isPrimitive();

            virtual jbool isUnshared();

            virtual JField* getField();

            virtual JString* getSignature();

            virtual JString* toString();

            virtual jint compareTo(JObject* o);

            virtual ~JObjectStreamField();
        };
    }
}

#endif
