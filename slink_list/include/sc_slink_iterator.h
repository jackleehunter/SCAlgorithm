
#ifndef _SC_ALGORITHM_SLIN_LIST_SC_SLINK_ITERATOR_H_
#define _SC_ALGORITHM_SLIN_LIST_SC_SLINK_ITERATOR_H_

#include "sc_slink_node.h"

namespace sc
{
    namespace algorithm
    {
        namespace slinklist
        {

            struct SCSlinklistIteratorBase 
            {
                typedef SCSlinklistBaseNode* ptr_base;
                ptr_base node_;

                void increment();
            };
            
            template<class Value, class Ref, class Ptr>
            struct SCSlinklistIterator : public SCSlinklistIteratorBase
            {
                typedef Value value_type;
                typedef Ref referance;
                typedef Ptr pointer;
                typedef SCSlinklistNode<Value>* link_type;
                typedef SCSlinklistIterator<Value, Value&, Value*> iterator;
                typedef SCSlinklistIterator<Value, const Value&, Value*> const_iterator;
                typedef SCSlinklistIterator<Value, Ref, Ptr> self;
                SCSlinklistIterator() {}
                SCSlinklistIterator(link_type v) {
                    node_ = v;
                }

                referance operator* () {return link_type(node_)->value_field_;}
                pointer operator->() {return &(operator*());}

                self& operator= (const SCSlinklistIterator& other) {
                    node_ = other.node_;
                    return *this;
                }

                self& operator++ () {
                    increment();
                    return *this;
                }

                self&& operator++(int) {
                    self tmp = *this;
                    increment();
                    return std::move(tmp);
                }

                bool operator== (const SCSlinklistIterator& other) {
                    return node_ == other.node_;
                }

                bool operator!= (const SCSlinklistIterator& other) {
                    return node_ != other.node_;
                }
            };
        } // namespace slinklist
        
    } // namespace algorithm
    
} // namespace sc


#endif //!_SC_ALGORITHM_SLIN_LIST_SC_SLINK_ITERATOR_H_