#include "jcpp/io/JFile.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/io/JFileSystem.h"
#include "jcpp/native/api/NativeFactory.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "jcpp/lang/JIllegalArgumentException.h"
#include "jcpp/lang/JNullPointerException.h"

using jcpp::native::api::NativeFactory;
using namespace jcpp::lang;

namespace jcpp{
    namespace io{

        jcpp::io::JFileSystem* JFile::fs = null;//TODO useless?

        jchar JFile::separatorChar = NativeFile::fileSeperator();

        JString* JFile::separator = new JString(NativeFile::fileSeperator());

        jchar JFile::pathSeparatorChar = NativeFile::pathSeperator();

        JString* JFile::pathSeparator = new JString(NativeFile::pathSeperator());

        JFile::JFile(JClass* _class, JString* pathname) : JObject(_class) {
        	nativeFile = NativeFactory::getNativeFileFactory()->createNativeFile(pathname->getNativeString());
			name = new JString(nativeFile->getName());
			path = new JString(nativeFile->getPath());
			absolutePath = null;
        }

        JFile::JFile(JString* pathname) : JObject(getClazz()) {
            nativeFile = NativeFactory::getNativeFileFactory()->createNativeFile(pathname->getNativeString());
            name = new JString(nativeFile->getName());
            path = new JString(nativeFile->getPath());
            absolutePath = null;
        }

        JFile::JFile(JString* parent,JString* child) : JObject(getClazz()) {
        	nativeFile = NativeFactory::getNativeFileFactory()->createNativeFile(parent->getNativeString(), child->getNativeString());
        	name = new JString(nativeFile->getName());
        	path = new JString(nativeFile->getPath());
        	absolutePath = null;
        }

        JFile::JFile(JFile* parent,JString* child) : JObject(getClazz()) {
        	nativeFile = NativeFactory::getNativeFileFactory()->createNativeFile(parent->getPath()->getNativeString(), child->getNativeString());
        	name = new JString(nativeFile->getName());
        	path = new JString(nativeFile->getPath());
        	absolutePath = null;
        }

        JString* JFile::getName(){
            return name;
        }

        JString* JFile::getParent(){
        	NativeString nativeParentPath = nativeFile->getParentPath();
        	return nativeParentPath.isEmpty() ? null : new JString(nativeParentPath);
        }

        JFile* JFile::getParentFile(){
            JString* p=getParent();
            if (p==null){
                return null;
            }
            return new JFile(p);
        }

        JString* JFile::getPath(){
            return path;
        }

        jbool JFile::isAbsolute(){
            return nativeFile->isAbsolute();
        }

        JString* JFile::getAbsolutePath(){
        	if(absolutePath == null) {
        		TRY_CATCH_NATIVE_EXCEPTION( absolutePath = new JString(nativeFile->getAbsolutePath()); )
        	}
            return absolutePath;
        }

        JFile* JFile::getAbsoluteFile(){
            return new JFile(getAbsolutePath());
        }

        JString* JFile::getCanonicalPath(){
        	//TODO
            return getAbsolutePath();
        }

        JFile* JFile::getCanonicalFile(){
        	return new JFile(getCanonicalPath());
        }

        jbool JFile::canRead(){
        	jbool value = false;
        	try {
        		value = nativeFile->canRead();
        	} catch(...) {
        		return false;
        	}
            return value;
        }

        jbool JFile::canWrite(){
        	jbool value = false;
        	try {
        		value = nativeFile->canWrite();
        	} catch(...) {
        		return false;
        	}
			return value;
        }

        jbool JFile::exists(){
        	jbool value = false;
			try {
				value = nativeFile->exists();
			} catch(...) {
				return false;
			}
			return value;
        }

        jbool JFile::isDirectory(){
        	jbool value = false;
			try {
				value = nativeFile->isDirectory();
			} catch(...) {
				return false;
			}
			return value;
        }

        jbool JFile::isFile(){
        	jbool value = false;
			try {
				value = nativeFile->isFile();
			} catch(...) {
				return false;
			}
			return value;
        }

        jbool JFile::isHidden(){
        	jbool value = false;
			TRY_CATCH_NATIVE_EXCEPTION( value = nativeFile->isHidden(); )
			return value;
        }

        jlong JFile::lastModified(){
        	jlong value = 0;
			try {
				value = nativeFile->getLastModified();
			} catch(...) {
				return 0;
			}
			return value;
        }

        jlong JFile::length(){
        	jlong value = 0;
			try {
				value = nativeFile->getSize();
			} catch(...) {
				return 0;
			}
			return value;
        }

