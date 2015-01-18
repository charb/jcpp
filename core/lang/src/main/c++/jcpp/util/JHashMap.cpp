#include "jcpp/util/JHashMap.h"
#include "jcpp/lang/JClass.h"
#include "jcpp/util/JNoSuchElementException.h"
#include "jcpp/util/JConcurrentModificationException.h"
#include "jcpp/util/JAbstractSet.h"
#include "jcpp/io/JInvalidObjectException.h"
#include "jcpp/lang/JVoid.h"
#include "jcpp/lang/JIllegalArgumentException.h"
#include "jcpp/lang/JInternalError.h"
#include "jcpp/lang/JSystem.h"
#include "jcpp/lang/JInteger.h"
#include "jcpp/lang/JIllegalStateException.h"
#include "jcpp/lang/reflect/JConstructor.h"
#include "jcpp/lang/reflect/JModifier.h"

using namespace jcpp::lang;
using namespace jcpp::lang::reflect;

namespace jcpp{
    namespace util{

        static jint DEFAULT_INITIAL_CAPACITY = 16;

        static jint MAXIMUM_CAPACITY = 1 << 30;

        static jfloat DEFAULT_LOAD_FACTOR = 0.75f;

        static jint UNTREEIFY_THRESHOLD = 6;

        static jint TREEIFY_THRESHOLD = 8;

        static jint MIN_TREEIFY_CAPACITY = 64;

        static jcpp::lang::JClass* nodeClazz = null;

        // @Class(canonicalName="java.util.HashMap$Node", simpleName="HashMap$Node");
        class JNode : public JMap::JEntry, public JObject{
            public:
                jint hash;
                JObject* key;
                JObject* value;
                JNode* next;

                JNode(jint hash,JObject* key,JObject* value,JNode* next):JObject(getClazz()){
                    this->hash=hash;
                    this->key=key;
                    this->value=value;
                    this->next=next;
                }

                JNode(jint hash,JObject* key,JObject* value,JNode* next,jcpp::lang::JClass* _class):JObject(_class){
                    this->hash=hash;
                    this->key=key;
                    this->value=value;
                    this->next=next;
                }

                static jcpp::lang::JClass* getClazz();

                virtual JObject* getKey() {
                    return key;
                }

                virtual JObject* getValue() {
                    return value;
                }

                virtual JObject* setValue(JObject* newValue) {
                    JObject* oldValue = value;
                    value=newValue;
                    return oldValue;
                }

                virtual jbool equals(JObject* o) {
                    if (o==this){
                        return true;
                    }
                    if (!(JEntry::getClazz()->isAssignableFrom(o->getClass()))){
                        return false;
                    }
                    JEntry* e = dynamic_cast<JEntry*>(o);
                    JObject* k1 = getKey();
                    JObject* k2 = e->getKey();
                    if (k1 == k2 || (k1 != null && k1->equals(k2))) {
                        JObject* v1 = getValue();
                        JObject* v2 = e->getValue();
                        if (v1 == v2 || (v1 != null && v1->equals(v2))){
                            return true;
                        }
                    }
                    return false;
                }

                virtual jint hashCode() {
                    return (getKey()==null   ? 0 : getKey()->hashCode()) ^ (getValue()==null ? 0 : getValue()->hashCode());
                }

                virtual JString* toString() {
                    JStringBuilder* builder=new JStringBuilder();
                    if (getKey()==null){
                        builder->append("null=");
                    }else{
                        builder->append(getKey()->toString())->append("=");
                    }
                    if (getValue()==null){
                        builder->append("null");
                    }else{
                        builder->append(getValue()->toString());
                    }
                    return builder->toString();
                }
        };


        // @Class(canonicalName="java.util.HashMap$TreeNode", simpleName="HashMap$TreeNode");
        class JTreeNode : public JNode {
        public:
            JNode* before;
            JNode* after;
            JTreeNode* parent;
            JTreeNode* left;
            JTreeNode* right;
            JTreeNode* prev;
            jbool red;

            JTreeNode(jint hash, JObject* key, JObject* val, JNode* next):JNode(hash, key, val, next,getClazz()) {
                before=null;
                after=null;
                parent=null;
                left=null;
                right=null;
                prev=null;
                red=false;
            }

            static jcpp::lang::JClass* getClazz();

            virtual JTreeNode* root() {
                JTreeNode* p=null;
                JTreeNode* r = this;
                for (;;) {
                    if ((p = r->parent) == null){
                        return r;
                    }
                    r = p;
                }
            }

            static void moveRootToFront(JPrimitiveObjectArray* tab, JTreeNode* nroot) {
                jint n=0;
                if (nroot != null && tab != null && (n = tab->size()) > 0) {
                    jint index = (n - 1) & nroot->hash;
                    JTreeNode* first = dynamic_cast<JTreeNode*>(tab->get(index));
                    if (nroot != first) {
                        JNode* rn=null;
                        tab->set(index, nroot);
                        JTreeNode* rp = nroot->prev;
                        if ((rn = nroot->next) != null){
                            (dynamic_cast<JTreeNode*>(rn))->prev = rp;
                        }
                        if (rp != null){
                            rp->next = rn;
                        }
                        if (first != null){
                            first->prev = nroot;
                        }
                        nroot->next = first;
                        nroot->prev = null;
                    }
                    if (!checkInvariants(nroot)){
                        throw new JInternalError();
                    }
                }
            }

