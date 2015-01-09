#include "jcpp/io/JFileWriter.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/io/JFileOutputStream.h"

namespace jcpp{
    namespace io{

        JFileWriter::JFileWriter(JString* filename,jbool append):JOutputStreamWriter(getClazz(),new JFileOutputStream(filename,append)){
        }

        JFileWriter::JFileWriter(JFile* f,jbool append):JOutputStreamWriter(getClazz(),new JFileOutputStream(f,append)){
        }

        JFileWriter::~JFileWriter(){
        }
    }
}
