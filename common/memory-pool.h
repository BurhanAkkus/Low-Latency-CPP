#pragma once
#include <cstdlib>
#include <vector>
#include "macros.h"

namespace Common{
    template<typename T>
    class MemoryPool final{
        public:
            MemoryPool(std::size_t num_elems):store(num_elems,{T{},true}){
                // Make sure that the ObjectBlock's memory starts with object_.
                ASSERT(reinterpret_cast<ObjectBlock*>(&(store[0].object_)) == &(store[0]), "ObjectBlock must start with T");
            }

            MemoryPool() = delete; // default constructor can't be called.
            MemoryPool(const MemoryPool&) = delete; // copy constructor can't be called.
            MemoryPool operator=(const MemoryPool&) = delete; // copy assignment can't be called.
            MemoryPool(const MemoryPool&&) = delete; // move constructor can't be called.
            MemoryPool operator=(const MemoryPool&&) = delete;// move assignment can't be called.

            template<typename ...Args>
            T* allocate(Args... args) noexcept {
                auto next_free_obj_block = &store[next_free_index];
                ASSERT(next_free_obj_block->is_free == true, "Expected free ObjectBlock at index: " +
                std::to_string(next_free_index));
                T* ret = &(next_free_obj_block->object_);
                ret = new(ret) T(args...);// new uses memory passed to it - ret in this case.
                next_free_obj_block->is_free = false;
                updateNextFreeIndex();
                return ret;
            }
            template<typename U>
            T* allocate(std::initializer_list<U> args) noexcept {
                auto next_free_obj_block = &store[next_free_index];
                ASSERT(next_free_obj_block->is_free == true, "Expected free ObjectBlock at index: " +
                std::to_string(next_free_index));
                T* ret = &(next_free_obj_block->object_);
                ret = new(ret) T(args);// new uses memory passed to it - ret in this case.
                next_free_obj_block->is_free = false;
                updateNextFreeIndex();
                return ret;
            }

            auto deallocate(const T* element) noexcept {
                const auto element_index = (reinterpret_cast<const ObjectBlock*> (element) - &store[0]);
                ASSERT(element_index >= 0 && static_cast<size_t>(element_index) < store.size(),"Element doesn't belong to this memory pool!" );
                ASSERT(!store[element_index].is_free, "Expected in-use ObjectBlock at index: " + std::to_string(element_index));
                store[element_index].is_free = true;
            }
        private:
            struct ObjectBlock{
                T object_;
                bool is_free = true;
            };
            std::vector<ObjectBlock> store;
            size_t next_free_index = 0;
            void updateNextFreeIndex(){
                const auto initial = next_free_index;
                    while(!store[next_free_index].is_free){
                    if(UNLIKELY(next_free_index + 1== store.size())){next_free_index = 0;}
                    else{next_free_index++;}
                    // if is redundant, serves for UNLIKELY.
                    if (UNLIKELY(initial == next_free_index)) {
                        ASSERT(initial != next_free_index, "Storage is FULL!!");
                    }
                }
            }
    }; 

}