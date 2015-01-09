#include "jcpp/lang/JProcess.h"
#include "jcpp/util/JArrayList.h"
#include "jcpp/util/JHashMap.h"
#include "jcpp/native/api/NativeFactory.h"
#include "jcpp/lang/JThrowable.h"

using namespace jcpp::util;
using namespace jcpp::native::api;
using namespace jcpp::native::api::process;

namespace jcpp {
    namespace lang {

    	class JProcessClass : public jcpp::lang::JClass {
    		// TODO fill
    	public:
    		JProcessClass():jcpp::lang::JClass() {
    			this->canonicalName=new JString("java.lang.Process");
    			this->name=new JString("java.lang.Process");
    			this->simpleName=new JString("Process");
    		}

    		virtual jcpp::lang::JClass* getSuperclass() {
    			return JObject::getClazz();
    		}

    	};


    	static jcpp::lang::JClass* jClass;

    	jcpp::lang::JClass* JProcess::getClazz() {
    		if(jClass == null) {
    			jClass = new JProcessClass();
    		}
    		return jClass;
    	}

    	JProcess::JProcess(NativeProcess* nativeProcess) : JObject(getClazz()) {
    		this->nativeProcess = nativeProcess;
    		pidStr = null;
    		cmdStr = null;
    		ownerStr = null;
    		workDirStr = null;
    		env = null;
    		processTree = null;
    	}

    	JProcess* JProcess::getLocalProcess() {
    		JProcess* process = null;
    		TRY_CATCH_NATIVE_EXCEPTION( process = new JProcess(NativeFactory::getNativeProcessFactory()->getLocalProcess()); )
    		return process;
    	}

		JList* JProcess::getAllProcesses() {
			std::vector<NativeProcess*> nativeProcesses;
			TRY_CATCH_NATIVE_EXCEPTION( NativeFactory::getNativeProcessFactory()->getAllProcesses(nativeProcesses); )
			JList* processes = new JArrayList();
			for (std::vector<NativeProcess*>::iterator it = nativeProcesses.begin(); it != nativeProcesses.end(); it++) {
				processes->add(new JProcess(*it));
			}
			return processes;
		}

		JString* JProcess::getPid() {
			if(pidStr == null) {
				TRY_CATCH_NATIVE_EXCEPTION( pidStr = new JString(nativeProcess->getPid()); )
			}
			return pidStr;
		}

		JList* JProcess::getProcessTree() {
			if(processTree == null) {
				std::vector<NativeString> nativeProcessTree;
				TRY_CATCH_NATIVE_EXCEPTION( nativeProcess->getProcessTree(nativeProcessTree); )
				processTree = new JArrayList();
				for (std::vector<NativeString>::iterator it = nativeProcessTree.begin(); it != nativeProcessTree.end(); it++) {
					processTree->add(new JString(*it));
				}
			}
			return processTree;
		}

		JString* JProcess::getCmd() {
			if(cmdStr == null) {
				TRY_CATCH_NATIVE_EXCEPTION( cmdStr = new JString(nativeProcess->getCmd()); )
			}
			return cmdStr;
		}

		JMap* JProcess::getEnvironment() {
			if(env == null) {
				std::map<NativeString, NativeString> nativeEnv;
				TRY_CATCH_NATIVE_EXCEPTION( nativeProcess->getEnvironment(nativeEnv); )
				env = new JHashMap();
				for (std::map<NativeString, NativeString>::iterator it = nativeEnv.begin(); it != nativeEnv.end(); ++it) {
					env->put(new JString(it->first), new JString(it->second));
				}
			}
			return env;
		}

		jint JProcess::getExitValue() {
			jint value = 0;
			TRY_CATCH_NATIVE_EXCEPTION( value = nativeProcess->getExitValue(); )
			return value;
		}

		JString* JProcess::getOwner() {
			if(ownerStr ==  null) {
				TRY_CATCH_NATIVE_EXCEPTION( ownerStr = new JString(nativeProcess->getOwner()); )
			}
			return ownerStr;
		}

		jlong JProcess::getStartDate() {
			jlong value = 0;
			TRY_CATCH_NATIVE_EXCEPTION( value = nativeProcess->getStartDate(); )
			return value;
		}

		JString* JProcess::getWorkingDirectory() {
			if(workDirStr == null) {
				TRY_CATCH_NATIVE_EXCEPTION( workDirStr = new JString(nativeProcess->getWorkingDirectory()); )
			}
			return workDirStr;
		}

		jint JProcess::waitFor() {
			jint value = 0;
			TRY_CATCH_NATIVE_EXCEPTION( value = nativeProcess->waitFor(); )
			return value;
		}

		void JProcess::kill() {
			TRY_CATCH_NATIVE_EXCEPTION( nativeProcess->kill(); )
		}

		jdouble JProcess::getCpuUsage() {
			jlong value = 0;
			TRY_CATCH_NATIVE_EXCEPTION( value = nativeProcess->getCpuUsage(); )
			return value;
		}

		jlong JProcess::getRealMemoryUsage() {
			jlong value = 0;
			TRY_CATCH_NATIVE_EXCEPTION( value = nativeProcess->getRealMemoryUsage(); )
			return value;
		}

		jlong JProcess::getVirtualMemoryUsage() {
			jlong value = 0;
			TRY_CATCH_NATIVE_EXCEPTION( value = nativeProcess->getVirtualMemoryUsage(); )
			return value;
		}

		void JProcess::finalize() {
			delete nativeProcess;
			nativeProcess = null;
		}

		JProcess::~JProcess() {
		}

    }
}
