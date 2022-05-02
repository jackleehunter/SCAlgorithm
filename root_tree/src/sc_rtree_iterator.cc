
#include "sc_rtree_iterator.h"

namespace sc
{
    namespace algorithm
    {
        namespace rtree
        {
            void SCRTreeIteratorBase::increment()
            {
                if (node->left_child_)
                {
                    node = node->left_child_;
                }
                else if (node->right_brother_)
                {
                    node = node->right_brother_;
                }
                else
                {
                    node_base c = node->parent_;
                    node_base pre = node;
                    while (c && !c->right_brother_)
                    {
                        pre = c;
                        c = c->parent_;
                    }
                    node = c ? c->right_brother_ : pre;
                }
            }
        } // namespace rtree
        
    } // namespace algorithm
    
} // namespace sc
