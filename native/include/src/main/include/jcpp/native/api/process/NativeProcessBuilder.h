#ifndef JCPP_NATIVE_API_PROCESS_NATIVEPROCESSBUILDER
#define JCPP_NATIVE_API_PROCESS_NATIVEPROCESSBUILDER

#include <vector>
#include <map>
#include "jcpp/native/api/NativeString.h"

namespace jcpp {
	namespace native {
		namespace api {
			namespace process {

				enum NativeProcessBuilderRedirectType {
					APPEND, INHERIT, PIPE, READ, WRITE
				};

				class JCPP_EXPORT NativeProcessBuilderRedirect {
				private:
					NativeProcessBuilderRedirectType type;
					NativeString file;

					NativeProcessBuilderRedirect(NativeProcessBuilderRedirectType type, const NativeString& file);
				public:
					static NativeProcessBuilderRedirect INHERIT;
					static NativeProcessBuilderRedirect REDIRECT_PIPE;

					NativeProcessBuilderRedirect(const NativeProcessBuilderRedirect& redirect);

					static NativeProcessBuilderRedirect appendTo(const NativeString& file);
					static NativeProcessBuilderRedirect from(const NativeString& file);
					static NativeProcessBuilderRedirect to(const NativeString& file);

					NativeProcessBuilderRedirectType getType() const;
					NativeString getFile() const;
				};

				class JCPP_EXPORT NativeProcessBuilder {

				private:
					NativeString directory;
					std::vector<NativeString> command;
					jbool inheritEnvironment;
					std::map<NativeString, NativeString> env;
					jbool redirectErrorStream;
					NativeProcessBuilderRedirect redirectOutput;
					NativeProcessBuilderRedirect redirectError;
					NativeProcessBuilderRedirect redirectInput;

				public:
					/**
					 * Creates a Native Process Builder with the following default values
					 * directory = "."
					 * command = []
					 * inheritEnvironment = true;
					 * env = [:]
					 * redirectErrorStream = false;
					 * redirectOutput = PIPE;
					 * redirectError = PIPE;
					 * redirectInput = PIPE;
					 */
					NativeProcessBuilder();

					//~-------------------------------------------------------------------------------------------------------------------------
					//~ Command Line Arguments
					//~-------------------------------------------------------------------------------------------------------------------------

					/**
					 * Fills this process builder's command arguments.
					 */
					void getCommand(std::vector<NativeString>& commandArgs);

					/**
					 * Sets this process builder's command arguments.
					 *
					 * Returns the reference to this ProcessBuilder
					 */
					NativeProcessBuilder& setCommand(std::vector<NativeString>& commandArgs);

					/**
					 *  Adds the command argument to this process builder's command arguments.
					 *
					 *  Returns the reference to this ProcessBuilder
					 */
					NativeProcessBuilder& addCommand(const NativeString& commandArg);

					//~-------------------------------------------------------------------------------------------------------------------------
					//~ Child Process Working Directory
					//~-------------------------------------------------------------------------------------------------------------------------

					/**
					 * Returns this process builder's working directory.
					 */
					NativeString getDirectory() const;

					/**
					 * Sets this process builder's working directory.
					 *
					 * Returns the reference to this ProcessBuilder
					 */
					NativeProcessBuilder& setDirectory(NativeString directory);

					//~-------------------------------------------------------------------------------------------------------------------------
					//~ Child Process Environment Variables
					//~-------------------------------------------------------------------------------------------------------------------------

					/**
					 * Returns if the child process should inherit the environment variables
					 * of the parent process
					 */
					jbool isInheritEnvironment() const;

					/**
					 * Sets if the child process should inherit the environment variables of the
					 * parent process
					 *
					 * Returns the reference to this ProcessBuilder
					 */
					NativeProcessBuilder& setInheritEnvironment(jbool inherit);

					/**
					 * Fills a string map view of this process builder's environment variables.
					 */
					void getEnvironment(std::map<NativeString, NativeString> & env);

