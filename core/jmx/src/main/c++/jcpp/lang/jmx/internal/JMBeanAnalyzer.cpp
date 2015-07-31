#include "jcpp/lang/jmx/internal/JMBeanAnalyzer.h"
#include "jcpp/lang/jmx/internal/JUtil.h"
#include "jcpp/util/JList.h"
#include "jcpp/util/JMap.h"

namespace jcpp{
	namespace lang{
		namespace jmx{
			namespace internal{

			//-------------
			//	MBeanVisitor
			//-------------

			JMBeanAnalyzer::JMBeanVisitor::~JMBeanVisitor(){
			}

			//------------
			//	JMethodOrder
			//------------
				JMBeanAnalyzer::JMethodOrder* JMBeanAnalyzer::JMethodOrder::instance = new JMethodOrder();

				JMBeanAnalyzer::JMethodOrder::JMethodOrder():JObject(JMethodOrder::getClazz()){
				}


				jint JMBeanAnalyzer::JMethodOrder::compare(JObject* a, JObject* b){
					return 0;
				}

				JMBeanAnalyzer::JMethodOrder::~JMethodOrder(){
				}

			//-----------
			//	JAttrMethods
			//-----------

				JMBeanAnalyzer::JAttrMethods::JAttrMethods():JObject(JAttrMethods::getClazz()){
				}
				JMBeanAnalyzer::JAttrMethods::~JAttrMethods(){
				}

			//-------------
			// Private
			//-------------
				JMBeanAnalyzer::JMBeanAnalyzer(JClass* mbeanInterface, JMBeanIntrospector* introspector):JObject(JMBeanAnalyzer::getClazz()){
					opMap = JUtil::newInsertionOrderMap();
					attrMap = JUtil::newInsertionOrderMap();
				}

				void JMBeanAnalyzer::initMaps(JClass* mbeanInterface, JMBeanIntrospector*introspector){

				}

			//-------------
			//	Protected
			//-------------
				JList* JMBeanAnalyzer::eliminateCovariantMethods(JPrimitiveObjectArray* methodArray){
					return null;
				}

				JMBeanAnalyzer* JMBeanAnalyzer::analyzer(JClass* mbeanInterface, JMBeanIntrospector* introspector){
					return null;
				}

				void JMBeanAnalyzer::visit(JMBeanVisitor* visitor){

				}
			//-----------
			//	Public
			//-----------

				JMBeanAnalyzer::~JMBeanAnalyzer(){
				}
			}
		}
	}
}
