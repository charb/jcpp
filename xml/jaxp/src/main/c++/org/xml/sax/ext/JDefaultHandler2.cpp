#include "org/xml/sax/ext/JDefaultHandler2.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JIllegalArgumentException.h"
#include "jcpp/lang/JArrayIndexOutOfBoundsException.h"
#include "jcpp/lang/JSystem.h"

namespace org{
    namespace xml{
        namespace sax{
            namespace ext{

                JDefaultHandler2::JDefaultHandler2(JClass* _class):JDefaultHandler(_class){
                }

                JDefaultHandler2::JDefaultHandler2():JDefaultHandler(getClazz()){
                }

                void JDefaultHandler2::startCDATA(){
                }

                void JDefaultHandler2::endCDATA(){
                }
                
                void JDefaultHandler2::startDTD(JString* name, JString* publicId, JString* systemId){
                }

                void JDefaultHandler2::endDTD(){
                }

                void JDefaultHandler2::startEntity(JString* name){
                }

                void JDefaultHandler2::endEntity(JString* name){
                }

                void JDefaultHandler2::comment(JPrimitiveCharArray* ch, jint start, jint length){
                }

                void JDefaultHandler2::attributeDecl(JString* eName, JString* aName,JString* type, JString* mode, JString* value){
                }

                void JDefaultHandler2::elementDecl(JString* name, JString* model){
                }

                void JDefaultHandler2::externalEntityDecl(JString* name,JString* publicId, JString* systemId){
                }

                void JDefaultHandler2::internalEntityDecl(JString* name, JString* value){
                }

                JInputSource* JDefaultHandler2::getExternalSubset(JString* name, JString* baseURI){
                    return null;
                }

                JInputSource* JDefaultHandler2::resolveEntity(JString* name, JString* publicId,JString* baseURI, JString* systemId){
                    return null;
                }
                
                JInputSource* JDefaultHandler2::resolveEntity(JString* publicId, JString* systemId){
                    return resolveEntity(null, publicId, null, systemId);
                }

                JDefaultHandler2::~JDefaultHandler2(){
                }
            }
        }
    }
}
