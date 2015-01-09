#ifndef JCPP_NATIVE_WINDOWS_FILE_WINDOWSFILE
#define JCPP_NATIVE_WINDOWS_FILE_WINDOWSFILE

#include "jcpp/native/api/file/NativeFile.h"

using namespace jcpp::native::api::file;

namespace jcpp {
	namespace native {
		namespace windows {
			namespace file {

				class FileHandle;

				class JCPP_EXPORT WindowsFile: public NativeFile {

					friend class FileHandle;

				private:
					static NativeString className;

				protected:
					virtual NativeString resolvePath(const NativeString& path) const;
					virtual NativeString joinPaths(const NativeString& parent, const NativeString& child) const;

					void list(std::vector<WindowsFile>& files) const;
					void removeLeaf();

					static void handleLastError(const NativeString& methodName, const NativeString& message);
				public:
					WindowsFile();
					WindowsFile(const NativeString& path);
					WindowsFile(const NativeString& parent, const NativeString& child);

					virtual void normalise();
					virtual jbool exists() const;
					virtual jbool isAbsolute() const;

					virtual NativeString getName() const;
					virtual NativeString getParentPath() const;

					virtual NativeString getAbsolutePath() const;

					virtual jlong getSize() const;
					virtual void setSize(jlong size);

					virtual jlong getFreeSpace() const;
					virtual jlong getTotalSpace() const;
					virtual jlong getUsableSpace() const;

					virtual jbool isFile() const;
					virtual jbool isLink() const;
					virtual jbool isDirectory() const;
					virtual jbool isHidden() const;

					virtual jlong getCreatedTime() const;
					virtual jlong getLastModified() const;
					virtual void setLastModified(const jlong lm);

					virtual jbool canRead() const;
					virtual jbool canWrite() const;
					virtual jbool canExecute() const;

					virtual void setWritable(jbool flag);
					virtual void setExecutable(jbool flag);

					virtual void list(std::vector<NativeString>& files) const;

					virtual void copyTo(const NativeString& path) const;
					virtual void moveTo(const NativeString& path);
					virtual void renameTo(const NativeString& path);

					virtual void remove(jbool recursive = false);
					virtual jbool createFile();
					virtual jbool createDirectory();
					virtual void createDirectories();
				};

			}
		}
	}
}

#endif
