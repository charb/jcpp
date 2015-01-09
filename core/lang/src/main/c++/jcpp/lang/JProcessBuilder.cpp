#include "jcpp/lang/JProcessBuilder.h"
#include "jcpp/native/api/NativeFactory.h"
#include "jcpp/util/JArrayList.h"
#include "jcpp/util/JHashMap.h"
#include "jcpp/lang/JThrowable.h"
#include "jcpp/lang/JNullPointerException.h"

using namespace jcpp::native::api;
using namespace jcpp::util;
using namespace jcpp::native::api::process;

namespace jcpp {
    namespace lang {

    	class JProcessBuilderClass : public jcpp::lang::JClass {
    		// TODO fill
    	public:
    		JProcessBuilderClass():jcpp::lang::JClass() {
    			this->canonicalName=new JString("java.lang.ProcessBuilder");
    			this->name=new JString("java.lang.ProcessBuilder");
    			this->simpleName=new JString("ProcessBuilder");
    		}

    		virtual jcpp::lang::JClass* getSuperclass() {
    			return JObject::getClazz();
    		}

    	};

    	class JRedirectClass : public jcpp::lang::JClass {
			// TODO fill
		public:
    		JRedirectClass():jcpp::lang::JClass() {
				this->canonicalName=new JString("java.lang.ProcessBuilder.Redirect");
				this->name=new JString("java.lang.ProcessBuilder$Redirect");
				this->simpleName=new JString("Redirect");
			}

			virtual jcpp::lang::JClass* getSuperclass() {
				return JObject::getClazz();
			}

		};

    	class JForkedProcessClass : public jcpp::lang::JClass {
			// TODO fill
		public:
    		JForkedProcessClass():jcpp::lang::JClass() {
				this->canonicalName=new JString("java.lang.ForkedProcess");
				this->name=new JString("java.lang.ForkedProcess");
				this->simpleName=new JString("ForkedProcess");
			}

			virtual jcpp::lang::JClass* getSuperclass() {
				return JObject::getClazz();
			}

		};

    	static jcpp::lang::JClass * jProcessBuilderClass;

    	jcpp::lang::JClass* JProcessBuilder::getClazz() {
			if (jProcessBuilderClass==null){
				jProcessBuilderClass=new JProcessBuilderClass();
			}
			return jProcessBuilderClass;
		}

    	static jcpp::lang::JClass * jRedirectClass;

    	jcpp::lang::JClass* JProcessBuilder::JRedirect::getClazz() {
			if (jRedirectClass==null){
				jRedirectClass=new JRedirectClass();
			}
			return jRedirectClass;
		}

    	static jcpp::lang::JClass * jForkedProcessClass;

		jcpp::lang::JClass* JForkedProcess::getClazz() {
			if (jForkedProcessClass==null){
				jForkedProcessClass=new JForkedProcessClass();
			}
			return jForkedProcessClass;
		}

    	JProcessBuilder::JRedirect* JProcessBuilder::JRedirect::INHERIT_STREAM = new JProcessBuilder::JRedirect(INHERIT, null);

    	JProcessBuilder::JRedirect* JProcessBuilder::JRedirect::PIPE_STREAM = new JProcessBuilder::JRedirect(PIPE, null);

    	JProcessBuilder::JRedirect::JRedirect(JProcessBuilder::JRedirect::JType _type, JFile* _file) : JObject(getClazz()) {
			type = _type;
			file = _file;
		}

		JProcessBuilder::JRedirect* JProcessBuilder::JRedirect::appendTo(JFile* file) {
			return new JRedirect(APPEND, file);
		}

		JProcessBuilder::JRedirect* JProcessBuilder::JRedirect::from(JFile* file) {
			return new JRedirect(READ, file);
		}

		JProcessBuilder::JRedirect* JProcessBuilder::JRedirect::to(JFile* file) {
			return new JRedirect(WRITE, file);
		}

		JProcessBuilder::JRedirect::JType JProcessBuilder::JRedirect::getType() const {
			return type;
		}

		JFile* JProcessBuilder::JRedirect::getFile() const {
			return file;
		}

