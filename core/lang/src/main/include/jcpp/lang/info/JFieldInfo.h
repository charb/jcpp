#ifndef JCPP_LANG_INFO_JFIELDINFO_H
#define JCPP_LANG_INFO_JFIELDINFO_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JPrimitiveLong.h"

using namespace jcpp::lang;


namespace jcpp{
	namespace lang{
		namespace info{

			class JObjectInfo;
			class JClassInfo;

			// @Class(canonicalName="java.lang.info.FieldInfo", simpleName="FieldInfo");
			class JCPP_EXPORT JFieldInfo : public JObject {
				private:
					JString *name;
					JPrimitiveLong *address;
					jbool bStaticField;
				public:
					static jcpp::lang::JClass* getClazz();
					JFieldInfo(JString* _name, JPrimitiveLong *_address);

					JFieldInfo(JString* _name, JPrimitiveLong *_address, jbool _bStaticField);

					JString *getName();

					JPrimitiveLong *getAddress();

					jbool isStaticField();

					virtual ~JFieldInfo();
			};

		}
	}
}

#endif
