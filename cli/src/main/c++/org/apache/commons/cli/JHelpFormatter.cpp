#include "org/apache/commons/cli/JHelpFormatter.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JString.h"
#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JDouble.h"
#include "jcpp/lang/JLong.h"
#include "jcpp/lang/JSystem.h"
#include "jcpp/lang/JCharacter.h"
#include "jcpp/io/JFile.h"
#include "jcpp/util/JHashMap.h"
#include "jcpp/util/JArrayList.h"
#include "jcpp/util/JArrays.h"
#include "jcpp/util/JCollections.h"
#include "jcpp/io/JBufferedReader.h"
#include "jcpp/io/JStringReader.h"
#include "jcpp/lang/JStringBuilder.h"
#include "org/apache/commons/cli/JAlreadySelectedException.h"
#include "org/apache/commons/cli/JPatternOptionBuilder.h"
#include "jcpp/lang/JIllegalArgumentException.h"

using namespace jcpp::io;

namespace org{
    namespace apache{
        namespace commons{
            namespace cli{

            	// @Class(canonicalName="org.apache.commons.cli.OptionComparator", simpleName="OptionComparator");
                class JOptionComparator : public JObject, public JComparator, public JSerializable{
                private:
                	static const jlong serialVersionUID = 5305467873966684014LL;
                public :
                        JOptionComparator():JObject(getClazz()){
                        }

                        static JClass* getClazz();

                        virtual jint compare(JObject* o1, JObject* o2){
                            JOption* opt1=dynamic_cast<JOption*>(o1);
                            JOption* opt2=dynamic_cast<JOption*>(o2);
                            return opt1->getKey()->compareToIgnoreCase(opt2->getKey());
                        }
                };

                jint JHelpFormatter::DEFAULT_WIDTH = 74;

                jint JHelpFormatter::DEFAULT_LEFT_PAD = 1;

                jint JHelpFormatter::DEFAULT_DESC_PAD = 3;

                JString* JHelpFormatter::DEFAULT_SYNTAX_PREFIX = new JString("usage: ");

                JString* JHelpFormatter::DEFAULT_OPT_PREFIX = new JString("-");

                JString* JHelpFormatter::DEFAULT_LONG_OPT_PREFIX = new JString("--");

                JString* JHelpFormatter::DEFAULT_LONG_OPT_SEPARATOR = new JString(" ");

                JString* JHelpFormatter::DEFAULT_ARG_NAME = new JString("arg");

                JHelpFormatter::JHelpFormatter():JObject(getClazz()){
                    defaultWidth = DEFAULT_WIDTH;
                    defaultLeftPad = DEFAULT_LEFT_PAD;
                    defaultDescPad = DEFAULT_DESC_PAD;
                    defaultSyntaxPrefix = DEFAULT_SYNTAX_PREFIX;
                    defaultNewLine = JSystem::lineSeparator();
                    defaultOptPrefix = DEFAULT_OPT_PREFIX;
                    defaultLongOptPrefix = DEFAULT_LONG_OPT_PREFIX;
                    defaultArgName = DEFAULT_ARG_NAME;
                    optionComparator = new JOptionComparator();
                    longOptSeparator = DEFAULT_LONG_OPT_SEPARATOR;
                }

                void JHelpFormatter::setWidth(jint width){
                    this->defaultWidth = width;
                }

                jint JHelpFormatter::getWidth(){
                    return defaultWidth;
                }

                void JHelpFormatter::setLeftPadding(jint padding){
                    this->defaultLeftPad = padding;
                }

                jint JHelpFormatter::getLeftPadding(){
                    return defaultLeftPad;
                }

                void JHelpFormatter::setDescPadding(jint padding){
                    this->defaultDescPad = padding;
                }

                jint JHelpFormatter::getDescPadding(){
                    return defaultDescPad;
                }

                void JHelpFormatter::setSyntaxPrefix(JString* prefix){
                    this->defaultSyntaxPrefix = prefix;
                }

                JString* JHelpFormatter::getSyntaxPrefix(){
                    return defaultSyntaxPrefix;
                }

                void JHelpFormatter::setNewLine(JString* newline){
                    this->defaultNewLine = newline;
                }

                JString* JHelpFormatter::getNewLine(){
                    return defaultNewLine;
                }

