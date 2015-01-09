#ifndef JCPP_XML_INTERNAL_TREE_XMLWRITABLE_H
#define JCPP_XML_INTERNAL_TREE_XMLWRITABLE_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/xml/internal/tree/JXmlWriteContext.h"

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace tree{            

            	// @Class(canonicalName="javax.xml.parsers.XmlWritable", simpleName="XmlWritable");
            	class JCPP_EXPORT JXmlWritable : public JInterface{
                public:
                    static JClass* getClazz();

                    virtual void writeXml(JXmlWriteContext* context)=0;
                    
                    virtual void writeChildrenXml(JXmlWriteContext* context)=0;

                    virtual ~JXmlWritable();
                };
            }
        }
    }
}

#endif
