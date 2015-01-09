#include "jcpp/native/unixos/file/UnixFile.h"
#include "jcpp/native/api/NativeException.h"
#include "jcpp/native/unixos/UnixUtils.h"

#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/statvfs.h>
#include <string.h>
#include <fcntl.h>
#include <dirent.h>
#include <stdio.h>


using namespace jcpp::native::api;

namespace jcpp {
	namespace native {
		namespace unixos {
			namespace file {

				NativeString UnixFile::className("jcpp::native::unixos::file::UnixFile");

				UnixFile::UnixFile() :
						NativeFile() {
				}

				UnixFile::UnixFile(const NativeString& path) :
						NativeFile() {
					this->path = resolvePath(path);
				}

				UnixFile::UnixFile(const NativeString& parent, const NativeString& child) :
						NativeFile() {
					this->path = joinPaths(parent, child);
				}

				NativeString UnixFile::resolvePath(const NativeString& path) const {
					NativeString p = path.trim();
					jchar ps = '/';
					p = p.replace('\\', ps);
					jint length = p.length();
					if ((length > 1) && (p[length - 1] == '/')) {
						p = p = p.substring(0, p.length() - 1);
					}
					return p;
				}

				NativeString UnixFile::joinPaths(const NativeString& parent, const NativeString& child) const {
					NativeString p = resolvePath(parent);
					return p.endsWith('/') ? p + resolvePath(child) : p + "/" + resolvePath(child);
				}

				void UnixFile::normalise() {
					if (!isAbsolute()) {
						path = getAbsolutePath();
					}
				}

				jbool UnixFile::exists() const {
					struct stat64 st;
					EINTR_RETRY(stat64(path.getString().c_str(), &st))
					return result == 0;
				}

				jbool UnixFile::isAbsolute() const {
					return (path.length() > 1) && (path[0] == '/');
				}

				NativeString UnixFile::getName() const {
					NativeString absolutePath = getAbsolutePath();
					if (absolutePath.length() == 1 && path[0] == '/') {
						return path;
					}
					jint index = absolutePath.lastIndexOf('/');
					if (index >= 0) {
						return absolutePath.substring(index + 1);
					}
					return absolutePath;
				}

				NativeString UnixFile::getParentPath() const {
					NativeString absolutePath = getAbsolutePath();
					if (absolutePath.length() > 1) {
						jint index = absolutePath.lastIndexOf('/');
						if (index > 0) {
							return absolutePath.substring(0, index);
						}
					}
					return NativeString();
				}

				NativeString UnixFile::getAbsolutePath() const {
					if (isAbsolute()) {
						return path;
					}
					char buffer[1024];

					char * result = 0;
					EINTR_RETRY_RV(result, NULL, getcwd(buffer, sizeof(buffer)))

					if (result) {
						int n = strlen(buffer);
						if (path == ".") {
							if (buffer[n - 1] == '/') {
								return NativeString(buffer, 0, n - 1);
							} else {
								return NativeString(buffer, 0, n);
							}
						} else {
							if ((path.length() > 1) && (path[0] == '/')) {
								if (buffer[n - 1] == '/') {
									return NativeString(buffer, 0, n - 1) + path;
								} else {
									return NativeString(buffer, 0, n) + path;
								}
							} else {
								if (buffer[n - 1] == '/') {
									return NativeString(buffer, 0, n) + path;
								} else {
									return NativeString(buffer, 0, n) + "/" + path;
								}
							}
						}
					} else {
						throw NativeException(className, "getAbsolutePath", SYSTEM_EXCEPTION, "getcwd");
					}
				}

				jlong UnixFile::getSize() const {
					struct stat64 st;
					EINTR_RETRY(stat64(path.getString().c_str(), &st))
					if (result == 0) {
						return (jlong) st.st_size;
					} else {
						handleLastError("getSize", path);
					}
					return 0;
				}

				void UnixFile::setSize(jlong size) {
					if (truncate(path.getString().c_str(), size) != 0) {
						handleLastError("setSize", path);
					}
				}

				jlong UnixFile::getFreeSpace() const {
					struct statvfs64 fsstat;
					memset(&fsstat, 0, sizeof(struct statvfs64));

					EINTR_RETRY(statvfs64(path.getString().c_str(), &fsstat))

					if (result == 0) {
						return (jlong) (fsstat.f_frsize) * (jlong) (fsstat.f_bfree);
					} else {
						handleLastError("getFreeSpace", path);
					}
					return 0;
				}

