#ifndef ORG_W3C_DOM_CHARACTER_DATA_H
#define ORG_W3C_DOM_CHARACTER_DATA_H

#include "jcpp/lang/JInterface.h"
#include "jcpp/lang/JClass.h"
#include "org/w3c/dom/JNode.h"

namespace org{
    namespace w3c{
        namespace dom{
            class JElement;
            class JTypeInfo;
            
            // @Class(canonicalName="org.w3c.dom.CharacterData", simpleName="CharacterData");
            class JCPP_EXPORT JCharacterData : public virtual JNode{
            public:
                static JClass* getClazz();

                virtual JString* getData()=0;

                virtual void setData(JString* data)=0;
                
                virtual jint getLength()=0;

                virtual JString* substringData(jint offset,jint count)=0;

                virtual void appendData(JString* arg)=0;

                virtual void insertData(jint offset,JString* arg)=0;

                virtual void deleteData(jint offset,jint count)=0;

                virtual void replaceData(jint offset,jint count,JString* arg)=0;

                virtual ~JCharacterData();
            };
        }
    }
}

#endif
