#ifndef JORG_APACHE_COMMONS_CLI_OPTION_H
#define JORG_APACHE_COMMONS_CLI_OPTION_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JException.h"
#include "jcpp/util/JList.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "jcpp/lang/JCloneable.h"
#include "jcpp/io/JSerializable.h"

using namespace jcpp::lang;
using namespace jcpp::util;
using namespace jcpp::io;

namespace org{
    namespace apache{
        namespace commons{
            namespace cli{
            	// @Class(canonicalName="org.apache.commons.cli.Option", simpleName="Option");
                class JCPP_EXPORT JOption : public JObject, public JCloneable, public JSerializable{
                	private:
                		static const jlong serialVersionUID = 1LL;

                	protected:
                        JString* strOpt;
                        JString* strLongOpt;
                        JString* strArgName;
                        JString* strDescription;
                        jbool bRequired;
                        jbool bOptionalArg;
                        jint iNumberOfArgs;
                        JClass* cType;
                        JList* values;
                        jchar cValuesep;
                        virtual void processValue(JString* value);
                        virtual void add(JString* value);
                        virtual jbool hasNoValues();
                        virtual void clearValues();
                        virtual jbool acceptsArg();
                        virtual jbool requiresArg();
                        friend class JDefaultParser;


                    public:
                        JOption(JOption* o);

                        JOption(JString* opt,JString* description);

                        JOption(JString* opt,jbool hasArg,JString* description);

                        JOption(JString* opt,JString* longOpt,jbool hasArg,JString* description);

                        static JClass* getClazz();

                        static jint UNINITIALIZED;

                        static jint UNLIMITED_VALUES;

                        virtual jint getId();

                        virtual JString* getKey();

                        virtual JString* getOpt();

                        virtual JClass* getType();

                        virtual void setType(JClass* t);

                        virtual JString* getLongOpt();

                        virtual void setLongOpt(JString* longOpt);

                        virtual void setOptionalArg(jbool o);

                        virtual jbool hasOptionalArg();

                        virtual jbool hasLongOpt();

                        virtual jbool hasArg();

                        virtual JString* getDescription();

                        virtual void setDescription(JString* d);

                        virtual jbool isRequired();

                        virtual void setRequired(jbool r);

                        virtual void setArgName(JString* a);

                        virtual JString* getArgName();

                        virtual jbool hasArgName();

                        virtual jbool hasArgs();

                        virtual void setArgs(jint n);

                        virtual void setValueSeparator(jchar s);

                        virtual jchar getValueSeparator();

                        virtual jbool hasValueSeparator();

                        virtual jint getArgs();

                        virtual void addValueForProcessing(JString* value);

                        virtual JString* getValue();

                        virtual JString* getValue(jint index);

                        virtual JString* getValue(JString* d);

                        virtual JPrimitiveObjectArray* getValues();

                        virtual JList* getValuesList();

                        virtual JString* toString();

                        virtual jbool equals(JObject* o);

                        virtual jint hashCode();

                        virtual JObject* clone();

                        // @Class(canonicalName="org.apache.commons.cli.Option$Builder", simpleName="Option$Builder");
                        class JCPP_EXPORT JBuilder : public JObject{
                        protected:
                            JString* strOpt;
                            JString* strDescription;
                            JString* strLongOpt;
                            JString* strArgName;
                            jbool bRequired;
                            jbool bOptionalArg;
                            jint iNumberOfArgs;
                            JClass* cType;
                            jchar cValuesep;

                            JBuilder(JString* opt);
                            friend class JOption;

                        public:

                            static JClass* getClazz();

                            JBuilder* argName(JString* s);

                            JBuilder* desc(JString* s);

                            JBuilder* longOpt(JString* l);

                            JBuilder* numberOfArgs(jint n);

                            JBuilder* optionalArg(jbool o);

                            JBuilder* required();

                            JBuilder* required(jbool r);

                            JBuilder* type(JClass* t);

                            JBuilder* valueSeparator();

                            JBuilder* valueSeparator(jchar s);

                            JBuilder* hasArg();

                            JBuilder* hasArg(jbool b);

                            JBuilder* hasArgs();

                            JOption* build();

                            virtual ~JBuilder();

                        };

                        static JBuilder* builder();

                        static JBuilder* builder(JString* opt);

                    protected:
                        JOption(JBuilder* builder);

                    public:

                        virtual ~JOption();
                };
            }
        }
    }
}
#endif
