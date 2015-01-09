#include "jcpp/xml/internal/parser/JContentModel.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JInternalError.h"
#include "jcpp/lang/JStringBuilder.h"
#include "jcpp/lang/JBoolean.h"

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace parser{
    
                JContentModel::JContentModel(JString* element):JObject(getClazz()){
                    type=0;
                    this->content=element;
                    next=null;
                    cache=new JHashtable();
                }

                JContentModel::JContentModel(jchar type, JContentModel* content):JObject(getClazz()){
                    type=type;
                    this->content=content;
                    next=null;
                    cache=new JHashtable();
                }

                jbool JContentModel::empty(){
                    switch (type) {
                        case '*':
                        case '?':
                            return true;

                        case '+':
                        case 0:
                            return false;

                      case '|':
                            if (content->isInstanceOf(JContentModel::getClazz()) && (dynamic_cast<JContentModel*>(content))->empty()) {
                                return true;
                            }
                            for (JContentModel* m = next; m != null; m = m->next) {
                                if (m->empty ()){
                                    return true;
                                }
                            }
                            return false;

                      case ',':
                            if (content->isInstanceOf(JContentModel::getClazz())) {
                                if (!(dynamic_cast<JContentModel*>(content))->empty()) {
                                    return false;
                                }
                            } else {
                                return false;
                            }
                            for (JContentModel* m = next; m != null; m = m->next) {
                                if (!m->empty()){
                                    return false;
                                }
                            }
                            return true;

                      default:
                            throw new JInternalError();
                    }
                }

                jbool JContentModel::first(JString* token){
                    JBoolean* b = dynamic_cast<JBoolean*>(cache->get(token));
                    jbool retval=false;

                    if (b != null){
                        return b->booleanValue();
                    }

                    switch (type) {
                        case '*':
                        case '?':
                        case '+':
                        case 0:
                            if (content->isInstanceOf(JString::getClazz())){
                                retval = (content == token);
                            }else{
                                retval = (dynamic_cast<JContentModel*>(content))->first(token);
                            }
                            break;

                        case ',':
                            if (content->isInstanceOf(JString::getClazz())){
                                retval = (content == token);
                            
                            }else if ((dynamic_cast<JContentModel*>(content))->first(token)){
                                retval = true;
                            
                            }else if (!(dynamic_cast<JContentModel*>(content))->empty()){
                                retval = false;
                            
                            }else if (next != null){
                                retval = (dynamic_cast<JContentModel*>(next))->first(token);
                            
                            }else{
                                retval = false;
                            }
                            break;

                        case '|':
                            if (content->isInstanceOf(JString::getClazz()) && content == token){
                                retval = true;
                        
                            }else if ((dynamic_cast<JContentModel*>(content))->first(token)){
                                retval = true;
                        
                            }else if (next != null){
                                retval = (dynamic_cast<JContentModel*>(next))->first(token);
                            
                            }else{
                                retval = false;
                            }
                            break;

                        default:
                            throw new JInternalError();
                    }

                    if (retval){
                        cache->put(token, JBoolean::TRUE);
                    
                    }else{
                        cache->put(token, JBoolean::FALSE);
                    }
                    return retval;
                }

                JString* JContentModel::toString(){
                    return toString(true);
                }

                JString* JContentModel::contentString(){
                    if (content->isInstanceOf(JContentModel::getClazz())){
                        return (dynamic_cast<JContentModel*>(content))->toString(false);
                    }else{
                        return dynamic_cast<JString*>(content);
                    }
                }

                JString* JContentModel::toString(jbool isOuter){
                    JString*  temp = contentString();
                    switch(type){
                        case '*':
                        case '?':
                        case '+':
                            if (isOuter && temp->charAt(0) != '('){
                                JStringBuilder* builder=new JStringBuilder();
                                builder->append('(')
                                       ->append(temp)
                                       ->append(type)
                                       ->append(')');
                                return builder->toString();
                            }else{
                                JStringBuilder* builder=new JStringBuilder();
                                builder->append(temp)
                                       ->append(type);
                                return builder->toString();
                            }

                        case 0:
                            if (isOuter){
                                JStringBuilder* builder=new JStringBuilder();
                                builder->append('(')
                                       ->append(temp)
                                       ->append(')');
                                return builder->toString();
                            }else{
                                return temp;
                            }

                        case ',':
                        case '|':{
                            if (next == null){
                                return temp;
                            }
                            JStringBuilder* builder=new JStringBuilder();
                            builder->append('(')
                                   ->append(temp);
                            for (JContentModel* m = next; m != null; m = m->next){
                                builder->append(type)->append(m->contentString());
                            }
                            builder->append(')');
                            return builder->toString();
                        }

                        default:
                            throw new JInternalError(new JString("foo"));
                    }
                }

                JContentModel::~JContentModel(){
                }
            }
        }
    }
}