		JProcessBuilder::JRedirect::~JRedirect() {
		}

		NativeProcessBuilderRedirect JProcessBuilder::createNativeRedirect(JProcessBuilder::JRedirect* redirect) {
			NativeString path("null");
			switch (redirect->type) {
				case INHERIT:
					return NativeProcessBuilderRedirect::INHERIT;
				case PIPE:
					return NativeProcessBuilderRedirect::REDIRECT_PIPE;
				case APPEND:
					path = redirect->file->getPath()->getNativeString();
					return NativeProcessBuilderRedirect::appendTo(path);
				case READ:
					path = redirect->file->getPath()->getNativeString();
					return NativeProcessBuilderRedirect::from(path);
				case WRITE:
					path = redirect->file->getPath()->getNativeString();
					return NativeProcessBuilderRedirect::to(path);
				default:
					return NativeProcessBuilderRedirect::REDIRECT_PIPE;
			}
		}

		JProcessBuilder::JProcessBuilder(JList* _command) : JObject(getClazz()) {
			command(_command);
			env = null;
			workdir = null;
			redirectErrorStreamToOutputStream = false;
			errorRedirect = null;
			inputRedirect = null;
			outputRedirect = null;
		}

		JProcessBuilder::JProcessBuilder(JPrimitiveObjectArray* _command) : JObject(getClazz()){
			command(_command);
			env = null;
			workdir = null;
			redirectErrorStreamToOutputStream = false;
			errorRedirect = null;
			inputRedirect = null;
			outputRedirect = null;
		}

		JList* JProcessBuilder::command() {
			return commandList;
		}

		JProcessBuilder* JProcessBuilder::command(JList* command) {
			if(command == null) {
				throw new JNullPointerException();
			}
			commandList = command;
			return this;
		}

		JProcessBuilder* JProcessBuilder::command(JPrimitiveObjectArray* command) {
			if(command == null) {
				throw new JNullPointerException();
			}
			jint size = command->size();
			commandList = new JArrayList(size);
			for(jint i = 0; i < size; i++) {
				commandList->add(command->get(i));
			}
			return this;
		}

		JMap* JProcessBuilder::environment() {
			if(env == null) {
				std::map<NativeString, NativeString> nativeEnv;
				NativeFactory::getNativeSystem()->getEnv(nativeEnv);
				env = new JHashMap();

				for (std::map<NativeString, NativeString>::iterator it = nativeEnv.begin(); it != nativeEnv.end(); ++it) {
					env->put(new JString(it->first), new JString(it->second));
				}
			}
			return env;
		}

		JFile* JProcessBuilder::directory() {
			return workdir;
		}

		JProcessBuilder* JProcessBuilder::directory(JFile* processDirectory) {
			workdir = processDirectory;
			return this;
		}

		JProcessBuilder* JProcessBuilder::inheritIO() {
			inputRedirect = JRedirect::INHERIT_STREAM;
			outputRedirect = JRedirect::INHERIT_STREAM;;
			errorRedirect = JRedirect::INHERIT_STREAM;;
			return this;
		}

		jbool JProcessBuilder::redirectErrorStream() {
			return redirectErrorStreamToOutputStream;
		}

		JProcessBuilder* JProcessBuilder::redirectErrorStream(jbool redirect) {
			redirectErrorStreamToOutputStream = redirect;
			return this;
		}

		JProcessBuilder::JRedirect* JProcessBuilder::redirectError() {
			return errorRedirect == null ? JRedirect::PIPE_STREAM : errorRedirect;
		}

		JProcessBuilder* JProcessBuilder::redirectError(JFile* file) {
			errorRedirect = JRedirect::to(file);
			return this;
		}

		JProcessBuilder* JProcessBuilder::redirectError(JRedirect* destination) {
			errorRedirect = destination;
			return this;
		}

		JProcessBuilder::JRedirect* JProcessBuilder::redirectInput() {
			return inputRedirect == null ? JRedirect::PIPE_STREAM : inputRedirect;
		}

