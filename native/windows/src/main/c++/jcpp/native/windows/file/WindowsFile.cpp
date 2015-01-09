#include "jcpp/native/windows/WindowsUtils.h"
#include "jcpp/native/windows/file/WindowsFile.h"
#include "jcpp/native/api/NativeException.h"

using namespace jcpp::native::api;

namespace jcpp {
	namespace native {
		namespace windows {
			namespace file {

				class FileHandle {
				private:
					HANDLE handle;
				public:
					FileHandle(const NativeString& path, DWORD access, DWORD share, DWORD disp) {
						handle = CreateFileA(path.getString().c_str(), access, share, 0, disp, 0, 0);
						if (handle == INVALID_HANDLE_VALUE) {
							jcpp::native::windows::file::WindowsFile::handleLastError("FileHandle", path);
						}
					}

					~FileHandle() {
						if (handle != INVALID_HANDLE_VALUE)
							CloseHandle(handle);
					}

					HANDLE get() const {
						return handle;
					}
				};

				NativeString WindowsFile::className("jcpp::native::windows::file::WindowsFile");

				WindowsFile::WindowsFile() :
						NativeFile() {
				}

				WindowsFile::WindowsFile(const NativeString& path) :
						NativeFile() {
					this->path = resolvePath(path);
				}

				WindowsFile::WindowsFile(const NativeString& parent, const NativeString& child) :
						NativeFile() {
					this->path = joinPaths(parent, child);
				}

				NativeString WindowsFile::resolvePath(const NativeString& path) const {
					NativeString p = path.trim();
					jchar ps = '\\';
					p = p.replace('/', ps);
					jint length = p.length();
					if ((length > 1) && (p[length - 1] == '\\') && !((length == 3 && p[1] == ':'))) {
						p = p = p.substring(0, p.length() - 1);
					}
					return p;
				}

				NativeString WindowsFile::joinPaths(const NativeString& parent, const NativeString& child) const {
					NativeString p = resolvePath(parent);
					return p.endsWith('\\') ? p + resolvePath(child) : p + "\\" + resolvePath(child);
				}

				void WindowsFile::normalise() {
					if (!isAbsolute()) {
						path = getAbsolutePath();
					}
				}

				jbool WindowsFile::exists() const {
					DWORD attr = GetFileAttributesA(path.getString().c_str());
					if (attr == 0xFFFFFFFF) {
						switch (GetLastError()) {
							case ERROR_FILE_NOT_FOUND:
							case ERROR_PATH_NOT_FOUND:
							case ERROR_NOT_READY:
							case ERROR_INVALID_DRIVE:
								return false;
							default:
								handleLastError("exists", path);
						}
					}
					return true;
				}

				jbool WindowsFile::isAbsolute() const {
					return ((path.length() > 2) && (path[0] >= 'A') && (path[0] <= 'z') && (path[1] == ':') && (path[2] == '\\')) || ((path.length() > 2) && (path[0] == '\\') && (path[1] == '\\'));
				}

				NativeString WindowsFile::getName() const {
					NativeString absolutePath = getAbsolutePath();
					if (absolutePath.length() > 3) {
						jint index = absolutePath.lastIndexOf('\\');
						if (index > 0) {
							return absolutePath.substring(index + 1);
						}
					}
					return absolutePath;
				}

				NativeString WindowsFile::getParentPath() const {
					NativeString absolutePath = getAbsolutePath();
					if (absolutePath.length() > 3) {
						jint index = absolutePath.lastIndexOf('\\');
						if (index > 2) {
							return absolutePath.substring(0, index);
						}
					}
					return NativeString();
				}

				NativeString WindowsFile::getAbsolutePath() const {
					if (isAbsolute()) {
						return path;
					}
					char buffer[MAX_PATH];
					DWORD n = GetCurrentDirectoryA(sizeof(buffer), buffer);
					if (n > 0 && n < sizeof(buffer)) {
						if (path == ".") {
							if (buffer[n - 1] == '\\') {
								return NativeString(buffer, 0, n - 1);
							} else {
								return NativeString(buffer, 0, n);
							}
						} else {
							if ((path.length() > 1) && (path[0] == '\\')) {
								if (buffer[n - 1] == '\\') {
									return NativeString(buffer, 0, n - 1) + path;
								} else {
									return NativeString(buffer, 0, n) + path;
								}
							} else {
								if (buffer[n - 1] == '\\') {
									return NativeString(buffer, 0, n) + path;
								} else {
									return NativeString(buffer, 0, n) + "\\" + path;
								}
							}
						}
					} else {
						throw NativeException(className, "getAbsolutePath", SYSTEM_EXCEPTION, "Get Current Directory");
					}
				}

