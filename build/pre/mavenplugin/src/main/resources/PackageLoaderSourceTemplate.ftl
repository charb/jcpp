#include "${model.headerIncludePath}"
#include "${model.packageHeaderIncludePath}"

${model.name}::${model.name}(){
}

JPackage* ${model.name}::getPackage(){
    return ${model.packageName}::getPackage();
}

${model.name}::~${model.name}(){
}

static JPackageLoader* packageLoader = null;

extern "C" JCPP_EXPORT JPackageLoader* getPackageLoader(){
    if (packageLoader==null){
        packageLoader=new ${model.name}();
    }
    return packageLoader;
}