				jlong UnixFile::getTotalSpace() const {
					struct statvfs64 fsstat;
					memset(&fsstat, 0, sizeof(struct statvfs64));

					EINTR_RETRY(statvfs64(path.getString().c_str(), &fsstat))

					if (result == 0) {
						return (jlong) (fsstat.f_frsize) * (jlong) (fsstat.f_blocks);
					} else {
						handleLastError("getFreeSpace", path);
					}
					return 0;
				}

				jlong UnixFile::getUsableSpace() const {
					struct statvfs64 fsstat;
					memset(&fsstat, 0, sizeof(struct statvfs64));

					EINTR_RETRY(statvfs64(path.getString().c_str(), &fsstat))

					if (result == 0) {
						return (jlong) (fsstat.f_frsize) * (jlong) (fsstat.f_bavail);
					} else {
						handleLastError("getFreeSpace", path);
					}
					return 0;
				}

				jbool UnixFile::isFile() const {
					struct stat64 st;
					EINTR_RETRY(stat64(path.getString().c_str(), &st))
					if (result == 0) {
						return S_ISREG(st.st_mode);
					} else {
						handleLastError("isFile", path);
					}
					return false;
				}

				jbool UnixFile::isLink() const {
					struct stat64 st;
					EINTR_RETRY(stat64(path.getString().c_str(), &st))
					if (result == 0) {
						return S_ISLNK(st.st_mode);
					} else {
						handleLastError("isLink", path);
					}
					return false;
				}

				jbool UnixFile::isDirectory() const {
					struct stat64 st;
					EINTR_RETRY(stat64(path.getString().c_str(), &st))
					if (result == 0) {
						return S_ISDIR(st.st_mode);
					} else {
						handleLastError("isDirectory", path);
					}
					return false;
				}

				jbool UnixFile::isHidden() const {
					NativeString name = getName();
					return name.length() > 1 && name[0] == '.';
				}

				jlong UnixFile::getCreatedTime() const {
					struct stat64 st;
					EINTR_RETRY(stat64(path.getString().c_str(), &st))
					if (result == 0) {
						return 1000 * (jlong) st.st_ctime;
					} else {
						handleLastError("created", path);
					}
					return 0;
				}

				jlong UnixFile::getLastModified() const {
					struct stat64 st;
					EINTR_RETRY(stat64(path.getString().c_str(), &st))
					if (result == 0) {
						return 1000 * (jlong) st.st_mtime;
					} else {
						handleLastError("getLastModified", path);
					}
					return 0;
				}

				void UnixFile::setLastModified(const jlong time) {
					struct stat64 st;
					EINTR_RETRY(stat64(path.getString().c_str(), &st))
					if (result == 0) {
						struct timeval tv[2];
						/* Preserve access time */
						tv[0].tv_sec = st.st_atime;
						tv[0].tv_usec = 0;

						/* Change last-modified time */
						tv[1].tv_sec = time / 1000;
						tv[1].tv_usec = (time % 1000) * 1000;

						if (utimes(path.getString().c_str(), tv) != 0) {
							handleLastError("setLastModified", path);
						}
					} else {
						handleLastError("setLastModified", path);
					}

				}

				jbool UnixFile::canRead() const {
					struct stat64 st;
					EINTR_RETRY(stat64(path.getString().c_str(), &st))
					if (result == 0) {
						if (st.st_uid == geteuid())
							return (st.st_mode & S_IRUSR) != 0;
						else if (st.st_gid == getegid())
							return (st.st_mode & S_IRGRP) != 0;
						else
							return (st.st_mode & S_IROTH) != 0 || geteuid() == 0;
					} else {
						handleLastError("getLastModified", path);
					}
					return 0;
				}

				jbool UnixFile::canWrite() const {
					struct stat64 st;
					EINTR_RETRY(stat64(path.getString().c_str(), &st))
					if (result == 0) {
						if (st.st_uid == geteuid())
							return (st.st_mode & S_IWUSR) != 0;
						else if (st.st_gid == getegid())
							return (st.st_mode & S_IWGRP) != 0;
						else
							return (st.st_mode & S_IWOTH) != 0 || geteuid() == 0;
					} else {
						handleLastError("getLastModified", path);
					}
					return 0;
				}

