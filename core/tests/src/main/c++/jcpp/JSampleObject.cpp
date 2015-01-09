#include "jcpp/JSampleObject.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JField.h"
#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JStringBuilder.h"

using namespace jcpp::lang::reflect;
using namespace jcpp::lang;

namespace jcpp{


    JSampleObject::JSampleObject():JObject(JSampleObject::getClazz()){
        i=new JPrimitiveInt(0);
        l=new JPrimitiveLong(0);
        s=new JPrimitiveShort(0);
        f=new JPrimitiveFloat(0);
        d=new JPrimitiveDouble(0);
        bo=new JPrimitiveBoolean(false);
        c=new JPrimitiveChar((jchar)0);
        by=new JPrimitiveByte(0);
    }

    JSampleObject::JSampleObject(jint i,jlong l,jshort s,jfloat f,jdouble d,jbool bo,jchar c,jbyte by):JObject(JSampleObject::getClazz()){
        this->i=new JPrimitiveInt(i);
        this->l=new JPrimitiveLong(l);
        this->s=new JPrimitiveShort(s);
        this->f=new JPrimitiveFloat(f);
        this->d=new JPrimitiveDouble(d);
        this->bo=new JPrimitiveBoolean(bo);
        this->c=new JPrimitiveChar((jchar)c);
        this->by=new JPrimitiveByte(by);
    }

    jint JSampleObject::getInt(){
        return i->get();
    }

    void JSampleObject::setInt(jint i){
        this->i->set(i);
    }

    jlong JSampleObject::getLong(){
        return l->get();
    }

    void JSampleObject::setLong(jlong l){
        this->l->set(l);
    }

    jshort JSampleObject::getShort(){
        return s->get();
    }

    void JSampleObject::setShort(jshort s){
        this->s->set(s);
    }

    jfloat JSampleObject::getFloat(){
        return f->get();
    }

    void JSampleObject::setFloat(jfloat f){
        this->f->set(f);
    }

    jdouble JSampleObject::getDouble(){
        return d->get();
    }

    void JSampleObject::setDouble(jdouble d){
        this->d->set(d);
    }

    jbool JSampleObject::getBoolean(){
        return bo->get();
    }

    void JSampleObject::setBoolean(jbool b){
        this->bo->set(b);
    }

    jchar JSampleObject::getChar(){
        return c->get();
    }

    void JSampleObject::setChar(jchar c){
        this->c->set(c);
    }

    jbyte JSampleObject::getByte(){
        return by->get();
    }

    void JSampleObject::setByte(jbyte b){
        this->by->set(b);
    }

    JString* JSampleObject::toString(){
        JStringBuilder* builder=new JStringBuilder();
        builder->append(new JString("int="))->append(i->get())
             ->append(new JString(",long="))->append(l->get())
             ->append(new JString(",short="))->append(s->get())
             ->append(new JString(",float="))->append(f->get())
             ->append(new JString(",double="))->append(d->get())
             ->append(new JString(",boolean="))->append(bo->get())
             ->append(new JString(",char="))->append(c->get())
             ->append(new JString(",byte="))->append(by->get());
        return builder->toString();
    }

    jbool JSampleObject::equals(JObject* obj){
        if (obj->getClass()!=getClazz()){
            return false;
        }
        JSampleObject* o=dynamic_cast<JSampleObject*>(obj);
        return i->equals(o->i) && l->equals(o->l) &&
               s->equals(o->s) && d->equals(o->d) &&
               bo->equals(o->bo) && c->equals(o->c) &&
               by->equals(o->by) && f->equals(o->f);
    }
    
    JSampleObject::~JSampleObject(){
    }
}
