/*
 * @Author: jack.hu 
 * @Date: 2022-04-17 22:17:13 
 * @Last Modified by: jack.hu
 * @Last Modified time: 2022-04-17 22:26:13
 * 
 * This file is part of root_tree. It is only used for learning and 
 * cannot be used as production code
 * 
 */

#ifndef _SC_ALGORITHM_ROOT_TREE_SC_RTREE_H_
#define _SC_ALGORITHM_ROOT_TREE_SC_RTREE_H_

#include "sc_rtree_node.h"
#include "sc_rtree_iterator.h"

namespace sc
{
    namespace algorithm
    {
        namespace rtree
        {
            template<class Key, class Value, class KeyOfValue>
            class SCRTree
            {
            protected:
                typedef void* void_pointer;
                typedef SCRTreeNodeBase* base_ptr;
                typedef SCRTreeNode<Value> root_tree_node;
            public:
                typedef Key key_type;
                typedef Value value_type;
                typedef value_type* pointer;
                typedef const value_type* const_pointer;
                typedef value_type& referance;
                typedef const value_type& const_referance;
                typedef root_tree_node* link_type;
                typedef size_t size_type;
            protected:
                link_type head_;
                size_type node_count_;

                link_type GetNode() {return new SCRTreeNode<value_type>();}
                void PutNode(link_type p) {delete p;}

                link_type CreateNode(const value_type& x) {
                    link_type tmp = GetNode();
                    tmp->value_field = x;
                    return tmp;
                }

            public:
                typedef SCRTreeIterator<value_type, referance, pointer> iterator;
            public:

                SCRTree() : node_count_(0)
                {}
                ~SCRTree() {}

                iterator begin() {return iterator(head_->left_child_);}
                iterator end() {return iterator(head_);}
                iterator find(const key_type& k) {
                    return iterator(__find(k));
                }
                bool empty() {return NULL == head_->left_child_;}

                size_type size() {return 0;}
                std::pair<iterator, bool> insert(const key_type& parent_key, const value_type& x) {
                    // find parent node
                    link_type parent = __find(parent_key);
                    if (!parent)
                    {
                        return std::pair<iterator, bool>(iterator(), false);
                    }
                    // constructor X node
                    return std::pair<iterator, bool>(__insert(parent, x), true);
                }
            private:
                iterator __insert(base_ptr parent, const value_type& v);
                link_type __find(const key_type& k) {
                    return __find(k, head_);
                }

                link_type __find(const key_type& k, link_type c);
            };

            template<class Key, class Value, class KeyOfValue>
            typename SCRTree<Key, Value, KeyOfValue>::iterator SCRTree<Key, Value, KeyOfValue>::__insert(base_ptr parent, const Value& v) {
                base_ptr c = parent->left_child_;
                if (!c)
                {
                    link_type x = CreateNode(v);
                    parent->left_child_ = x;
                    return SCRTree<Key, Value, KeyOfValue>::iterator(x);
                }
                base_ptr pre = c;
                while (c)
                {
                    pre = c;
                    c = c->right_brother_;
                }
                link_type x = CreateNode(v);
                pre->right_brother_ = x;
                return SCRTree<Key, Value, KeyOfValue>::iterator(x);
            }

            template<class Key, class Value, class KeyOfValue>
            typename SCRTree<Key, Value, KeyOfValue>::link_type SCRTree<Key, Value, KeyOfValue>::__find(const key_type& k, link_type c) {
                if (!c) return c;

                if (KeyOfValue() (c->value_field) == k)
                {
                    return c;
                }
                
                link_type ret = __find(k, link_type(c->left_child_));
                if (ret)
                    return ret;

                return __find(k, link_type(c->right_brother_));
            }
        } // namespace rtree
        
    } // namespace algorithm
    
} // namespace sc


#endif //!_SC_ALGORITHM_ROOT_TREE_SC_RTREE_H_
