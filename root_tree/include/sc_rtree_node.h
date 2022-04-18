
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

#ifndef _SC_ALGORITHM_ROOT_TREE_SC_RTREE_NODE_H_
#define _SC_ALGORITHM_ROOT_TREE_SC_RTREE_NODE_H_

#include <memory>

namespace sc
{
    namespace algorithm
    {
        namespace rtree
        {
            struct SCRTreeNodeBase
            {
                typedef SCRTreeNodeBase* ptr_base;
                SCRTreeNodeBase()
                {}
                ~SCRTreeNodeBase();
                
                ptr_base parent_;
                ptr_base left_child_;
                ptr_base right_brother_;
            };

            template<typename Value>
            struct SCRTreeNode : SCRTreeNodeBase {
                typedef SCRTreeNode<Value>* link_type;
                Value value_field;
            };
        } // namespace rtree
        
    } // namespace algorithm
    
} // namespace sc


#endif //!_SC_ALGORITHM_ROOT_TREE_SC_RTREE_NODE_H_
