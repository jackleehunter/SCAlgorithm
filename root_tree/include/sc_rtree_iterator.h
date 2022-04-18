
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
 
#ifndef _SC_ALGORITHM_ROOT_TREE_SC_RTREE_ITERATOR_H_
#define _SC_ALGORITHM_ROOT_TREE_SC_RTREE_ITERATOR_H_

#include "sc_rtree_node.h"

namespace sc
{
    namespace algorithm
    {
        namespace rtree
        {
            struct SCRTreeIteratorBase {

                typedef SCRTreeNodeBase* node_base;
                node_base node;

                void increment();
                void decrement();
            };

            template<class Value, class Ref, class Ptr>
            struct SCRTreeIterator : SCRTreeIteratorBase {
                typedef Value value_type;
                typedef Ref referance;
                typedef Ptr pointer;
                typedef SCRTreeNode<Value>* link_type;
                typedef SCRTreeIterator<Value, Value&, Value*> iterator;
                typedef SCRTreeIterator<Value, const Value&, Value*> const_iterator;
                typedef SCRTreeIterator<Value, Ref, Ptr> self;

                SCRTreeIterator() {}
                SCRTreeIterator(link_type x) {node = x;}
                SCRTreeIterator(const iterator& it) {node = it.node;}

                referance operator* () const {return link_type(node)->value_field;}
                pointer operator-> () {return &(operator*());}
                self& operator++ () {
                    increment();
                    return *this;
                }
                self operator++ (int) {
                    self tmp = *this;
                    increment();
                    return tmp;
                }
                self& operator--() {
                    decrement();
                    return *this;
                }
                self operator--(int) {
                    self tmp = *this;
                    decrement();
                    return tmp;
                }
            };
        } // namespace rtree
        
    } // namespace algorithm
    
} // namespace sc


#endif //!_SC_ALGORITHM_ROOT_TREE_SC_RTREE_ITERATOR_H_
