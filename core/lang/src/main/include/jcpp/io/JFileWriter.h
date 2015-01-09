#ifndef JCPP_IO_JFILEWRITER_H
#define JCPP_IO_JFILEWRITER_H

#include "jcpp/io/JOutputStreamWriter.h"
#include "jcpp/io/JFile.h"

namespace jcpp{
    namespace io{

    	//@Class(canonicalName="java.io.FileWriter", simpleName="FileWriter");
        class JCPP_EXPORT JFileWriter : public JOutputStreamWriter  {
            public:
                JFileWriter(JString* filename,jbool append=false);

                JFileWriter(JFile* f,jbool append=false);

                static jcpp::lang::JClass* getClazz();

                virtual ~JFileWriter();
        };
    }
}

#endif
