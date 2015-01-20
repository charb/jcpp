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

	class JCPP_EXPORT ${class.simpleName}Class : public <#if class.enumClass>JEnum::JEnumClass<#elseif class.proxyClass>JProxy::JProxyClass<#else>jcpp::lang::JClass</#if> 
	{
	protected:
		<#list class.constructors as constructor>
		static JObject* create${class.simpleName}${constructor_index}(jcpp::util::JList* args){
			<#if class.abstractClass>
			throw new JInstantiationException(new JString("Class ${class.className} is an abstract class!"));
			return null;
			<#else>
			<#if constructor.hasParameters>
			if((args == null) || (args->size() != ${constructor.argCount})) {
				throw new JIllegalArgumentException(new JString("wrong argument count"));
			}			
			</#if>
			return dynamic_cast<JObject*>( (new ${class.className}(<#list constructor.parameters as param><#if param.primitive>(dynamic_cast<${param.typeClass}*>(args->get(${param_index})))->get()<#else>dynamic_cast<${param.type}>(args->get(${param_index}))</#if><#if param_has_next>, </#if></#list>)) );
			</#if>
		}

		</#list>
		<#list class.fields as field>
		static JObject* staticGet${field.name}(JObject* object){
			<#if field.staticField>
			return dynamic_cast<JObject*>( (<#if field.primitive>new ${field.typeClass}(${class.className}::${field.name})<#else>${class.className}::${field.name}</#if>) );
			<#else>
			${class.className}* o = dynamic_cast<${class.className}*>(object);
			return dynamic_cast<JObject*>( (<#if field.primitive>new ${field.typeClass}(o->${field.name})<#else>o->${field.name}</#if>) );
			</#if>
		}
		
		static void staticSet${field.name}(JObject* object, JObject* value){
			<#if field.constField>
			throw new JIllegalAccessException(new JString("Field ${field.name} in Class ${class.className} is Const!"));
			<#else>
			<#if field.staticField>
			${class.className}::${field.name} = <#if field.primitive>(dynamic_cast<${field.typeClass}*>(value))->get()<#else>dynamic_cast<${field.type}>(value)</#if>;
			<#else>
			${class.className}* o = dynamic_cast<${class.className}*>(object);
			o->${field.name} = <#if field.primitive>(dynamic_cast<${field.typeClass}*>(value))->get()<#else>dynamic_cast<${field.type}>(value)</#if>;
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
			<#if method.hasParameters>
			if((args == null) || (args->size() != ${method.argCount})) {
				throw new JIllegalArgumentException(new JString("wrong argument count"));
			}			
			</#if>			
			<#if method.staticMethod>
				<#if method.voidReturnType>
			${class.className}::${method.name}(<#list method.parameters as param><#if param.primitive>(dynamic_cast<${param.typeClass}*>(args->get(${param_index})))->get()<#else>dynamic_cast<${param.type}>(args->get(${param_index}))</#if><#if param_has_next>, </#if></#list>);
			return null;
				<#elseif method.primitiveReturnType>
			return dynamic_cast<JObject*>( (new ${method.returnTypeClass}(${class.className}::${method.name}(<#list method.parameters as param><#if param.primitive>(dynamic_cast<${param.typeClass}*>(args->get(${param_index})))->get()<#else>dynamic_cast<${param.type}>(args->get(${param_index}))</#if><#if param_has_next>, </#if></#list>))) );
				<#else>
			return dynamic_cast<JObject*>( (${class.className}::${method.name}(<#list method.parameters as param><#if param.primitive>(dynamic_cast<${param.typeClass}*>(args->get(${param_index})))->get()<#else>dynamic_cast<${param.type}>(args->get(${param_index}))</#if><#if param_has_next>, </#if></#list>)) );
				</#if>	
			<#else>
			${class.className}* o = dynamic_cast<${class.className}*>(object);
				<#if method.voidReturnType>
			o->${method.name}(<#list method.parameters as param><#if param.primitive>(dynamic_cast<${param.typeClass}*>(args->get(${param_index})))->get()<#else>dynamic_cast<${param.type}>(args->get(${param_index}))</#if><#if param_has_next>, </#if></#list>);
			return null;
				<#elseif method.primitiveReturnType>
			return dynamic_cast<JObject*>( (new ${method.returnTypeClass}(o->${method.name}(<#list method.parameters as param><#if param.primitive>(dynamic_cast<${param.typeClass}*>(args->get(${param_index})))->get()<#else>dynamic_cast<${param.type}>(args->get(${param_index}))</#if><#if param_has_next>, </#if></#list>))) );
				<#else>
			return dynamic_cast<JObject*>( (o->${method.name}(<#list method.parameters as param><#if param.primitive>(dynamic_cast<${param.typeClass}*>(args->get(${param_index})))->get()<#else>dynamic_cast<${param.type}>(args->get(${param_index}))</#if><#if param_has_next>, </#if></#list>)) );
				</#if>
			</#if>
		}
		
		</#list>
	
	public:
		${class.simpleName}Class() : <#if class.enumClass>JEnum::JEnumClass()<#elseif class.proxyClass>JProxy::JProxyClass()<#else>JClass()</#if> {
			this->canonicalName = new JString("${class.annotatedCanonicalName}");
			this->name = new JString("${class.annotatedCanonicalName}");
			this->simpleName = new JString("${class.annotatedSimpleName}");
			<#if class.serialVersionUIDFound>this->serialVersionUID = ${class.serialVersionUID?c}ULL;</#if>
			<#if class.primitive>this->bIsPrimitive=true;</#if>
			<#if class.interfaceClass>this->bIsInterface=true;</#if>
			<#if class.proxyClass>bIsProxy=true;</#if> 
		}
		
		virtual void initialize() {
			<#if class.enumClass>JEnum::JEnumClass::initialize();</#if>
			
			<#list class.constructors as constructor>
			JConstructor* cons${constructor_index} = addConstructor(new JConstructor(${class.className}::getClazz(), JModifier::PUBLIC, create${class.simpleName}${constructor_index}));
			<#list constructor.parameters as param>
			cons${constructor_index}->addParameterType(${param.typeClass}::getClazz());
			</#list>
			<#if constructor.publicMethod>cons${constructor_index}->setPublic();</#if>
			</#list>
			
			JField* jField = null;
			<#list class.fields as field>
			jField = new JField(new JString("${field.name}"),${field.typeClass}::getClazz(),this,staticGet${field.name},staticSet${field.name},adr${field.name});
			<#if field.publicField>jField->setPublic();<#elseif field.privateField>jField->setPrivate();<#elseif field.protectedField>jField->setProtected();</#if>
			<#if field.staticField>jField->setStatic();</#if>
			<#if field.constField>jField->setFinal();</#if>
			<#if field.transientField>jField->setTransient();</#if>
			addField(jField);
			</#list>
			
			<#list class.methods as method>
			JMethod* m${method_index}=addMethod(new JMethod(new JString("${method.name}"),this,${method.returnTypeClass}::getClazz(),invoke${method.modifiedName}));
			<#list method.parameters as param>
			m${method_index}->addParameterType(${param.typeClass}::getClazz());
			</#list>
			<#if method.staticMethod>m${method_index}->setStatic();</#if>
			<#if method.publicMethod>m${method_index}->setPublic();<#elseif method.privateMethod>m${method_index}->setPrivate();<#elseif method.protectedMethod>m${method_index}->setProtected();</#if>
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
<#if class.enumClass>
    	virtual void fillEnumConstants(){
    		<#list class.enumConstants as enumConstant>
        	addEnumConstant(${class.className}::${enumConstant});
        	</#list>
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