                void JHelpFormatter::setOptPrefix(JString* prefix){
                    this->defaultOptPrefix = prefix;
                }

                JString* JHelpFormatter::getOptPrefix(){
                    return defaultOptPrefix;
                }

                void JHelpFormatter::setLongOptPrefix(JString* prefix){
                    this->defaultLongOptPrefix = prefix;
                }

                JString* JHelpFormatter::getLongOptPrefix(){
                    return defaultLongOptPrefix;
                }

                void JHelpFormatter::setLongOptSeparator(JString* longOptSeparator){
                    this->longOptSeparator = longOptSeparator;
                }

                JString* JHelpFormatter::getLongOptSeparator(){
                    return longOptSeparator;
                }

                void JHelpFormatter::setArgName(JString* name){
                    this->defaultArgName = name;
                }

                JString* JHelpFormatter::getArgName(){
                    return defaultArgName;
                }

                JComparator* JHelpFormatter::getOptionComparator(){
                    return optionComparator;
                }

                void JHelpFormatter::setOptionComparator(JComparator* comparator){
                    this->optionComparator = comparator;
                }

                void JHelpFormatter::printHelp(JString* cmdLineSyntax, JOptions* options){
                    printHelp(getWidth(), cmdLineSyntax, null, options, null, false);
                }

                void JHelpFormatter::printHelp(JString* cmdLineSyntax, JOptions* options, jbool autoUsage){
                    printHelp(getWidth(), cmdLineSyntax, null, options, null, autoUsage);
                }

                void JHelpFormatter::printHelp(JString* cmdLineSyntax, JString* header, JOptions* options, JString* footer){
                    printHelp(cmdLineSyntax, header, options, footer, false);
                }

                void JHelpFormatter::printHelp(JString* cmdLineSyntax, JString* header, JOptions* options, JString* footer, jbool autoUsage){
                    printHelp(getWidth(), cmdLineSyntax, header, options, footer, autoUsage);
                }

                void JHelpFormatter::printHelp(jint width, JString* cmdLineSyntax, JString* header, JOptions* options, JString* footer){
                    printHelp(width, cmdLineSyntax, header, options, footer, false);
                }

                void JHelpFormatter::printHelp(jint width, JString* cmdLineSyntax, JString* header,JOptions* options, JString* footer, jbool autoUsage){
                    JPrintWriter* pw = new JPrintWriter(JSystem::out);

                    printHelp(pw, width, cmdLineSyntax, header, options, getLeftPadding(), getDescPadding(), footer, autoUsage);
                    pw->flush();
                }

                void JHelpFormatter::printHelp(JPrintWriter* pw, jint width, JString* cmdLineSyntax, JString* header, JOptions* options, jint leftPad, jint descPad, JString* footer){
                    printHelp(pw, width, cmdLineSyntax, header, options, leftPad, descPad, footer, false);
                }

                void JHelpFormatter::printHelp(JPrintWriter* pw, jint width, JString* cmdLineSyntax,JString* header, JOptions* options, jint leftPad,jint descPad, JString* footer, jbool autoUsage){
                    if ((cmdLineSyntax == null) || (cmdLineSyntax->length() == 0)){
                        throw new JIllegalArgumentException(new JString("cmdLineSyntax not provided"));
                    }

                    if (autoUsage){
                        printUsage(pw, width, cmdLineSyntax, options);
                    }else{
                        printUsage(pw, width, cmdLineSyntax);
                    }

                    if ((header != null) && (header->trim()->length() > 0)){
                        printWrapped(pw, width, header);
                    }

                    printOptions(pw, width, options, leftPad, descPad);

                    if ((footer != null) && (footer->trim()->length() > 0)){
                        printWrapped(pw, width, footer);
                    }
                }

                void JHelpFormatter::printUsage(JPrintWriter* pw, jint width, JString* app, JOptions* options){
                    JStringBuffer* buff = new JStringBuffer(getSyntaxPrefix());
                    buff->append(app)->append((jchar)' ');

                    JCollection* processedGroups = reinterpret_cast<JCollection*>(new JArrayList());

                    JList* optList = new JArrayList(options->getOptions());
                    if (getOptionComparator() != null){
                        JCollections::sort(optList, getOptionComparator());
                    }
                    for (JIterator* it = optList->iterator(); it->hasNext();){
                        JOption* option = dynamic_cast<JOption*>(it->next());

                        JOptionGroup* group = options->getOptionGroup(option);

                        if (group != null){
                            if (!processedGroups->contains(group)){
                                processedGroups->add(group);
                                appendOptionGroup(buff, group);
                            }
                        }else{
                            appendOption(buff, option, option->isRequired());
                        }
                        if (it->hasNext()){
                            buff->append(new JString(" "));
                        }
                    }

                    printWrapped(pw, width, buff->toString()->indexOf(new JString(" ")) + 1, buff->toString());
                }