					/**
					 * Adds an environment variable to be set in the child process
					 *
					 * Returns the reference to this ProcessBuilder
					 */
					NativeProcessBuilder& addEnvironment(const NativeString& key, const NativeString& value);

					/**
					 * Removes an environment variable that was to be set in the child process
					 *
					 * Returns the reference to this ProcessBuilder
					 */
					NativeProcessBuilder& removeEnvironment(const NativeString& key);

					//~-------------------------------------------------------------------------------------------------------------------------
					//~ Child Standard Output, Error and Input Streams
					//~-------------------------------------------------------------------------------------------------------------------------

					/**
					 * Sets the source and destination for subprocess standard I/O to be the same as those of the current Java process.
					 *
					 * Returns the reference to this ProcessBuilder
					 */
					NativeProcessBuilder& inheritIO();

					//~-------------------------------------------------------------------------------------------------------------------------
					//~ Standard Error Stream
					//~-------------------------------------------------------------------------------------------------------------------------

					/**
					 * Tells whether this process builder merges standard error and standard output.
					 * If this property is true, then any error output generated by subprocesses started by this builder
					 * will be merged with the standard output. The initial value is false.
					 */
					jbool isRedirectErrorStreamToOutputStream() const;

					/**
					 * Sets this process builder's redirectErrorStream property.
					 * If this property is true, then any error output generated by subprocesses started by this builder
					 * will be merged with the standard output. The initial value is false.
					 *
					 * Returns the reference to this ProcessBuilder
					 */
					NativeProcessBuilder& setRedirectErrorStreamToOutputStream(jbool redirectErrorStream);

					/**
					 * Returns this process builder's standard error destination.
					 */
					NativeProcessBuilderRedirect getRedirectError() const;

					/**
					 * Sets this process builder's standard error destination to a file.
					 * Similar to setRedirectError(NativeProcessBuilderRedirect::to(file))
					 *
					 * Returns the reference to this ProcessBuilder
					 */
					NativeProcessBuilder& setRedirectError(const NativeString& file);

					/**
					 * Sets this process builder's standard error destination.
					 *
					 * Returns the reference to this ProcessBuilder
					 */
					NativeProcessBuilder& setRedirectError(const NativeProcessBuilderRedirect& destination);

					//~-------------------------------------------------------------------------------------------------------------------------
					//~ Standard Output Stream
					//~-------------------------------------------------------------------------------------------------------------------------

					/**
					 *
					 * Returns this process builder's standard output destination.
					 */
					NativeProcessBuilderRedirect getRedirectOutput() const;

					/**
					 * Sets this process builder's standard output destination to a file.
					 * Similar to setRedirectOutput(NativeProcessBuilderRedirect::to(file))
					 *
					 * Returns the reference to this ProcessBuilder
					 */
					NativeProcessBuilder& setRedirectOutput(const NativeString& file);

					/**
					 * Sets this process builder's standard output destination.
					 *
					 * Returns the reference to this ProcessBuilder
					 */
					NativeProcessBuilder& setRedirectOutput(const NativeProcessBuilderRedirect& destination);

					//~-------------------------------------------------------------------------------------------------------------------------
					//~ Standard Input Stream
					//~-------------------------------------------------------------------------------------------------------------------------

					/**
					 * Returns this process builder's standard input source.
					 */
					NativeProcessBuilderRedirect getRedirectInput() const;

					/**
					 * Sets this process builder's standard input source to a file.
					 * Similar to setRedirectInput(NativeProcessBuilderRedirect::from(file))
					 *
					 * Returns the reference to this ProcessBuilder
					 */
					NativeProcessBuilder& setRedirectInput(const NativeString& file);

					/**
					 * Sets this process builder's standard input source.
					 *
					 * Returns the reference to this ProcessBuilder
					 */
					NativeProcessBuilder& setRedirectInput(const NativeProcessBuilderRedirect& source);

				};

			}
		}
	}
}

#endif
