#include "jcpp/lang/JClass.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/JString.h"
#include "jcpp/lang/JIllegalArgumentException.h"
#include "jcpp/lang/JIllegalAccessException.h"
#include "jcpp/lang/JInstantiationException.h"
#include "jcpp/lang/reflect/JModifier.h"

#include "jcpp/lang/JPrimitiveInt.h"
#include "jcpp/lang/JPrimitiveShort.h"
#include "jcpp/lang/JPrimitiveLong.h"
#include "jcpp/lang/JPrimitiveByte.h"
#include "jcpp/lang/JPrimitiveFloat.h"
#include "jcpp/lang/JPrimitiveDouble.h"
#include "jcpp/lang/JPrimitiveChar.h"
#include "jcpp/lang/JPrimitiveBoolean.h"
#include "jcpp/lang/JPrimitiveVoid.h"

<#list model.includes as include>
#include "${include}"
</#list>

using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

<#list model.usingNamespaceDeclarations as usingNamespaceDeclaration>
using namespace ${usingNamespaceDeclaration};
</#list>

<#list model.classes as class>
<#list class.namespaces as namespace>
namespace ${namespace} {
</#list>

	class JCPP_EXPORT ${class.simpleName}Class : public jcpp::lang::JClass 
	{
	protected:
		<#list class.constructors as constructor>
		static JObject* create${class.simpleName}${constructor_index}(jcpp::util::JList* args){
			<#if class.abstractClass>
			throw new JInstantiationException(new JString("Class ${class.className} is an abstract class!"));
			return null;
			<#else>
			if(args == null) {
				if (${constructor.argCount} != 0) {
					throw new JIllegalArgumentException(new JString("wrong argument count"));
				}
			} else {
				if (args->size()!=${constructor.argCount}) {
					throw new JIllegalArgumentException(new JString("wrong argument count"));
				}
			}
			return (JObject*)(new ${class.className}(<#list constructor.parameters as param><#if param.primitive>(dynamic_cast<${param.typeClass}*>(args->get(${param_index})))->get()<#else>dynamic_cast<${param.type}>(args->get(${param_index}))</#if><#if param_has_next>, </#if></#list>));
			</#if>
		}
		
		</#list>
		<#list class.fields as field>
		static JObject* staticGet${field.name}(JObject* object){
			<#if field.staticField>
			return (JObject*)(<#if field.primitive>new ${field.typeClass}(${class.simpleName}::${field.name})<#else>${class.simpleName}::${field.name}</#if>);
			<#else>
			${class.className}* o = dynamic_cast<${class.className}*>(object);
			return (JObject*)(<#if field.primitive>new ${field.typeClass}(o->${field.name})<#else>o->${field.name}</#if>);
			</#if>
		}
		
		static void staticSet${field.name}(JObject* object, JObject* value){
			<#if field.constField>
			throw new JIllegalAccessException(new JString("Field ${field.name} in Class ${class.simpleName} is Const!"));
			<#else>
			<#if field.staticField>
			${class.simpleName}::${field.name} = <#if field.primitive>(${field.type})<#else>dynamic_cast<${field.type}></#if>(value);
			<#else>
			${class.className}* o = dynamic_cast<${class.className}*>(object);
			o->${field.name} = <#if field.primitive>(${field.type})<#else>dynamic_cast<${field.type}></#if>(value);
			</#if>
			</#if>
		}
		
		static JObject** adr${field.name}(JObject* object){
			${class.className}* o = dynamic_cast<${class.className}*>(object);
			return <#if field.primitive>null<#else>(JObject**)&o->${field.name}</#if>;
		}
		</#list>
		
		<#list class.methods as method>
		static JObject* invoke${method.modifiedName}(JObject* object, JList* args){
			if(args == null) {
				if (${method.argCount} != 0) {
					throw new JIllegalArgumentException(new JString("wrong argument count"));
				}
			} else {
				if (args->size()!=${method.argCount}) {
					throw new JIllegalArgumentException(new JString("wrong argument count"));
				}
			}
			${class.className}* o = dynamic_cast<${class.className}*>(object);
			o->${method.name}(<#list method.parameters as param><#if param.primitive>(dynamic_cast<${param.typeClass}*>(args->get(${param_index})))->get()<#else>dynamic_cast<${param.type}>(args->get(${param_index}))</#if><#if param_has_next>, </#if></#list>);
			return null;
		}
		
		</#list>
	
	public:
		${class.simpleName}Class() : JClass() {
			this->canonicalName = new JString("${class.annotatedCanonicalName}");
			this->name = new JString("${class.annotatedCanonicalName}");
			this->simpleName = new JString("${class.annotatedSimpleName}");
			<#if class.serialVersionUIDFound>this->serialVersionUID = ${class.serialVersionUID?c}ULL;</#if>
		}
		
		virtual void initialize() {
			<#list class.constructors as constructor>
			JConstructor* cons${constructor_index} = addConstructor(new JConstructor(${class.className}::getClazz(), JModifier::PUBLIC, create${class.simpleName}${constructor_index}));
			<#list constructor.parameters as param>
			cons${constructor_index}->addParameterType(${param.typeClass}::getClazz());
			</#list>
			<#if constructor.publicMethod>
			cons${constructor_index}->setPublic();
			</#if>
			</#list>
			
			JField* jField = null;
			
			<#list class.fields as field>
			jField = new JField(new JString("${field.name}"),${field.typeClass}::getClazz(),this,staticGet${field.name},staticSet${field.name},adr${field.name});
			<#if field.staticField>
			jField->setStatic();
			</#if>
			<#if field.constField>
			jField->setFinal();
			</#if>
			<#if field.publicField>
			jField->setPublic();
			<#elseif field.privateField>
			jField->setPrivate();
			<#elseif field.protectedField>
			jField->setProtected();
			</#if>
			addField(jField);
			
			</#list>
			
			<#list class.methods as method>
			JMethod* m${method_index}=addMethod(new JMethod(new JString("${method.name}"),this,${method.returnType}::getClazz(),invoke${method.modifiedName}));
			<#list method.parameters as param>
			m${method_index}->addParameterType(${param.typeClass}::getClazz());
			</#list>
			<#if method.staticMethod>
			m${method_index}->setStatic();
			</#if>
			<#if method.publicMethod>
			m${method_index}->setPublic();
			<#elseif method.privateMethod>
			m${method_index}->setPrivate();
			<#elseif method.protectedMethod>
			m${method_index}->setProtected();
			</#if>

			</#list>
			
			<#list class.interfaces as interface>
			addInterface(${interface}::getClazz());
			</#list>
			
			<#list class.declaredClasses as declaredClass>
			addDeclaredClass(${declaredClass}::getClazz());
			</#list>
		}
		
		virtual JClass* getSuperclass() {
			return <#if class.hasSuperClass>${class.superClass}::getClazz()<#else>null</#if>;
		}
<#if class.hasDeclaringClass>		
		virtual JClass* getDeclaringClass() {
			return ${class.declaringClass}::getClazz();
		}
</#if>	
	};
	
	static jcpp::lang::JClass* ${class.simpleName}Clazz;
	
	jcpp::lang::JClass* ${class.className}::getClazz(){
        if (${class.simpleName}Clazz==null){
            ${class.simpleName}Clazz = new ${class.simpleName}Class();
        }
        return ${class.simpleName}Clazz;
    }

<#list class.namespaces as namespace>
}
</#list>

</#list>
