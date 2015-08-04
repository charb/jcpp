/*
 * JTreeMap.h
 *
 *  Created on: Jul 21, 2015
 *      Author: mmaarouf
 */

#ifndef JTREEMAP_H_
#define JTREEMAP_H_

#include "jcpp/util/JAbstractMap.h"
#include "jcpp/util/JMap.h"
#include "jcpp/lang/JCloneable.h"
#include "jcpp/io/JSerializable.h"
#include "jcpp/util/JAbstractSet.h"
#include "jcpp/util/JNavigableSet.h"
#include "jcpp/util/JNavigableMap.h"


namespace jcpp{
	namespace lang{
		class JPrimitiveInt;
	}
}

using namespace jcpp::lang;

namespace jcpp{
	namespace util{

		class JComparator;
		class JSet;

		// @Class(canonicalName="java.util.TreeMap", simpleName="TreeMap");
		class JCPP_EXPORT JTreeMap: public JNavigableMap, public JAbstractMap, public JCloneable, public jcpp::io::JSerializable{
		private:

			static const jlong serialVersionUID = 919286545866124006LL;

			// @Class(canonicalName="java.util.Map$Entry", simpleName="Map$Entry");
			static class JCPP_EXPORT JTreeEntry :public JObject, public JMap::JEntry{

			public:
				JObject* key;
				JObject* value;
				JTreeEntry* left;
				JTreeEntry* right;
				JTreeEntry* parent;
				jbool color;


				static jcpp::lang::JClass* getClazz();

				JTreeEntry(JObject* key, JObject* value, JTreeEntry* parent);

				virtual JObject* getKey();

				virtual JObject* getValue();

				virtual JObject* setValue(JObject* value);

				virtual jbool equals(JObject* o);

				virtual jint hashCode();

				virtual ~JTreeEntry();
			};

			// @Class(canonicalName="java.util.TreeMap$KeySet", simpleName="TreeMap$KeySet");
			static class JTreeKeySet: public JAbstractSet, public JNavigableSet{
			private:
				JNavigableMap* m;
			protected:
				JTreeKeySet(JNavigableMap* map);
			public:

				virtual JIterator* iterator();
				virtual JIterator* descendingIterator();
				virtual jint size();
				virtual jbool isEmpty();
				virtual jbool contains();
				virtual void clear();
				virtual JObject* lower(JObject* e);
				virtual JObject* floor(JObject* e);
				virtual JObject* ceiling(JObject* e);
				virtual JObject* higher(JObject* e);
				virtual JObject* first();
				virtual JObject* last();
				virtual JComparator* comparator();
				virtual JObject* pollFirst();
				virtual JObject* pollLast();
				virtual jbool remove(JObject* o);
				virtual JNavigableSet* subSet(JObject* fromElement, jbool fromInclusive, JObject* toElement, jbool toInclusive);
				virtual JNavigableSet* headSet(JObject* toElement, jbool inclusive);
				virtual JNavigableSet* tailSet(JObject* fromElement, jbool inclusive);
				virtual JSortedSet* subSet(JObject* fromElement, JObject* toElement);
				virtual JSortedSet* headSet(JObject* toElement);
				virtual JSortedSet* tailSet(JObject* fromElement);
				virtual JNavigableSet* descendingSet();

				virtual jbool equals(JObject* o){
					return false;
				}
				virtual jint hashCode(){
					return 0;
				}


				static jcpp::lang::JClass* getClazz();
				virtual ~JTreeKeySet();

				friend class JTreeMap;
			};

			// @Class(canonicalName="java.util.TreeMap$PrivateEntryIterator", simpleName="TreeMap$PrivateEntryIterator");
			class JCPP_EXPORT JPrivateEntryIterator: public JObject, public JIterator{
			private:

				JTreeEntry* next;
				JTreeEntry* lastReturned;
				jint expectedModCount;

				JTreeMap* parent;
			protected:
				JPrivateEntryIterator(JTreeEntry* first, JTreeMap* parent, JClass* clazz);

				JTreeEntry* nextEntry();

				JTreeEntry* prevEntry();
			public:
				jbool hasNext();

				void remove();

				static jcpp::lang::JClass* getClazz();
				virtual ~JPrivateEntryIterator();

			};


			static const jbool RED = false;
			static const jbool BLACK = true;

			JComparator* comparator;

			/*TODO transient*/ JTreeMap::JTreeEntry* root;

			/*TODO transient*/ jint sz;




			static jbool valEquals(JObject* o1, JObject* o2);

			static JTreeEntry* parentOf(JTreeEntry* p);

			static JTreeEntry* leftOf(JTreeEntry* p);

			static JTreeEntry* rightOf(JTreeEntry* p);