            virtual JTreeNode* find(jint h, JObject* k, jcpp::lang::JClass* kc) {
                JTreeNode* p = this;
                do {
                    jint ph=0;
                    jint dir=0;
                    JObject* pk=null;
                    JTreeNode* pl = p->left;
                    JTreeNode* pr = p->right;
                    JTreeNode* q = null;

                    if ((ph = p->hash) > h){
                        p = pl;
                    
                    }else if (ph < h){
                        p = pr;
                    
                    }else if ((pk = p->key) == k || (k != null && k->equals(pk))){
                        return p;

                    }else if (pl == null){
                        p = pr;
                    
                    }else if (pr == null){
                        p = pl;
                    
                    }else if ((kc != null || (kc = JHashMap::comparableClassFor(k)) != null) && (dir = JHashMap::compareComparables(kc, k, pk)) != 0){
                        p = (dir < 0) ? pl : pr;
                    
                    }else if ((q = pr->find(h, k, kc)) != null){
                        return q;
                    
                    }else{
                        p = pl;
                    }

                } while (p != null);
                return null;
            }

            virtual JTreeNode* getTreeNode(jint h, JObject* k) {
                return ((parent != null) ? root() : this)->find(h, k, null);
            }

            static jint tieBreakOrder(JObject* a, JObject* b) {
                jint d=0;
                if (a == null || b == null || (d = a->getClass()->getName()->compareTo(b->getClass()->getName())) == 0){
                    d = (JSystem::identityHashCode(a) <= JSystem::identityHashCode(b) ?-1 : 1);
                }
                return d;
            }

            virtual void treeify(JPrimitiveObjectArray* tab) {
                JTreeNode* nroot = null;
                JTreeNode* next = null;

                for (JTreeNode* x = this; x != null; x = next) {
                    next = dynamic_cast<JTreeNode*>(x->next);
                    x->left = null;
                    x->right = null;
                    
                    if (nroot == null) {
                        x->parent = null;
                        x->red = false;
                        nroot = x;

                    }else {
                        JObject* k = x->key;
                        jint h = x->hash;
                        jcpp::lang::JClass* kc = null;

                        for (JTreeNode* p = nroot;;) {
                            jint dir=0;
                            jint ph=0;
                            JObject* pk = p->key;

                            if ((ph = p->hash) > h){
                                dir = -1;
                            
                            }else if (ph < h){
                                dir = 1;
                            
                            }else if ((kc == null && (kc = JHashMap::comparableClassFor(k)) == null) || (dir = JHashMap::compareComparables(kc, k, pk)) == 0){
                                dir = tieBreakOrder(k, pk);
                            }

                            JTreeNode* xp = p;
                            if ((p = (dir <= 0) ? p->left : p->right) == null) {
                                x->parent = xp;
                                if (dir <= 0){
                                    xp->left = x;
                                
                                }else{
                                    xp->right = x;
                                }
                                nroot = balanceInsertion(nroot, x);
                                break;
                            }
                        }
                    }
                }
                moveRootToFront(tab, nroot);
            }

            virtual JNode* untreeify(JHashMap* map) {
                JNode* hd = null;
                JNode* tl = null;
                for (JNode* q = this; q != null; q = q->next) {
                    JNode* p = map->replacementNode(q, null);
                    if (tl == null){
                        hd = p;
                    
                    }else{
                        tl->next = p;
                    }
                    tl = p;
                }
                return hd;
            }

            virtual JTreeNode* putTreeVal(JHashMap* map, JPrimitiveObjectArray* tab,jint h, JObject* k, JObject* v) {
                jcpp::lang::JClass* kc = null;
                jbool searched = false;
                JTreeNode* nroot = (parent != null) ? root() : this;
                for (JTreeNode* p = nroot;;) {
                    jint dir=0;
                    jint ph=0;
                    JObject* pk=null;

                    if ((ph = p->hash) > h){
                        dir = -1;
                    
                    }else if (ph < h){
                        dir = 1;
                    
                    }else if ((pk = p->key) == k || (k != null && k->equals(pk))){
                        return p;
                    
                    }else if ((kc == null && (kc = JHashMap::comparableClassFor(k)) == null) || (dir = JHashMap::compareComparables(kc, k, pk)) == 0) {
                        if (!searched) {
                            JTreeNode* q=null;
                            JTreeNode* ch=null;
                            searched = true;
                            if (((ch = p->left) != null && (q = ch->find(h, k, kc)) != null) || ((ch = p->right) != null && (q = ch->find(h, k, kc)) != null)){
                                return q;
                            }
                        }
                        dir = tieBreakOrder(k, pk);
                    }

                    JTreeNode* xp = p;
                    if ((p = (dir <= 0) ? p->left : p->right) == null) {
                        JNode* xpn = xp->next;
                        JTreeNode* x = map->newTreeNode(h, k, v, xpn);
                        if (dir <= 0){
                            xp->left = x;
                        }else{
                            xp->right = x;
                        }
                        xp->next = x;
                        x->parent = x->prev = xp;
                        if (xpn != null){
                            (dynamic_cast<JTreeNode*>(xpn))->prev = x;
                        }
                        moveRootToFront(tab, balanceInsertion(nroot, x));
                        return null;
                    }
                }
            }

