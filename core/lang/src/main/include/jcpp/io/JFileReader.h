#ifndef JCPP_IO_JFILEREADER_H
#define JCPP_IO_JFILEREADER_H

#include "jcpp/io/JInputStreamReader.h"
#include "jcpp/io/JFile.h"

namespace jcpp{
    namespace io{

    	//@Class(canonicalName="java.io.FileReader", simpleName="FileReader");
        class JCPP_EXPORT JFileReader : public JInputStreamReader  {
            public:
                JFileReader(JString* name);

                JFileReader(JFile* f);

                static jcpp::lang::JClass* getClazz();

                virtual ~JFileReader();
        };
    }
}

#endif
