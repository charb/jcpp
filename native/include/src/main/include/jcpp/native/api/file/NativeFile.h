#ifndef JCPP_NATIVE_API_FILE_NATIVEFILE
#define JCPP_NATIVE_API_FILE_NATIVEFILE

#include "jcpp/native/api/NativeString.h"
#include <vector>

using namespace jcpp::native::api;

namespace jcpp {
	namespace native {
		namespace api {
			namespace file {

				class JCPP_EXPORT NativeFile {

				protected:
					NativeString path;

					NativeFile();
					NativeFile(const NativeString& path);

					virtual NativeString resolvePath(const NativeString& path) const = 0;
					virtual NativeString joinPaths(const NativeString& parent, const NativeString& child) const = 0;
				public:
					virtual ~NativeFile();

					/**
					 * Returns the os File separator
					 * Unix '/'
					 * Windows '\'
					 */
					static jchar fileSeperator();

					/**
					 * Returns the os PATH separator.
					 * Unix ':'
					 * Windows ';'
					 */
					static jchar pathSeperator();
					/**
					 * Returns the file path
					 */
					NativeString getPath() const;

					/**
					 * Sets the path to the absolute path
					 */
					virtual void normalise() = 0;
					/**
					 * Tests whether the file or directory denoted by this abstract pathname exists.
					 *
					 * Throws: NativeException
					 */
					virtual jbool exists() const = 0;
					/**
					 * Tests whether this abstract pathname is absolute.
					 */
					virtual jbool isAbsolute() const = 0;

					/**
					 * Returns the name of the file or directory denoted by this abstract pathname.
					 */
					virtual NativeString getName() const = 0;
					/**
					 * Returns the pathname string of this abstract pathname's parent, or empty String if this pathname is the root dir.
					 *
					 * Throws: NativeException
					 */
					virtual NativeString getParentPath() const = 0;
					/**
					 * If the file path is absolute, the cached path will be returned
					 * otherwise the absolute path is calculated and returned
					 *
					 * Throws: NativeException
					 */
					virtual NativeString getAbsolutePath() const = 0;

					/*
					 * Gets the file Size of the file
					 *
					 * Throws: NativeException
					 */
					virtual jlong getSize() const = 0;
					/*
					 * Sets the file Size. Can be used to truncate a file.
					 *
					 * Throws: NativeException
					 */
					virtual void setSize(jlong size) = 0;

					/**
					 * Returns the number of unallocated bytes in the partition named by this abstract path name.
					 *
					 * Throws: NativeException
					 */
					virtual jlong getFreeSpace() const = 0;
					/**
					 * Returns the size of the partition named by this abstract pathname.
					 *
					 * Throws: NativeException
					 */
					virtual jlong getTotalSpace() const = 0;
					/**
					 * Returns the number of unallocated bytes in the partition named by this abstract path name.
					 *
					 * Throws: NativeException
					 */
					virtual jlong getUsableSpace() const = 0;

					/**
					 * Tests whether the file denoted by this abstract pathname is a normal file.
					 *
					 * Throws: NativeException
					 */
					virtual jbool isFile() const = 0;
					/**
					 * Tests whether the file denoted by this abstract pathname is a symbolic link.
					 *
					 * Throws: NativeException
					 */
					virtual jbool isLink() const = 0;
					/**
					 * Tests whether the file denoted by this abstract pathname is a directory.
					 *
					 * Throws: NativeException
					 */
					virtual jbool isDirectory() const = 0;
					/**
					 * Tests whether the file named by this abstract pathname is a hidden file.
					 * On Unix a hidden path is a path that starts with '.'
					 *
					 * Throws: NativeException
					 */
					virtual jbool isHidden() const = 0;

					/**
					 * Returns the time that the file denoted by this abstract pathname was created.
					 *
					 * Throws: NativeException
					 */
					virtual jlong getCreatedTime() const = 0;
					/**
					 * Returns the time that the file denoted by this abstract pathname was last modified.
					 *
					 * Throws: NativeException
					 */
					virtual jlong getLastModified() const = 0;
					/**
					 * Sets the last-modified time of the file or directory named by this abstract pathname.
					 *
					 * Throws: NativeException
					 */
					virtual void setLastModified(const jlong lm) = 0;

					/**
					 * Tests whether the application can read the file denoted by this abstract pathname.
					 *
					 * Throws: NativeException
					 */
					virtual jbool canRead() const = 0;
					/**
					 * Tests whether the application can modify the file denoted by this abstract pathname.
					 *
					 * Throws: NativeException
					 */
					virtual jbool canWrite() const = 0;
					/**
					 * Tests whether the application can execute the file denoted by this abstract pathname.
					 *
					 * Throws: NativeException
					 */
					virtual jbool canExecute() const = 0;

					/**
					 * A convenience method to set the owner's write permission for this abstract pathname
					 *
					 * Throws: NativeException
					 */
					virtual void setWritable(jbool flag) = 0;
					/**
					 * A convenience method to set the owner's execute permission for this abstract pathname.
					 *
					 * Throws: NativeException
					 */
					virtual void setExecutable(jbool flag) = 0;

					/**
					 * Fills the files vector with the names of the files and directories in the directory denoted by this abstract pathname.
					 *
					 * Parameters:
					 * 	- The files vector to fill
					 *
					 * Throws: NativeException
					 */
					virtual void list(std::vector<NativeString>& files) const = 0;

					/**
					 * Copies the file denoted by this abstract pathname to the specified path
					 *
					 * Throws: NativeException
					 */
					virtual void copyTo(const NativeString& path) const = 0;
					/**
					 * Copies the file denoted by this abstract pathname to the specified path, then deletes the local path recursively
					 * Sets the local path to the specified new path
					 *
					 * Throws: NativeException
					 */
					virtual void moveTo(const NativeString& path) = 0;
					/**
					 * Renames the file denoted by this abstract pathname.
					 *
					 * Throws: NativeException
					 */
					virtual void renameTo(const NativeString& path) = 0;

					/**
					 * Deletes the file denoted by this abstract pathname. If the path is a directory then
					 * recursive should be set to true so that the child files get deleted recursively.
					 *
					 * Throws: NativeException
					 */
					virtual void remove(jbool recursive = false) = 0;

					/**
					 * Creates a new, empty file named by this abstract pathname if and only if a file with this name does not yet exist.
					 *
					 * Returns: True is a new file was created. False if a file already exists
					 *
					 * Throws: NativeException
					 */
					virtual jbool createFile() = 0;
					/**
					 * Creates the directory named by this abstract pathname.
					 *
					 * Returns: True is a new directory was created. False if a directory already exists
					 *
					 * Throws: NativeException
					 */
					virtual jbool createDirectory() = 0;
					/**
					 * Creates the directory named by this abstract pathname, including any necessary but nonexistent parent directories.
					 *
					 * Returns: True is a new directory was created. False if a directory already exists
					 *
					 * Throws: NativeException
					 */
					virtual void createDirectories() = 0;

				};

			}
		}
	}
}

#endif