            virtual void removeTreeNode(JHashMap* map, JPrimitiveObjectArray* tab,jbool movable) {
                jint n=0;
                if (tab == null || (n = tab->size()) == 0){
                    return;
                }
                jint index = (n - 1) & hash;
                JTreeNode* first = dynamic_cast<JTreeNode*>(tab->get(index));
                JTreeNode* nroot = first;
                JTreeNode* rl = null;
                JTreeNode* succ = dynamic_cast<JTreeNode*>(next);
                JTreeNode* pred = prev;

                if (pred == null){
                    first = succ;
                    tab->set(index,first) ;
                
                }else{
                    pred->next = succ;
                }

                if (succ != null){
                    succ->prev = pred;
                }

                if (first == null){
                    return;
                }

                if (nroot->parent != null){
                    nroot = nroot->root();
                }

                if (nroot == null || nroot->right == null || (rl = nroot->left) == null || rl->left == null) {
                    tab->set(index, first->untreeify(map));
                    return;
                }
                
                JTreeNode* p = this;
                JTreeNode* pl = left;
                JTreeNode* pr = right;
                JTreeNode* replacement = null;

                if (pl != null && pr != null) {
                    JTreeNode* s = pr;
                    JTreeNode* sl = null;

                    while ((sl = s->left) != null){
                        s = sl;
                    }
                    jbool c = s->red; 
                    s->red = p->red; 
                    p->red = c;

                    JTreeNode* sr = s->right;
                    JTreeNode* pp = p->parent;
                    if (s == pr) {
                        p->parent = s;
                        s->right = p;

                    }else {
                        JTreeNode* sp = s->parent;
                        if ((p->parent = sp) != null) {
                            if (s == sp->left){
                                sp->left = p;
                            }else{
                                sp->right = p;
                            }
                        }

                        if ((s->right = pr) != null){
                            pr->parent = s;
                        }
                    }

                    p->left = null;
                    if ((p->right = sr) != null){
                        sr->parent = p;
                    }

                    if ((s->left = pl) != null){
                        pl->parent = s;
                    }

                    if ((s->parent = pp) == null){
                        nroot = s;
                    
                    }else if (p == pp->left){
                        pp->left = s;
                    
                    }else{
                        pp->right = s;
                    }

                    if (sr != null){
                        replacement = sr;

                    }else{
                        replacement = p;
                    }

                }else if (pl != null){
                    replacement = pl;
                
                }else if (pr != null){
                    replacement = pr;
                
                }else{
                    replacement = p;
                }

                if (replacement != p) {
                    JTreeNode* pp = replacement->parent = p->parent;
                    if (pp == null){
                        nroot = replacement;
                    
                    }else if (p == pp->left){
                        pp->left = replacement;
                    
                    }else{
                        pp->right = replacement;
                    }
                    p->left = p->right = p->parent = null;
                }

                JTreeNode* r = p->red ? nroot : balanceDeletion(nroot, replacement);

                if (replacement == p) {
                    JTreeNode* pp = p->parent;
                    p->parent = null;
                    if (pp != null) {
                        if (p == pp->left){
                            pp->left = null;
                        
                        }else if (p == pp->right){
                            pp->right = null;
                        }
                    }
                }
                if (movable){
                    moveRootToFront(tab, r);
                }
            }

            virtual void split(JHashMap* map, JPrimitiveObjectArray* tab, jint index, jint bit) {
                JTreeNode* b = this;
                JTreeNode* loHead = null;
                JTreeNode* loTail = null;
                JTreeNode* hiHead = null;
                JTreeNode* hiTail = null;
                jint lc = 0;
                jint hc = 0;
                JTreeNode* next = null;

                for (JTreeNode* e = b ; e != null; e = next) {
                    next = dynamic_cast<JTreeNode*>(e->next);
                    e->next = null;
                    if ((e->hash & bit) == 0) {
                        if ((e->prev = loTail) == null){
                            loHead = e;
                        
                        }else{
                            loTail->next = e;
                        }
                        loTail = e;
                        ++lc;

                    }else {
                        if ((e->prev = hiTail) == null){
                            hiHead = e;
                        
                        }else{
                            hiTail->next = e;
                        }
                        hiTail = e;
                        ++hc;
                    }
                }

                if (loHead != null) {
                    if (lc <= UNTREEIFY_THRESHOLD){
                        tab->set(index,loHead->untreeify(map));
                    
                    }else {
                        tab->set(index,loHead);
                        if (hiHead != null){
                            loHead->treeify(tab);
                        }
                    }
                }

                if (hiHead != null) {
                    if (hc <= UNTREEIFY_THRESHOLD){
                        tab->set(index + bit, hiHead->untreeify(map));
                    
                    }else {
                        tab->set(index + bit, hiHead);
                        if (loHead != null){
                            hiHead->treeify(tab);
                        }
                    }
                }
            }

            static JTreeNode* rotateLeft(JTreeNode* nroot,JTreeNode* p) {
                JTreeNode* r=null;
                JTreeNode* pp=null;
                JTreeNode* rl=null;

                if (p != null && (r = p->right) != null) {

                    if ((rl = p->right = r->left) != null){
                        rl->parent = p;
                    }

                    if ((pp = r->parent = p->parent) == null){
                        (nroot = r)->red = false;
                    
                    }else if (pp->left == p){
                        pp->left = r;
                    
                    }else{
                        pp->right = r;
                    }

                    r->left = p;
                    p->parent = r;
                }
                return nroot;
            }

            static JTreeNode* rotateRight(JTreeNode* nroot,JTreeNode* p) {
                JTreeNode* l=null;
                JTreeNode* pp=null;
                JTreeNode* lr=null;

                if (p != null && (l = p->left) != null) {

                    if ((lr = p->left = l->right) != null){
                        lr->parent = p;
                    }

                    if ((pp = l->parent = p->parent) == null){
                        (nroot = l)->red = false;
                    
                    }else if (pp->right == p){
                        pp->right = l;
                    
                    }else{
                        pp->left = l;
                    }
                    l->right = p;
                    p->parent = l;
                }
                return nroot;
            }

