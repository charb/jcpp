#include "jcpp/nio/charset/JCharset.h"
#include "jcpp/nio/cs/JUTF_8.h"
#include <string.h>


namespace jcpp {
	namespace nio {
		namespace charset {

		JCharset::JCharset(jcpp::lang::JClass* _class, JString* canonicalName, JPrimitiveObjectArray* aliases)
			:	JObject(_class)
		{
			checkName(canonicalName);
			JPrimitiveObjectArray* as = (aliases == null)? new JPrimitiveObjectArray(JString::getClazz(),0) : aliases;
			for (int i=0; i < as->size(); i++)
				checkName(dynamic_cast<JString*>(as->get(i)));
			this->name = canonicalName;
			this->aliases = as;
		}

		void JCharset::checkName(JString* s){
			int n = s->length();
			if (n==0)
				throw new JIllegalArgumentException(s);

			for (int i=0; i<n; i++){
				jchar c = s->charAt(i);
				if (c >= 'A' && c <= 'Z')	continue;
				if (c >= 'a' && c <= 'a')	continue;
				if (c >= '0' && c <= '9')	continue;
				if (c == '-' && i != 0)		continue;
				if (c == '+' && i != 0)		continue;
				if (c == ':' && i != 0)		continue;
				if (c == '_' && i != 0)		continue;
				if (c == '.' && i != 0)		continue;
				throw new JIllegalCharsetNameException(s);
			}
		}

		JCharset* JCharset::lookup(JString* charsetName)
		{
			if (charsetName == null)
				throw new JIllegalArgumentException(new JString("Null charset name"));
			return lookup2(charsetName);
		}

		JCharset* JCharset::lookup2(JString* charsetName)
		{
			JCharset* cs;
			//TODO

			//FIXME remove the following, replace with actual lookup
			if (charsetName->equals(new JString("UTF-8"))){
				return new JUTF_8();
			}
			return null;
		}

		JCharset* JCharset::forName(JString* charsetName)
		{
			JCharset* cs = lookup(charsetName);
			if (cs != null)
				return cs;
			throw new JUnsupportedCharsetException(charsetName);
		}

		JCharset* JCharset::defaultCharset()
		{
			return forName(new JString("UTF-8"));
		}

		jbool JCharset::isSupported(JString* charsetName){
			return (lookup(charsetName) != null);
		}

		JString* JCharset::getName(){
			return this->name;
		}

		jint JCharset::compareTo(JObject* that){
			return name->compareToIgnoreCase((reinterpret_cast<JCharset*>(that))->name);
		}

		JCharset::~JCharset()
		{	}


		}
	}
}