				jlong WindowsFile::getSize() const {
					WIN32_FILE_ATTRIBUTE_DATA fad;
					if (GetFileAttributesEx(path.getString().c_str(), GetFileExInfoStandard, &fad) == 0) {
						handleLastError("getSize", path);
					}
					LARGE_INTEGER li;
					li.u.LowPart = fad.nFileSizeLow;
					li.u.HighPart = fad.nFileSizeHigh;
					return (jlong) li.QuadPart;
				}

				void WindowsFile::setSize(jlong size) {
					FileHandle fh(path, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, OPEN_EXISTING);
					LARGE_INTEGER li;
					li.QuadPart = size;
					if (SetFilePointer(fh.get(), li.u.LowPart, &li.u.HighPart, FILE_BEGIN) == -1) {
						handleLastError("setSize", path);
					}
					if (SetEndOfFile(fh.get()) == 0) {
						handleLastError("setSize", path);
					}
				}

				jlong WindowsFile::getFreeSpace() const {
					if (exists()) {
						NativeString dirPath = isDirectory() ? path : getParentPath();
						ULARGE_INTEGER totalSpace, freeSpace, usableSpace;
						if (GetDiskFreeSpaceEx(dirPath.getString().c_str(), &usableSpace, &totalSpace, &freeSpace) == 0) {
							handleLastError("getFreeSpace", path);
						}
						return (jlong) freeSpace.QuadPart;
					}
					return 0;
				}

				jlong WindowsFile::getTotalSpace() const {
					if (exists()) {
						NativeString dirPath = isDirectory() ? path : getParentPath();
						ULARGE_INTEGER totalSpace, freeSpace, usableSpace;
						if (GetDiskFreeSpaceEx(dirPath.getString().c_str(), &usableSpace, &totalSpace, &freeSpace) == 0) {
							handleLastError("getFreeSpace", path);
						}
						return (jlong) totalSpace.QuadPart;
					}
					return 0;
				}

				jlong WindowsFile::getUsableSpace() const {
					if (exists()) {
						NativeString dirPath = isDirectory() ? path : getParentPath();
						ULARGE_INTEGER totalSpace, freeSpace, usableSpace;
						if (GetDiskFreeSpaceEx(dirPath.getString().c_str(), &usableSpace, &totalSpace, &freeSpace) == 0) {
							handleLastError("getFreeSpace", path);
						}
						return (jlong) usableSpace.QuadPart;
					}
					return 0;
				}

				jbool WindowsFile::isFile() const {
					return !isDirectory();
				}

				jbool WindowsFile::isLink() const {
					return false;
				}

				jbool WindowsFile::isDirectory() const {
					DWORD attr = GetFileAttributesA(path.getString().c_str());
					if (attr == 0xFFFFFFFF) {
						handleLastError("isDirectory", path);
					}
					return (attr & FILE_ATTRIBUTE_DIRECTORY) != 0;
				}

				jbool WindowsFile::isHidden() const {
					DWORD attr = GetFileAttributesA(path.getString().c_str());
					if (attr == 0xFFFFFFFF) {
						handleLastError("isHidden", path);
					}
					return (attr & FILE_ATTRIBUTE_HIDDEN) != 0;
				}

				jlong WindowsFile::getCreatedTime() const {
					WIN32_FILE_ATTRIBUTE_DATA fad;
					if (GetFileAttributesExA(path.getString().c_str(), GetFileExInfoStandard, &fad) == 0) {
						handleLastError("created", path);
					}
					return WindowsUtils::fileTimeToJlong(fad.ftCreationTime);
				}

				jlong WindowsFile::getLastModified() const {
					WIN32_FILE_ATTRIBUTE_DATA fad;
					if (GetFileAttributesExA(path.getString().c_str(), GetFileExInfoStandard, &fad) == 0) {
						handleLastError("getLastModified", path);
					}
					return WindowsUtils::fileTimeToJlong(fad.ftLastWriteTime);
				}

