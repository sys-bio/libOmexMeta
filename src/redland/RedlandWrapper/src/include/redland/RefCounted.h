//
// Created by Ciaran on 06/08/2021.
//

#ifndef LIBOMEXMETA_REFCOUNTED_H
#define LIBOMEXMETA_REFCOUNTED_H

#include "redland/LibrdfWorld.h"
#include "raptor2.h"
#include "rasqal.h"
#include "librdf.h"
#include <variant>
#include "rdf_uri_internal.h"

namespace redland {

    using world_free_func = std::function<void(librdf_world *)>;
    using storage_free_func = std::function<void(librdf_storage *)>;
    using serializer_free_func = std::function<void(librdf_serializer *)>;
    using parser_free_func = std::function<void(librdf_parser *)>;
    using statement_free_func = std::function<void(librdf_statement *)>;
    using query_free_func = std::function<void(librdf_query *)>;
    using query_results_free_func = std::function<void(librdf_query_results *)>;
    using model_free_func = std::function<void(librdf_model *)>;

    template<typename ObjType, typename FreeFuncType>
    class RefCounted {
    public:

        /**
         * @brief default constructor. Users would need to populate obj_ and freeFunc_
         * manually if default constructor is used.
         * @see RefCounted::setFreeFunc
         * @see RefCounted::setObj
         */
        RefCounted() = default;

        /**
         * @brief generic constructor for ref counted types
         * @param objType instance of ObjType*, this is the object being ref counted
         * @param func the function that free's the ref counted type
         */
        RefCounted(ObjType *objType, std::function<void(ObjType*)> func)
            : obj_(objType), freeFunc_(func) {
            RefCounted::checkForNull();
        }

        /**
         * @brief destructor calls the free function specified by the user.
         * This allows multiple redland types to use the same logic for
         * the rule of 5.
         */
        virtual ~RefCounted() {
            freeObj();
        }

        /**
         * @brief copy constructor.
         * @details takes a copy of freeFunc from other. If this RefCounted has
         * a obj_ then it is deleted with the freeFunc. Then the address of
         * the obj_ from other is stored in this->obj_ and the internal reference
         * counter is incremented by 1.
         */
        RefCounted(const RefCounted &other) : freeFunc_(other.freeFunc_) {
            if (obj_) {
                freeFunc_(obj_);
                obj_ = nullptr;
            }
            obj_ = other.get();// automatically increments the reference count
        }

        /**
         * @brief move constructor.
         * @details takes a copy of freeFunc from other. If this RefCounted has
         * a obj_ then it is deleted with the freeFunc. Then the address of
         * the obj_ from other is stored in this->obj_ but the internal reference
         * counter is not incremented by 1.
         */
        RefCounted(RefCounted &&other) noexcept : freeFunc_(other.freeFunc_) {
            if (obj_) {
                freeFunc_(obj_);
                obj_ = nullptr;
            }
            obj_ = other.getWithoutIncrement();
            other.obj_ = nullptr;
        }

        /**
         * @brief copy assignment constructor.
         * @details takes a copy of freeFunc from other if we do not already have one. If this RefCounted has
         * a obj_ then it is deleted with the freeFunc. Then the address of
         * the obj_ from other is stored in this->obj_ and the internal reference
         * counter is incremented by 1.
         */
        RefCounted &operator=(const RefCounted &other) {
            if (*this != other) {
                // this is a weird one since we're treating the method that free's memory
                // as a member variable. It means that we want to free an existing obj_ with a
                // uninitialized freeFunc_. So we copy it across first.
                if (!freeFunc_)
                    freeFunc_ = other.freeFunc_;
                // now we can deal with obj.
                if (obj_) {
                    freeFunc_(obj_);
                    obj_ = nullptr;
                }
                obj_ = other.get();// handles reference count automatically
            }
            return *this;
        }

        /**
         * @brief move assignment constructor.
         * @details takes a copy of freeFunc from other if we do not already have one. If this RefCounted has
         * a obj_ then it is deleted with the freeFunc. Then the address of
         * the obj_ from other is stored in this->obj_ and the internal reference
         * counter is not incremented by 1.
         */
        RefCounted &operator=(RefCounted &&other) noexcept {
            if (*this != other) {
                if (obj_) {
                    // this is a weird one since we're treating the method that free's memory
                    // as a member variable. It means that we want to free an existing obj_ with a
                    // uninitialized freeFunc_. So we copy it across first.
                    if (!freeFunc_)
                        freeFunc_ = other.freeFunc_;
                    // now we can deal with obj.
                    freeFunc_(obj_);
                    obj_ = nullptr;
                }
                obj_ = other.getWithoutIncrement();
                other.obj_ = nullptr;
            }
            return *this;
        }

