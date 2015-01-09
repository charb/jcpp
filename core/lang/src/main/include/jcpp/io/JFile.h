#ifndef JCPP_IO_JFILE_H
#define JCPP_IO_JFILE_H

#include "jcpp/io/JSerializable.h"
#include "jcpp/lang/JString.h"
#include "jcpp/io/JFileFilter.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/io/JFilenameFilter.h"
#include "jcpp/lang/JComparable.h"
#include "jcpp/io/JObjectOutputStream.h"
#include "jcpp/io/JObjectInputStream.h"
#include "jcpp/io/JFileSystem.h"
#include "jcpp/native/api/file/NativeFile.h"

using namespace jcpp::lang;
using jcpp::native::api::file::NativeFile;

namespace jcpp{
    namespace io{

        //@Class(canonicalName="java.io.File", simpleName="File");
        class JCPP_EXPORT JFile : public JObject, public JSerializable, public JComparable  {
        private:
				static const jlong serialVersionUID = 301077366599181567LL;
            protected:
                static jcpp::io::JFileSystem* fs;//TODO maybe useless

                NativeFile* nativeFile;
                JString* name;
                JString* path;
                JString* absolutePath;

                virtual void writeObject(JObjectOutputStream* out);
                virtual void readObject(JObjectInputStream* in);


                JFile(JClass* _class, JString* pathname);

            public:
                static JClass* getClazz();

                static jchar separatorChar;

                static JString* separator;

                static jchar pathSeparatorChar;

                static JString* pathSeparator;

                JFile(JString* pathname);

                JFile(JString* parent,JString* child);

                JFile(JFile* parent,JString* child);

                virtual JString* getName();

                virtual JString* getParent();

                virtual JFile* getParentFile();

                virtual JString* getPath();

                virtual jbool isAbsolute();

                virtual JString* getAbsolutePath();

                virtual JFile* getAbsoluteFile();

                virtual JString* getCanonicalPath();

                virtual JFile* getCanonicalFile();

                virtual jbool canRead();

                virtual jbool canWrite();

                virtual jbool exists();

                virtual jbool isDirectory();

                virtual jbool isFile();

                virtual jbool isHidden();

                virtual jlong lastModified();

                virtual jlong length();

                virtual jbool createNewFile();

                virtual jbool deleteFile();

                virtual void deleteOnExit();

                virtual JPrimitiveObjectArray* list();

                virtual JPrimitiveObjectArray* list(JFilenameFilter* filter);

                virtual JPrimitiveObjectArray* listFiles();

                virtual JPrimitiveObjectArray* listFiles(JFilenameFilter* filter);

                virtual JPrimitiveObjectArray* listFiles(JFileFilter* filter);

                virtual jbool mkdir();

                virtual jbool mkdirs();

                virtual jbool renameTo(JFile* dest);

                virtual jbool setLastModified(jlong time);

                virtual jbool setReadOnly();

                virtual jbool setWritable(jbool writable, jbool ownerOnly);

                virtual jbool setWritable(jbool writable);

                virtual jbool setReadable(jbool readable,jbool ownerOnly);

                virtual jbool setReadable(jbool readable);

                virtual jbool setExecutable(jbool executable,jbool ownerOnly);

                virtual jbool setExecutable(jbool executable);

                virtual jbool canExecute();

                static JPrimitiveObjectArray* listRoots();

                virtual jlong getTotalSpace();

                virtual jlong getFreeSpace();

                virtual jlong getUsableSpace();

                static JFile* createTempFile(JString* prefix, JString* suffix, JFile* directory);

                static JFile* createTempFile(JString* prefix, JString* suffix);

                virtual jint compareTo(JObject* pathname);

                virtual jbool equals(JObject* object);

                virtual jint hashCode();

                virtual JString* toString();

                virtual void finalize();

                virtual ~JFile();
        };
    }
}

#endif 
