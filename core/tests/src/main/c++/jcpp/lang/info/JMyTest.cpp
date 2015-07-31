#include "jcpp/lang/info/JMyTest.h"

#include "jcpp/util/JArrayList.h"
#include "jcpp/lang/JInteger.h"
#include "jcpp/util/JList.h"

namespace jcpp{
	namespace lang{
		namespace info{
			JMyTest::JMyTest(): JTestCase(getClazz(), new JString("test")){
			}

			void JMyTest::test(){
				JList *list = new JArrayList();
				list->add(new JInteger(3));
				JInteger *integer = new JInteger(3);
				JAssert::assertEquals(integer, list->get(0));
			}

			JMyTest::~JMyTest(){
			}

		}
	}
}