        jbool JFile::createNewFile(){
        	jbool value = false;
			TRY_CATCH_NATIVE_EXCEPTION( value = nativeFile->createFile(); )
			return value;
        }

        jbool JFile::deleteFile(){
        	try {
        		nativeFile->remove(false);
        	} catch (...) {
        		return false;
        	}
			return true;
        }

        void  JFile::deleteOnExit(){
            //TODO DeleteOnExitHook::add(path)
        }

        JPrimitiveObjectArray* JFile::list(){
        	std::vector<NativeString> files;
        	try {
				nativeFile->list(files);
			} catch (...) {
				return null;
			}

        	JPrimitiveObjectArray* array = new JPrimitiveObjectArray(JString::getClazz(), files.size());
        	jint index = 0;
        	for (std::vector<NativeString>::iterator it = files.begin(); it != files.end(); ++it) {
        		array->set(index++, new JString(*it));
			}

            return array;
        }

        JPrimitiveObjectArray* JFile::list(JFilenameFilter* filter){
        	std::vector<NativeString> files;
			try {
				nativeFile->list(files);
			} catch (...) {
				return null;
			}

			jint acceptedCount = 0;
			for (std::vector<NativeString>::iterator it = files.begin(); it != files.end(); ++it) {
				if (filter == null) {
					acceptedCount++;
				} else {
					JString* itName = new JString(*it);
					itName = itName->substring(this->getAbsolutePath()->length() + 1);
					if (filter->accept(this, itName)) {
						acceptedCount++;
					}
				}
			}

			JPrimitiveObjectArray* array = new JPrimitiveObjectArray(JString::getClazz(), acceptedCount);
			jint index = 0;
				for (std::vector<NativeString>::iterator it = files.begin(); it != files.end(); ++it) {
					if (filter == null) {
						array->set(index++, new JFile(new JString(*it)));
					} else {
						JString* itName = new JString(*it);
						itName = itName->substring(this->getAbsolutePath()->length() + 1);
						if (filter->accept(this, itName)) {
						array->set(index++,itName);
						}
					}
				}
			return array;
        }

        JPrimitiveObjectArray* JFile::listFiles(){
        	std::vector<NativeString> files;
        	try {
        		nativeFile->list(files);
        	} catch (...) {
        		return null;
        	}

			JPrimitiveObjectArray* array = new JPrimitiveObjectArray(JFile::getClass(), files.size());
			jint index = 0;
			for (std::vector<NativeString>::iterator it = files.begin(); it != files.end(); ++it) {
			JString* itName = new JString(*it);
			itName = itName->substring(this->getAbsolutePath()->length() + 1);
			array->set(index++, new JFile(this, new JString(itName)));
			}

			return array;
        }

        JPrimitiveObjectArray* JFile::listFiles(JFilenameFilter* filter){
        	std::vector<NativeString> files;
			try {
				nativeFile->list(files);
			} catch (...) {
				return null;
			}

        	jint acceptedCount = 0;
			for (std::vector<NativeString>::iterator it = files.begin(); it != files.end(); ++it) {
			if (filter == null) {
				acceptedCount++;
			} else {
				JString* itName = new JString(*it);
				itName = itName->substring(this->getAbsolutePath()->length() + 1);
				if (filter->accept(this, itName))
				{
					acceptedCount++;
				}
			}
		}
			JPrimitiveObjectArray* array = new JPrimitiveObjectArray(JFile::getClass(), acceptedCount);
			jint index = 0;
			for (std::vector<NativeString>::iterator it = files.begin(); it != files.end(); ++it) {
			if (filter == null) {
					array->set(index++, new JFile(new JString(*it)));
			} else {
				JString* itName = new JString(*it);
				itName = itName->substring(this->getAbsolutePath()->length() + 1);
				if (filter->accept(this, itName)) {
					array->set(index++, new JFile(this, itName));
				}
			}
		}
			return array;
        }

        JPrimitiveObjectArray* JFile::listFiles(JFileFilter* filter){
        	std::vector<NativeString> files;
			try {
				nativeFile->list(files);
			} catch (...) {
				return null;
			}

			jint acceptedCount = 0;
			for (std::vector<NativeString>::iterator it = files.begin(); it != files.end(); ++it) {
			if (filter == null)  {
				acceptedCount++;
			} else {
				JString* itName = new JString(*it);
				itName = itName->substring(this->getAbsolutePath()->length() + 1);
				if (filter->accept(new JFile(this, itName))) {
					acceptedCount++;
				}
			}
		}

			JPrimitiveObjectArray* array = new JPrimitiveObjectArray(JFile::getClass(), acceptedCount);
			jint index = 0;
			for (std::vector<NativeString>::iterator it = files.begin(); it != files.end(); ++it) {
			JString* itName = new JString(*it);
			itName = itName->substring(this->getAbsolutePath()->length() + 1);
			JFile* file = new JFile(this, itName);
				if((filter == null) || filter->accept(file)) {
					array->set(index++, file);
				}
			}

			return array;
        }