            static JTreeNode* balanceInsertion(JTreeNode* nroot,JTreeNode* x) {
                x->red = true;
                JTreeNode* xp=null;
                JTreeNode* xpp=null;
                JTreeNode* xppl=null;
                JTreeNode* xppr=null;

                for (;;) {
                    if ((xp = x->parent) == null) {
                        x->red = false;
                        return x;

                    }else if (!xp->red || (xpp = xp->parent) == null){
                        return nroot;
                    }

                    if (xp == (xppl = xpp->left)) {

                        if ((xppr = xpp->right) != null && xppr->red) {
                            xppr->red = false;
                            xp->red = false;
                            xpp->red = true;
                            x = xpp;

                        }else {
                            if (x == xp->right) {
                                nroot = rotateLeft(nroot, x = xp);
                                xpp = (xp = x->parent) == null ? null : xp->parent;
                            }

                            if (xp != null) {
                                xp->red = false;
                                if (xpp != null) {
                                    xpp->red = true;
                                    nroot = rotateRight(nroot, xpp);
                                }
                            }
                        }

                    }else {
                        if (xppl != null && xppl->red) {
                            xppl->red = false;
                            xp->red = false;
                            xpp->red = true;
                            x = xpp;
                        
                        }else {
                            if (x == xp->left) {
                                nroot = rotateRight(nroot, x = xp);
                                xpp = (xp = x->parent) == null ? null : xp->parent;
                            }
                            if (xp != null) {
                                xp->red = false;
                                if (xpp != null) {
                                    xpp->red = true;
                                    nroot = rotateLeft(nroot, xpp);
                                }
                            }
                        }
                    }
                }
            }

            static JTreeNode* balanceDeletion(JTreeNode* nroot,JTreeNode* x) {
                JTreeNode* xp=null;
                JTreeNode* xpl=null;
                JTreeNode* xpr=null;

                for (;;)  {
                    if (x == null || x == nroot){
                        return nroot;
                    
                    }else if ((xp = x->parent) == null) {
                        x->red = false;
                        return x;
                    
                    }else if (x->red) {
                        x->red = false;
                        return nroot;
                    
                    }else if ((xpl = xp->left) == x) {

                        if ((xpr = xp->right) != null && xpr->red) {
                            xpr->red = false;
                            xp->red = true;
                            nroot = rotateLeft(nroot, xp);
                            xpr = (xp = x->parent) == null ? null : xp->right;
                        }

                        if (xpr == null){
                            x = xp;
                        
                        }else {
                            JTreeNode* sl = xpr->left;
                            JTreeNode* sr = xpr->right;

                            if ((sr == null || !sr->red) &&(sl == null || !sl->red)) {
                                xpr->red = true;
                                x = xp;

                            }else {
                                if (sr == null || !sr->red) {
                                    if (sl != null){
                                        sl->red = false;
                                    }
                                    xpr->red = true;
                                    nroot = rotateRight(nroot, xpr);
                                    xpr = (xp = x->parent) == null ? null : xp->right;
                                }

                                if (xpr != null) {
                                    xpr->red = (xp == null) ? false : xp->red;
                                    if ((sr = xpr->right) != null){
                                        sr->red = false;
                                    }
                                }

                                if (xp != null) {
                                    xp->red = false;
                                    nroot = rotateLeft(nroot, xp);
                                }
                                x = nroot;
                            }
                        }

                    }else {
                        if (xpl != null && xpl->red) {
                            xpl->red = false;
                            xp->red = true;
                            nroot = rotateRight(nroot, xp);
                            xpl = (xp = x->parent) == null ? null : xp->left;
                        }

                        if (xpl == null){
                            x = xp;
                        
                        }else {
                            JTreeNode* sl = xpl->left;
                            JTreeNode* sr = xpl->right;

                            if ((sl == null || !sl->red) && (sr == null || !sr->red)) {
                                xpl->red = true;
                                x = xp;

                            }else {
                                if (sl == null || !sl->red) {
                                    if (sr != null){
                                        sr->red = false;
                                    }
                                    xpl->red = true;
                                    nroot = rotateLeft(nroot, xpl);
                                    xpl = (xp = x->parent) == null ? null : xp->left;
                                }

                                if (xpl != null) {
                                    xpl->red = (xp == null) ? false : xp->red;
                                    if ((sl = xpl->left) != null){
                                        sl->red = false;
                                    }
                                }
                                if (xp != null) {
                                    xp->red = false;
                                    nroot = rotateRight(nroot, xp);
                                }
                                x = nroot;
                            }
                        }
                    }
                }
            }

            static jbool checkInvariants(JTreeNode* t) {
                JTreeNode* tp = t->parent;
                JTreeNode* tl = t->left;
                JTreeNode* tr = t->right;
                JTreeNode* tb = t->prev;
                JTreeNode* tn = dynamic_cast<JTreeNode*>(t->next);

                if (tb != null && tb->next != t){
                    return false;
                }
                if (tn != null && tn->prev != t){
                    return false;
                }
                if (tp != null && t != tp->left && t != tp->right){
                    return false;
                }
                if (tl != null && (tl->parent != t || tl->hash > t->hash)){
                    return false;
                }
                if (tr != null && (tr->parent != t || tr->hash < t->hash)){
                    return false;
                }
                if (t->red && tl != null && tl->red && tr != null && tr->red){
                    return false;
                }
                if (tl != null && !checkInvariants(tl)){
                    return false;
                }
                if (tr != null && !checkInvariants(tr)){
                    return false;
                }
                return true;
            }
        };

        JNode* JHashMap::newNode(jint hash, JObject* key, JObject* value, JNode* next) {
            return new JNode(hash, key, value, next);
        }

        JNode* JHashMap::replacementNode(JNode* p, JNode* next) {
            return new JNode(p->hash, p->key, p->value, next);
        }

        JTreeNode* JHashMap::newTreeNode(jint hash, JObject* key, JObject* value, JNode* next) {
            return new JTreeNode(hash, key, value, next);
        }

