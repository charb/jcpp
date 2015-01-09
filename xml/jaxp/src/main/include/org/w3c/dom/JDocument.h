#ifndef ORG_W3C_DOM_DOCUMENT_H
#define ORG_W3C_DOM_DOCUMENT_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "org/w3c/dom/JNode.h"
#include "org/w3c/dom/JDocumentType.h"
#include "org/w3c/dom/JText.h"
#include "org/w3c/dom/JDocumentFragment.h"
#include "org/w3c/dom/JDOMConfiguration.h"
#include "org/w3c/dom/JElement.h"
#include "org/w3c/dom/JNodeList.h"
#include "org/w3c/dom/JCDATASection.h"
#include "org/w3c/dom/JProcessingInstruction.h"
#include "org/w3c/dom/JEntityReference.h"
#include "org/w3c/dom/JAttr.h"
#include "org/w3c/dom/JComment.h"

namespace org{
    namespace w3c{
        namespace dom{
            class JDOMImplementation;

            // @Class(canonicalName="org.w3c.dom.Document", simpleName="Document");
            class JCPP_EXPORT JDocument : public virtual JNode{
            public:
                static JClass* getClazz();

                virtual JDocumentType* getDoctype()=0;

                virtual JDOMImplementation* getImplementation()=0;

                virtual JElement* getDocumentElement()=0;

                virtual JElement* createElement(JString* tagName)=0;
                
                virtual JDocumentFragment* createDocumentFragment()=0;

                virtual JText* createTextNode(JString* data)=0;

                virtual JComment* createComment(JString* data)=0;

                virtual JCDATASection* createCDATASection(JString* data)=0;

                virtual JProcessingInstruction* createProcessingInstruction(JString* target,JString* data)=0;

                virtual JAttr* createAttribute(JString* name)=0;

                virtual JEntityReference* createEntityReference(JString* name)=0;

                virtual JNodeList* getElementsByTagName(JString* tagname)=0;

                virtual JNode* importNode(JNode* importedNode,jbool deep)=0;

                virtual JElement* createElementNS(JString* namespaceURI,JString* qualifiedName)=0;

                virtual JAttr* createAttributeNS(JString* namespaceURI,JString* qualifiedName)=0;

                virtual JNodeList* getElementsByTagNameNS(JString* namespaceURI,JString* localName)=0;
    
                virtual JElement* getElementById(JString* elementId)=0;

                virtual JString* getInputEncoding()=0;

                virtual JString* getXmlEncoding()=0;

                virtual jbool getXmlStandalone()=0;

                virtual void setXmlStandalone(jbool xmlStandalone)=0;

                virtual JString* getXmlVersion()=0;

                virtual void setXmlVersion(JString* xmlVersion)=0;

                virtual jbool getStrictErrorChecking()=0;

                virtual void setStrictErrorChecking(jbool strictErrorChecking)=0;

                virtual JString* getDocumentURI()=0;

                virtual void setDocumentURI(JString* documentURI)=0;

                virtual JNode* adoptNode(JNode* source)=0;

                virtual JDOMConfiguration* getDomConfig()=0;

                virtual void normalizeDocument()=0;

                virtual JNode* renameNode(JNode* n,JString* namespaceURI,JString* qualifiedName)=0;

                virtual ~JDocument();
            };
        }
    }
}

#endif
