#include "jcpp/util/JTreeMap.h"
#include "jcpp/util/JComparator.h"
#include "jcpp/util/JSet.h"
#include "jcpp/util/JNoSuchElementException.h"
#include "jcpp/util/JConcurrentModificationException.h"
#include "jcpp/util/JNavigableMap.h"
#include "jcpp/util/JNavigableSet.h"
#include "jcpp/util/JSortedSet.h"


#include "jcpp/lang/JIllegalArgumentException.h"
#include "jcpp/lang/JNullPointerException.h"
#include "jcpp/lang/JIllegalStateException.h"
#include "jcpp/lang/JPrimitiveInt.h"
#include "jcpp/lang/JComparable.h"


namespace jcpp{
	namespace util{

		//-------------------
		//     JTreeEntry
		//-------------------
		JTreeMap::JTreeEntry::JTreeEntry(JObject* key, JObject* value, JTreeEntry* parent): JObject(JTreeEntry::getClazz()){
			this->key = key;
			this->value = value;
			this->parent = parent;
			this->left = null;
			this->right = null;
			this->color = BLACK;
		}


		JObject* JTreeMap::JTreeEntry::getKey(){
			return key;
		}

		JObject* JTreeMap::JTreeEntry::getValue(){
			return value;
		}

		JObject* JTreeMap::JTreeEntry::setValue(JObject* value){
			JObject* oldValue = this->value;
			this->value = value;
			return oldValue;
		}

		jbool JTreeMap::JTreeEntry::equals(JObject* o){
			if(o == this){
				return true;
			}
			if(!(JMap::JEntry::getClazz()->isAssignableFrom(o->getClass()))){
				return false;
			}
			JMap::JEntry* e = dynamic_cast<JMap::JEntry*>(o);
			return JTreeMap::valEquals(key, e->getKey()) && JTreeMap::valEquals(value, e->getValue());
		}

		jint JTreeMap::JTreeEntry::hashCode(){
			jint keyHash = (key == null ? 0 : key->hashCode());
			jint valueHash = (value == null ? 0 : value->hashCode());
			return keyHash ^ valueHash;
		}

		JTreeMap::JTreeEntry::~JTreeEntry(){
		}


		//------------------------
		//	JPrivateEntryIterator
		//------------------------

		JTreeMap::JPrivateEntryIterator::JPrivateEntryIterator(JTreeEntry* first, JTreeMap* parent, JClass* clazz):JObject(clazz){
			this->parent = parent;
			expectedModCount = parent->modCount;
			lastReturned = null;
			next = first;
		}

		JTreeMap::JTreeEntry* JTreeMap::JPrivateEntryIterator::nextEntry(){
			JTreeEntry* e = next;
			if(e == null){
				throw new JNoSuchElementException();
			}
			if(parent->modCount != expectedModCount){
				throw new JConcurrentModificationException();
			}
			next = JTreeMap::successor(e);
			lastReturned = e;
			return e;
		}

		JTreeMap::JTreeEntry* JTreeMap::JPrivateEntryIterator::prevEntry(){
			JTreeEntry* e = next;
			if(e == null){
				throw new JNoSuchElementException();
			}
			if(parent->modCount != expectedModCount){
				throw new JConcurrentModificationException();
			}
			next = JTreeMap::predecessor(e);
			lastReturned = e;
			return e;
		}

		jbool JTreeMap::JPrivateEntryIterator::hasNext(){
			return next != null;
		}

		void JTreeMap::JPrivateEntryIterator::remove(){
			if(lastReturned == null){
				throw new JIllegalStateException();
			}
			if(parent->modCount != expectedModCount){
				throw new JConcurrentModificationException();
			}
			if(lastReturned->left != null && lastReturned->right != null){
				next = lastReturned;
			}
		}

		JTreeMap::JPrivateEntryIterator::~JPrivateEntryIterator(){
		}

		//----------------------
		//	JTreeEntryIterator
		//----------------------

		JTreeMap::JTreeEntryIterator::JTreeEntryIterator(JTreeEntry* first, JTreeMap* parent) : JPrivateEntryIterator(first,parent, JTreeEntryIterator::getClazz()){
			this->parent = parent;
		}

		JObject* JTreeMap::JTreeEntryIterator::next(){
			return nextEntry();
		}

		JTreeMap::JTreeEntryIterator::~JTreeEntryIterator(){
		}


		//-----------------------
		//	JTreeEntrySet
		//-----------------------

		JTreeMap::JTreeEntrySet::JTreeEntrySet(JTreeMap* parent):JAbstractSet(JTreeEntrySet::getClazz()){
			this->parent = parent;
		}

