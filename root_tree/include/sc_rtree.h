/*
 * @Author: jack.hu 
 * @Date: 2022-04-17 22:17:13 
 * @Last Modified by: jack.hu
 * @Last Modified time: 2022-04-18 09:58:52
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
                uint32_t max_deepth_;

                link_type GetNode() {return (link_type)(::operator new((size_type)(sizeof(root_tree_node))));}
                void PutNode(link_type p) {
                    ::operator delete(p);
                    node_count_--;
                }

                link_type CreateNode(const value_type& x) {
                    link_type tmp = CreateNode();
                    tmp->value_field = x;
                    return tmp;
                }

                link_type CreateNode() {
                    link_type tmp = GetNode();
                    new(tmp) root_tree_node();
                    node_count_++;
                    return tmp;
                }

            public:
                typedef SCRTreeIterator<value_type, referance, pointer> iterator;
            public:

                SCRTree() : node_count_(0), max_deepth_(0)
                {
                    head_ = CreateNode();
                }
                ~SCRTree() {
                    PutNode(head_);
                }

                iterator begin() {return head_->left_child_ ? iterator(link_type(head_->left_child_)) : iterator(head_);}
                iterator end() {return iterator(head_);}
                iterator find(const key_type& k) {
                    link_type f = __find(k);
                    if (f) return iterator(f);
                    return iterator(head_);
                }
                bool empty() {return NULL == head_->left_child_;}

                size_type size() {return node_count_ - 1;}
                uint32_t MaxDeepth() {return max_deepth_;}

                std::pair<iterator, bool> insert(const iterator& itr, const value_type& x) {
                    link_type parent_value = (link_type)itr.node;
                    return std::pair<iterator, bool>(__insert(parent_value, x), true);
                }
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

                iterator erase(const iterator& itr);
                iterator erase(const key_type& k);
                
            private:
                iterator __insert(base_ptr parent, const value_type& v);
                link_type __find(const key_type& k) {
                    return __find(k, head_);
                }

                link_type __find(const key_type& k, link_type c);
            };

            /**
             * @brief implement function
             * 
             * @tparam Key , this field storage the object key
             * @tparam Value , storage object type
             * @tparam KeyOfValue , this field storage the function that convet object to key.
             * @param parent , parent node
             * @param v , current object value
             * @return SCRTree<Key, Value, KeyOfValue>::iterator 
             */
            template<class Key, class Value, class KeyOfValue>
            typename SCRTree<Key, Value, KeyOfValue>::iterator 
            SCRTree<Key, Value, KeyOfValue>::__insert(base_ptr parent, const Value& v) {
                base_ptr c = parent->left_child_;
                if (!c)
                {
                    link_type x = CreateNode(v);
                    x->deepth_ = parent->deepth_ + 1;
                    x->parent_ = parent;

                    parent->left_child_ = x;

                    max_deepth_ = x->deepth_ > max_deepth_ ? x->deepth_ : max_deepth_;
                    return SCRTree<Key, Value, KeyOfValue>::iterator(x);
                }
                
                base_ptr pre = c;
                while (pre && pre->right_brother_)
                {
                    pre = pre->right_brother_;
                }
                link_type x = CreateNode(v);
                x->deepth_ = pre->deepth_;
                x->parent_ = parent;
                pre->right_brother_ = x;
                return SCRTree<Key, Value, KeyOfValue>::iterator(x);
            }

            template<class Key, class Value, class KeyOfValue>
            typename SCRTree<Key, Value, KeyOfValue>::link_type 
            SCRTree<Key, Value, KeyOfValue>::__find(const key_type& k, link_type c) {
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

            template<class Key, class Value, class KeyOfValue>
            typename SCRTree<Key, Value, KeyOfValue>::iterator
            SCRTree<Key, Value, KeyOfValue>::erase(const iterator& itr)
            {
                typedef typename SCRTree<Key, Value, KeyOfValue>::iterator itr_type;
                typedef typename SCRTree<Key, Value, KeyOfValue>::link_type lk_type;
                lk_type value = (lk_type)itr.node;
                lk_type ret;
                // 1. There is left child and right brother
                // 2. There is no left child, but there is right brother
                // 3. there is no left child and right brother

                lk_type p = (lk_type)value->parent_;
                if (value->left_child_)
                {
                    lk_type left_value = (lk_type)value->left_child_;
                    lk_type right_value = (lk_type)value->right_brother_;
                    left_value->parent_ = value->parent_;

                    if (p->left_child_ == value)
                    {
                        left_value->parent_ = p;
                        p->left_child_ = left_value;
                    }
                    else
                    {
                        lk_type pre_value = (lk_type)value->parent_->left_child_;
                        while (pre_value && pre_value->right_brother_ && pre_value->right_brother_ != value)
                        {
                            pre_value = (lk_type)pre_value->right_brother_;
                        }
                        left_value->parent_ = p;
                        pre_value->right_brother_ = left_value;
                    }

                    lk_type sub_right_value = left_value;
                    while (sub_right_value && sub_right_value->right_brother_)
                    {
                        sub_right_value = (lk_type)sub_right_value->right_brother_;
                    }
                    sub_right_value->right_brother_ = right_value;
                    
                    PutNode(value);
                    ret = left_value;
                }
                else if (value->right_brother_)
                {
                    lk_type right_value = (lk_type)value->right_brother_;

                    if (p->left_child_ == value)
                    {
                        p->left_child_ = right_value;
                    }
                    else
                    {
                        lk_type pre_value = (lk_type)p->left_child_;
                        while (pre_value && pre_value->right_brother_ && pre_value->right_brother_ != value)
                        {
                            pre_value = (lk_type)pre_value->right_brother_;
                        }
                        pre_value->right_brother_ = right_value;
                    }
                    PutNode(value);
                    ret = right_value;
                }
                else
                {
                    if (p->left_child_ == value)
                    {
                        p->left_child_ = NULL;
                    }
                    else
                    {
                        lk_type pre_value = (lk_type)p->left_child_;
                        while (pre_value && pre_value->right_brother_ && pre_value->right_brother_ != value)
                        {
                            pre_value = (lk_type)pre_value->right_brother_;
                        }
                        pre_value->right_brother_ = NULL;
                    }
                    PutNode(value);
                    ret = (lk_type)value->parent_;
                }
                return iterator(ret);
            }

            template<class Key, class Value, class KeyOfValue>
            typename SCRTree<Key, Value, KeyOfValue>::iterator
            SCRTree<Key, Value, KeyOfValue>::erase(const key_type& k)
            {
                typedef typename SCRTree<Key, Value, KeyOfValue>::iterator itr_type;
                itr_type itr = find(k);
                return itr_type(erase(itr));
            }
        } // namespace rtree
        
    } // namespace algorithm
    
} // namespace sc


#endif //!_SC_ALGORITHM_ROOT_TREE_SC_RTREE_H_