				jbool UnixFile::canExecute() const {
					struct stat64 st;
					EINTR_RETRY(stat64(path.getString().c_str(), &st))
					if (result == 0) {
						if (st.st_uid == geteuid() || geteuid() == 0)
							return (st.st_mode & S_IXUSR) != 0;
						else if (st.st_gid == getegid())
							return (st.st_mode & S_IXGRP) != 0;
						else
							return (st.st_mode & S_IXOTH) != 0;
					} else {
						handleLastError("getLastModified", path);
					}
					return 0;
				}

				void UnixFile::setWritable(jbool flag) {
					struct stat64 st;
					EINTR_RETRY(stat64(path.getString().c_str(), &st))
					if (result != 0) {
						handleLastError("setWritable", path);
					}
					mode_t mode;
					if (flag) {
						mode = st.st_mode | S_IWUSR;
					} else {
						mode_t wmask = S_IWUSR | S_IWGRP | S_IWOTH;
						mode = st.st_mode & ~wmask;
					}
					if (chmod(path.getString().c_str(), mode) != 0) {
						handleLastError("setWritable", path);
					}
				}

				void UnixFile::setExecutable(jbool flag) {
					struct stat64 st;
					EINTR_RETRY(stat64(path.getString().c_str(), &st))
					if (result != 0) {
						handleLastError("setExecutable", path);
					}
					mode_t mode;
					if (flag) {
						mode = st.st_mode | S_IXUSR;
					} else {
						mode_t wmask = S_IXUSR | S_IXGRP | S_IXOTH;
						mode = st.st_mode & ~wmask;
					}

					EINTR_RETRY_R(result, chmod(path.getString().c_str(), mode))
					if (result != 0) {
						handleLastError("setExecutable", path);
					}
				}

				void UnixFile::list(std::vector<NativeString>& files) const {
					std::vector<UnixFile> unixFiles;
					list(unixFiles);
					for (std::vector<UnixFile>::iterator it = unixFiles.begin(); it != unixFiles.end(); ++it) {
						files.push_back(it->path);
					}
				}

				void UnixFile::list(std::vector<UnixFile>& files) const {
					if (!exists() || !isDirectory()) {
						return;
					}

					DIR* pDir;
					std::string current;

					pDir = opendir(path.getString().c_str());
					if (!pDir) {
						handleLastError("list", path);
					}

					while (true) {
						struct dirent* pEntry = readdir(pDir);
						if (pEntry) {
							current = pEntry->d_name;
						} else {
							break;
						}
						if (current != "." && current != "..") {
							if (path.endsWith('/')) {
								files.push_back(UnixFile(path + current));
							} else {
								files.push_back(UnixFile(path + "/" + current));
							}
						}
					}

					if (pDir) {
						closedir(pDir);
					}
				}

				void UnixFile::copyTo(const NativeString& newPath) const {

					int sd = 0;
					EINTR_RETRY_R(sd, open(path.getString().c_str(), O_RDONLY))

					if (sd == -1) {
						handleLastError("copyTo", path);
					}

					struct stat64 st;
					EINTR_RETRY(fstat64(sd, &st))

					if (result != 0) {
						EINTR_RETRY_R(result, ::close(sd))
						handleLastError("copyTo", path);
					}

					const long blockSize = st.st_blksize;

					int dd = 0;
					EINTR_RETRY_R(dd, open(newPath.getString().c_str(), O_CREAT | O_TRUNC | O_WRONLY, st.st_mode & S_IRWXU))

					if (dd == -1) {
						EINTR_RETRY_R(result, ::close(sd))
						handleLastError("copyTo", path);
					}

					char * buffer = new char[blockSize];
					try {
						int n = 0;

						while (true) {
							EINTR_RETRY_R(result, read(sd, buffer, blockSize))
							if (result <= 0) {
								break;
							}

							int n = result;

							EINTR_RETRY_R(result, write(dd, buffer, n))
							if (result != n) {
								handleLastError("copyTo", path);
							}
						}
						if (n < 0) {
							handleLastError("copyTo", path);
						}
					} catch (...) {
						delete[] buffer;
						EINTR_RETRY_R(result, ::close(sd))
						EINTR_RETRY_R(result, ::close(dd))
						throw;
					}

					delete[] buffer;
					EINTR_RETRY_R(result, ::close(sd))
					if (fsync(dd) != 0) {
						EINTR_RETRY_R(result, ::close(dd))
						handleLastError("copyTo", path);
					}
					EINTR_RETRY_R(result, ::close(dd))
					if (result != 0) {
						handleLastError("copyTo", path);
					}
				}

