#include "jcpp/util/concurrent/JAbstractExecutorService.h"
#include "jcpp/lang/JClass.h"

namespace jcpp{
    namespace util{
        namespace concurrent{

            JAbstractExecutorService::JAbstractExecutorService(JClass* _class):JObject(_class){
            }

            JRunnableFuture* JAbstractExecutorService::newTaskFor(JRunnable* runnable, JObject* result){
                return new JFutureTask(runnable, result);
            }

            JRunnableFuture* JAbstractExecutorService::newTaskFor(JCallable* callable){
                return new JFutureTask(callable);
            }

            JFuture* JAbstractExecutorService::submit(JRunnable* task) {
                JRunnableFuture* ftask = newTaskFor(task, null);
                execute(ftask);
                return ftask;
            }

            JFuture* JAbstractExecutorService::submit(JRunnable* task, JObject* result) {
                JRunnableFuture* ftask = newTaskFor(task, result);
                execute(ftask);
                return ftask;
            }

            JFuture* JAbstractExecutorService::submit(JCallable* task) {
                JRunnableFuture* ftask = newTaskFor(task);
                execute(ftask);
                return ftask;
            }

            JAbstractExecutorService::~JAbstractExecutorService(){
            }
        }
    }
}
