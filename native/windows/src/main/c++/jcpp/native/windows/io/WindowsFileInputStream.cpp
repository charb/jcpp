#include "jcpp/native/windows/io/WindowsFileInputStream.h"
#include "jcpp/native/api/NativeException.h"

namespace jcpp {
	namespace native {
		namespace windows {
			namespace io {

				NativeString WindowsFileInputStream::className("jcpp::native::windows::io::WindowsFileInputStream");

				WindowsFileInputStream::WindowsFileInputStream(const NativeString& path) :
						fileDescriptor() {

					HANDLE h = CreateFile(path.getString().c_str(), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

					if (h == INVALID_HANDLE_VALUE) {
						DWORD err = GetLastError();
						switch (err) {
							case ERROR_TOO_MANY_OPEN_FILES:
								throw NativeException(className, "WindowsFileInputStream", IO_EXCEPTION, "No more file descriptors available (too many open files)", err);
							case ERROR_FILE_NOT_FOUND:
								throw NativeException(className, "WindowsFileInputStream", FILE_NOT_FOUND_EXCEPTION, path, err);
							case ERROR_PATH_NOT_FOUND:
							case ERROR_BAD_NETPATH:
							case ERROR_CANT_RESOLVE_FILENAME:
							case ERROR_INVALID_DRIVE:
								throw NativeException(className, "WindowsFileInputStream", PATH_NOT_FOUND_EXCEPTION, path, err);
							default:
								throw NativeException(className, "WindowsFileInputStream", IO_EXCEPTION, "Failed to open: " + path, err);
						}
					}
					fileDescriptor.setHandle(h);
				}

				WindowsFileInputStream::WindowsFileInputStream(const WindowsFileDescriptor& fileDescriptor) :
						fileDescriptor(fileDescriptor) {
				}

				WindowsFileInputStream::~WindowsFileInputStream() {
					try {
						close();
					} catch (...) {
					}
				}

				NativeFileDescriptor * WindowsFileInputStream::getNativeFileDescriptor() {
					return &fileDescriptor;
				}

				jbyte WindowsFileInputStream::read() {
					jbyte byte = 0;
					jint n = read(&byte, 0, 1);
					if (n == 0) {
						return -1;
					}
					return byte;
				}

				jint WindowsFileInputStream::read(jbyte * buf, jint offset, jint length) {
					if (fileDescriptor.getHandle() == null) {
						throw NativeException(className, "read", IO_EXCEPTION, "The file stream was closed!");
					}
					DWORD read = 0;
					if (ReadFile(fileDescriptor.getHandle(), (buf + offset), length, &read, NULL) == 0) {
						int error = GetLastError();
						if (error == ERROR_BROKEN_PIPE) {
							return -1; /* EOF */
						}
						throw NativeException(className, "read", IO_EXCEPTION, "Read Error");
					} else if (read == 0) {
						return -1;
					}
					return read;
				}

				jlong WindowsFileInputStream::skip(jlong offset) {
					if (fileDescriptor.getHandle() == null) {
						throw NativeException(className, "skip", IO_EXCEPTION, "The file stream was closed!");
					}
					DWORD lowPos = 0;
					long highPos = 0;
					lowPos = SetFilePointer(fileDescriptor.getHandle(), lowPos, &highPos, FILE_CURRENT);
					if (lowPos == ((DWORD) -1)) {
						if (GetLastError() != ERROR_SUCCESS) {
							return -1;
						}
					}
					jlong oldPosition = (((jlong) highPos) << 32) | lowPos;

					lowPos = (DWORD) offset;
					highPos = (long) (offset >> 32);
					lowPos = SetFilePointer(fileDescriptor.getHandle(), lowPos, &highPos, FILE_CURRENT);
					if (lowPos == ((DWORD) -1)) {
						if (GetLastError() != ERROR_SUCCESS) {
							return -1;
						}
					}
					jlong newPosition = (((jlong) highPos) << 32) | lowPos;

					return newPosition - oldPosition;
				}

				jlong WindowsFileInputStream::available() {
					HANDLE h = fileDescriptor.getHandle();
					if (h == null) {
						throw NativeException(className, "available", IO_EXCEPTION, "The file stream was closed!");
					}
					DWORD type = GetFileType(h);

					if (type == FILE_TYPE_CHAR || type == FILE_TYPE_PIPE) {
						long lpbytes;
						HANDLE stdInHandle = GetStdHandle(STD_INPUT_HANDLE);

						if (stdInHandle == h) { /* Handle is for keyboard */

							HANDLE stdHandle;
							DWORD numEventsRead = 0; /* Number of events read from buffer */
							DWORD numEvents = 0; /* Number of events in buffer */
							DWORD i = 0; /* Loop index */
							DWORD curLength = 0; /* Position marker */
							DWORD actualLength = 0; /* Number of bytes readable */
							INPUT_RECORD * lpBuffer; /* Pointer to records of input events */
							DWORD bufferSize = 0;

							if ((stdHandle = GetStdHandle(STD_INPUT_HANDLE)) == INVALID_HANDLE_VALUE) {
								throw NativeException(className, "available", IO_EXCEPTION, "Failed to get available bytes");
							}

							/* Construct an array of input records in the console buffer */
							if (GetNumberOfConsoleInputEvents(stdHandle, &numEvents) == 0) {
								throw NativeException(className, "available", IO_EXCEPTION, "Failed to get available bytes");
							}

							/* lpBuffer must fit into 64K or else PeekConsoleInput fails */
							if (numEvents > 2000) {
								numEvents = 2000;
							}

							bufferSize = numEvents * sizeof(INPUT_RECORD);
							if (bufferSize == 0) {
								bufferSize = 1;
							}
							lpBuffer = (INPUT_RECORD *) malloc(bufferSize);
							if (lpBuffer == NULL) {
								throw NativeException(className, "available", IO_EXCEPTION, "Failed to get available bytes");
							}

							if (PeekConsoleInput(stdHandle, lpBuffer, numEvents, &numEventsRead) == 0) {
								free(lpBuffer);
								throw NativeException(className, "available", IO_EXCEPTION, "Failed to get available bytes");
							}

							/* Examine input records for the number of bytes available */
							for (i = 0; i < numEvents; i++) {
								if (lpBuffer[i].EventType == KEY_EVENT) {
									KEY_EVENT_RECORD *keyRecord = (KEY_EVENT_RECORD *) &(lpBuffer[i].Event);
									if (keyRecord->bKeyDown == TRUE) {
										CHAR *keyPressed = (CHAR *) &(keyRecord->uChar);
										curLength++;
										if (*keyPressed == '\r') {
											actualLength = curLength;
										}
									}
								}
							}
							if (lpBuffer != NULL)
								free(lpBuffer);
							return (jlong) actualLength;

						} else { /* Handle is for pipe */

							DWORD pbytes;
							if (!PeekNamedPipe(h, NULL, 0, NULL, &pbytes, NULL)) {
								if (GetLastError() != ERROR_BROKEN_PIPE) {
									throw NativeException(className, "available", IO_EXCEPTION, "Failed to get available bytes");
								}
								return 0;
							}
							return (jlong) pbytes;
						}

					} else if (type == FILE_TYPE_DISK) {
						long highPos = 0;
						DWORD sizeLow = 0;
						DWORD sizeHigh = 0;
						DWORD lowPos = SetFilePointer(h, 0, &highPos, FILE_CURRENT);
						if (lowPos == ((DWORD) -1)) {
							throw NativeException(className, "available", IO_EXCEPTION, "Failed to get available bytes");
						}
						jlong current = (((jlong) highPos) << 32) | lowPos;
						jlong end = GetFileSize(h, &sizeHigh);
						if (sizeLow == ((DWORD) -1)) {
							throw NativeException(className, "available", IO_EXCEPTION, "Failed to get available bytes");
						}
						return end - current;
					} else {
						throw NativeException(className, "available", IO_EXCEPTION, "Failed to get available bytes");
					}
				}

				void WindowsFileInputStream::close() {
					HANDLE h = fileDescriptor.getHandle();
					if (h != null && h != INVALID_HANDLE_VALUE) {
						if (CloseHandle(h) == 0) {
							throw NativeException(className, "close", IO_EXCEPTION, "Failed to close handle");
						}
						fileDescriptor.setHandle(null);
					}
				}

			}
		}
	}
}
