#include "org/apache/commons/cli/JOption.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JString.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/util/JArrayList.h"
#include "jcpp/lang/JRuntimeException.h"
#include "jcpp/lang/JStringBuilder.h"
#include "jcpp/lang/JIllegalArgumentException.h"

using namespace jcpp::util;

namespace org{
    namespace apache{
        namespace commons{
            namespace cli{

                jint JOption::UNINITIALIZED = -1;

                jint JOption::UNLIMITED_VALUES = -2;

                JOption::JOption(JOption* o):JObject(getClazz()){
                    this->strOpt=o->strOpt;
                    this->strDescription=o->strDescription;
                    this->strLongOpt=o->strLongOpt;
                    iNumberOfArgs=o->iNumberOfArgs;
                    strArgName=o->strArgName;
                    bRequired=o->bRequired;
                    bOptionalArg=o->bOptionalArg;
                    cType=o->cType;
                    values=new JArrayList(o->values);
                    cValuesep=o->cValuesep;
                }

                JOption::JOption(JString* opt,JString* description):JObject(getClazz()){
                    this->strOpt=opt;
                    this->strDescription=description;
                    this->strLongOpt=null;
                    iNumberOfArgs=UNINITIALIZED;
                    strArgName=null;
                    bRequired=false;
                    bOptionalArg=false;
                    cType=JString::getClazz();
                    values=new JArrayList();
                    cValuesep=0;
                }

                JOption::JOption(JString* opt,jbool hasArg,JString* description):JObject(getClazz()){
                    this->strOpt=opt;
                    this->strLongOpt=null;
                    if (hasArg){
                        iNumberOfArgs=1;
                    }else{
                        iNumberOfArgs=UNINITIALIZED;
                    }
                    this->strDescription=description;
                    strArgName=null;
                    bRequired=false;
                    bOptionalArg=false;
                    cType=JString::getClazz();
                    values=new JArrayList();
                    cValuesep=0;
                }

                JOption::JOption(JString* opt,JString* longOpt,jbool hasArg,JString* description):JObject(getClazz()){
                    this->strOpt=opt;
                    this->strLongOpt=longOpt;
                    if (hasArg){
                        iNumberOfArgs=1;
                    }else{
                        iNumberOfArgs=UNINITIALIZED;
                    }
                    this->strDescription=description;
                    strArgName=null;
                    bRequired=false;
                    bOptionalArg=false;
                    cType=JString::getClazz();
                    values=new JArrayList();
                    cValuesep=0;
                }

                JOption::JOption(JBuilder* builder):JObject(getClazz()){
                    this->strOpt=builder->strOpt;
                    this->strLongOpt=builder->strLongOpt;
                    iNumberOfArgs=builder->iNumberOfArgs;
                    this->strDescription=builder->strDescription;
                    strArgName=builder->strArgName;
                    bRequired=builder->bRequired;
                    bOptionalArg=builder->bOptionalArg;
                    cType=builder->cType;
                    values=new JArrayList();
                    cValuesep=builder->cValuesep;
                }


                jint JOption::getId(){
                    return getKey()->charAt(0);
                }

                JString* JOption::getKey(){
                    return (strOpt==null ? strLongOpt : strOpt);
                }

                JString* JOption::getOpt(){
                    return strOpt;
                }

                JClass* JOption::getType(){
                    return cType;
                }

                void JOption::setType(JClass* t){
                    cType=t;
                }

                JString* JOption::getLongOpt(){
                    return strLongOpt;
                }

                void JOption::setLongOpt(JString* longOpt){
                    this->strLongOpt=strLongOpt;
                }

                void JOption::setOptionalArg(jbool o){
                    bOptionalArg=o;
                }

                jbool JOption::hasOptionalArg(){
                    return bOptionalArg;
                }

                jbool JOption::hasLongOpt(){
                    return strLongOpt!=null;
                }

                jbool JOption::hasArg(){
                    return iNumberOfArgs>0 || iNumberOfArgs==UNLIMITED_VALUES;
                }

                JString* JOption::getDescription(){
                    return strDescription;
                }

                void JOption::setDescription(JString* d){
                    strDescription=d;
                }

                jbool JOption::isRequired(){
                    return bRequired;
                }

                void JOption::setRequired(jbool r){
                    bRequired=r;
                }

                void JOption::setArgName(JString* a){
                    strArgName=a;
                }

                JString* JOption::getArgName(){
                    return strArgName;
                }

                jbool JOption::hasArgName(){
                    return strArgName!=null && strArgName->length()>0;
                }

                jbool JOption::hasArgs(){
                    return iNumberOfArgs>1 || iNumberOfArgs==UNLIMITED_VALUES;
                }

                void JOption::setArgs(jint n){
                    iNumberOfArgs=n;
                }

                void JOption::setValueSeparator(jchar s){
                    cValuesep=s;
                }

                jchar JOption::getValueSeparator(){
                    return cValuesep;
                }

                jbool JOption::hasValueSeparator(){
                    return cValuesep>0;
                }

                jint JOption::getArgs(){
                    return iNumberOfArgs;
                }

                void JOption::addValueForProcessing(JString* value){
                    if (iNumberOfArgs==UNINITIALIZED){
                        throw new JRuntimeException(new JString("NO args allowed"));
                    }
                    processValue(value);
                }

                void JOption::processValue(JString* value){
                    if (hasValueSeparator()){
                        jchar sep = getValueSeparator();
                        jint index = value->indexOf(sep);
                        while (index != -1){
                            if (values->size() == (iNumberOfArgs - 1)){
                                break;
                            }
                            add(value->substring(0, index));
                            value = value->substring(index + 1);
                            index = value->indexOf(sep);
                        }
                    }
                    add(value);
                }

