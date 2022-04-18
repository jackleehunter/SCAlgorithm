
/*
 * @Author: jack.hu 
 * @Date: 2022-04-17 22:17:13 
 * @Last Modified by: jack.hu
 * @Last Modified time: 2022-04-17 22:26:36
 * 
 * This file is part of root_tree. It is only used for learning and 
 * cannot be used as production code
 * 
 */

#ifndef _SC_ALGORITHM_ROOT_TREE_SC_RTREE_DEF_H_
#define _SC_ALGORITHM_ROOT_TREE_SC_RTREE_DEF_H_

#include <memory>
#include <new>

namespace sc
{
    namespace algorithm
    {
        namespace rtree
        {
            template<class T, class Alloc>
            class SCRTreeAlloc {
            public:
                static T* allocate(size_t n) {
                    return 0 == n ? (T*)0 : (T*)Alloc::allocate(n * sizeof(T));
                }

                static T* allocate() {
                    return (T*)Alloc::allocate(sizeof(T));
                }

                static void deallocate(T* p, size_t n) {
                    if (0 != n)
                        Alloc::deallocate(p, n * sizeof(T));
                }

                static void deallocate() {
                    Alloc::deallocate(p, sizeof(T));
                }
            };

            template<class T, class Value>
            inline void construct(T* p, const Value& v) {
                new (p) T(v);
            }

            template<class T>
            inline void destory(T* pointer) {
                pointer->~T();
            }
        } // namespace rtree
        
    } // namespace algorithm
    
} // namespace sc

#endif //!_SC_ALGORITHM_ROOT_TREE_SC_RTREE_DEF_H_
