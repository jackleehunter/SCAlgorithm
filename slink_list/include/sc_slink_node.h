
#ifndef _SC_ALGORITHM_SC_LINK_LIST_SC_SLINK_NODE_H_
#define _SC_ALGORITHM_SC_LINK_LIST_SC_SLINK_NODE_H_

#include <memory>

namespace sc
{
    namespace algorithm
    {
        namespace slinklist
        {
            class SCSlinklistBaseNode 
            {
            public:
                typedef SCSlinklistBaseNode* ptr_base;
                SCSlinklistBaseNode() {}
                virtual ~SCSlinklistBaseNode() {
                    
                }

                ptr_base next_;
            };

            template<class Value>
            struct SCSlinklistNode : public SCSlinklistBaseNode
            {
                typedef Value value_type;
                typedef SCSlinklistNode<Value>* link_type;
                value_type value_field_;
            };
        } // namespace slinklist
        
    } // namespace algorithm
    
} // namespace sc


#endif //!_SC_ALGORITHM_SC_LINK_LIST_SC_SLINK_NODE_H_