			static jbool colorOf(JTreeEntry* p);

			static void setColor(JTreeEntry* p, jbool c);

			static JTreeEntry* predecessor(JTreeEntry* t);

			static JTreeEntry* successor(JTreeEntry* t);

			void rotateLeft(JTreeEntry* p);

			void rotateRight(JTreeEntry* p);

			void fixAfterInsertion(JTreeEntry* x);

			void fixAfterDeletion(JTreeEntry* x);

			JTreeEntry* getFirstEntry();

		protected:

			// @Class(canonicalName="java.util.TreeMap$EntryIterator", simpleName="TreeMap$EntryIterator");
			class JCPP_EXPORT JTreeEntryIterator: public JPrivateEntryIterator{
			private:
				JTreeMap* parent;
			protected:

			public:
				JTreeEntryIterator(JTreeEntry* first, JTreeMap* parent);

				virtual JObject* next();

				static jcpp::lang::JClass* getClazz();
				virtual ~JTreeEntryIterator();
			};

			class JCPP_EXPORT JTreeEntrySet: public JAbstractSet{
			private:
				JTreeMap* parent;
			public:


				JTreeEntrySet(JTreeMap* parent);

				virtual JIterator* iterator();

				virtual jbool contains(JObject* o);

				virtual jbool remove(JObject* o);

				virtual jint size();

				virtual void clear();

				static jcpp::lang::JClass* getClazz();
				virtual ~JTreeEntrySet();

				friend class JTreeEntryIterator;
			};


			// @Class(canonicalName="java.util.TreeMap$Values", simpleName="TreeMap$Values");
			class JCPP_EXPORT JTreeValues: public JAbstractCollection{
			protected:
				JTreeValues();
			public:
				virtual JIterator* iterator();

				virtual jint size();

				virtual jbool contains(JObject* o);

				virtual jbool remove(JObject* o);

				virtual void clear();

				static jcpp::lang::JClass* getClazz();
				virtual ~JTreeValues();

				friend class JTreeMap;
			};

			//-----------------------------------------------------------------------------
			/*TODO transient*/ jint modCount;

			/*TODO transient*/ JTreeEntrySet* entrySetMemeber;

			/*TODO transient*/ JTreeKeySet* navigableKeySetMember;

			JTreeEntry* getEntry(JObject* key);

			JTreeEntry* getEntryUsingComparator(JObject* key);

			void deleteEntry(JTreeEntry* p);


		public:

			JTreeMap(JComparator* comparator);

			JComparator* getComparator();

			JObject* put(JObject* key, JObject* value);

			virtual JObject* clone();

			virtual JSet* entrySet();

			virtual JSet* keySet();

			virtual JCollection* values();

			virtual jint size();

			virtual void clear();

			virtual JNavigableSet* navigableKeySet();

			virtual jbool isEmpty();
			virtual jbool containsKey(JObject* k);
			virtual jbool containsValue(JObject* v);
			virtual JObject* get(JObject* k);
			virtual JObject* remove(JObject* k);
			virtual void putAll(JMap* m);
			virtual jbool equals(JObject* o);
			virtual jint hashCode();
			virtual JSortedMap* subMap(JObject* fromElement, JObject* toElement);
			virtual JObject* firstKey();
			virtual JObject* lastKey();
			virtual JMap::JEntry* lowerEntry(JObject* k);
			virtual JObject* lowerKey(JObject* k);
			virtual JMap::JEntry* floorEntry(JObject* k);
			virtual JObject* floorKey(JObject* k);
			virtual JMap::JEntry* ceilingEntry(JObject* k);
			virtual JObject* ceilingKey(JObject* k);
			virtual JMap::JEntry* higherEntry(JObject* k);
			virtual JObject* higherKey(JObject* k);
			virtual JMap::JEntry* firstEntry();
			virtual JMap::JEntry* lastEntry();
			virtual JMap::JEntry* pollFirstEntry();
			virtual JMap::JEntry* pollLastEntry();
			virtual JNavigableMap* descendingMap();
			virtual JNavigableSet* descendingKeySet();
			virtual JNavigableMap* subMap(JObject* fromElement, jbool fromInclusive, JObject* toElement, jbool toInclusive);
			virtual JSortedMap* headMap(JObject* o);
			virtual JNavigableMap* headMap(JObject* o, jbool inclusive);
			virtual JSortedMap* tailMap(JObject* o);
			virtual JNavigableMap* tailMap(JObject* o, jbool inclusive);




			static jcpp::lang::JClass* getClazz();
			virtual ~JTreeMap();


			friend class JTreeEntrySet;
		};
	}
}



#endif /* JTREEMAP_H_ */
