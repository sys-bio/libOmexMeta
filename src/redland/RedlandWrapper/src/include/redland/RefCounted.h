//
// Created by Ciaran on 06/08/2021.
//

#ifndef LIBOMEXMETA_REFCOUNTED_H
#define LIBOMEXMETA_REFCOUNTED_H

#include "redland/LibrdfWorld.h"
#include <variant>


namespace redland {

    namespace _for_tests{
        typedef struct ref_counted_type_t {
            int usage = 0;
        } ref_counted_type;

        ref_counted_type * makeRefCountedType(){
            ref_counted_type * obj = new ref_counted_type();
            obj->usage++;
            return obj;
        }

        void free_ref_counted_type(ref_counted_type* refCountedType){
            if (refCountedType->usage == 0){
                return;
            }
            refCountedType->usage--;
            if (refCountedType->usage == 0){
                delete refCountedType;
            }
        }
    }

    using world_free_func = std::function<void(librdf_world *)>;
    using uri_free_func = std::function<void(librdf_uri *)>;
    using storage_free_func = std::function<void(librdf_storage *)>;
    using serializer_free_func = std::function<void(librdf_serializer *)>;
    using parser_free_func = std::function<void(librdf_parser *)>;
    using statement_free_func = std::function<void(librdf_statement *)>;
    using query_free_func = std::function<void(librdf_query *)>;
    using query_results_free_func = std::function<void(librdf_query_results *)>;
    using node_free_func = std::function<void(librdf_node *)>;
    using model_free_func = std::function<void(librdf_model *)>;
    using ref_counted_type_free_func = std::function<void(_for_tests::ref_counted_type*)>;

    template<typename ObjType, typename FreeFuncType>
    class RefCounted {
    public:
        /**
         * @brief generic constructor for ref counted types
         * @param objType instance of ObjType*, this is the object being ref counted
         * @param func the function that free's the ref counted type
         */
        RefCounted(ObjType *objType, FreeFuncType func)
            : obj_(objType), freeFunc_(func) {
            RefCounted::checkForNull();
        }

        virtual ~RefCounted() {
            freeFunc_(obj_);
        }

        RefCounted(const RefCounted &other) {
            checkForNull();
            if (obj_) {
                freeFunc_(obj_);
                obj_ = nullptr;
            }
            obj_ = other.get();// automatically increments the reference count
        }

        RefCounted(RefCounted &&other) noexcept {
            if (obj_) {
                freeFunc_(obj_);
                obj_ = nullptr;
            }
            obj_ = other.getWithoutIncrement();
            other.obj_ = nullptr;
        }

        RefCounted &operator=(const RefCounted &other) {
            if (*this != other) {
                if (obj_) {
                    freeFunc_(obj_);
                    obj_ = nullptr;
                }
                obj_ = other.get();// handles reference count automatically
            }
            return *this;
        }

        RefCounted &operator=(RefCounted &&other) noexcept{
            if (*this != other) {
                if (obj_) {
                    freeFunc_(obj_);
                    obj_ = nullptr;
                }
                obj_ = other.getWithoutIncrement();
                other.obj_ = nullptr;
            }
            return *this;
        }

        virtual void checkForNull() {
            if (!obj_) {
                throw RedlandNullPointerException(
                        "RedlandNullPointerException: checkForNull(): obj_ is null");
            }
            if (!freeFunc_){
                throw RedlandNullPointerException(
                        "RedlandNullPointerException: checkForNull(): freeFunc_ is null");
            }
        }

        void free() {
            if (!obj_)
                return;
            int usage = getUsage();
            freeFunc_(obj_);
            if (usage - 1 == 0) {
                obj_ = nullptr;
            }
        }

        int getUsage() const {
            return obj_->usage;
        }

        void incrementUsage() const {
            obj_->usage++;
        }

        ObjType *get() const {
            incrementUsage();
            return obj_;
        }

        ObjType *getWithoutIncrement() const {
            return obj_;
        }

//        void freeFunc_(obj_){
//            return free()
//            std::visit([&](){
//                return std::get<
//                if (auto f = std::get_if<ref_counted_type_free_func>(&freeFunc_)){
//                    return (*f)(obj_);
//                } else if (auto f = std::get_if<world_free_func>(&freeFunc_)){
//                    return (*f)(obj_);
//                } else if (auto f = std::get_if<uri_free_func>(&freeFunc_)){
//                    return (*f)(obj_);
//                } else if (auto f = std::get_if<storage_free_func>(&freeFunc_)){
//                    return (*f)(obj_);
//                } else if (auto f = std::get_if<serializer_free_func>(&freeFunc_)){
//                    return (*f)(obj_);
//                } else if (auto f = std::get_if<parser_free_func>(&freeFunc_)){
//                    return (*f)(obj_);
//                } else if (auto f = std::get_if<query_free_func>(&freeFunc_)){
//                    return (*f)(obj_);
//                } else if (auto f = std::get_if<query_results_free_func>(&freeFunc_)){
//                    return (*f)(obj_);
//                } else if (auto f = std::get_if<node_free_func>(&freeFunc_)){
//                    return (*f)(obj_);
//                } else if (auto f = std::get_if<model_free_func>(&freeFunc_)){
//                    return (*f)(obj_);
//                }
//            }, freeFunc_);
//        }

        bool operator==(const RefCounted &rhs) const {
            return obj_ == rhs.obj_ &&
                   typeid(freeFunc_) == typeid(rhs.freeFunc_);
        }

        bool operator!=(const RefCounted &rhs) const {
            return !(rhs == *this);
        }

    private:
        ObjType *obj_;

        FreeFuncType freeFunc_;
    };

}// namespace redland

#endif//LIBOMEXMETA_REFCOUNTED_H
