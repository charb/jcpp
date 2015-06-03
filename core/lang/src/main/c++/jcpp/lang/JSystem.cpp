#include "jcpp/lang/JSystem.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JInstantiationException.h"
#include "jcpp/native/api/NativeFactory.h"
#include "jcpp/native/api/NativeSystem.h"
#include "jcpp/io/JNativeInputStream.h"
#include "jcpp/io/JNativeOutputStream.h"
#include "jcpp/gc/GarbageCollector.h"

using namespace jcpp::native::api;
using namespace jcpp::io;
using namespace jcpp::gc;

namespace jcpp{
    namespace lang{

        NativeSystem* JSystem::nativeSystem = NativeFactory::getNativeSystem();

        //TODO add encoding parameter in JPrintStream constructor
        JPrintStream* JSystem::out = new JPrintStream(new JNativeOutputStream(NativeFactory::getNativeIOFactory()->getStandardOutputStream(), false), new JString("UTF-8"));

        JPrintStream* JSystem::err = new JPrintStream(new JNativeOutputStream(NativeFactory::getNativeIOFactory()->getStandardErrorStream(), false), new JString("UTF-8"));

        JInputStream* JSystem::in = new JNativeInputStream(NativeFactory::getNativeIOFactory()->getStandardInputStream(), false);

        jlong JSystem::currentTimeMillis(){
            return nativeSystem->currentTimeMillis();
        }

        jint JSystem::identityHashCode(JObject* x){
            return (jint)(jlong)x;
        }

        void JSystem::arraycopy(JPrimitiveObjectArray* src,jint srcPos,JPrimitiveObjectArray* dest, jint destPos, jint length){
            for (jint i=0;i<length;i++){
                dest->set(destPos+i,src->get(srcPos+i));
            }
        }

        void JSystem::arraycopy(JPrimitiveCharArray* src,jint srcPos,JPrimitiveCharArray* dest, jint destPos, jint length){
            for (jint i=0;i<length;i++){
                dest->setChar(destPos+i,src->getChar(srcPos+i));
            }
        }

        void JSystem::arraycopy(JPrimitiveByteArray* src,jint srcPos,JPrimitiveByteArray* dest, jint destPos, jint length){
            for (jint i=0;i<length;i++){
                dest->setByte(destPos+i,src->getByte(srcPos+i));
            }
        }

        void JSystem::arraycopy(JPrimitiveBooleanArray* src,jint srcPos,JPrimitiveBooleanArray* dest, jint destPos, jint length){
            for (jint i=0;i<length;i++){
                dest->setBoolean(destPos+i,src->getBoolean(srcPos+i));
            }
        }

        void JSystem::arraycopy(JPrimitiveIntArray* src,jint srcPos,JPrimitiveIntArray* dest, jint destPos, jint length){
            for (jint i=0;i<length;i++){
                dest->setInt(destPos+i,src->getInt(srcPos+i));
            }
        }

        JString* JSystem::lSeparator = new JString(NativeFactory::getNativeSystem()->lineSeparator());

        JString* JSystem::lineSeparator(){
            return lSeparator;
        }

        JProperties* JSystem::props = null;

        JProperties* JSystem::initProperties(JProperties* props){
            props->setProperty(new JString("java.version"),new JString("TODO"));
            props->setProperty(new JString("java.vendor"),new JString("TODO"));
            props->setProperty(new JString("java.vendor.url"),new JString("TODO"));
            props->setProperty(new JString("java.home"),new JString("TODO"));
            props->setProperty(new JString("java.class.version"),new JString("TODO"));
            props->setProperty(new JString("java.class.path"),new JString("TODO"));
            props->setProperty(new JString("os.name"),new JString("TODO"));
            props->setProperty(new JString("os.arch"),new JString("TODO"));
            props->setProperty(new JString("os.version"),new JString("TODO"));
            props->setProperty(new JString("file.separator"),new JString("TODO"));
            props->setProperty(new JString("path.separator"),new JString("TODO"));
            props->setProperty(new JString("line.separator"),new JString("TODO"));
            props->setProperty(new JString("user.name"),new JString("TODO"));
            props->setProperty(new JString("user.home"),new JString("TODO"));
            props->setProperty(new JString("user.dir"),new JString("TODO"));
            return props;
        }

        JProperties* JSystem::getProperties(){
            if (props == null) {
                props = new JProperties();
                initProperties(props);
            }
            return props;
        }

        void JSystem::setProperties(JProperties* props){
            if (props == null) {
                props = new JProperties();
                initProperties(props);
            }
            JSystem::props = props;
        }

        JString* JSystem::getProperty(JString* key){
            return getProperties()->getProperty(key);
        }

        JString* JSystem::getProperty(JString* key,JString* def){
            return getProperties()->getProperty(key, def);
        }

        JString* JSystem::setProperty(JString* key, JString* value){
            return dynamic_cast<JString*>(getProperties()->setProperty(key, value));
        }

        JString* JSystem::clearProperty(JString* key){
            return dynamic_cast<JString*>(getProperties()->remove(key));
        }

        JSystem::ExitListener* JSystem::exitListener = null;

        void JSystem::exit(jint code){
            if (exitListener!=null){
                exitListener->exit(code);
            }
        }

        void JSystem::gc(){
        	GarbageCollector::getGarbageCollector()->gc();
        }

        JSystem::~JSystem(){
        }
    }
}