        JTreeNode* JHashMap::replacementTreeNode(JNode* p, JNode* next) {
            return new JTreeNode(p->hash, p->key, p->value, next);
        }

        void JHashMap::reinitialize() {
            table = null;
            modCount=0;
            threshold->set(0);
            isize = 0;
        }

        void JHashMap::afterNodeAccess(JNode* p) {
        }

        void JHashMap::afterNodeInsertion(jbool evict) {
        }

        void JHashMap::afterNodeRemoval(JNode* p) {
        }

        jint JHashMap::hash(JObject* key) {
            return (key == null) ? 0 : key->hashCode();
        }

        jcpp::lang::JClass* JHashMap::comparableClassFor(JObject* x) {
            if (x->isInstanceOf(JComparable::getClazz())) {
                return x->getClass();
            }
            return null;
        }

        jint JHashMap::compareComparables(jcpp::lang::JClass* kc, JObject* k, JObject* x) {
            return (x == null ? 0 : ( dynamic_cast<JComparable*>(k))->compareTo(x) );
        }

        jint JHashMap::tableSizeFor(jint cap) {
            jint n = cap - 1;
            n |= n >> 1;
            n |= n >> 2;
            n |= n >> 4;
            n |= n >> 8;
            n |= n >> 16;
            return (n < 0) ? 1 : (n >= MAXIMUM_CAPACITY) ? MAXIMUM_CAPACITY : n + 1;
        }

        JHashMap::JHashMap():JAbstractMap(getClazz()){
            table=null;
            isize=0;
            modCount=0;
            this->loadFactor =new JPrimitiveFloat(DEFAULT_LOAD_FACTOR);
            this->threshold =new JPrimitiveInt(0);
        }

        JHashMap::JHashMap(jint initialCapacity, jfloat loadFactor):JAbstractMap(getClazz()){
            table=null;
            isize=0;
            modCount=0;
            if (initialCapacity < 0){
                throw new JIllegalArgumentException();
            }
            if (initialCapacity > MAXIMUM_CAPACITY){
                initialCapacity = MAXIMUM_CAPACITY;
            }
            if (loadFactor <= 0){
                throw new JIllegalArgumentException();
            }
            this->loadFactor=new JPrimitiveFloat(loadFactor);
            this->threshold =new JPrimitiveInt(tableSizeFor(initialCapacity));
        }

        JHashMap::JHashMap(JMap* m):JAbstractMap(getClazz()){
            table=null;
            isize=0;
            modCount=0;
            this->loadFactor =new JPrimitiveFloat(DEFAULT_LOAD_FACTOR);
            this->threshold =new JPrimitiveInt(0);
            putMapEntries(m, false);
        }

        void JHashMap::putMapEntries(JMap* m, jbool evict) {
            jint s = m->size();
            if (s > 0) {
                if (table == null) {
                    jfloat ft = ((jfloat)s / loadFactor->get()) + 1.0F;
                    jint t = ((ft < (jfloat)MAXIMUM_CAPACITY) ? (jint)ft : MAXIMUM_CAPACITY);
                    if (t > threshold->get()){
                        threshold->set(tableSizeFor(t));
                    }
                
                }else if (s > threshold->get()){
                    resize();
                }

                JSet* set=m->entrySet();
                for (JIterator* it = set->iterator(); it->hasNext() ; ) {
                    JMap::JEntry* e=dynamic_cast<JMap::JEntry*>(it->next());
                    JObject* key = e->getKey();
                    JObject* value = e->getValue();
                    putVal(hash(key), key, value, false, evict);
                }
            }
        }

        jint JHashMap::size(){
            return isize;
        }

        jbool JHashMap::isEmpty(){
            return isize==0;
        }

        JObject* JHashMap::get(JObject* key){
            JNode* e=getNode(hash(key), key);
            return (e == null ? null : e->getValue());
        }

        JNode* JHashMap::getNode(jint hash, JObject* key) {
            JPrimitiveObjectArray* tab=null;
            JNode* first=null;
            JNode* e=null; 
            jint n=0; 
            JObject* k=null;

            if ((tab = table) != null && (n = tab->size()) > 0 && (first = dynamic_cast<JNode*>(tab->get((n - 1) & hash))) != null) {
                if (first->hash == hash && ((k = first->key) == key || (key != null && key->equals(k)))){
                    return first;
                }

                if ((e = first->next) != null) {
                    if (first->getClass()==JTreeNode::getClazz()){
                        return (dynamic_cast<JTreeNode*>(first))->getTreeNode(hash, key);
                    }
                    do {
                        if (e->hash == hash && ((k = e->key) == key || (key != null && key->equals(k)))){
                            return e;
                        }
                    } while ((e = e->next) != null);
                }
            }
            return null;
        }

        jbool JHashMap::containsKey(JObject* key){
            return getNode(hash(key), key) != null;
        }

        JObject* JHashMap::put(JObject* key, JObject* value){
            return putVal(hash(key), key, value, false, true);
        }

