#ifndef JORG_APACHE_COMMONS_CLI_HELP_FORMATTER_H
#define JORG_APACHE_COMMONS_CLI_HELP_FORMATTER_H

#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JPrimitiveObjectArray.h"
#include "jcpp/lang/JStringBuffer.h"
#include "jcpp/util/JComparator.h"
#include "org/apache/commons/cli/JCommandLine.h"
#include "org/apache/commons/cli/JCommandLineParser.h"
#include "org/apache/commons/cli/JOptions.h"
#include "jcpp/io/JPrintWriter.h"

using namespace jcpp::lang;
using namespace jcpp::util;
using namespace jcpp::io;

namespace org{
    namespace apache{
        namespace commons{
            namespace cli{
            	// @Class(canonicalName="org.apache.commons.cli.HelpFormatter", simpleName="HelpFormatter");
                class JCPP_EXPORT JHelpFormatter : public JObject{
                    protected:
                        jint defaultWidth;
                        jint defaultLeftPad;
                        jint defaultDescPad;
                        JString* defaultSyntaxPrefix;
                        JString* defaultNewLine;
                        JString* defaultOptPrefix;
                        JString* defaultLongOptPrefix;
                        JString* defaultArgName;
                        JComparator* optionComparator;
                        JString* longOptSeparator;
                        void appendOptionGroup(JStringBuffer* buff, JOptionGroup* group);
                        void appendOption(JStringBuffer* buff, JOption* option, jbool required);
                        JStringBuffer* renderOptions(JStringBuffer* sb, jint width, JOptions* options, jint leftPad, jint descPad);
                        JStringBuffer* renderWrappedText(JStringBuffer* sb, jint width,jint nextLineTabStop, JString* text);
                        JAppendable* renderWrappedTextBlock(JStringBuffer* sb, jint width, jint nextLineTabStop, JString* text);
                        jint findWrapPos(JString* text, jint width, jint startPos);
                        JString* createPadding(jint len);
                        JString* rtrim(JString* s);

                    public:
                        JHelpFormatter();

                        static JClass* getClazz();

                        static jint DEFAULT_WIDTH;

                        static jint DEFAULT_LEFT_PAD;

                        static jint DEFAULT_DESC_PAD;

                        static JString* DEFAULT_SYNTAX_PREFIX;

                        static JString* DEFAULT_OPT_PREFIX;

                        static JString* DEFAULT_LONG_OPT_PREFIX;

                        static JString* DEFAULT_LONG_OPT_SEPARATOR;

                        static JString* DEFAULT_ARG_NAME;

                        void setWidth(jint width);

                        jint getWidth();

                        void setLeftPadding(jint padding);

                        jint getLeftPadding();

                        void setDescPadding(jint padding);

                        jint getDescPadding();

                        void setSyntaxPrefix(JString* prefix);

                        JString* getSyntaxPrefix();

                        void setNewLine(JString* newline);

                        JString* getNewLine();

                        void setOptPrefix(JString* prefix);

                        JString* getOptPrefix();

                        void setLongOptPrefix(JString* prefix);

                        JString* getLongOptPrefix();

                        void setLongOptSeparator(JString* longOptSeparator);

                        JString* getLongOptSeparator();

                        void setArgName(JString* name);

                        JString* getArgName();

                        JComparator* getOptionComparator();

                        void setOptionComparator(JComparator* comparator);

                        void printHelp(JString* cmdLineSyntax, JOptions* options);

                        void printHelp(JString* cmdLineSyntax, JOptions* options, jbool autoUsage);

                        void printHelp(JString* cmdLineSyntax, JString* header, JOptions* options, JString* footer);

                        void printHelp(JString* cmdLineSyntax, JString* header, JOptions* options, JString* footer, jbool autoUsage);

                        void printHelp(jint width, JString* cmdLineSyntax, JString* header, JOptions* options, JString* footer);

                        void printHelp(jint width, JString* cmdLineSyntax, JString* header, JOptions* options, JString* footer, jbool autoUsage);

                        void printHelp(JPrintWriter* pw, jint width, JString* cmdLineSyntax, JString* header, JOptions* options, jint leftPad,jint descPad, JString* footer);

                        void printHelp(JPrintWriter* pw, jint width, JString* cmdLineSyntax,JString* header, JOptions* options, jint leftPad,jint descPad, JString* footer, jbool autoUsage);

                        void printUsage(JPrintWriter* pw, jint width, JString* app, JOptions* options);

                        void printUsage(JPrintWriter* pw, jint width, JString* cmdLineSyntax);

                        void printOptions(JPrintWriter* pw, jint width, JOptions* options, jint leftPad, jint descPad);

                        void printWrapped(JPrintWriter* pw, jint width, JString* text);

                        void printWrapped(JPrintWriter* pw, jint width, jint nextLineTabStop, JString* text);

                        virtual ~JHelpFormatter();
                };
            }
        }
    }
}
#endif
