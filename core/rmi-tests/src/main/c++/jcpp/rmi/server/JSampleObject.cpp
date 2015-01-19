#include "jcpp/rmi/server/JSampleObject.h"
#include "jcpp/rmi/server/JIRemoteSample.h"
#include "jcpp/lang/reflect/JMethod.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JStringBuilder.h"
#include "jcpp/lang/JSystem.h"
#include "jcpp/util/JList.h"

using namespace jcpp::lang::reflect;
using namespace jcpp::util;

namespace jcpp{
    namespace rmi{
        namespace server{

            JSampleObject::JSampleObject():JObject(getClazz()){
                bool1=null;
                byte1=null;
                c1=null;
                d1=null;
                f1=null;
                l1=null;
                s1=null;
                i1=null;
                rs=null;
            }

            jbool JSampleObject::equals(JObject* other){
                if (getClass()!=other->getClass()){
                    return false;
                }
                JSampleObject* s=dynamic_cast<JSampleObject*>(other);
                if (s->bool1->equals(bool1)){
                    if (s->byte1->equals(byte1)){
                        if (s->c1->equals(c1)){
                            if (s->d1->equals(d1)){
                                if (s->f1->equals(f1)){
                                    if (s->i1->equals(i1)){
                                        if (s->l1->equals(l1)){
                                            if (s->s1->equals(s1)){
                                                return true;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                return false;
            }

            JPrimitiveBoolean* JSampleObject::getBool1(){
                return bool1;
            }

            void JSampleObject::setBool1(JPrimitiveBoolean* bool1){
                this->bool1=bool1;
            }

            JPrimitiveByte* JSampleObject::getByte1(){
                return byte1;
            }

            void JSampleObject::setByte1(JPrimitiveByte* byte1){
                this->byte1=byte1;
            }

            JPrimitiveChar* JSampleObject::getC1(){
                return c1;
            }

            void JSampleObject::setC1(JPrimitiveChar* c1){
                this->c1=c1;
            }

            JPrimitiveDouble* JSampleObject::getD1(){
                return d1;
            }

            void JSampleObject::setD1(JPrimitiveDouble* d1){
                this->d1=d1;
            }

            JPrimitiveFloat* JSampleObject::getF1(){
                return f1;
            }

            void JSampleObject::setF1(JPrimitiveFloat* f1){
                this->f1=f1;
            }

            JPrimitiveLong* JSampleObject::getL1(){
                return l1;
            }

            void JSampleObject::setL1(JPrimitiveLong* l1){
                this->l1=l1;
            }

            JPrimitiveShort* JSampleObject::getS1(){
                return s1;
            }

            void JSampleObject::setS1(JPrimitiveShort* s1){
                this->s1=s1;
            }

            JPrimitiveInt* JSampleObject::getI1(){
                return i1;
            }

            void JSampleObject::setI1(JPrimitiveInt* i1){
                this->i1=i1;
            }

            JIRemoteSample* JSampleObject::getRemoteSample(){
                return rs;
            }

            void JSampleObject::setRemoteSample(JIRemoteSample* rs){
                this->rs=rs;
            }

            JString* JSampleObject::toString(){
                JString* n1=new JString("\r\n");
                JStringBuilder* builder=new JStringBuilder();
                builder->append("bool1=")->append(bool1)->append(n1)
                       ->append("byte1=")->append(byte1)->append(n1)
                       ->append("c1=")->append(c1)->append(n1)
                       ->append("d1=")->append(d1)->append(n1)
                       ->append("f1=")->append(f1)->append(n1)
                       ->append("l1=")->append(l1)->append(n1)
                       ->append("s1=")->append(s1)->append(n1)
                       ->append("i1=")->append(i1)->append(n1)
                       ->append("rs=")->append(dynamic_cast<JObject*>(rs))->append(n1);
                return builder->toString();
            }

            JSampleObject::~JSampleObject(){
            }
        }
    }
}
