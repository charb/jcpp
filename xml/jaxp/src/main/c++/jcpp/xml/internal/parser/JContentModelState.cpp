#include "jcpp/xml/internal/parser/JContentModelState.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JInternalError.h"
#include "jcpp/lang/JStringBuilder.h"
#include "jcpp/lang/JInternalError.h"
#include "jcpp/io/JIOException.h"

using namespace jcpp::io;

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace parser{

                JContentModelState::JContentModelState(JContentModel* model):JObject(getClazz()){
                    this->model=model;
                    next=null;
                    sawOne=false;
                }

                JContentModelState::JContentModelState(JObject* content, JContentModelState* next):JObject(getClazz()){
                    this->model=dynamic_cast<JContentModel*>(content);
                    this->next=next;
                    sawOne=false;
                }

                jbool JContentModelState::terminate(){
                    switch (model->type) {
                        case '+':
                            if (!sawOne && !(dynamic_cast<JContentModel*>(model))->empty()){
                                return false;
                            }
                        
                        case '*':
                        case '?':
                            return (next == null) || next->terminate();

                        case '|':
                            return model->empty () && (next == null || next->terminate());

                        case ',':{
                            JContentModel* m=null;
                            for (m = model; (m != null) && m->empty() ; m = m->next){
                                continue;
                            }
                            if (m != null){
                                return false;
                            }
                            return (next == null) || next->terminate();
                        }

                        case 0:
                            return false;
                    
                        default:
                            throw new JInternalError ();
                    }
                }

                JContentModelState* JContentModelState::advance(JString* token){
                    switch(model->type) {
                        case '+':
                        case '*':
                            if (model->first(token)) {
                                sawOne = true;
                                if (model->content->isInstanceOf(JString::getClazz())){
                                    return this;
                                }
                                return (new JContentModelState(model->content, this))->advance(token);
                            }
                            if ((model->type == '*' || sawOne) && next != null){
                                return next->advance(token);
                            }
                            break;

                        case '?':
                            if (model->first(token)) {
                                if (model->content->isInstanceOf(JString::getClazz())){
                                    return next;
                                }
                                return (new JContentModelState(model->content, next))->advance(token);
                            }
                            if (next != null){
                                return next->advance(token);
                            }
                            break;

                        case '|':
                            for (JContentModel* m = model; m != null; m = m->next) {
                                if (m->content->isInstanceOf(JString::getClazz())) {
                                    if (token == m->content){
                                        return next;
                                    }
                                    continue;
                                }
                                if ((dynamic_cast<JContentModel*>(m->content))->first(token)){
                                    return (new JContentModelState(m->content, next))->advance(token);
                                }
                            }
                            if (model->empty () && next != null){
                                return next->advance(token);
                            }
                            break;

                        case ',':
                            if (model->first(token)) {
                                JContentModelState*   nextState=null;
                                if (model->type == 0){
                                    return next;
                                }
                                if (model->next == null){
                                    nextState = new JContentModelState(model->content, next);
                                
                                }else {
                                    nextState = new JContentModelState(model->content, this);
                                    model = model->next;
                                }
                                return nextState->advance(token);

                            } else if (model->empty () && next != null) {
                                return next->advance(token);
                            }
                            break;

                        case 0:
                            if (model->content == token){
                                return next;
                            }
                    }
                    throw new JIOException ();
                }

                JContentModelState::~JContentModelState(){
                }
            }
        }
    }
}