		JIterator* JTreeMap::JTreeEntrySet::iterator(){
			return new JTreeEntryIterator(parent->getFirstEntry(), parent);
		}

		jbool JTreeMap::JTreeEntrySet::contains(JObject* o){

			if(o == this){
				return true;
			}
			if((o == null) || !JTreeEntrySet::getClazz()->isAssignableFrom(o->getClass())){
				return false;
			}
			JMap::JEntry* entry = dynamic_cast<JMap::JEntry*>(o);
			JObject* value = entry->getValue();
			JTreeEntry* p = parent->getEntry(entry->getKey());
			return p != null && valEquals(p->getValue(), value);
		}

		jbool JTreeMap::JTreeEntrySet::remove(JObject* o){
			if((o == null) || !JTreeEntrySet::getClazz()->isAssignableFrom(o->getClass())){
				return false;
			}
			JMap::JEntry* entry = dynamic_cast<JMap::JEntry*>(o);
			JObject* value = entry->getValue();
			JTreeEntry* p = parent->getEntry(entry->getKey());
			if(p != null && valEquals(p->getValue(), value)){
				parent->deleteEntry(p);
				return true;
			}
			return false;
		}

		jint JTreeMap::JTreeEntrySet::size(){
			return parent->size();
		}

		void JTreeMap::JTreeEntrySet::clear(){
			parent->clear();
		}
		JTreeMap::JTreeEntrySet::~JTreeEntrySet(){
		}


		//-----------------------
		//	JTreeKeySet
		//-----------------------

//
		JTreeMap::JTreeKeySet::JTreeKeySet(JNavigableMap* map):JAbstractSet(JTreeKeySet::getClazz()){
			m = map;
		}

//		TODO: implement

		JIterator* JTreeMap::JTreeKeySet::iterator(){
			return null;
		}
		JIterator* JTreeMap::JTreeKeySet::descendingIterator(){
			return null;
		}
		jint JTreeMap::JTreeKeySet::size(){
			return null;
		}
		jbool JTreeMap::JTreeKeySet::isEmpty(){
			return null;
		}
		jbool JTreeMap::JTreeKeySet::contains(){
			return null;
		}
		void JTreeMap::JTreeKeySet::clear(){

		}
		JObject* JTreeMap::JTreeKeySet::lower(JObject* e){
			return null;
		}
		JObject* JTreeMap::JTreeKeySet::floor(JObject* e){
			return null;
		}
		JObject* JTreeMap::JTreeKeySet::ceiling(JObject* e){
			return null;
		}
		JObject* JTreeMap::JTreeKeySet::higher(JObject* e){
			return null;
		}
		JObject* JTreeMap::JTreeKeySet::first(){
			return null;
		}
		JObject* JTreeMap::JTreeKeySet::last(){
			return null;
		}
		JComparator* JTreeMap::JTreeKeySet::comparator(){
			return null;
		}
		JObject* JTreeMap::JTreeKeySet::pollFirst(){
			return null;
		}
		JObject* JTreeMap::JTreeKeySet::pollLast(){
			return null;
		}
		jbool JTreeMap::JTreeKeySet::remove(JObject* o){
			return null;
		}
		JNavigableSet* JTreeMap::JTreeKeySet::subSet(JObject* fromElement, jbool fromInclusive, JObject* toElement, jbool toInclusive){
			return null;
		}
		JNavigableSet* JTreeMap::JTreeKeySet::headSet(JObject* toElement, jbool inclusive){
			return null;
		}
		JNavigableSet* JTreeMap::JTreeKeySet::tailSet(JObject* fromElement, jbool inclusive){
			return null;
		}
		JSortedSet* JTreeMap::JTreeKeySet::subSet(JObject* fromElement, JObject* toElement){
			return null;
		}
		JSortedSet* JTreeMap::JTreeKeySet::headSet(JObject* toElement){
			return null;
		}
		JSortedSet* JTreeMap::JTreeKeySet::tailSet(JObject* fromElement){
			return null;
		}
		JNavigableSet* JTreeMap::JTreeKeySet::descendingSet(){
			return null;
		}

		JTreeMap::JTreeKeySet::~JTreeKeySet(){
		}


		//-----------------------
		//	JTreeValues
		//-----------------------

		JTreeMap::JTreeValues::JTreeValues():JAbstractCollection(JTreeValues::getClazz()){
		}

		JIterator* JTreeMap::JTreeValues::iterator(){
			return null;
		}

		jbool JTreeMap::JTreeValues::contains(JObject* o){
			return false;
		}

		jbool JTreeMap::JTreeValues::remove(JObject* o){
			return false;
		}

