
#ifndef _SC_ALGORITHM_SLINK_LIST_SC_SLINK_LIST_H_
#define _SC_ALGORITHM_SLINK_LIST_SC_SLINK_LIST_H_

#include "sc_slink_iterator.h"

namespace sc
{
    namespace algorithm
    {
        namespace slinklist
        {
            template<class Value>
            class SCSLinkList
            {
            protected:
                typedef void* void_pointer;
                typedef SCSlinklistBaseNode* ptr_base;
                typedef SCSlinklistNode<Value> slink_list_node;
            public:
                typedef Value value_type;
                typedef value_type& referance;
                typedef value_type* pointer;
                typedef slink_list_node* link_type;
                typedef size_t size_type;
            protected:
                link_type head_;
                link_type tail_;
                size_type node_count_;
                
                link_type GetNode() {return (link_type)(::operator new((size_type)(sizeof(slink_list_node))));}
                link_type CreateNode() {
                    link_type p = GetNode();
                    new(p) slink_list_node();
                    node_count_++;
                    return p;
                }
                link_type CreateNode(const value_type& x) {
                    link_type p = CreateNode();
                    p->value_field_ = x;
                    return p;
                }

                void PutNode(link_type p) {
                    p->~slink_list_node();
                    ::operator delete(p);
                    node_count_--;
                }
            public:
                typedef SCSlinklistIterator<value_type, referance, pointer> iterator;
            public:
                SCSLinkList() : head_(nullptr), tail_(nullptr) {
                    head_ = CreateNode();
                    tail_ = head_;
                    tail_->next_ = head_;
                }
                ~SCSLinkList() {}

                iterator begin() {return (head_->next_ ? iterator((link_type)head_->next_) : iterator(head_));}
                iterator end() {return iterator(head_);}
                iterator erase(iterator& itr) {
                    return __erase(itr);
                }

                size_type size() {return node_count_ - 1;}

                std::pair<iterator, bool> insert(iterator& itr, const value_type& x) {
                    iterator ret = __insert(itr, x);
                    return std::pair<iterator, bool>(ret, (ret != end()));
                }

                void push_back(const value_type& x) {
                    __push_back(x);
                }
                void pop_back() {
                    __pop_back();
                }
            private:
                iterator __erase(iterator& itr);
                void __push_back(const value_type& x);
                void __pop_back();
                iterator __insert(iterator& itr, const value_type& x);
            };

            template<class Value>
            typename SCSLinkList<Value>::iterator
            SCSLinkList<Value>::__erase(iterator& itr) {
                link_type pre = head_;
                link_type rm = (link_type)itr.node_;
                while (pre && pre->next_ != rm)
                {
                    pre = (link_type)pre->next_;
                }
                pre->next_ = rm->next_;
                if (rm == tail_)
                {
                    tail_ = pre;
                }
                PutNode(rm);
                return iterator((link_type)pre->next_);
            }

            template<class Value>
            typename SCSLinkList<Value>::iterator
            SCSLinkList<Value>::__insert(iterator& itr, const value_type& x) {
                link_type in = CreateNode(x);
                if (!in)
                {
                    return iterator(head_);
                }
                link_type p = (link_type)itr.node_;
                link_type next = (link_type)p->next_;
                p->next_ = in;
                in->next_ = next;
                return iterator(in);
            }


            template<class Value>
            void SCSLinkList<Value>::__push_back(const value_type& x) {
                link_type p = CreateNode(x);
                p->next_ = tail_->next_;
                tail_->next_ = p;
                tail_ = p;
            }

            template<class Value>
            void SCSLinkList<Value>::__pop_back() {
                link_type pre = head_;
                while (pre && (link_type)pre->next_ != tail_)
                {
                    pre = (link_type)pre->next_;
                }
                link_type tmp = tail_;
                pre->next_ = tail_->next_;
                tail_ = pre;
                PutNode(tmp);
            }
        } // namespace slinklist
    } // namespace algorithm
    
} // namespace sc


#endif //!_SC_ALGORITHM_SLINK_LIST_SLINK_LIST_H_
