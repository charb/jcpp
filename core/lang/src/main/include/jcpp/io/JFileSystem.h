#ifndef JCPP_IO_JFILESYSTEM_H
#define JCPP_IO_JFILESYSTEM_H

#include "jcpp/lang/JString.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{
        class JFile;

        //@Class(canonicalName="java.io.FileSystem", simpleName="FileSystem");
        class JCPP_EXPORT JFileSystem : public JObject  {
        protected:
            JFileSystem(jcpp::lang::JClass* _class);

            public:
                static jint BA_EXISTS;
                static jint BA_REGULAR;
                static jint BA_DIRECTORY;
                static jint BA_HIDDEN;

                static jint ACCESS_READ;
                static jint ACCESS_WRITE;
                static jint ACCESS_EXECUTE;

                static jint SPACE_TOTAL;
                static jint SPACE_FREE;
                static jint SPACE_USABLE;

                static jcpp::lang::JClass* getClazz();

                virtual jchar getSeparator()=0;

                virtual jchar getPathSeparator()=0;

                virtual JString* normalize(JString* path)=0;
                
                virtual jint prefixLength(JString* path)=0;
                
                virtual JString* resolve(JString* parent, JString* child)=0;
                
                virtual JString* getDefaultParent()=0;
                
                virtual JString* fromURIPath(JString* path)=0;
                
                virtual jbool isAbsolute(JFile* f)=0;
                
                virtual JString* resolve(JFile* f)=0;
                
                virtual JString* canonicalize(JString* path)=0;
                
                virtual jint getBooleanAttributes(JFile* f)=0;
                
                virtual jbool checkAccess(JFile* f, jint access)=0;
                
                virtual jbool setPermission(JFile* f,jint access,jbool enable,jbool owneronly)=0;
                
                virtual jlong getLastModifiedTime(JFile* f)=0;
                
                virtual jlong getLength(JFile* f)=0;
                
                virtual jbool createFileExclusively(JString* pathname)=0;
                
                virtual jbool deleteFile(JFile* f)=0;
                
                virtual JPrimitiveObjectArray* list(JFile* f)=0;

                virtual jbool createDirectory(JFile* f)=0;

                virtual jbool rename(JFile* f1, JFile* f2)=0;

                virtual jbool setLastModifiedTime(JFile* f, jlong time)=0;

                virtual jbool setReadOnly(JFile* f)=0;

                virtual JPrimitiveObjectArray* listRoots()=0;

                virtual jlong getSpace(JFile* f, jint t)=0;

                virtual jint compare(JFile* f1, JFile* f2)=0;

                virtual jint hashCode(JFile* f)=0;

                virtual ~JFileSystem();
        };
    }
}

#endif