		jint JTreeMap::JTreeValues::size(){
			return -1;
		}

		void JTreeMap::JTreeValues::clear(){

		}

		JTreeMap::JTreeValues::~JTreeValues(){
		}


		//-----------------------
		//	JTreeMap
		//-----------------------

		jbool JTreeMap::valEquals(JObject* o1, JObject* o2){
			return (o1 == null ? o2 == null : o1->equals(o2));
		}

		JTreeMap::JTreeEntry* JTreeMap::parentOf(JTreeEntry* p){
			return (p == null ? null : p->parent);
		}

		JTreeMap::JTreeEntry* JTreeMap::leftOf(JTreeEntry* p){
			return (p == null) ? null: p->left;
		}

		JTreeMap::JTreeEntry* JTreeMap::rightOf(JTreeEntry* p){
			return (p == null) ? null: p->right;
		}

		jbool JTreeMap::colorOf(JTreeEntry* p){
			return (p == null ? BLACK : p->color);
		}

		void JTreeMap::setColor(JTreeEntry* p, jbool c){
			if(p != null)
				p->color = c;
		}

		JTreeMap::JTreeEntry* JTreeMap::predecessor(JTreeEntry* t){
			if(t == null){
				return null;
			}
			else if(t->left != null){
				JTreeEntry* p = t->left;
				while(p->right != null){
					p = p->right;
				}
				return p;
			}
			else{
				JTreeEntry* p = t->parent;
				JTreeEntry* ch = t;
				while(p != null && ch == p->left){
					ch = p;
					p = p->parent;
				}
				return p;
			}
		}

		JTreeMap::JTreeEntry* JTreeMap::successor(JTreeEntry* t){
			if(t == null){
				return null;
			}
			else if(t->right != null){
				JTreeEntry* p = t->right;
				while(p->left != null){
					p = p->left;
				}
				return p;
			}
			else{
				JTreeEntry* p = t->parent;
				JTreeEntry* ch = t;
				while(p != null && ch == p->right){
					ch = p;
					p = p->parent;
				}
				return p;
			}
		}

		void JTreeMap::rotateLeft(JTreeEntry* p){
			if(p != null){
				JTreeEntry* r = p->right;
				p->right = r->left;
				if(r->left != null)
					r->left->parent = p;
					r->parent = p->parent;
				if(p->parent == null)
					root = r;
				else if(p->parent->left == p)
					p->parent->left = r;
				else
					p->parent->right = r;
				r->left = p;
				p->parent = r;
			}
		}

		void JTreeMap::rotateRight(JTreeEntry* p){
			if(p != null){
				JTreeEntry* l = p->left;
				p->left = l->right;
				if(l->right != null)
					l->right->parent = p;
				l->parent = p->parent;
				if(p->parent == null)
					root = l;
				else if(p->parent->right == p)
					p->parent->right = l;
				else
					p->parent->left = l;
				l->right = p;
				p->parent = l;
			}
		}


		void JTreeMap::fixAfterInsertion(JTreeEntry* x){
			x->color = RED;
			while(x != null && x != root && x->parent->color == RED){
				if(parentOf(x) == leftOf(parentOf(parentOf(x)))){
					JTreeEntry* y = rightOf(parentOf(parentOf(x)));
					if(colorOf(y) == RED){
						setColor(parentOf(x), BLACK);
						setColor(y, BLACK);
						setColor(parentOf(parentOf(x)), RED);
						x = parentOf(parentOf(x));
					}else{
						if(x == rightOf(parentOf(x))){
							x = parentOf(x);
							rotateLeft(x);
						}
						setColor(parentOf(x), BLACK);
						setColor(parentOf(parentOf(x)), RED);
						rotateRight(parentOf(parentOf(x)));
					}
				}else{
					JTreeEntry* y = leftOf(parentOf(parentOf(x)));
					if(colorOf(y) == RED){
						setColor(parentOf(x), BLACK);
						setColor(y, BLACK);
						setColor(parentOf(parentOf(x)), RED);
						x = parentOf(parentOf(x));
					}else{
						if(x == leftOf(parentOf(x))){
							x = parentOf(x);
							rotateRight(x);
						}
						setColor(parentOf(x), BLACK);
						setColor(parentOf(parentOf(x)), RED);
						rotateLeft(parentOf(parentOf(x)));
					}
				}
			}
			root->color = BLACK;
		}





