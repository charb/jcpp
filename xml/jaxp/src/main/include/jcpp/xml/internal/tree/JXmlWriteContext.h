#ifndef JCPP_XML_INTERNAL_TREE_XMLWRITE_CONTEXT_H
#define JCPP_XML_INTERNAL_TREE_XMLWRITE_CONTEXT_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/io/JWriter.h"

using namespace jcpp::io;

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace tree{            

            	// @Class(canonicalName="javax.xml.parsers.XmlWriteContext", simpleName="XmlWriteContext");
                class JCPP_EXPORT JXmlWriteContext : public JObject{
                protected:
                    JWriter* writer;
                    jint indentLevel;
                    jbool prettyOutput;
                    JXmlWriteContext(JClass* _class,JWriter* out);
                    JXmlWriteContext(JClass* _class,JWriter* out,jint level);

                public:
                    JXmlWriteContext(JWriter* out);

                    JXmlWriteContext(JWriter* out,jint level);

                    static JClass* getClazz();

                    virtual JWriter* getWriter();

                    virtual jbool isEntityDeclared(JString* name);

                    virtual jint getIndentLevel();

                    virtual void setIndentLevel(jint level);

                    virtual void printIndent();

                    virtual jbool isPrettyOutput();

                    virtual ~JXmlWriteContext();
                };
            }
        }
    }
}

#endif
