#include "org/xml/sax/helpers/JNamespaceSupport.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JException.h"
#include "jcpp/lang/JArrayIndexOutOfBoundsException.h"
#include "jcpp/lang/JIllegalStateException.h"
#include "jcpp/lang/JSystem.h"

namespace org{
    namespace xml{
        namespace sax{
            namespace helpers{

                JString* JNamespaceSupport::XMLNS = new JString("http://www.w3.org/XML/1998/namespace");
                JString* JNamespaceSupport::NSDECL = new JString("http://www.w3.org/xmlns/2000/");

                JNamespaceSupport::JNamespaceSupport():JObject(getClazz()){
                    contexts=null;
                    currentContext=null;
                    contextPos=0;
                    namespaceDeclUris=false;
                    reset();
                }

                JEnumeration* JNamespaceSupport::EMPTY_ENUMERATION =  (new JVector())->elements();

                JNamespaceSupport::JContext::JContext(JNamespaceSupport* support):JObject(getClazz()){
                    this->support=support;
                    prefixTable=null;
                    uriTable=null;
                    elementNameTable=null;
                    attributeNameTable=null;
                    defaultNS=null;
                    declarations=null;
                    declSeen=false;
                    parent=null;
                    copyTables();
                }

                void JNamespaceSupport::JContext::setParent(JContext* parent){
                    this->parent = parent;
                    declarations = null;
                    prefixTable = parent->prefixTable;
                    uriTable = parent->uriTable;
                    elementNameTable = parent->elementNameTable;
                    attributeNameTable = parent->attributeNameTable;
                    defaultNS = parent->defaultNS;
                    declSeen = false;
                }

                void JNamespaceSupport::JContext::clear(){
                    parent = null;
                    prefixTable = null;
                    uriTable = null;
                    elementNameTable = null;
                    attributeNameTable = null;
                    defaultNS = null;
                }

                void JNamespaceSupport::JContext::declarePrefix(JString* prefix, JString* uri){
                    if (!declSeen) {
                        copyTables();
                    }
                    if (declarations == null) {
                        declarations = new JVector();
                    }

                    uri = uri;
                    if ((new JString(""))->equals(prefix)) {
                        if ((new JString(""))->equals(uri)) {
                            defaultNS = null;

                        } else {
                            defaultNS = uri;
                        }

                    } else {
                        prefixTable->put(prefix, uri);
                        uriTable->put(uri, prefix);
                    }
                    declarations->addElement(prefix);
                }

                JPrimitiveObjectArray* JNamespaceSupport::JContext::processName(JString* qName, jbool isAttribute){
                    JPrimitiveObjectArray* name=null;
                    JHashtable* table=null;

                    if (isAttribute) {
                        table = attributeNameTable;
                    } else {
                        table = elementNameTable;
                    }

                    name = dynamic_cast<JPrimitiveObjectArray*>(table->get(qName));
                    if (name != null) {
                        return name;
                    }

                    name = new JPrimitiveObjectArray(JString::getClazz(),3);
                    name->set(2, qName);
                    jint index = qName->indexOf(':');

                    if (index == -1) {
                        if (isAttribute) {
                            if (qName->equals(new JString("xmlns")) && support->namespaceDeclUris){
                                name->set(0, NSDECL);
                            }else{
                                name->set(0, new JString(""));
                            }

                        } else if (defaultNS == null) {
                            name->set(0, new JString(""));

                        } else {
                            name->set(0, defaultNS);
                        }
                        name->set(1, name->get(2));

                    }else {
                        JString* prefix = qName->substring(0, index);
                        JString* local = qName->substring(index+1);
                        JString* uri=null;

                        if ((new JString(""))->equals(prefix)) {
                            uri = defaultNS;

                        } else {
                            uri = dynamic_cast<JString*>(prefixTable->get(prefix));
                        }

                        if (uri == null || (!isAttribute && (new JString("xmlns"))->equals(prefix))) {
                            return null;
                        }
                        name->set(0, uri);
                        name->set(1, local);
                    }

                    table->put(name->get(2), name);
                    return name;
                }

                JString* JNamespaceSupport::JContext::getURI(JString* prefix){
                    if ((new JString(""))->equals(prefix)) {
                        return defaultNS;
                    
                    } else if (prefixTable == null) {
                        return null;
                    
                    } else {
                        return dynamic_cast<JString*>(prefixTable->get(prefix));
                    }
                }

                JString* JNamespaceSupport::JContext::getPrefix(JString* uri){
                    if (uriTable == null) {
                        return null;

                    } else {
                        return dynamic_cast<JString*>(uriTable->get(uri));
                    }
                }

                JEnumeration* JNamespaceSupport::JContext::getDeclaredPrefixes(){
                    if (declarations == null) {
                        return EMPTY_ENUMERATION;

                    } else {
                        return declarations->elements();
                    }
                }