        JObject* JHashMap::putVal(jint hash, JObject* key, JObject* value, jbool onlyIfAbsent,jbool evict) {
            JPrimitiveObjectArray* tab=null;
            JNode* p=null; 
            jint n=0;
            jint i=0;

            if ((tab = table) == null || (n = tab->size()) == 0){
                n = (tab = resize())->size();
            }

            if ((p = dynamic_cast<JNode*>(tab->get(i = (n - 1) & hash))) == null){
                tab->set(i, newNode(hash, key, value, null));

            }else {
                JNode* e=null; 
                JObject* k=null;

                if (p->hash == hash && ((k = p->key) == key || (key != null && key->equals(k)))){
                    e = p;

                }else if (p->getClass()==JTreeNode::getClazz()){
                    e = (dynamic_cast<JTreeNode*>(p))->putTreeVal(this, tab, hash, key, value);

                }else {
                    for (jint binCount = 0; ; ++binCount) {
                        if ((e = p->next) == null) {
                            p->next = newNode(hash, key, value, null);
                            if (binCount >= TREEIFY_THRESHOLD - 1){
                                treeifyBin(tab, hash);
                            }
                            break;
                        }
                        if (e->hash == hash && ((k = e->key) == key || (key != null && key->equals(k)))){
                            break;
                        }
                        p = e;
                    }
                }

                if (e != null) {
                    JObject* oldValue = e->value;
                    if (!onlyIfAbsent || oldValue == null){
                        e->value = value;
                    }
                    afterNodeAccess(e);
                    return oldValue;
                }
            }
            ++modCount;
            if (++isize > threshold->get()){
                resize();
            }
            afterNodeInsertion(evict);
            return null;
        }

        JPrimitiveObjectArray* JHashMap::resize() {
            JPrimitiveObjectArray* oldTab = table;
            jint oldCap = (oldTab == null) ? 0 : oldTab->size();
            jint oldThr = threshold->get();
            jint newCap=0;
            jint newThr = 0;

            if (oldCap > 0) {
                if (oldCap >= MAXIMUM_CAPACITY) {
                    threshold->set(JInteger::MAX_VALUE);
                    return oldTab;

                } else if ((newCap = oldCap << 1) < MAXIMUM_CAPACITY && oldCap >= DEFAULT_INITIAL_CAPACITY){
                    newThr = oldThr << 1;
                }

            }else if (oldThr > 0){
                newCap = oldThr;
            
            }else {
                newCap = DEFAULT_INITIAL_CAPACITY;
                newThr = (jint)(DEFAULT_LOAD_FACTOR * DEFAULT_INITIAL_CAPACITY);
            }

            if (newThr == 0) {
                jfloat ft = (jfloat)newCap * loadFactor->get();
                newThr = (newCap < MAXIMUM_CAPACITY && ft < (jfloat)MAXIMUM_CAPACITY ? (jint)ft : JInteger::MAX_VALUE);
            }

            threshold->set(newThr);

            JPrimitiveObjectArray* newTab = new JPrimitiveObjectArray(JNode::getClazz(),newCap);
            table = newTab;
            if (oldTab != null) {
                for (jint j = 0; j < oldCap; ++j) {
                    JNode* e=null;
                    if ((e = dynamic_cast<JNode*>(oldTab->get(j))) != null) {
                        oldTab->set(j, null);

                        if (e->next == null){
                            newTab->set(e->hash & (newCap - 1), e);
                        
                        }else if (e->getClass()==JTreeNode::getClazz()) {
                            (dynamic_cast<JTreeNode*>(e))->split(this, newTab, j, oldCap);
                        
                        }else {
                            JNode* loHead = null;
                            JNode* loTail = null;
                            JNode* hiHead = null;
                            JNode* hiTail = null;
                            JNode* next = null;

                            do {
                                next = e->next;
                                if ((e->hash & oldCap) == 0) {
                                    if (loTail == null){
                                        loHead = e;
                                    }else{
                                        loTail->next = e;
                                    }
                                    loTail = e;

                                }else {
                                    if (hiTail == null){
                                        hiHead = e;
                                    }else{
                                        hiTail->next = e;
                                    }
                                    hiTail = e;
                                }
                            } while ((e = next) != null);

                            if (loTail != null) {
                                loTail->next = null;
                                newTab->set(j,loHead);
                            }

                            if (hiTail != null) {
                                hiTail->next = null;
                                newTab->set(j + oldCap, hiHead);
                            }
                        }
                    }
                }
            }
            return newTab;
        }

        void JHashMap::treeifyBin(JPrimitiveObjectArray* tab, jint hash) {
            jint n=0;
            jint index=0;
            JNode* e=null;

            if (tab == null || (n = tab->size()) < MIN_TREEIFY_CAPACITY){
                resize();
            
            }else if ((e = dynamic_cast<JNode*>(tab->get(index = ((n - 1) & hash)))) != null) {
                JTreeNode* hd = null;
                JTreeNode* tl = null;
                do {
                    JTreeNode* p = replacementTreeNode(e, null);
                    if (tl == null){
                        hd = p;
                    
                    }else {
                        p->prev = tl;
                        tl->next = p;
                    }

                    tl = p;
                } while ((e = e->next) != null);
                tab->set(index,hd);
                if (hd != null){
                    hd->treeify(tab);
                }
            }
        }

        void JHashMap::putAll(JMap* m) {
            putMapEntries(m, true);
        }

        JObject* JHashMap::remove(JObject* key){
            JNode* e= removeNode(hash(key), key, null, false, true);
            return (e == null ? null : e->value);
        }

        JNode* JHashMap::removeNode(jint hash, JObject* key, JObject* value,jbool matchValue, jbool movable) {
            JPrimitiveObjectArray* tab=null;
            JNode* p=null; 
            jint n=0;
            jint index=0;

            if ((tab = table) != null && (n = tab->size()) > 0 && (p = dynamic_cast<JNode*>(tab->get(index = ((n - 1) & hash)))) != null) {
                JNode* node = null;
                JNode* e=null; 
                JObject* k=null; 
                JObject* v=null;

                if (p->hash == hash && ((k = p->key) == key || (key != null && key->equals(k)))){
                    node = p;
                
                }else if ((e = p->next) != null) {
                    if (p->getClass()==JTreeNode::getClazz()){
                        node = (dynamic_cast<JTreeNode*>(p))->getTreeNode(hash, key);
                    
                    }else {
                        do {
                            if (e->hash == hash && ((k = e->key) == key || (key != null && key->equals(k)))) {
                                node = e;
                                break;
                            }
                            p = e;
                        } while ((e = e->next) != null);
                    }
                }

                if (node != null && (!matchValue || (v = node->value) == value || (value != null && value->equals(v)))) {
                    if (node->getClass()==JTreeNode::getClazz()){
                        (dynamic_cast<JTreeNode*>(node))->removeTreeNode(this, tab, movable);

                    }else if (node == p){
                        tab->set(index,node->next);
                    
                    }else{
                        p->next = node->next;
                    }

                    ++modCount;
                    --isize;
                    afterNodeRemoval(node);
                    return node;
                }
            }
            return null;
        }