                void JHelpFormatter::appendOptionGroup(JStringBuffer* buff, JOptionGroup* group){
                    if (!group->isRequired()){
                        buff->append(new JString("["));
                    }

                    JList* optList = new JArrayList(group->getOptions());
                    if (getOptionComparator() != null){
                        JCollections::sort(optList, getOptionComparator());
                    }
                    for (JIterator* it = optList->iterator(); it->hasNext();){
                        appendOption(buff, dynamic_cast<JOption*>(it->next()), true);
                        if (it->hasNext()){
                            buff->append(new JString(" | "));
                        }
                    }
                    if (!group->isRequired()){
                        buff->append((jchar)']');
                    }
                }

                void JHelpFormatter::appendOption(JStringBuffer* buff, JOption* option, jbool required){
                    if (!required){
                        buff->append(new JString("["));
                    }

                    if (option->getOpt() != null){
                        buff->append(new JString("-"))->append(option->getOpt());
                    }else{
                        buff->append(new JString("--"))->append(option->getLongOpt());
                    }
                    
                    if (option->hasArg() && (option->getArgName() == null || option->getArgName()->length() != 0)){
                        buff->append(option->getOpt() == null ? longOptSeparator : new JString(" "));
                        buff->append((jchar)'<')->append(option->getArgName() != null ? option->getArgName() : getArgName())->append((jchar)'>');
                    }
                    if (!required){
                        buff->append(new JString("]"));
                    }
                }

                void JHelpFormatter::printUsage(JPrintWriter* pw, jint width, JString* cmdLineSyntax){
                    jint argPos = cmdLineSyntax->indexOf(new JString(' ')) + 1;
                    JStringBuffer* buf=new JStringBuffer();
                    buf->append(getSyntaxPrefix())->append(cmdLineSyntax);
                    printWrapped(pw, width, getSyntaxPrefix()->length() + argPos,buf->toString() );
                }

                void JHelpFormatter::printOptions(JPrintWriter* pw, jint width, JOptions* options, jint leftPad, jint descPad){
                    JStringBuffer* sb = new JStringBuffer();
                    renderOptions(sb, width, options, leftPad, descPad);
                    pw->println(sb->toString());
                }

                void JHelpFormatter::printWrapped(JPrintWriter* pw, jint width, JString* text){
                    printWrapped(pw, width, 0, text);
                }

                void JHelpFormatter::printWrapped(JPrintWriter* pw, jint width, jint nextLineTabStop, JString* text){
                    JStringBuffer* sb = new JStringBuffer();

                    renderWrappedTextBlock(sb, width, nextLineTabStop, text);
                    pw->println(sb->toString());
                }

