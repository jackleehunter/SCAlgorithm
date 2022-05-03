
#include "sc_slink_iterator.h"

namespace sc
{
    namespace algorithm
    {
        namespace slinklist
        {
            void SCSlinklistIteratorBase::increment()
            {
                node_ = node_->next_;
            }
        } // namespace slinklist
        
    } // namespace algorithm
    
} // namespace sc