        void JHashMap::clear(){
            JPrimitiveObjectArray* tab;
            modCount++;
            if ((tab = table) != null && isize > 0) {
                isize = 0;
                for (jint i = 0; i < tab->size(); ++i){
                    tab->set(i,null);
                }
            }
        }

        jbool JHashMap::containsValue(JObject* value){
            JPrimitiveObjectArray*  tab=null;
            JObject* v=null;
            if ((tab = table) != null && isize > 0) {
                for (jint i = 0; i < tab->size(); ++i) {
                    for (JNode* e = dynamic_cast<JNode*>(tab->get(i)); e != null; e = e->next) {
                        if ((v = e->value) == value || (value != null && value->equals(v))){
                            return true;
                        }
                    }
                }
            }
            return false;
        }

        JHashMap* JHashMap::clone(){
            return new JHashMap(this);
        }

        // @Class(canonicalName="java.util.HashMap$HashIterator", simpleName="HashMap$HashIterator");
        class JHashIterator : public JObject, public JIterator {
        protected:
            JHashMap* hashMap;
            JNode* next;
            JNode* current;
            jint expectedModCount;
            jint index;
            
            JHashIterator(jcpp::lang::JClass* _class,JHashMap* hashMap):JObject(_class) {
                this->hashMap=hashMap;
                expectedModCount = hashMap->modCount;
                JPrimitiveObjectArray* t = hashMap->table;
                current = next = null;
                index = 0;
                if (t != null && hashMap->size() > 0) {
                    do {
                    } while (index < t->size() && (next = dynamic_cast<JNode*>(t->get(index++))) == null);
                }
            }

        public:
            static jcpp::lang::JClass* getClazz();

            JHashIterator(JHashMap* hashMap):JObject(getClazz()) {
                this->hashMap=hashMap;
                expectedModCount = hashMap->modCount;
                JPrimitiveObjectArray* t = hashMap->table;
                current = next = null;
                index = 0;
                if (t != null && hashMap->size() > 0) {
                    do {
                    } while (index < t->size() && (next = dynamic_cast<JNode*>(t->get(index++))) == null);
                }
            }

            virtual jbool hasNext() {
                return next != null;
            }

            virtual JNode* nextNode() {
                JPrimitiveObjectArray* t=null;
                JNode* e = next;
                if (hashMap->modCount != expectedModCount){
                    throw new JConcurrentModificationException();
                }
                if (e == null){
                    throw new JNoSuchElementException();
                }
                if ((next = (current = e)->next) == null && (t = hashMap->table) != null) {
                    do {
                    } while (index < t->size() && (next = dynamic_cast<JNode*>(t->get(index++))) == null);
                }
                return e;
            }

            virtual void remove() {
                JNode* p = current;
                if (p == null){
                    throw new JIllegalStateException();
                }
                if (hashMap->modCount != expectedModCount){
                    throw new JConcurrentModificationException();
                }
                current = null;
                JObject* key = p->key;
                hashMap->removeNode(JHashMap::hash(key), key, null, false, false);
                expectedModCount = hashMap->modCount;
            }
        };

        // @Class(canonicalName="java.util.HashMap$ValueIterator", simpleName="HashMap$ValueIterator");
        class JValueIterator : public JHashIterator {
        public:
            static jcpp::lang::JClass* getClazz();

            JValueIterator(JHashMap* hashMap):JHashIterator(getClazz(),hashMap){
            }

            virtual JObject* next() {
                return nextNode()->value;
            }
        };

        // @Class(canonicalName="java.util.HashMap$KeyIterator", simpleName="HashMap$KeyIterator");
        class JKeyIterator : public JHashIterator {
        public:
            static jcpp::lang::JClass* getClazz();

            JKeyIterator(JHashMap* hashMap):JHashIterator(getClazz(),hashMap){
            }

            virtual JObject* next() {
                return nextNode()->key;
            }
        };

        // @Class(canonicalName="java.util.HashMap$EntryIterator", simpleName="HashMap$EntryIterator");
        class JEntryIterator : public JHashIterator{
        public:
            static jcpp::lang::JClass* getClazz();

            JEntryIterator(JHashMap* hashMap):JHashIterator(getClazz(),hashMap){
            }

            virtual JObject* next() {
                return nextNode();
            }
        };

        JIterator* JHashMap::newKeyIterator(){
            return new JKeyIterator(this);
        }

        JIterator* JHashMap::newValueIterator(){
            return new JValueIterator(this);
        }

        JIterator* JHashMap::newEntryIterator(){
            return new JEntryIterator(this);
        }

        // @Class(canonicalName="java.util.HashMap$KeySet", simpleName="HashMap$KeySet");
        class JHashMapKeySetImpl : public JAbstractSet {
        protected:
            JHashMap* map;
        public:
            static jcpp::lang::JClass* getClazz();

            JHashMapKeySetImpl(JHashMap* map):JAbstractSet(getClazz()){
                this->map=map;
            }

            virtual JIterator* iterator() {
                return map->newKeyIterator();
            }

            virtual jint size() {
                return map->isize;
            }

