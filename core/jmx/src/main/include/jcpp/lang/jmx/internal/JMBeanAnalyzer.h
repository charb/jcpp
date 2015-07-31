/*
 * JMBeanAnalyzer.h
 *
 *  Created on: Jul 30, 2015
 *      Author: mmaarouf
 */

#ifndef JMBEANANALYZER_H_
#define JMBEANANALYZER_H_

#include "jcpp/lang/JObject.h"
#include "jcpp/util/JComparator.h"


namespace jcpp{
	namespace util{
		class JList;
		class JMap;
	}
	namespace lang{
		class JPrimitiveObjectArray;
		namespace jmx{
			namespace internal{
				class JMBeanIntrospector;
			}
		}
	}
}

using namespace jcpp::util;

namespace jcpp{
	namespace lang{
		namespace jmx{
			namespace internal{

				class JCPP_EXPORT JMBeanAnalyzer:public JObject{
					class JMBeanVisitor;
				private:
					static class JCPP_EXPORT JMethodOrder: public JObject, public JComparator{
					private:
						JMethodOrder();
					public:
						static JMethodOrder* instance;
						jint compare(JObject* a, JObject* b);
						static JClass* getClazz();
						virtual ~JMethodOrder();
					};

					static class JCPP_EXPORT JAttrMethods:public JObject{
					protected:
						JObject* getter;
						JObject* setter;
						JAttrMethods();
					public:
						static JClass* getClazz();
						virtual ~JAttrMethods();
						friend class JMBeanAnalyzer;
					};
					JMap* opMap;
					JMap* attrMap;

					JMBeanAnalyzer(JClass* mbeanInterface, JMBeanIntrospector* introspector);

					void initMaps(JClass* mbeanInterface, JMBeanIntrospector*introspector);
				protected:
					static JList* eliminateCovariantMethods(JPrimitiveObjectArray* methodArray);

					static JMBeanAnalyzer* analyzer(JClass* mbeanInterface, JMBeanIntrospector* introspector);

					void visit(JMBeanAnalyzer::JMBeanVisitor* visitor);
				public:
					class JCPP_EXPORT JMBeanVisitor:public JInterface{
					public:
						virtual void visitAttribute(JString* attributeName, JObject* getter, JObject* setter) = 0;
						virtual void visitOperation(JString* operationName, JObject* operation) = 0;
						static JClass* getClazz();
						virtual ~JMBeanVisitor();
						friend class JMBeanAnalyzer;
					};



					static JClass* getClazz();
					virtual ~JMBeanAnalyzer();
				};
			}
		}
	}
}



#endif /* JMBEANANALYZER_H_ */
