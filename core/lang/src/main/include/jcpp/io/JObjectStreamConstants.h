#ifndef JCPP_IO_JOBJECTSTREAMCONSTANTS_H
#define JCPP_IO_JOBJECTSTREAMCONSTANTS_H

#include "jcpp/lang/JObject.h"
#include "jcpp/lang/JInterface.h"

using namespace jcpp::lang;

namespace jcpp{
    namespace io{

    	//@Class(canonicalName="java.io.ObjectStreamConstants", simpleName="ObjectStreamConstants");
        class JCPP_EXPORT JObjectStreamConstants : public JInterface{

        public:
            static jcpp::lang::JClass* getClazz();

            static const jshort STREAM_MAGIC = (jshort)0xaced;

            static const jshort STREAM_VERSION = 5;

            const static jbyte TC_BASE = 0x70;

            const static jbyte TC_NULL = 	(jbyte)0x70;

            static const jbyte TC_REFERENCE =	(jbyte)0x71;

            static const jbyte TC_CLASSDESC =       (jbyte)0x72;

            static const jbyte TC_OBJECT = 	(jbyte)0x73;

            const static jbyte TC_STRING = 	(jbyte)0x74;

            const static jbyte TC_ARRAY = 	(jbyte)0x75;

            const static jbyte TC_CLASS = 	(jbyte)0x76;

            const static jbyte TC_BLOCKDATA = 	(jbyte)0x77;

            const static jbyte TC_ENDBLOCKDATA =	(jbyte)0x78;

             static const jbyte TC_RESET = 	(jbyte)0x79;

             const static jbyte TC_BLOCKDATALONG= (jbyte)0x7A;

             const static jbyte TC_EXCEPTION = 	(jbyte)0x7B;

             const static jbyte TC_LONGSTRING = 	(jbyte)0x7C;

             const static jbyte TC_PROXYCLASSDESC =	(jbyte)0x7D;

             const static jbyte TC_ENUM =		(jbyte)0x7E;

             const static jbyte TC_MAX = 		(jbyte)0x7E;

            const static jint baseWireHandle = 0x7e0000;

            const static jbyte SC_WRITE_METHOD = 0x01;

            const static jbyte SC_BLOCK_DATA = 0x08;

            const static jbyte SC_SERIALIZABLE = 0x02;

            const static jbyte SC_EXTERNALIZABLE = 0x04;

            const static jbyte SC_ENUM = 0x10;

        };
    }
}

#endif
