#include "org/xml/sax/JInputSource.h"
#include "jcpp/lang/JClass.h"

namespace org{
    namespace xml{
        namespace sax{

            JInputSource::JInputSource():JObject(getClazz()){
                this->publicId=null;
                this->systemId=null;
                this->byteStream=null;
                this->encoding=null;
                this->characterStream=null;
            }

            JInputSource::JInputSource(JString* systemId):JObject(getClazz()){
                this->publicId=null;
                this->systemId=null;
                this->byteStream=null;
                this->encoding=null;
                this->characterStream=null;
                setSystemId(systemId);
            }

            JInputSource::JInputSource(JInputStream* byteStream):JObject(getClazz()){
                this->publicId=null;
                this->systemId=null;
                this->byteStream=null;
                this->encoding=null;
                this->characterStream=null;
                setByteStream(byteStream);
            }

            JInputSource::JInputSource(JReader* characterStream):JObject(getClazz()){
                this->publicId=null;
                this->systemId=null;
                this->byteStream=null;
                this->encoding=null;
                this->characterStream=null;
                setCharacterStream(characterStream);
            }

            void JInputSource::setPublicId(JString* publicId){
                this->publicId = publicId;
            }

            JString* JInputSource::getPublicId (){
                return publicId;
            }

            void JInputSource::setSystemId(JString* systemId){
                this->systemId = systemId;
            }

            JString* JInputSource::getSystemId(){
                return systemId;
            }

            void JInputSource::setByteStream(JInputStream* byteStream){
                this->byteStream = byteStream;
            }

            JInputStream* JInputSource::getByteStream(){
                return byteStream;
            }

            void JInputSource::setEncoding(JString* encoding){
                this->encoding = encoding;
            }

            JString* JInputSource::getEncoding(){
                return encoding;
            }

            void JInputSource::setCharacterStream(JReader* characterStream){
                this->characterStream = characterStream;
            }

            JReader* JInputSource::getCharacterStream(){
                return characterStream;
            }

            JInputSource::~JInputSource(){
            }
        }
    }
}