                JEnumeration* JNamespaceSupport::JContext::getPrefixes(){
                    if (prefixTable == null) {
                        return EMPTY_ENUMERATION;
                        
                    } else {
                        return prefixTable->keys();
                    }
                }

                void JNamespaceSupport::JContext::copyTables(){
                    if (prefixTable != null) {
                        prefixTable = dynamic_cast<JHashtable*>(prefixTable->clone());
                    } else {
                        prefixTable = new JHashtable();
                    }

                    if (uriTable != null) {
                        uriTable = dynamic_cast<JHashtable*>(uriTable->clone());
                    } else {
                        uriTable = new JHashtable();
                    }

                    elementNameTable = new JHashtable();
                    attributeNameTable = new JHashtable();
                    declSeen = true;
                }

                JNamespaceSupport::JContext::~JContext(){
                }

                void JNamespaceSupport::reset(){
                    contexts = new JPrimitiveObjectArray(JContext::getClazz(),32);
                    namespaceDeclUris = false;
                    contextPos = 0;
                    currentContext = new JContext(this);
                    contexts->set(contextPos, currentContext);
                    currentContext->declarePrefix(new JString("xml"), XMLNS);
                }

                void JNamespaceSupport::pushContext(){
                    jint max = contexts->size();
                    contextPos++;
                    if (contextPos >= max) {
                        JPrimitiveObjectArray* newContexts = new JPrimitiveObjectArray(JContext::getClazz(),max*2);
                        JSystem::arraycopy(contexts, 0, newContexts, 0, max);
                        max *= 2;
                        contexts = newContexts;
                    }

                    currentContext = dynamic_cast<JContext*>(contexts->get(contextPos));
                    if (currentContext == null) {
                        currentContext = new JContext(this);
                        contexts->set(contextPos, currentContext);
                    }

                    if (contextPos > 0) {
                        currentContext->setParent(dynamic_cast<JContext*>(contexts->get(contextPos - 1)));
                    }
                }

                void JNamespaceSupport::popContext(){
                    dynamic_cast<JContext*>(contexts->get(contextPos))->clear();
                    contextPos--;
                    if (contextPos < 0) {
                        throw new JException(new JString("empty stack"));
                    }
                    currentContext = dynamic_cast<JContext*>(contexts->get(contextPos));
                }

                jbool JNamespaceSupport::declarePrefix(JString* prefix, JString* uri){
                    if (prefix->equals(new JString("xml")) || prefix->equals(new JString("xmlns"))) {
                        return false;

                    } else {
                        currentContext->declarePrefix(prefix, uri);
                        return true;
                    }
                }

                JPrimitiveObjectArray* JNamespaceSupport::processName(JString* qName, JPrimitiveObjectArray* parts,jbool isAttribute){
                    JPrimitiveObjectArray* myParts = currentContext->processName(qName, isAttribute);
                    if (myParts == null) {
                        return null;
                    
                    } else {
                        parts->set(0, myParts->get(0));
                        parts->set(1, myParts->get(1));
                        parts->set(2, myParts->get(2));
                        return parts;
                    }
                }

                JString* JNamespaceSupport::getURI(JString* prefix){
                    return currentContext->getURI(prefix);
                }

                JEnumeration* JNamespaceSupport::getPrefixes(){
                    return currentContext->getPrefixes();
                }

                JString* JNamespaceSupport::getPrefix(JString* uri){
                    return currentContext->getPrefix(uri);
                }

                JEnumeration* JNamespaceSupport::getPrefixes(JString* uri){
                    JVector* prefixes = new JVector();
                    JEnumeration* allPrefixes = getPrefixes();
                    while (allPrefixes->hasMoreElements()) {
                        JString* prefix = dynamic_cast<JString*>(allPrefixes->nextElement());
                        if (uri->equals(getURI(prefix))) {
                            prefixes->addElement(prefix);
                        }
                    }
                    return prefixes->elements();
                }

                JEnumeration* JNamespaceSupport::getDeclaredPrefixes(){
                    return currentContext->getDeclaredPrefixes();
                }

                void JNamespaceSupport::setNamespaceDeclUris(jbool value){
                    if (contextPos != 0){
                        throw new JIllegalStateException();
                    }
                    if (value == namespaceDeclUris){
                        return;
                    }
                    namespaceDeclUris = value;
                    if (value){
                        currentContext->declarePrefix(new JString("xmlns"), NSDECL);
                    
                    }else {
                        currentContext = new JContext(this);
                        contexts->set(contextPos,currentContext); 
                        currentContext->declarePrefix(new JString("xml"), XMLNS);
                    }
                }

                jbool JNamespaceSupport::isNamespaceDeclUris(){ 
                    return namespaceDeclUris; 
                }

                JNamespaceSupport::~JNamespaceSupport(){
                }
            }
        }
    }
}
