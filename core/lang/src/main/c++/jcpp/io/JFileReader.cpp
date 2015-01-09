#include "jcpp/io/JFileReader.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/io/JFileInputStream.h"

namespace jcpp{
    namespace io{

        JFileReader::JFileReader(JString* name):JInputStreamReader(getClazz(),new JFileInputStream(name)){
        }

        JFileReader::JFileReader(JFile* f):JInputStreamReader(getClazz(),new JFileInputStream(f)){
        }

        JFileReader::~JFileReader(){
        }
    }
}