		void JTreeMap::fixAfterDeletion(JTreeEntry* x){
			while(x != root && colorOf(x) == BLACK){
				if(x == leftOf(parentOf(x))){
					JTreeEntry* sib = rightOf(parentOf(x));

					if(colorOf(sib) == RED){
						setColor(sib, BLACK);
						setColor(parentOf(x), RED);
						rotateLeft(parentOf(x));
						sib = rightOf(parentOf(x));
					}

					if(colorOf(leftOf(sib)) == BLACK && colorOf(rightOf(sib)) == BLACK){
						setColor(sib, RED);
						x = parentOf(x);
					}
					else{
						if(colorOf(rightOf(sib)) == BLACK){
							setColor(leftOf(sib), BLACK);
							setColor(sib, RED);
							rotateRight(sib);
							sib = rightOf(parentOf(x));
						}
						setColor(sib, colorOf(parentOf(x)));
						setColor(parentOf(x), BLACK);
						setColor(rightOf(sib), BLACK);
						rotateLeft(parentOf(x));
						x = root;
					}
				}
				else{
					JTreeEntry* sib = leftOf(parentOf(x));

					if(colorOf(sib) == RED){
						setColor(sib, BLACK);
						setColor(parentOf(x), RED);
						rotateRight(parentOf(x));
						sib = leftOf(parentOf(x));
					}

					if(colorOf(rightOf(sib)) == BLACK && colorOf(leftOf(sib)) == BLACK){
						setColor(sib, RED);
						x = parentOf(x);
					}
					else{
						if(colorOf(leftOf(sib)) == BLACK){
							setColor(rightOf(sib), BLACK);
							setColor(sib, RED);
							rotateLeft(sib);
							sib = leftOf(parentOf(x));
						}
						setColor(sib, colorOf(parentOf(x)));
						setColor(parentOf(x), BLACK);
						setColor(leftOf(sib), BLACK);
						rotateRight(parentOf(x));
						x = root;
					}
				}
			}
			setColor(x, BLACK);
		}

		JTreeMap::JTreeEntry* JTreeMap::getFirstEntry(){
			JTreeEntry* p = root;
			if(p != null){
				while(p->left != null){
					p = p->left;
				}
			}
			return p;
		}

		JTreeMap::JTreeEntry* JTreeMap::getEntry(JObject* key){
			if(comparator != null){
				return getEntryUsingComparator(key);
			}
			if(key == null){
				throw new JNullPointerException();
			}
			JComparable* k = dynamic_cast<JComparable*>(key);
			JTreeEntry* p = root;
			while(p != null){
				int cmp = k->compareTo(p->key);
				if(cmp < 0)
					p = p->left;
				else if(cmp > 0)
					p = p->right;
				else
					return p;
			}
			return null;
		}

		JTreeMap::JTreeEntry* JTreeMap::getEntryUsingComparator(JObject* key){
			JObject* k = key;
			JComparator* cpr = comparator;

			if(cpr != null){
				JTreeEntry* p = root;
				while(p != null){
					int cmp = cpr->compare(k, p->key);
					if(cmp < 0)
						p = p->left;
					else if(cmp > 0)
						p = p->right;
					else
						return p;
				}
			}
			return null;
		}

		void JTreeMap::deleteEntry(JTreeEntry* p){
			modCount++;
			sz--;

			if(p->left != null && p->right != null){
				JTreeEntry* s = successor(p);
				p->key = s->key;
				p->value = s->value;
				p = s;
			}

			JTreeEntry* replacement = (p->left != null ? p->left : p->right);
			if(replacement != null){
				replacement->parent = p->parent;
				if(p->parent == null)
					root = replacement;
				else if(p == p->parent->left)
					p->parent->left = replacement;
				else
					p->parent->right = replacement;

				p->left = null; p->right = null; p->parent = null;

				if(p->color == BLACK)
					fixAfterDeletion(replacement);
			}
			else if(p->parent == null){
				root = null;
			}
			else{
				if(p->color == BLACK)
					fixAfterDeletion(p);
				if(p->parent != null){
					if(p == p->parent->left)
						p->parent->left = null;
					else if(p == p->parent->right)
						p->parent->right = null;
					p->parent = null;
				}
			}
		}


		JTreeMap::JTreeMap(JComparator* comparator):JAbstractMap(JTreeMap::getClazz()){
			this->comparator = comparator;
			this->root = null;
			this->sz = 0;
			this->modCount = 0;
			this->entrySetMemeber = null;
			this->navigableKeySetMember = null;
			this->valuesMember = null;
		}

		JComparator* JTreeMap::getComparator(){
			return comparator;
		}

