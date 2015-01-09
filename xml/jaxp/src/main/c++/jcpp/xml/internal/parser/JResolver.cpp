#include "jcpp/xml/internal/parser/JResolver.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/io/JFileInputStream.h"
#include "jcpp/io/JInputStreamReader.h"

namespace jcpp{
    namespace xml{
        namespace internal{
            namespace parser{

                JResolver::JResolver():JObject(getClazz()){
                    ignoringMIME=false;
                    id2uri=null;
                    id2resource=null;
                    id2loader=null;
                }

                JPrimitiveObjectArray* JResolver::types = null;

                JPrimitiveObjectArray* JResolver::getTypes(){
                    if (types==null){
                        types=new JPrimitiveObjectArray(JString::getClazz(),6);
                        types->set(0,new JString("application/xml"));
                        types->set(1,new JString("text/xml"));
                        types->set(2,new JString("text/plain"));
                        types->set(3,new JString("text/html"));
                        types->set(4,new JString("application/x-netcdf"));
                        types->set(5,new JString("content/unknown"));
                    }
                    return types;
                }

                JInputSource* JResolver::createInputSource(JString* contentType,JInputStream* stream, jbool checkType,JString* scheme){
                    JInputSource* retval=null;
                    JString* charset = null;
                        
                    if (contentType != null) {
                        jint index=0;

                        contentType = contentType->toLowerCase();
                        index = contentType->indexOf(';');
                        if (index != -1) {
                            JString*  attributes=contentType->substring(index + 1);
                            contentType = contentType->substring(0, index);
                            index = attributes->indexOf(new JString("charset"));

                            if (index != -1) {
                                attributes = attributes->substring(index + 7);

                                if ((index = attributes->indexOf(';')) != -1){
                                    attributes = attributes->substring(0, index);
                                }

                                if ((index = attributes->indexOf('=')) != -1) {
                                    attributes = attributes->substring(index + 1);

                                    if ((index = attributes->indexOf('(')) != -1){
                                        attributes = attributes->substring(0, index);
                                    }

                                    if ((index = attributes->indexOf('"')) != -1) {
                                        attributes = attributes->substring(index + 1);
                                        attributes = attributes->substring(0,attributes->indexOf('"'));
                                    }
                                    charset = attributes->trim();
                                }
                            }
                        }

                        if (checkType) {
                            jbool isOK = false;
                            for (jint i = 0; i < getTypes()->size(); i++){
                                if (getTypes()->get(i)->equals(contentType)) {
                                    isOK = true;
                                    break;
                                }
                            }
                            if (!isOK){
                                throw new JIOException(new JString("Not XML: "));
                            }
                        }

                        if (charset == null) {
                            contentType = contentType->trim();
                            if (contentType->startsWith(new JString("text/"))) {
                                if (!(new JString("file"))->equalsIgnoreCase(scheme)){
                                    charset = new JString("US-ASCII");
                                }
                            }
                        }
                    }

                    retval = new JInputSource(new JInputStreamReader(stream));//TODO ,charset));
                    retval->setByteStream(stream);
                    retval->setEncoding(charset);
                    return retval;
                }

                JInputSource* JResolver::createInputSource(JFile* file){
                    JInputSource* retval=null;
                    JString* path=null;
                    
                    retval = new JInputSource(new JInputStreamReader(new JFileInputStream(file)));
                    path = file->getAbsolutePath();

                    JStringBuilder* builder=new JStringBuilder();
                    builder->append(new JString("file:"))->append(path);
                    retval->setSystemId(builder->toString());
                    return retval;
                }

                JInputSource* JResolver::resolveEntity(JString* name, JString* uri){
                    JInputSource* retval=null;        
                    JString* mappedURI = name2uri (name);
                    JInputStream* stream=null;

                    if (mappedURI == null && (stream = mapResource(name)) != null) {
                        JStringBuilder* builder=new JStringBuilder();
                        builder->append(new JString("java:resource:"))->append(id2resource->get(name));
                        uri = builder->toString();
                        retval = new JInputSource(new JInputStreamReader(stream));

                    } else {
                        if (mappedURI != null){
                            uri = mappedURI;
                        
                        }else if (uri == null){
                            return null;
                        }

                        JFileInputStream* is = new JFileInputStream(uri);
                        retval = new JInputSource(new JInputStreamReader(is));                        
                    }
                    retval->setSystemId(uri);
                    retval->setPublicId(name);
                    return retval;
                }

                jbool JResolver::isIgnoringMIME(){
                    return ignoringMIME;
                }

                void JResolver::setIgnoringMIME(jbool value){
                    ignoringMIME = value;
                }

                JString* JResolver::name2uri(JString* publicId){
                    if (publicId == null || id2uri == null){
                        return null;
                    }
                    return dynamic_cast<JString*>(id2uri->get(publicId));
                }

                void JResolver::registerCatalogEntry(JString* publicId,JString* uri){
                    if (id2uri == null){
                        id2uri = new JHashtable (17);
                    }
                    id2uri->put(publicId, uri);
                }

                JInputStream* JResolver::mapResource(JString* publicId){
                    if (publicId == null || id2resource == null){
                        return null;
                    }

                    JString* resourceName = dynamic_cast<JString*>(id2resource->get(publicId));
                    JClassLoader* loader = null;

                    if (resourceName == null){
                        return null;
                    }
                    
                    if (id2loader != null){
                        loader = dynamic_cast<JClassLoader*>(id2loader->get(publicId));
                    }

                    /*TODO
                    if (loader == null){
                        return JClassLoader::getSystemResourceAsStream(resourceName);
                    }
                    return loader->getResourceAsStream(resourceName);
                    */
                    return null;
                }

                void JResolver::registerCatalogEntry(JString* publicId,JString* resourceName,JClassLoader* loader){
                    if (id2resource == null){
                        id2resource = new JHashtable(17);
                    }
                    id2resource->put(publicId, resourceName);

                    if (loader != null) {
                        if (id2loader == null){
                            id2loader = new JHashtable(17);
                        }
                        id2loader->put(publicId, loader);
                    }
                }

                JResolver::~JResolver(){
                }
            }
        }
    }
}
