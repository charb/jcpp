#ifndef JCPP_LANG_JPROCESS_H
#define JCPP_LANG_JPROCESS_H

#include "jcpp/native/api/process/NativeProcess.h"
#include "jcpp/util/JList.h"
#include "jcpp/util/JMap.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/io/JFile.h"

using namespace jcpp::util;
using namespace jcpp::native::api::process;
using namespace jcpp::io;

namespace jcpp{
    namespace lang{

    	class JProcessBuilder;

    	class JCPP_EXPORT JProcess : public JObject {

    	private:
    		JString* pidStr;
    		JString* cmdStr;
    		JString* ownerStr;
    		JString* workDirStr;
    		JMap* env;
    		JList* processTree;

    		NativeProcess* nativeProcess;

    		JProcess(NativeProcess* nativeProcess);

    	public:
    		static jcpp::lang::JClass* getClazz();

    		static JProcess* getLocalProcess();

    		static JList* getAllProcesses(); // List of JProcess

    		JString* getPid();

    		JList* getProcessTree(); // List of JString of Pids

    		JString* getCmd();

    		JMap* getEnvironment();

    		jint getExitValue();

    		JString* getOwner();

    		jlong getStartDate();

    		JString* getWorkingDirectory();

    		jint waitFor();

    		void kill();

    		jdouble getCpuUsage();

    		jlong getRealMemoryUsage();

    		jlong getVirtualMemoryUsage();

    		virtual void finalize();

    		virtual ~JProcess();

    		friend class JProcessBuilder;
    	};

    }
}

#endif
