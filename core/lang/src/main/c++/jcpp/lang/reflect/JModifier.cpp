#include "jcpp/lang/reflect/JModifier.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JClassLoader.h"
#include "jcpp/lang/JStringBuilder.h"

namespace jcpp{
    namespace lang{
        namespace reflect{

            jint JModifier::PUBLIC = 0x00000001;

            jint JModifier::PRIVATE = 0x00000002;

            jint JModifier::PROTECTED = 0x00000004;

            jint JModifier::STATIC = 0x00000008;

            jint JModifier::FINAL = 0x00000010;

            jint JModifier::SYNCHRONIZED = 0x00000020;

            jint JModifier::VOLATILE = 0x00000040;

            jint JModifier::TRANSIENT = 0x00000080;

            jint JModifier::NATIVE = 0x00000100;

            jint JModifier::INTERFACE = 0x00000200;

            jint JModifier::ABSTRACT = 0x00000400;

            jint JModifier::STRICT = 0x00000800;

            jint JModifier::BRIDGE    = 0x00000040;

            jint JModifier::VARARGS   = 0x00000080;

            jint JModifier::SYNTHETIC = 0x00001000;

            jint JModifier::ANNOTATION  = 0x00002000;

            jint JModifier::ENUM      = 0x00004000;

            jint JModifier::SYNTHESIZED = 0x00010000;

            jbool JModifier::isAbstract(jint mod){
                return (mod & ABSTRACT) !=0;
            }
                
            jbool JModifier::isFinal(jint mod){
                return (mod & FINAL) !=0;
            }

            jbool JModifier::isInterface(jint mod){
                return (mod & INTERFACE) !=0;
            }

            jbool JModifier::isNative(jint mod){
                return (mod & NATIVE) !=0;
            }

            jbool JModifier::isPrivate(jint mod){
                return (mod & PRIVATE) !=0;
            }

            jbool JModifier::isProtected(jint mod){
                return (mod & PROTECTED) !=0;
            }

            jbool JModifier::isPublic(jint mod){
                return (mod & PUBLIC) !=0;
            }

            jbool JModifier::isStatic(jint mod){
                return (mod & STATIC) !=0;
            }

            jbool JModifier::isStrict(jint mod){
                return (mod & STRICT) !=0;
            }

            jbool JModifier::isSynchronized(jint mod){
                return (mod & SYNCHRONIZED) !=0;
            }

            jbool JModifier::isTransient(jint mod){
                return (mod & TRANSIENT) !=0;
            }

            jbool JModifier::isVolatile(jint mod){
                return (mod & VOLATILE) !=0;
            }

            JString* JModifier::toString(jint mod){
                JStringBuilder* sb = new JStringBuilder();

                if ((mod & PUBLIC) != 0){
                    sb->append("public ");
                }
                if ((mod & PROTECTED) != 0){
                    sb->append("protected ");
                }
                if ((mod & PRIVATE) != 0){
                    sb->append("private ");
                }
                if ((mod & ABSTRACT) != 0){
                    sb->append("abstract ");
                }
                if ((mod & STATIC) != 0){
                    sb->append("static ");
                }
                if ((mod & FINAL) != 0){
                    sb->append("final ");
                }
                if ((mod & TRANSIENT) != 0){
                    sb->append("transient ");
                }
                if ((mod & VOLATILE) != 0){
                    sb->append("volatile ");
                }
                if ((mod & SYNCHRONIZED) != 0){
                    sb->append("synchronized ");
                }
                if ((mod & NATIVE) != 0){
                    sb->append("native ");
                }
                if ((mod & STRICT) != 0){
                    sb->append("strictfp ");
                }
                if ((mod & INTERFACE) != 0){
                    sb->append("interface ");
                }
                return sb->toString();
            }

            JModifier::~JModifier(){
            }
        }
    }
}
