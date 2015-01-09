#ifndef JCPP_LANG_JPROCESSBUILDER_H
#define JCPP_LANG_JPROCESSBUILDER_H

#include "jcpp/native/api/process/NativeProcessBuilder.h"
#include "jcpp/util/JList.h"
#include "jcpp/util/JMap.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/io/JFile.h"
#include "jcpp/lang/JProcess.h"
#include "jcpp/io/JNativeOutputStream.h"
#include "jcpp/io/JNativeInputStream.h"

using namespace jcpp::util;
using namespace jcpp::native::api::process;
using namespace jcpp::io;

namespace jcpp{
    namespace lang{
    	class JForkedProcess;

    	class JCPP_EXPORT JProcessBuilder : public JObject {
    	public:

    		class JCPP_EXPORT JRedirect : public JObject {
    		public:
    			enum JType {
					APPEND, INHERIT, PIPE, READ, WRITE
				};

			private:
    			JType type;
				JFile* file;

				JRedirect(JType type, JFile* file);

			public:
				static jcpp::lang::JClass* getClazz();

				static JRedirect* INHERIT_STREAM;
				static JRedirect* PIPE_STREAM;

				static JRedirect* appendTo(JFile* file);
				static JRedirect* from(JFile* file);
				static JRedirect* to(JFile* file);

				JType getType() const;
				JFile* getFile() const;

				virtual ~JRedirect();

				friend class JProcessBuilder;
			};

        	private:
        		JList* commandList;
        		JMap* env;
        		JFile* workdir;

        		jbool redirectErrorStreamToOutputStream;

        		JRedirect* errorRedirect;
        		JRedirect* inputRedirect;
        		JRedirect* outputRedirect;

        		static NativeProcessBuilderRedirect createNativeRedirect(JRedirect* redirect);

        	public:

				static jcpp::lang::JClass* getClazz();

				JProcessBuilder(JList* command);
				JProcessBuilder(JPrimitiveObjectArray* command);

				JList* command();
				JProcessBuilder* command(JList* command);
				JProcessBuilder* command(JPrimitiveObjectArray* command);

				JMap* environment();

				JFile* directory();
				JProcessBuilder* directory(JFile* processDirectory);

				JProcessBuilder* inheritIO();

				jbool redirectErrorStream();
				JProcessBuilder* redirectErrorStream(jbool redirect);

				JRedirect* redirectError();
				JProcessBuilder* redirectError(JFile* file);
				JProcessBuilder* redirectError(JRedirect* destination);

				JRedirect* redirectInput();
				JProcessBuilder* redirectInput(JFile* file);
				JProcessBuilder* redirectInput(JRedirect* source);

				JRedirect* redirectOutput();
				JProcessBuilder* redirectOutput(JFile* file);
				JProcessBuilder* redirectOutput(JRedirect* destination);

				JForkedProcess* start();

				virtual ~JProcessBuilder();

    	};

    	class JCPP_EXPORT JForkedProcess : public JObject {
    	private:
    		JProcess* process;
    		JNativeOutputStream* inputStreamWritePipeEnd;
    		JNativeInputStream* outputStreamReadPipeEnd;
    		JNativeInputStream* errorStreamReadPipeEnd;

    		JForkedProcess(JProcess* process, JNativeOutputStream* inputStreamWritePipeEnd, JNativeInputStream* outputStreamReadPipeEnd, JNativeInputStream* errorStreamReadPipeEnd);
    	public:
    		static jcpp::lang::JClass* getClazz();

    		JProcess* getProcess();

    		JNativeOutputStream* getInputStreamWritePipeEnd();
    		JNativeInputStream* getOutputStreamReadPipeEnd();
    		JNativeInputStream* getErrorStreamReadPipeEnd();

    		virtual ~JForkedProcess();

    		friend class JProcessBuilder;
    	};

    }
}

#endif