				void WindowsFile::setLastModified(const jlong lm) {
					FILETIME ft;
					WindowsUtils::jlongToFileTime(lm, ft);

					FileHandle fh(path, FILE_ALL_ACCESS, FILE_SHARE_READ | FILE_SHARE_WRITE, OPEN_EXISTING);
					if (SetFileTime(fh.get(), 0, &ft, &ft) == 0) {
						handleLastError("setLastModified", path);
					}
				}

				jbool WindowsFile::canRead() const {
					DWORD attr = GetFileAttributesA(path.getString().c_str());
					if (attr == 0xFFFFFFFF) {
						switch (GetLastError()) {
							case ERROR_ACCESS_DENIED:
								return false;
							default:
								handleLastError("canRead", path);
						}

					}
					return true;
				}

				jbool WindowsFile::canWrite() const {
					DWORD attr = GetFileAttributesA(path.getString().c_str());
					if (attr == 0xFFFFFFFF) {
						handleLastError("canWrite", path);
					}
					return (attr & FILE_ATTRIBUTE_READONLY) == 0;
				}

				jbool WindowsFile::canExecute() const {
					return exists() && path.endsWith(".exe");
				}

				void WindowsFile::setWritable(jbool flag) {
					DWORD attr = GetFileAttributesA(path.getString().c_str());
					if (attr == 0xFFFFFFFF) {
						handleLastError("setWritable", path);
					}
					if (flag) {
						attr &= ~FILE_ATTRIBUTE_READONLY;
					} else {
						attr |= FILE_ATTRIBUTE_READONLY;
					}
					if (SetFileAttributesA(path.getString().c_str(), attr) == 0) {
						handleLastError("setWritable", path);
					}
				}

				void WindowsFile::setExecutable(jbool flag) {
				}

				void WindowsFile::list(std::vector<NativeString>& files) const {
					std::vector<WindowsFile> windowsFiles;
					list(windowsFiles);
					for (std::vector<WindowsFile>::iterator it = windowsFiles.begin(); it != windowsFiles.end(); ++it) {
						files.push_back(it->path);
					}
				}

				void WindowsFile::list(std::vector<WindowsFile>& files) const {
					if (!exists() || !isDirectory()) {
						return;
					}

					HANDLE fileHandle;
					WIN32_FIND_DATA findData;
					std::string current;

					NativeString pattern = path.endsWith('\\') ? path + "*" : path + "\\*";
					fileHandle = FindFirstFile(pattern.getString().c_str(), &findData);

					if (fileHandle == INVALID_HANDLE_VALUE) {
						if (GetLastError() != ERROR_NO_MORE_FILES) {
							handleLastError("list", path);
						}
					} else {
						current = findData.cFileName;

						while (true) {
							if (current != "." && current != "..") {
								if (path.endsWith('\\')) {
									files.push_back(WindowsFile(path + current));
								} else {
									files.push_back(WindowsFile(path + "\\" + current));
								}
							}
							if (FindNextFile(fileHandle, &findData) == 0) {
								if (GetLastError() != ERROR_NO_MORE_FILES) {
									if (fileHandle != INVALID_HANDLE_VALUE) {
										FindClose(fileHandle);
									}
									handleLastError("list", path);
								}
								break;
							}
							current = findData.cFileName;
						}

						if (fileHandle != INVALID_HANDLE_VALUE) {
							FindClose(fileHandle);
						}
					}
				}

				void WindowsFile::copyTo(const NativeString& newPath) const {
					if (CopyFileA(path.getString().c_str(), newPath.getString().c_str(), FALSE) != 0) {
						WindowsFile copy(newPath);
						copy.setWritable(true);
					} else {
						handleLastError("copyTo", path + " to " + newPath);
					}
				}

				void WindowsFile::moveTo(const NativeString& newPath) {
					copyTo(newPath);
					remove(true);
					path = newPath;
				}

				void WindowsFile::renameTo(const NativeString& newPath) {
					if (MoveFileA(path.getString().c_str(), newPath.getString().c_str()) == 0) {
						handleLastError("renameTo", path + " to " + newPath);
					}
					path = newPath;
				}

				void WindowsFile::remove(jbool recursive) {
					if (recursive && isDirectory()) {
						std::vector<WindowsFile> files;
						list(files);
						for (std::vector<WindowsFile>::iterator it = files.begin(); it != files.end(); ++it) {
							it->remove(true);
						}
					}
					removeLeaf();
				}

