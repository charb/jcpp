#include "jcpp/rmi/server/connection/JMethodDigester.h"
#include "jcpp/rmi/server/transport/JConnection.h"
#include "jcpp/rmi/server/connection/JConnectionException.h"
#include "jcpp/rmi/server/connection/JConnectionOutputStream.h"
#include "jcpp/rmi/server/connection/JConnectionInputStream.h"
#include "jcpp/util/JMap.h"
#include "jcpp/util/JList.h"
#include "jcpp/util/JHashMap.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/JLong.h"
#include "jcpp/lang/JSystem.h"
#include "jcpp/lang/JStringBuilder.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"

using namespace jcpp::util;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace rmi{
        namespace server{
            namespace connection{

                JMethodDigester::JMethodDigester():JObject(getClazz()){
                    digestToMethodMap = new JHashMap();
                    methodToDigestMap = new JHashMap();
                }

                JMethod* JMethodDigester::getMethodFromDigest(JObject* object, jlong digest){
                    JMethod* m=null;
                    synchronized(this,{
                        JClass* classObject = object->getClass();
                        JMap* internalMap = dynamic_cast<JMap*>(digestToMethodMap->get(classObject));
                        if (internalMap == null) {
                            createDigests(classObject);
                            internalMap =dynamic_cast<JMap*>(digestToMethodMap->get(classObject));
                        }
                        m=dynamic_cast<JMethod*>(internalMap->get(new JLong(digest)));
                        return m;
                    })
                }

                JPrimitiveObjectArray* JMethodDigester::getMethods(JObject* object){
                    synchronized(this,{
                        JClass* classObject = object->getClass();
                        JMap* internalMap = dynamic_cast<JMap*>(digestToMethodMap->get(classObject));
                        if (internalMap == null) {
                            createDigests(classObject);
                            internalMap = dynamic_cast<JMap*>(digestToMethodMap->get(classObject));
                        }
                        return internalMap->values()->toArray();
                    })
                }

                jlong JMethodDigester::getDigestFromMethod(JMethod* method){
                    jlong l=0;
                    synchronized(this,{
                        JClass* classObject = method->getDeclaringClass();
                        JMap* internalMap = dynamic_cast<JMap*>(methodToDigestMap->get(classObject));
                        if (internalMap == null) {
                            createDigests(classObject);
                            internalMap = dynamic_cast<JMap*>(methodToDigestMap->get(classObject));
                        }
                        JLong* ll=dynamic_cast<JLong*>(internalMap->get(method));
                        if (ll!=null){
                            l=ll->get();
                        }
                        return l;
                    })
                }

                void JMethodDigester::clear(){
                    methodToDigestMap->clear();
                    digestToMethodMap->clear();
                }

                JPrimitiveObjectArray* JMethodDigester::array = null;
                
                JPrimitiveObjectArray* JMethodDigester::getArray(){
                    if (array==null){
                        array=new JPrimitiveObjectArray(JObject::getClazz(),0);
                    }
                    return array;
                }

                void JMethodDigester::createDigests(JClass* classObject){
                    JMap* iDigestToMethodMap = new JHashMap();
                    JMap* iMethodToDigestMap = new JHashMap();

                    JList* methods = classObject->getMethods();
                    for (jint i=0;i<methods->size();i++){
                        JMethod* method=dynamic_cast<JMethod*>(methods->get(i));
                        JList* paramTypes = method->getParameterTypes();
                        JStringBuilder* builder = new JStringBuilder();
                        builder->append(method->getName())
                               ->append(":");
                        for (jint j=0;j<paramTypes->size();j++){
                            JClass* param=dynamic_cast<JClass*>(paramTypes->get(j));
                            if (param->isArray() && !param->getComponentType()->isPrimitive()){
                                builder->append(getArray()->getClass()->getName());
                            }else{
                                builder->append(param->getName());
                            }
                            if (j<paramTypes->size()-1){
                                builder->append(",");
                            }
                        }
                        jlong digest = builder->toString()->hashCode();
                        JLong* ll=new JLong(digest);
                        iDigestToMethodMap->put(ll, method);
                        iMethodToDigestMap->put(method, ll);
                    }
                    digestToMethodMap->put(classObject, dynamic_cast<JObject*>(iDigestToMethodMap));
                    methodToDigestMap->put(classObject, dynamic_cast<JObject*>(iMethodToDigestMap));
                }

                JMethodDigester::~JMethodDigester(){
                }
            }
        }
    }
}


