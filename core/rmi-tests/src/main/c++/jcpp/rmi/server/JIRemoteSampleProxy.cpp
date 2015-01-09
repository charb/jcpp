#include "jcpp/rmi/server/JIRemoteSampleProxy.h"
#include "jcpp/util/JList.h"
#include "jcpp/util/JArrayList.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::util;

namespace jcpp{
    namespace rmi{
        namespace server{


            JIRemoteSampleProxy::JIRemoteSampleProxy():JProxy(getClazz()){
            }

            JSampleObject* JIRemoteSampleProxy::getSampleObject(){
                JList* args=new JArrayList();
                JList* types=new JArrayList();
                JSampleObject* so=dynamic_cast<JSampleObject*>(invoke(new JString("getSampleObject"),types,args));
                return so;
            }

            JIRemoteSample* JIRemoteSampleProxy::getRemoteSample(){
                JList* args=new JArrayList();
                JList* types=new JArrayList();
                return dynamic_cast<JIRemoteSample*>(invoke(new JString("getRemoteSample"),types,args));
            }

            void JIRemoteSampleProxy::checkRemoteSample(JIRemoteSample* rs){
                JList* args=new JArrayList();
                args->add(dynamic_cast<JObject*>(rs));
                JList* types=new JArrayList();
                types->add(JIRemoteSample::getClazz());

                invoke(new JString("checkRemoteSample"),types,args);
            }

            void JIRemoteSampleProxy::checkCallback(JIRemoteSample* rs){
                JList* args=new JArrayList();
                args->add(dynamic_cast<JObject*>(rs));
                JList* types=new JArrayList();
                types->add(JIRemoteSample::getClazz());

                invoke(new JString("checkCallback"),types,args);
            }

            JIRemoteSampleProxy::~JIRemoteSampleProxy(){
            }
        }
    }
}