		JObject* JTreeMap::put(JObject* key, JObject* value){
			JTreeMap::JTreeEntry* t = root;
			if(t == null){
				root = new JTreeMap::JTreeEntry(key, value, null);
				sz = 1;
				modCount++;
				return null;
			}
			int cmp;
			JTreeMap::JTreeEntry* parent;

			JComparator* cpr = comparator;
			if(cpr != null){
				do{
					parent = t;
					cmp = cpr->compare(key, t->getKey());
					if(cmp < 0)
						t = t->left;
					else if(cmp > 0)
						t = t->right;
					else
						return t->setValue(value);
				} while (t != null);
			}
			else{
				if(key == null)
					throw new JNullPointerException();
				JComparable* k = dynamic_cast<JComparable*>(key);
				do{
					parent = t;
					cmp = k->compareTo(t->key);
					if(cmp < 0)
						t = t->left;
					else if(cmp > 0)
						t = t->right;
					else
						return t->setValue(value);
				} while (t != null);
			}
			JTreeMap::JTreeEntry* e = new JTreeMap::JTreeEntry(key, value, parent);
			if(cmp < 0)
				parent->left = e;
			else
				parent->right = e;
			fixAfterInsertion(e);
			sz++;
			modCount++;
			return null;
		}

		JObject* JTreeMap::clone(){
			//TODO
			return null;
		}

		JSet* JTreeMap::entrySet(){
			JTreeEntrySet* es = entrySetMemeber;
			return (es != null) ? es : (entrySetMemeber = new JTreeEntrySet(this));
		}

		JSet* JTreeMap::keySet(){
			return navigableKeySet();
		}

		JCollection* JTreeMap::values(){
			JCollection* vs = valuesMember;
			return (vs != null) ? vs : (valuesMember = new JTreeValues());
		}

		jint JTreeMap::size(){
			return sz;
		}

		void JTreeMap::clear(){
			modCount++;
			sz = 0;
			root = null;
		}

		JNavigableSet* JTreeMap::navigableKeySet(){
			JTreeKeySet* nks = navigableKeySetMember;
			return (nks != null) ? nks : (navigableKeySetMember = new JTreeKeySet(this));
		}


		jbool JTreeMap::isEmpty(){
			return false;
		}
		jbool JTreeMap::containsKey(JObject* k){
			return false;
		}
		jbool JTreeMap::containsValue(JObject* v){
			return false;
		}
		JObject* JTreeMap::get(JObject* k){
			return false;
		}
		JObject* JTreeMap::remove(JObject* k){
			return false;
		}
		void JTreeMap::putAll(JMap* m){

		}
		jbool JTreeMap::equals(JObject* o){
			return false;
		}
		jint JTreeMap::hashCode(){
			return null;
		}
		JSortedMap* JTreeMap::subMap(JObject* fromElement, JObject* toElement){
			return null;
		}
		JObject* JTreeMap::firstKey(){
			return null;
		}
		JObject* JTreeMap::lastKey(){
			return null;
		}
		JMap::JEntry* JTreeMap::lowerEntry(JObject* k){
			return null;
		}
		JObject* JTreeMap::lowerKey(JObject* k){
			return null;
		}
		JMap::JEntry* JTreeMap::floorEntry(JObject* k){
			return null;
		}
		JObject* JTreeMap::floorKey(JObject* k){
			return null;
		}
		JMap::JEntry* JTreeMap::ceilingEntry(JObject* k){
			return null;
		}
		JObject* JTreeMap::ceilingKey(JObject* k){
			return null;
		}
		JMap::JEntry* JTreeMap::higherEntry(JObject* k){
			return null;
		}
		JObject* JTreeMap::higherKey(JObject* k){
			return null;
		}
		JMap::JEntry* JTreeMap::firstEntry(){
			return null;
		}
		JMap::JEntry* JTreeMap::lastEntry(){
			return null;
		}
		JMap::JEntry* JTreeMap::pollFirstEntry(){
			return null;
		}
		JMap::JEntry* JTreeMap::pollLastEntry(){
			return null;
		}
		JNavigableMap* JTreeMap::descendingMap(){
			return null;
		}
		JNavigableSet* JTreeMap::descendingKeySet(){
			return null;
		}
		JNavigableMap* JTreeMap::subMap(JObject* fromElement, jbool fromInclusive, JObject* toElement, jbool toInclusive){
			return null;
		}
		JSortedMap* JTreeMap::headMap(JObject* o){
			return null;
		}
		JNavigableMap* JTreeMap::headMap(JObject* o, jbool inclusive){
			return null;
		}
		JSortedMap* JTreeMap::tailMap(JObject* o){
			return null;
		}
		JNavigableMap* JTreeMap::tailMap(JObject* o, jbool inclusive){
			return null;
		}





		JTreeMap::~JTreeMap(){
		}
	}
}