        jbool JFile::mkdir(){
        	jbool value = false;
			try {
				value = nativeFile->createDirectory();
			} catch (...) {
				return false;
			}
			return value;
        }

        jbool JFile::mkdirs(){
            if (exists()){
                return false;
            }
            if (mkdir()){
                return true;
            }
            JFile* canonFile=null;
            try{
                canonFile=getCanonicalFile();
            }catch(JIOException* e){
                return false;
            }
            JFile* parent=canonFile->getParentFile();
            return (parent!= null && (parent->mkdirs() || parent->exists()) && canonFile->mkdir());
        }

        jbool JFile::renameTo(JFile* dest){
        	if(dest == null) {
        		throw new JNullPointerException(new JString("Null rename to destination"));
        	}
			try {
				nativeFile->renameTo(dest->getPath()->getNativeString());
			} catch (...) {
			}
			return true;
        }

        jbool JFile::setLastModified(jlong time){
        	if(time < 0) {
        		throw new JIllegalArgumentException(new JString("Illegal negative last modified time"));
        	}
			try {
				nativeFile->setLastModified(time);
			} catch (...) {
				return false;
			}
			return true;
        }

        jbool JFile::setReadOnly(){
			try {
				nativeFile->setWritable(false);
			} catch (...) {
				return false;
			}
			return true;
        }

        jbool JFile::setWritable(jbool writable, jbool ownerOnly){
            //TODO
            return setWritable(writable);
        }

        jbool JFile::setWritable(jbool writable){
			try {
				nativeFile->setWritable(writable);
			} catch (...) {
				return false;
			}
			return true;
        }

        jbool JFile::setReadable(jbool readable,jbool ownerOnly){
        	return false;//TODO
        }

        jbool JFile::setReadable(jbool readable){
            return false;//TODO
        }

        jbool JFile::setExecutable(jbool executable,jbool ownerOnly){
        	//TODO
        	return setExecutable(executable);
        }

        jbool JFile::setExecutable(jbool executable){
			try {
				nativeFile->setExecutable(executable);
			} catch (...) {
				return false;
			}
			return true;
        }

        jbool JFile::canExecute(){
        	jbool value = false;
			try {
				value = nativeFile->canExecute();
			} catch (...) {
				return false;
			}
			return value;
        }

        JPrimitiveObjectArray* JFile::listRoots(){
            return null;//TODO
        }

        jlong JFile::getTotalSpace(){
        	jlong value = 0;
			try {
				value = nativeFile->getTotalSpace();
			} catch (...) {
				return 0;
			}
			return value;
        }

        jlong JFile::getFreeSpace(){
        	jlong value = 0;
			try {
				value = nativeFile->getFreeSpace();
			} catch (...) {
				return 0;
			}
			return value;
        }

        jlong JFile::getUsableSpace(){
        	jlong value = 0;
			try {
				value = nativeFile->getUsableSpace();
			} catch (...) {
				return 0;
			}
			return value;
        }

        JFile* JFile::createTempFile(JString*, JString*, JFile* ){
            return null;//TODO
        }

        JFile* JFile::createTempFile(JString*, JString*){
            return null;//TODO
        }

        jint JFile::compareTo(JObject* pathname){
            return 0;//TODO
        }

        jbool JFile::equals(JObject* object){
            if ((object == null) || object->getClass()!=getClass()){
                return false;
            }
            return compareTo((JFile*)object)==0;
        }

        jint JFile::hashCode(){
            return 0;//TODO
        }

        JString* JFile::toString(){
            return getPath();//TODO
        }

        void JFile::writeObject(JObjectOutputStream* out){
            out->defaultWriteObject();
            out->writeChar(separatorChar);
        }

        void JFile::readObject(JObjectInputStream* in){
            JObjectInputStream::JGetField* fields = in->readFields();
            JString* pathField = dynamic_cast<JString*>(fields->get(new JString("path"), (JObject*)null));
            jchar sep = in->readChar();//TODO

            if (sep != separatorChar){
                pathField = pathField->replace(sep, separatorChar);
            }
            //path = fs->normalize(pathField); TODO
        }

        void JFile::finalize(){
        	if(nativeFile) {
        		delete nativeFile;
        		nativeFile = null;
        	}
        }

        JFile::~JFile(){
        }
    }
}