                JStringBuffer* JHelpFormatter::renderOptions(JStringBuffer* sb, jint width, JOptions* options, jint leftPad, jint descPad){
                    JString* lpad = createPadding(leftPad);
                    JString* dpad = createPadding(descPad);

                    jint max = 0;
                    JList* prefixList = new JArrayList();
                    JList* optList = options->helpOptions();

                    if (getOptionComparator() != null){
                        JCollections::sort(optList, getOptionComparator());
                    }

                    for (jint i=0;i<optList->size();i++){
                        JOption* option = dynamic_cast<JOption*>(optList->get(i));
                        JStringBuffer* optBuf = new JStringBuffer();

                        if (option->getOpt() == null){
                            optBuf->append(lpad)->append(new JString("   "))->append(getLongOptPrefix())->append(option->getLongOpt());
                        }else{
                            optBuf->append(lpad)->append(getOptPrefix())->append(option->getOpt());

                            if (option->hasLongOpt()){
                                optBuf->append((jchar)',')->append(getLongOptPrefix())->append(option->getLongOpt());
                            }
                        }

                        if (option->hasArg()){
                            JString* argName = option->getArgName();
                            if (argName != null && argName->length() == 0){
                                optBuf->append((jchar)' ');
                            }else{
                                optBuf->append(option->hasLongOpt() ? longOptSeparator : new JString(" "));
                                optBuf->append((jchar)'<')->append(argName != null ? option->getArgName() : getArgName())->append((jchar)'>');
                            }
                        }

                        prefixList->add(optBuf);
                        max = (optBuf->length() > max) ? optBuf->length() : max;
                    }

                    jint x = 0;

                    for (JIterator* it = optList->iterator(); it->hasNext();){
                        JOption* option = dynamic_cast<JOption*>(it->next());
                        JStringBuilder* optBuf = new JStringBuilder(prefixList->get(x++)->toString());

                        if (optBuf->length() < max){
                            optBuf->append(createPadding(max - optBuf->length()));
                        }

                        optBuf->append(dpad);

                        jint nextLineTabStop = max + descPad;

                        if (option->getDescription() != null){
                            optBuf->append(option->getDescription());
                        }

                        renderWrappedText(sb, width, nextLineTabStop, optBuf->toString());

                        if (it->hasNext()){
                            sb->append(getNewLine());
                        }
                    }
                    return sb;
                }

                JStringBuffer* JHelpFormatter::renderWrappedText(JStringBuffer* sb, jint width, jint nextLineTabStop, JString* text){
                    jint pos = findWrapPos(text, width, 0);
                    if (pos == -1){
                        sb->append(rtrim(text));
                        return sb;
                    }
                    sb->append(rtrim(text->substring(0, pos)))->append(getNewLine());
                    if (nextLineTabStop >= width){
                        nextLineTabStop = 1;
                    }
                    JString* padding = createPadding(nextLineTabStop);
                    while (true){
                        JStringBuffer* buf=new JStringBuffer();
                        buf->append(padding)->append(text->substring(pos)->trim());
                        text =  buf->toString() ;
                        pos = findWrapPos(text, width, 0);
                        if (pos == -1){
                            sb->append(text);
                            return sb;
                        }
                        if ((text->length() > width) && (pos == nextLineTabStop - 1)){
                            pos = width;
                        }
                        sb->append(rtrim(text->substring(0, pos)))->append(getNewLine());
                    }
                }

                JAppendable* JHelpFormatter::renderWrappedTextBlock(JStringBuffer* sb, jint width, jint nextLineTabStop, JString* text){
                    JBufferedReader* in = new JBufferedReader(new JStringReader(text));
                    JString* line;
                    jbool firstLine = true;
                    while ((line = in->readLine()) != null){
                        if (!firstLine){
                            sb->append(getNewLine());
                        }else{
                            firstLine = false;
                        }
                        renderWrappedText(sb, width, nextLineTabStop, line);
                    }
                    return sb;
                }

                jint JHelpFormatter::findWrapPos(JString* text, jint width, jint startPos){
                    jint pos = text->indexOf(new JString("\n"), startPos);
                    if (pos != -1 && pos <= width){
                        return pos + 1;
                    }
                    pos = text->indexOf(new JString("\t"), startPos);
                    if (pos != -1 && pos <= width){
                        return pos + 1;
                    }
                    if (startPos + width >= text->length()){
                        return -1;
                    }
                    for (pos = startPos + width; pos >= startPos; --pos){
                        jchar c = text->charAt(pos);
                        if (c == ' ' || c == '\n' || c == '\r'){
                            break;
                        }
                    }
                    if (pos > startPos){
                        return pos;
                    }
                    pos = startPos + width;
                    return pos == text->length() ? -1 : pos;
                }

                JString* JHelpFormatter::createPadding(jint len){
                    JPrimitiveCharArray* padding = new JPrimitiveCharArray(len);
                    JArrays::fill(padding, (jchar)' ');
                    return new JString(padding);
                }

                JString* JHelpFormatter::rtrim(JString* s){
                    if ((s == null) || (s->length() == 0)){
                        return s;
                    }
                    jint pos = s->length();
                    while ((pos > 0) && JCharacter::isWhitespace(s->charAt(pos - 1))){
                        --pos;
                    }
                    return s->substring(0, pos);
                }

                JHelpFormatter::~JHelpFormatter(){
                }
            }
        }
    }
}

