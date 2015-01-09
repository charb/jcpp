#include "jcpp/rmi/server/JRemoteSample.h"
#include "jcpp/lang/JSystem.h"
#include "jcpp/lang/JException.h"

namespace jcpp{
    namespace rmi{
        namespace server{

            JRemoteSample::JRemoteSample():JObject(getClazz()){
            }

            JSampleObject* JRemoteSample::getSampleObject(){
                JSampleObject* o=new JSampleObject();
                o->setBool1(new JPrimitiveBoolean(false));
                o->setByte1(new JPrimitiveByte(123));
                o->setC1(new JPrimitiveChar('c'));
                o->setD1(new JPrimitiveDouble(456));
                o->setF1(new JPrimitiveFloat(789));
                o->setL1(new JPrimitiveLong(124));
                o->setS1(new JPrimitiveShort(235));
                o->setI1(new JPrimitiveInt(345));
                o->setRemoteSample(this);
                return o;
            }

            JIRemoteSample* JRemoteSample::getRemoteSample(){
                return this;
            }

            void JRemoteSample::checkRemoteSample(JIRemoteSample* rs){
                if (rs!=this){
                    throw new JException(new JString("replacing remote object failed"));
                }
            }

            void JRemoteSample::checkCallback(JIRemoteSample* rs){
                JSystem::out->println(new JString("debut checkcallback"));
                JSystem::out->println(rs->getSampleObject());
            }

            JRemoteSample::~JRemoteSample(){
            }
        }
    }
}