				void WindowsFile::removeLeaf() {
					if (isDirectory()) {
						if (RemoveDirectoryA(path.getString().c_str()) == 0) {
							handleLastError("removeLeaf", "Delete Directory: " + path);
						}
					} else {
						if (DeleteFileA(path.getString().c_str()) == 0) {
							handleLastError("removeLeaf", "Delete File: " + path);
						}
					}
				}

				jbool WindowsFile::createFile() {
					HANDLE hFile = CreateFileA(path.getString().c_str(), GENERIC_WRITE, 0, 0, CREATE_NEW, 0, 0);
					if (hFile != INVALID_HANDLE_VALUE) {
						CloseHandle(hFile);
						return true;
					} else if (GetLastError() == ERROR_FILE_EXISTS) {
						return false;
					} else {
						handleLastError("createFile", path);
					}
					return false;
				}

				jbool WindowsFile::createDirectory() {
					if (exists() && isDirectory()) {
						return false;
					}
					if (CreateDirectoryA(path.getString().c_str(), 0) == 0) {
						handleLastError("createDirectory", path);
					}
					return true;
				}

				void WindowsFile::createDirectories() {
					if (!exists()) {
						NativeString parentPath = getParentPath();
						if (!parentPath.isEmpty()) {
							WindowsFile parent(parentPath);
							parent.createDirectories();
						}
					}
					createDirectory();
				}

				void WindowsFile::handleLastError(const NativeString& methodName, const NativeString& message) {
					DWORD err = GetLastError();
					switch (err) {
						case ERROR_FILE_NOT_FOUND:
							throw NativeException(className, methodName, FILE_NOT_FOUND_EXCEPTION, message, err);
						case ERROR_PATH_NOT_FOUND:
						case ERROR_BAD_NETPATH:
						case ERROR_CANT_RESOLVE_FILENAME:
						case ERROR_INVALID_DRIVE:
							throw NativeException(className, methodName, PATH_NOT_FOUND_EXCEPTION, message, err);
						case ERROR_ACCESS_DENIED:
							throw NativeException(className, methodName, FILE_ACCESS_DENIED_EXCEPTION, message, err);
						case ERROR_ALREADY_EXISTS:
						case ERROR_FILE_EXISTS:
							throw NativeException(className, methodName, FILE_EXISTS_EXCEPTION, message, err);
						case ERROR_INVALID_NAME:
						case ERROR_DIRECTORY:
						case ERROR_FILENAME_EXCED_RANGE:
						case ERROR_BAD_PATHNAME:
							throw NativeException(className, methodName, PATH_SYNTAX_EXCEPTION, message, err);
						case ERROR_FILE_READ_ONLY:
							throw NativeException(className, methodName, FILE_READ_ONLY_EXCEPTION, message, err);
						case ERROR_CANNOT_MAKE:
							throw NativeException(className, methodName, FILE_CREATE_EXCEPTION, message, err);
						case ERROR_DIR_NOT_EMPTY:
							throw NativeException(className, methodName, FILE_EXCEPTION, "Directory Not Empty: " + message, err);
						case ERROR_WRITE_FAULT:
							throw NativeException(className, methodName, FILE_WRITE_EXCEPTION, message, err);
						case ERROR_READ_FAULT:
							throw NativeException(className, methodName, FILE_READ_EXCEPTION, message, err);
						case ERROR_SHARING_VIOLATION:
							throw NativeException(className, methodName, FILE_EXCEPTION, "Sharing Violation: " + message, err);
						case ERROR_LOCK_VIOLATION:
							throw NativeException(className, methodName, FILE_EXCEPTION, "Lock Violation: " + message, err);
						case ERROR_HANDLE_EOF:
							throw NativeException(className, methodName, FILE_READ_EXCEPTION, "EOF Reached: " + message, err);
						case ERROR_HANDLE_DISK_FULL:
						case ERROR_DISK_FULL:
							throw NativeException(className, methodName, FILE_WRITE_EXCEPTION, "Disk is Full: " + message, err);
						case ERROR_NEGATIVE_SEEK:
							throw NativeException(className, methodName, FILE_EXCEPTION, "Negative Seek: " + message, err);
						default:
							throw NativeException(className, methodName, FILE_EXCEPTION, message, err);
					}
				}

			}
		}
	}
}
