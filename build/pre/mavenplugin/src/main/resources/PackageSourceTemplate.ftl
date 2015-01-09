#include "${model.headerIncludePath}"

<#list model.subClasses as subClass>
#include "${subClass.headerIncludePath}"
</#list>

<#list model.subPackages as subPackage>
#include "${subPackage.headerIncludePath}"
</#list>

<#if model.hasSuperPackage>#include "${model.superPackage.headerIncludePath}"</#if>

<#list model.namespaces as namespace>
namespace ${namespace}{
</#list>

	${model.name}::${model.name}():JPackage(new JString("${model.packageName}"), JPackage::getClazz()){
		<#list model.subClasses as subClass>
		addClass(${subClass.name}::getClazz());
		</#list>
	}

	JPackage* ${model.name}::getSuperPackage(){
		return <#if model.hasSuperPackage>${model.superPackage.qualifiedName}::getPackage()<#else>null</#if>;
	}
	
	JList* ${model.name}::getPackages() {
		<#if model.hasSubPackages>
		if (packages->size()==0){
			<#list model.subPackages as subPackage>
			addPackage(${subPackage.qualifiedName}::getPackage());
			</#list>
		}
		</#if>
		return packages;
	}

	static ${model.name}* pack = null;
	
	${model.name}* ${model.name}::getPackage(){
		if (pack == null){
			pack = new ${model.name}();
		}
		return pack;
	}
	
	${model.name}::~${model.name}(){
	}

<#list model.namespaces as namespace>
}
</#list>
