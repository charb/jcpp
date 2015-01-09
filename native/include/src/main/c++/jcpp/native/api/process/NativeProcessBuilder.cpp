#include "jcpp/native/api/process/NativeProcessBuilder.h"

namespace jcpp {
	namespace native {
		namespace api {
			namespace process {

				//~-------------------------------------------------------------------------------------------------------------------------
				//~ NativeProcessBuilderRedirect
				//~-------------------------------------------------------------------------------------------------------------------------

				NativeProcessBuilderRedirect NativeProcessBuilderRedirect::INHERIT(jcpp::native::api::process::INHERIT, NativeString());
				NativeProcessBuilderRedirect NativeProcessBuilderRedirect::REDIRECT_PIPE(jcpp::native::api::process::PIPE, NativeString());

				NativeProcessBuilderRedirect::NativeProcessBuilderRedirect(NativeProcessBuilderRedirectType type, const NativeString& file) :
						type(type), file(file) {
				}

				NativeProcessBuilderRedirect::NativeProcessBuilderRedirect(const NativeProcessBuilderRedirect& redirect) :
						type(redirect.type), file(redirect.file) {
				}

				NativeProcessBuilderRedirect NativeProcessBuilderRedirect::appendTo(const NativeString& file) {
					return NativeProcessBuilderRedirect(APPEND, file);
				}

				NativeProcessBuilderRedirect NativeProcessBuilderRedirect::from(const NativeString& file) {
					return NativeProcessBuilderRedirect(READ, file);
				}

				NativeProcessBuilderRedirect NativeProcessBuilderRedirect::to(const NativeString& file) {
					return NativeProcessBuilderRedirect(WRITE, file);
				}

				NativeProcessBuilderRedirectType NativeProcessBuilderRedirect::getType() const {
					return type;
				}

				NativeString NativeProcessBuilderRedirect::getFile() const {
					return file;
				}

				//~-------------------------------------------------------------------------------------------------------------------------
				//~ NativeProcessBuilder
				//~-------------------------------------------------------------------------------------------------------------------------

				NativeProcessBuilder::NativeProcessBuilder() :
						directory("."), command(), inheritEnvironment(true), env(), redirectErrorStream(false), redirectOutput(NativeProcessBuilderRedirect::REDIRECT_PIPE), redirectError(NativeProcessBuilderRedirect::REDIRECT_PIPE), redirectInput(
								NativeProcessBuilderRedirect::REDIRECT_PIPE) {
				}

				void NativeProcessBuilder::getCommand(std::vector<NativeString>& commandArgs) {
					for (std::vector<NativeString>::iterator it = command.begin(); it != command.end(); ++it) {
						commandArgs.push_back(*it);
					}
				}

				NativeProcessBuilder& NativeProcessBuilder::setCommand(std::vector<NativeString>& commandArgs) {
					command.clear();
					for (std::vector<NativeString>::iterator it = commandArgs.begin(); it != commandArgs.end(); ++it) {
						command.push_back(*it);
					}
					return *this;
				}

				NativeProcessBuilder& NativeProcessBuilder::addCommand(const NativeString& commandArg) {
					command.push_back(commandArg);
					return *this;
				}

				NativeString NativeProcessBuilder::getDirectory() const {
					return directory;
				}

				NativeProcessBuilder& NativeProcessBuilder::setDirectory(NativeString dir) {
					directory = dir;
					return *this;
				}

				jbool NativeProcessBuilder::isInheritEnvironment() const {
					return inheritEnvironment;
				}

				NativeProcessBuilder& NativeProcessBuilder::setInheritEnvironment(jbool inherit) {
					inheritEnvironment = inherit;
					return *this;
				}

				void NativeProcessBuilder::getEnvironment(std::map<NativeString, NativeString> & envMap) {
					for (std::map<NativeString, NativeString>::iterator it = env.begin(); it != env.end(); ++it) {
						envMap.insert(std::pair<NativeString, NativeString>(it->first, it->second));
					}
				}

				NativeProcessBuilder& NativeProcessBuilder::addEnvironment(const NativeString& key, const NativeString& value) {
					env.insert(std::pair<NativeString, NativeString>(key, value));
					return *this;
				}

				NativeProcessBuilder& NativeProcessBuilder::removeEnvironment(const NativeString& key) {
					env.erase(key);
					return *this;
				}

				NativeProcessBuilder& NativeProcessBuilder::inheritIO() {
					redirectOutput = NativeProcessBuilderRedirect::INHERIT;
					redirectError = NativeProcessBuilderRedirect::INHERIT;
					redirectInput = NativeProcessBuilderRedirect::INHERIT;
					return *this;
				}

				jbool NativeProcessBuilder::isRedirectErrorStreamToOutputStream() const {
					return redirectErrorStream;
				}

				NativeProcessBuilder& NativeProcessBuilder::setRedirectErrorStreamToOutputStream(jbool redirect) {
					redirectErrorStream = redirect;
					return *this;
				}

				NativeProcessBuilderRedirect NativeProcessBuilder::getRedirectError() const {
					return redirectError;
				}

				NativeProcessBuilder& NativeProcessBuilder::setRedirectError(const NativeString& file) {
					redirectError = NativeProcessBuilderRedirect::to(file);
					return *this;
				}

				NativeProcessBuilder& NativeProcessBuilder::setRedirectError(const NativeProcessBuilderRedirect& destination) {
					redirectError = destination;
					return *this;
				}

				NativeProcessBuilderRedirect NativeProcessBuilder::getRedirectOutput() const {
					return redirectOutput;
				}

				NativeProcessBuilder& NativeProcessBuilder::setRedirectOutput(const NativeString& file) {
					redirectOutput = NativeProcessBuilderRedirect::to(file);
					return *this;
				}

				NativeProcessBuilder& NativeProcessBuilder::setRedirectOutput(const NativeProcessBuilderRedirect& destination) {
					redirectOutput = destination;
					return *this;
				}

				NativeProcessBuilderRedirect NativeProcessBuilder::getRedirectInput() const {
					return redirectInput;
				}

				NativeProcessBuilder& NativeProcessBuilder::setRedirectInput(const NativeString& file) {
					redirectInput = NativeProcessBuilderRedirect::from(file);
					return *this;
				}

				NativeProcessBuilder& NativeProcessBuilder::setRedirectInput(const NativeProcessBuilderRedirect& source) {
					redirectInput = source;
					return *this;
				}

			}
		}
	}
}