                void JOption::add(JString* value){
                    if (!acceptsArg()){
                        throw new JRuntimeException(new JString("Cannot add value, list full."));
                    }
                    values->add(value);
                }

                JString* JOption::getValue(){
                    return hasNoValues() ? null : dynamic_cast<JString*>(values->get(0));
                }

                JString* JOption::getValue(jint index){
                    return hasNoValues() ? null : dynamic_cast<JString*>(values->get(index));
                }

                JString* JOption::getValue(JString* d){
                    JString* value = getValue();
                    return (value != null) ? value : d;
                }

                JPrimitiveObjectArray* JOption::getValues(){
                    return hasNoValues() ? null : dynamic_cast<JPrimitiveObjectArray*>(values->toArray(new JPrimitiveObjectArray(JString::getClazz(),values->size())));
                }

                JList* JOption::getValuesList(){
                    return values;
                }

                JString* JOption::toString(){
                    JStringBuilder* buf = new JStringBuilder();
                    buf->append(new JString("[ option: "));
                    buf->append(strOpt);
                    if (strLongOpt != null){
                        buf->append(new JString(" "))->append(strLongOpt);
                    }
                    buf->append(new JString(" "));

                    if (hasArgs()){
                        buf->append(new JString("[ARG...]"));
                    }else if (hasArg()){
                        buf->append(new JString(" [ARG]"));
                    }

                    buf->append(new JString(" :: "))->append(strDescription);
                    if (cType != null){
                        buf->append(new JString(" :: "))->append(strDescription);
                    }

                    buf->append(new JString("]"));
                    return buf->toString();
                }

                jbool JOption::hasNoValues(){
                    return values->isEmpty();
                }

                jbool JOption::equals(JObject* o){
                    if (this == o){
                        return true;
                    }
                    if (o == null || getClass() != o->getClass()){
                        return false;
                    }
                    JOption* option = dynamic_cast<JOption*>(o);
                    if (strOpt != null ? !strOpt->equals(option->strOpt) : option->strOpt != null){
                        return false;
                    }
                    if (strLongOpt != null ? !strLongOpt->equals(option->strLongOpt) : option->strLongOpt != null){
                        return false;
                    }
                    return true;
                }

                jint JOption::hashCode(){
                    jint result = strOpt != null ? strOpt->hashCode() : 0;
                    result = 31 * result + (strLongOpt != null ? strLongOpt->hashCode() : 0);
                    return result;
                }

                JObject* JOption::clone(){
                    return new JOption(this);
                }

                void JOption::clearValues(){
                    values->clear();
                }

                jbool JOption::acceptsArg(){
                    return (hasArg() || hasArgs() || hasOptionalArg()) && (iNumberOfArgs <= 0 || values->size() < iNumberOfArgs);
                }

                jbool JOption::requiresArg(){
                    if (bOptionalArg){
                        return false;
                    }
                    if (iNumberOfArgs == UNLIMITED_VALUES){
                        return values->isEmpty();
                    }
                    return acceptsArg();
                }

                JOption::JBuilder* JOption::builder(){
                    return JOption::builder(null);
                }

                JOption::JBuilder* JOption::builder(JString* opt){
                    return new JBuilder(opt);
                }

                JOption::JBuilder::JBuilder(JString* opt):JObject(JBuilder::getClazz()){
                    this->strOpt=opt;
                    strDescription=null;
                    strLongOpt=null;
                    strArgName=null;
                    bRequired=false;
                    bOptionalArg=false;
                    iNumberOfArgs=UNINITIALIZED;
                    cType=JString::getClazz();
                    cValuesep=0;
                }


                JOption::JBuilder* JOption::JBuilder::argName(JString* a){
                    this->strArgName=a;
                    return this;
                }

                JOption::JBuilder* JOption::JBuilder::desc(JString* s){
                    this->strDescription=s;
                    return this;
                }

                JOption::JBuilder* JOption::JBuilder::longOpt(JString* l){
                    strLongOpt=l;
                    return this;
                }

                JOption::JBuilder* JOption::JBuilder::numberOfArgs(jint n){
                    iNumberOfArgs=n;
                    return this;
                }

                JOption::JBuilder* JOption::JBuilder::optionalArg(jbool o){
                    bOptionalArg=o;
                    return this;
                }

                JOption::JBuilder* JOption::JBuilder::required(){
                    bRequired=true;
                    return this;
                }

                JOption::JBuilder* JOption::JBuilder::required(jbool r){
                    bRequired=r;
                    return this;
                }

                JOption::JBuilder* JOption::JBuilder::type(JClass* t){
                    cType=t;
                    return this;
                }

                JOption::JBuilder* JOption::JBuilder::valueSeparator(){
                    cValuesep='=';
                    return this;
                }

                JOption::JBuilder* JOption::JBuilder::valueSeparator(jchar s){
                    cValuesep=s;
                    return this;
                }

                JOption::JBuilder* JOption::JBuilder::hasArg(){
                    hasArg(true);
                    return this;
                }

                JOption::JBuilder* JOption::JBuilder::hasArg(jbool b){
                    iNumberOfArgs = b ? 1 : JOption::UNINITIALIZED;
                    return this;
                }

                JOption::JBuilder* JOption::JBuilder::hasArgs(){
                    iNumberOfArgs = JOption::UNLIMITED_VALUES;
                    return this;
                }

                JOption* JOption::JBuilder::build(){
                    if (strOpt == null && strLongOpt == null){
                        throw new JIllegalArgumentException(new JString("Either opt or longOpt must be specified"));
                    }
                    return new JOption(this);
                }

                JOption::JBuilder::~JBuilder(){                    
                }

                JOption::~JOption(){
                }
            }
        }
    }
}

