#include "jcpp/util/JUTIL_PACKAGE.h"
#include "jcpp/JCPP_PACKAGE.h"
#include "jcpp/util/JAbstractCollection.h"
#include "jcpp/util/JAbstractList.h"
#include "jcpp/util/JAbstractMap.h"
#include "jcpp/util/JAbstractQueue.h"
#include "jcpp/util/JAbstractSet.h"
#include "jcpp/util/JArrayList.h"
#include "jcpp/util/JArrays.h"
#include "jcpp/util/JCollection.h"
#include "jcpp/util/JCollections.h"
#include "jcpp/util/JComparator.h"
#include "jcpp/util/JConcurrentModificationException.h"
#include "jcpp/util/JDictionary.h"
#include "jcpp/util/JEnumeration.h"
#include "jcpp/util/JHashMap.h"
#include "jcpp/util/JHashSet.h"
#include "jcpp/util/JHashtable.h"
#include "jcpp/util/JIterator.h"
#include "jcpp/util/JList.h"
#include "jcpp/util/JListIterator.h"
#include "jcpp/util/JMap.h"
#include "jcpp/util/JNoSuchElementException.h"
#include "jcpp/util/JProperties.h"
#include "jcpp/util/JQueue.h"
#include "jcpp/util/JRandomAccess.h"
#include "jcpp/util/JSet.h"
#include "jcpp/util/JStringTokenizer.h"
#include "jcpp/util/JTimerTask.h"
#include "jcpp/util/JTimer.h"
#include "jcpp/util/JVector.h"
#include "jcpp/lang/JString.h"

using namespace jcpp::util::concurrent;

namespace jcpp{
    namespace util{
        JUTIL_PACKAGE::JUTIL_PACKAGE():JPackage(new JString("jcpp.util"),JPackage::getClazz()){//better class
            addClass(JAbstractCollection::getClazz());
            addClass(JAbstractList::getClazz());
            addClass(JAbstractMap::getClazz());
            addClass(JAbstractQueue::getClazz());
            addClass(JAbstractSet::getClazz());
            addClass(JArrayList::getClazz());
            addClass(JArrays::getClazz());
            addClass(JCollection::getClazz());
            addClass(JCollections::getClazz());
            addClass(JComparator::getClazz());
            addClass(JConcurrentModificationException::getClazz());
            addClass(JDictionary::getClazz());
            addClass(JEnumeration::getClazz());
            addClass(JHashMap::getClazz());
            addClass(JHashSet::getClazz());
            addClass(JHashtable::getClazz());
            addClass(JIterator::getClazz());
            addClass(JList::getClazz());
            addClass(JListIterator::getClazz());
            addClass(JMap::getClazz());
            addClass(JNoSuchElementException::getClazz());
            addClass(JProperties::getClazz());
            addClass(JQueue::getClazz());
            addClass(JRandomAccess::getClazz());
            addClass(JSet::getClazz());
            addClass(JStringTokenizer::getClazz());
            addClass(JTimerTask::getClazz());
            addClass(JTimer::getClazz());
            addClass(JVector::getClazz());
        }

        JPackage* JUTIL_PACKAGE::getSuperPackage(){
            return JCPP_PACKAGE::getPackage();
        }

        JList* JUTIL_PACKAGE::getPackages(){
            if (packages->size()==0){
            }
            return packages;
        }

        static JUTIL_PACKAGE* jutil=null;

        JUTIL_PACKAGE* JUTIL_PACKAGE::getPackage(){
            if (jutil==null){
                jutil=new JUTIL_PACKAGE();
            }
            return jutil;
        }

        JUTIL_PACKAGE::~JUTIL_PACKAGE(){
        }
    }
}
