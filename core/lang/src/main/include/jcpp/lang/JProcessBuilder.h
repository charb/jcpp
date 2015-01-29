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
#include "jcpp/lang/JEnum.h"


using namespace jcpp::util;
using namespace jcpp::native::api::process;
using namespace jcpp::io;

namespace jcpp{
    namespace lang{
    	class JForkedProcess;

    	// @Class(canonicalName="java.lang.ProcessBuilder", simpleName="ProcessBuilder");
    	class JCPP_EXPORT JProcessBuilder : public JObject {
    	public:

    		// @Class(canonicalName="java.lang.ProcessBuilder$Redirect", simpleName="ProcessBuilder$Redirect");
    		class JCPP_EXPORT JRedirect : public JObject {
    		public:

    			// @Class(canonicalName="java.lang.ProcessBuilder$Redirect$Type", simpleName="ProcessBuilder$Redirect$Type");
    			class JCPP_EXPORT JType : public JEnum {
    			    protected:

    					JType(JString* name, JPrimitiveInt* ordinal);

    			    public:

    			        static JClass* getClazz();

    			        static JType* APPEND;

    			        static JType* INHERIT;

    			        static JType* PIPE;

    			        static JType* READ;

    			        static JType* WRITE;

    			        virtual ~JType();
    			    };

			private:
    			JType* type;
				JFile* file;

				JRedirect(JType* type, JFile* file);

			public:
				static jcpp::lang::JClass* getClazz();

				static JRedirect* INHERIT_STREAM;
				static JRedirect* PIPE_STREAM;

				static JRedirect* appendTo(JFile* file);
				static JRedirect* from(JFile* file);
				static JRedirect* to(JFile* file);

				JType* getType();
				JFile* getFile();

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

        		// @IgnoreReflection()
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

    	// @Class(canonicalName="java.lang.ForkedProcess", simpleName="ForkedProcess");
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