		JProcessBuilder* JProcessBuilder::redirectInput(JFile* file) {
			inputRedirect = JRedirect::from(file);
			return this;
		}

		JProcessBuilder* JProcessBuilder::redirectInput(JRedirect* source) {
			inputRedirect = source;
			return this;
		}

		JProcessBuilder::JRedirect* JProcessBuilder::redirectOutput() {
			return outputRedirect == null ? JRedirect::PIPE_STREAM : outputRedirect;
		}

		JProcessBuilder* JProcessBuilder::redirectOutput(JFile* file) {
			outputRedirect = JRedirect::to(file);
			return this;
		}

		JProcessBuilder* JProcessBuilder::redirectOutput(JRedirect* destination) {
			outputRedirect = destination;
			return this;
		}

		JForkedProcess* JProcessBuilder::start() {
			NativeProcessBuilder builder;

			std::vector<NativeString> nativeCommand;
			for(jint i = 0; i < commandList->size(); i++) {
				JString* command = dynamic_cast<JString*>(commandList->get(i));
				builder.addCommand(command->getNativeString());
			}

			builder.setInheritEnvironment(false);

			JSet* entrySet = env->entrySet();
			JIterator* iterator = entrySet->iterator();
			while(iterator->hasNext()) {
				JMap::JEntry* entry = dynamic_cast<JMap::JEntry*>(iterator->next());
				JString* envKey = dynamic_cast<JString*>(entry->getKey());
				JString* envValue = dynamic_cast<JString*>(entry->getValue());
				builder.addEnvironment(envKey->getNativeString(), envValue->getNativeString());
			}

			if(workdir != null) {
				builder.setDirectory(workdir->getPath()->getNativeString());
			} else {
				builder.setDirectory(NativeString("."));
			}

			builder.setRedirectErrorStreamToOutputStream(redirectErrorStreamToOutputStream);

			if(!redirectErrorStreamToOutputStream && (errorRedirect != null)) {
				builder.setRedirectError(createNativeRedirect(errorRedirect));
			}

			if(outputRedirect != null) {
				builder.setRedirectOutput(createNativeRedirect(outputRedirect));
			}

			if(inputRedirect != null) {
				builder.setRedirectInput(createNativeRedirect(inputRedirect));
			}

			JForkedProcess* jForkedProcess = null;

			TRY_CATCH_NATIVE_EXCEPTION({
			NativeForkedProcess forkedProcess = NativeFactory::getNativeProcessFactory()->createNativeProcess(builder);
			jForkedProcess = new JForkedProcess(new JProcess(forkedProcess.getProcess()),
				new JNativeOutputStream(forkedProcess.getInputStreamWritePipeEnd(), true),
				new JNativeInputStream(forkedProcess.getOutputStreamReadPipeEnd(), true),
				new JNativeInputStream(forkedProcess.getErrorStreamReadPipeEnd(), true));
			})

			return jForkedProcess;
		}

		JProcessBuilder::~JProcessBuilder() {
		}

		JForkedProcess::JForkedProcess(JProcess* process, JNativeOutputStream* inputStreamWritePipeEnd, JNativeInputStream* outputStreamReadPipeEnd, JNativeInputStream* errorStreamReadPipeEnd) : JObject(getClazz()) {
			this->process = process;
			this->inputStreamWritePipeEnd = inputStreamWritePipeEnd;
			this->outputStreamReadPipeEnd = outputStreamReadPipeEnd;
			this->errorStreamReadPipeEnd = errorStreamReadPipeEnd;
		}

		JProcess* JForkedProcess::getProcess() {
			return process;
		}

		JNativeOutputStream* JForkedProcess::getInputStreamWritePipeEnd() {
			return inputStreamWritePipeEnd;
		}

		JNativeInputStream* JForkedProcess::getOutputStreamReadPipeEnd() {
			return outputStreamReadPipeEnd;
		}

		JNativeInputStream* JForkedProcess::getErrorStreamReadPipeEnd() {
			return errorStreamReadPipeEnd;
		}

		JForkedProcess::~JForkedProcess() {
		}
    }
}