            virtual jbool contains(JObject* o) {
                return map->containsKey(o);
            }

            virtual jbool remove(JObject* o) {
                return map->remove(o) != null;
            }

            virtual void clear() {
                map->clear();
            }
        };

        JSet* JHashMap::keySet(){
            return new JHashMapKeySetImpl(this);
        }

        // @Class(canonicalName="java.util.HashMap$Values", simpleName="HashMap$Values");
        class JHashMapValues : public JAbstractCollection {
        protected:
            JHashMap* map;
        public:
            static jcpp::lang::JClass* getClazz();

            JHashMapValues(JHashMap* map):JAbstractCollection(getClazz()){
                this->map=map;
            }

            virtual JIterator* iterator() {
                return map->newValueIterator();
            }

            virtual jint size() {
                return map->isize;
            }

            virtual jbool contains(JObject* o) {
                return map->containsValue(o);
            }

            virtual void clear() {
                map->clear();
            }
        };

        JCollection* JHashMap::values(){
            return new JHashMapValues(this);
        }

        // @Class(canonicalName="java.util.HashMap$EntrySet", simpleName="HashMap$EntrySet");
        class JHashMapEntrySetImpl : public JAbstractSet{
        protected:
            JHashMap* map;
        public:
            static jcpp::lang::JClass* getClazz();

            JHashMapEntrySetImpl(JHashMap* map):JAbstractSet(getClazz()){
                this->map=map;
            }

            virtual JIterator* iterator() {
                return map->newEntryIterator();
            }

            virtual jbool contains(JObject* o) {
                if (!(JMap::JEntry::getClazz()->isAssignableFrom(o->getClass()))){
                    return false;
                }
                JMap::JEntry* e = dynamic_cast<JMap::JEntry*>(o);
                JObject* key = e->getKey();
                JNode* candidate = map->getNode(JHashMap::hash(key), key);
                return candidate != null && candidate->equals(dynamic_cast<JObject*>(e));
            }

            virtual jbool remove(JObject* o) {
                if (!(JMap::JEntry::getClazz()->isAssignableFrom(o->getClass()))){
                    return false;
                }
                JMap::JEntry* e = dynamic_cast<JMap::JEntry*>(o);
                JObject* key = e->getKey();
                JObject* value = e->getValue();
                return map->removeNode(JHashMap::hash(key), key, value, true, true) != null;
            }

            virtual jint size() {
                return map->isize;
            }

            virtual void clear() {
                map->clear();
            }
        };

        JSet* JHashMap::entrySet(){
            return new JHashMapEntrySetImpl(this);
        }

        jint JHashMap::capacity() {
            return (table != null) ? table->size() : (threshold->get() > 0) ? threshold->get() : DEFAULT_INITIAL_CAPACITY;
        }

        JPrimitiveObjectArray* JHashMap::serialPersistentFields = null;

        JPrimitiveObjectArray* JHashMap::getSerialPersistentFields(){
            if (serialPersistentFields==null){
                serialPersistentFields=new JPrimitiveObjectArray(JObjectStreamField::getClazz(),2);
                serialPersistentFields->set(0,new JObjectStreamField(new JString("threshold"),JPrimitiveInt::getClazz()));
                serialPersistentFields->set(1,new JObjectStreamField(new JString("loadFactor"),JPrimitiveFloat::getClazz()));
            }
            return serialPersistentFields;
        }
        
        void JHashMap::writeObject(JObjectOutputStream* out){
            JObjectOutputStream::JPutField* fields = out->putFields();
            fields->put(new JString("threshold"), threshold->get());
            fields->put(new JString("loadFactor"), loadFactor->get());
            out->writeFields();

            out->writeInt(capacity());
            out->writeInt(isize);

            JPrimitiveObjectArray* tab=null;
            if (isize > 0 && (tab = table) != null) {
                for (jint i = 0; i < tab->size(); ++i) {
                    for (JNode* e = dynamic_cast<JNode*>(tab->get(i)); e != null; e = e->next) {
                        out->writeObject(e->key);
                        out->writeObject(e->value);
                    }
                }
            }
        }

        void JHashMap::readObject(JObjectInputStream* in){
            JObjectInputStream::JGetField* fields = in->readFields();
            threshold->set(fields->get(new JString("threshold"), (jint)0));
            loadFactor->set(fields->get(new JString("loadFactor"), (jfloat)0));

            reinitialize();

            if (loadFactor <= 0){
                throw new JInvalidObjectException();
            }

            in->readInt();
            jint nb = in->readInt();
            if (nb < 0){
                throw new JInvalidObjectException();

            }else if (nb > 0) {
                jfloat f=(0.25f > loadFactor->get() ? 0.25f : loadFactor->get());
                jfloat lf = (f<4.0f ? f : 4.0f);
                jfloat fc = (jfloat)nb / lf + 1.0f;
                jint cap = ((fc < DEFAULT_INITIAL_CAPACITY) ? DEFAULT_INITIAL_CAPACITY : (fc >= MAXIMUM_CAPACITY) ? MAXIMUM_CAPACITY : tableSizeFor((jint)fc));
                jfloat ft = (jfloat)cap * lf;
                threshold->set(((cap < MAXIMUM_CAPACITY && ft < MAXIMUM_CAPACITY) ? (jint)ft : JInteger::MAX_VALUE));

                JPrimitiveObjectArray* tab = new JPrimitiveObjectArray(JNode::getClazz(),cap);
                table = tab;
                for (jint i = 0; i < nb; i++) {
                    JObject* key = in->readObject();
                    JObject* value = in->readObject();
                    putVal(hash(key), key, value, false, false);
                }
            }
        }

        JHashMap::~JHashMap(){
        }
    }
}

