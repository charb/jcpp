#ifndef ORG_XML_SAX_INPUT_SOURCE_H
#define ORG_XML_SAX_INPUT_SOURCE_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/io/JInputStream.h"
#include "jcpp/io/JReader.h"

using namespace jcpp::io;

namespace org{
    namespace xml{
        namespace sax{

        	// @Class(canonicalName="org.xml.sax.InputSource", simpleName="InputSource");
            class JCPP_EXPORT JInputSource : public JObject{
            protected:
                JString* publicId;
                JString* systemId;
                JInputStream* byteStream;
                JString* encoding;
                JReader* characterStream;

            public:
                JInputSource();

                JInputSource(JString* systemId);

                JInputSource(JInputStream* byteStream);

                JInputSource(JReader* characterStream);

                static JClass* getClazz();

                virtual void setPublicId(JString* publicId);

                virtual JString* getPublicId();

                virtual void setSystemId(JString* systemId);

                virtual JString* getSystemId();

                virtual void setByteStream(JInputStream* byteStream);

                virtual JInputStream* getByteStream();

                virtual void setEncoding(JString* encoding);

                virtual JString* getEncoding();

                virtual void setCharacterStream(JReader* characterStream);

                virtual JReader* getCharacterStream();

                virtual ~JInputSource();
            };
        }
    }
}

#endif