        /**
         * @breif throws an error if the internal members of RefCounter are nullptr
         */
        virtual void checkForNull() {
            if (!obj_) {
                throw RedlandNullPointerException(
                        "RedlandNullPointerException: checkForNull(): obj_ is null");
            }
            if (!freeFunc_) {
                throw RedlandNullPointerException(
                        "RedlandNullPointerException: checkForNull(): freeFunc_ is null");
            }
        }

        /**
         * @brief use the user supplied freeFunc to delete memory pointed to by obj_
         */
        void freeObj() {
            if (!obj_)
                return;
            int usage = getUsage();
            freeFunc_(obj_);
            if (usage - 1 == 0) {
                obj_ = nullptr;
            }
        }

        /**
         * @brief returns the current usage count of obj_
         */
        int getUsage() const {
            return obj_->usage;
        }

        /**
         * @brief Adds 1 to the usage count of obj_
         */
        void incrementUsage() const {
            obj_->usage++;
        }

        /**
         * @brief get a pointer to the ObjType stored by this RefCounted. The usage
         * count is incremented by one so that memory is properly handled via shared ownership.
         * @details using RefCounted::get vs RefCounted::getWithoutIncrement in the correct place
         * is critical for proper memory mangement. Using RefCounted::get in an R-value statement
         * will increment the ref counter but not decrement it, causing a memory leak - todo check if this is right
         */
        ObjType *get() const {
            incrementUsage();
            return obj_;
        }

        /**
         * @brief get a pointer to the ObjType stored by this RefCounted. The usage
         * count is not incremented.
         * @details using RefCounted::get vs RefCounted::getWithoutIncrement in the correct place
         * is critical for proper memory mangement. Using RefCounted::get in an R-value statement
         * will increment the ref counter but not decrement it, causing a memory leak - todo check if this is right
         */
         ObjType *getWithoutIncrement() const {
            return obj_;
        }

        /**
         * @brief equality operator. This RefCounted is equal to rhs if their obj_ is the same
         * (i.e. the address of the object pointed to by obj_ is equal) and if the signature
         * of their freeFunc is the same.
         */
        bool operator==(const RefCounted &rhs) const {
            return obj_ == rhs.obj_ &&
                   typeid(freeFunc_) == typeid(rhs.freeFunc_);
        }

        /**
         * @brief inequality operator. Inverse of RefCounted::operator==
         */
        bool operator!=(const RefCounted &rhs) const {
            return !(rhs == *this);
        }

        /**
         * @brief Set or replace the free function associated with
         * this RefCounted.
         */
        void setFreeFunc(FreeFuncType freeFunc){
            freeFunc_ = freeFunc;
        }

        /**
         * @brief Set or replace the object stored in this RefCounted.
         * @details if obj_ is not nullptr, the current memory is
         * released since this RefCounted only manages a single instance of
         * ObjType*.
         */
        void setObj(ObjType* objType){
            if (obj_){
                freeFunc_(obj_);
                obj_ = nullptr;
            }
            obj_ = objType;
        }

        /**
         * @brief Free the memory pointed to by obj_ with freeFunc but
         * do not destroy this object. If
         * @details if the ref counter of obj_ is not 0, the object will not
         * be freed, but the usage count will be decremented by 1. The remaining
         * ref counts would be the responsibility of the caller.
         */
        void release(){
            if (obj_){
                freeFunc_(obj_);
                obj_ = nullptr;
            }
        }

    protected:
        /**
         * @brief Pointer to the heap allocated object that is managed by this RefCounted.
         * @details the type pointed to by this RefCounted must have public access to a
         * "usage" count, which is the current reference count. Used for redland types.
         */
        ObjType *obj_ = nullptr;

        /**
         * @brief the signature of the C function that should be used to free obj_.
         * @example for instance if obj_ is a librdf_uri* then freeFunc_ would be
         * std::function<void(librdf_uri*)> and the actual function that does the freeing
         * is void librdf_free_uri(librdf_uri*).
         * @details this is necessary so that the RefCounted can store the function responsible
         * for freeing redland types as a member variable, in a general way. Without this,
         * each subclass would need to define their own freeFunc using inheritance, leading
         * to significant code duplication.
         */
        FreeFuncType freeFunc_;
    };

}// namespace redland

#endif//LIBOMEXMETA_REFCOUNTED_H