				void UnixFile::moveTo(const NativeString& newPath) {
					copyTo(newPath);
					remove(true);
					path = newPath;
				}

				void UnixFile::renameTo(const NativeString& newPath) {
					if (rename(path.getString().c_str(), newPath.getString().c_str()) != 0) {
						handleLastError("renameTo", path);
					}
					path = newPath;
				}

				void UnixFile::remove(jbool recursive) {
					if (recursive && isDirectory()) {
						std::vector<UnixFile> files;
						list(files);
						for (std::vector<UnixFile>::iterator it = files.begin(); it != files.end(); ++it) {
							it->remove(true);
						}
					}
					removeLeaf();
				}

				void UnixFile::removeLeaf() {
					int rc;
					if (!isLink() && isDirectory()) {
						rc = rmdir(path.getString().c_str());
					} else {
						rc = unlink(path.getString().c_str());
					}
					if (rc) {
						handleLastError("remove", path);
					}
				}

				jbool UnixFile::createFile() {

					int n = 0;
					EINTR_RETRY_R(n, open(path.getString().c_str(), O_WRONLY | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH))

					if (n != -1) {
						EINTR_RETRY(::close(n))
						return true;
					}
					if (n == -1 && errno == EEXIST) {
						return false;
					} else {
						handleLastError("createFile", path);
					}
					return false;
				}

				jbool UnixFile::createDirectory() {
					if (exists() && isDirectory()) {
						return false;
					}
					if (mkdir(path.getString().c_str(), S_IRWXU | S_IRWXG | S_IRWXO) != 0) {
						handleLastError("createDirectory", path);
					}
					return true;
				}

				void UnixFile::createDirectories() {
					if (!exists()) {
						NativeString parentPath = getParentPath();
						if (!parentPath.isEmpty()) {
							UnixFile parent(parentPath);
							parent.createDirectories();
						}
					}
					createDirectory();
				}

				void UnixFile::handleLastError(const NativeString& methodName, const NativeString& message) const {
					switch (errno) {
						case EIO:
							throw NativeException(className, methodName, IO_EXCEPTION, message, errno);
						case EPERM:
							throw NativeException(className, methodName, FILE_ACCESS_DENIED_EXCEPTION, "insufficient permissions: " + message, errno);
						case EACCES:
							throw NativeException(className, methodName, FILE_ACCESS_DENIED_EXCEPTION, message, errno);
						case ENOENT:
							throw NativeException(className, methodName, FILE_NOT_FOUND_EXCEPTION, message, errno);
						case ENOTDIR:
							throw NativeException(className, methodName, FILE_OPEN_EXCEPTION, "not a directory: " + message, errno);
						case EISDIR:
							throw NativeException(className, methodName, FILE_OPEN_EXCEPTION, "not a file: " + message, errno);
						case EROFS:
							throw NativeException(className, methodName, FILE_READ_ONLY_EXCEPTION, message, errno);
						case EEXIST:
							throw NativeException(className, methodName, FILE_EXISTS_EXCEPTION, message, errno);
						case ENOSPC:
							throw NativeException(className, methodName, FILE_EXCEPTION, "no space left on device: " + message, errno);
						case EDQUOT:
							throw NativeException(className, methodName, FILE_EXCEPTION, "disk quota exceeded: " + message, errno);
#ifndef _AIX
						case ENOTEMPTY:
							throw NativeException(className, methodName, FILE_EXCEPTION, "directory not empty: " + message, errno);
#endif
						case ENAMETOOLONG:
							throw NativeException(className, methodName, PATH_SYNTAX_EXCEPTION, message, errno);
						case ENFILE:
						case EMFILE:
							throw NativeException(className, methodName, FILE_EXCEPTION, "too many open files: " + message, errno);
						default:
							throw NativeException(className, methodName, FILE_EXCEPTION, message, errno);
					}
				}

			}
		}
	}
}
