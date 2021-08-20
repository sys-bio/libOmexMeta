//
// Created by Ciaran on 06/08/2021.
//

#ifndef LIBOMEXMETA_REFCOUNTEDREDLANDTYPE_H
#define LIBOMEXMETA_REFCOUNTEDREDLANDTYPE_H

#include "RedlandType.h"
#include "librdf.h"
#include "raptor2.h"
#include "rasqal.h"
#include "rdf_uri_internal.h"
#include "redland/LibrdfWorld.h"
#include <variant>

namespace redland {

    //    using world_free_func = std::function<void(librdf_world *)>;
    //    using storage_free_func = std::function<void(librdf_storage *)>;
    //    using serializer_free_func = std::function<void(librdf_serializer *)>;
    //    using parser_free_func = std::function<void(librdf_parser *)>;
    //    using statement_free_func = std::function<void(librdf_statement *)>;
    //    using query_free_func = std::function<void(librdf_query *)>;
    //    using query_results_free_func = std::function<void(librdf_query_results *)>;
    //    using model_free_func = std::function<void(librdf_model *)>;

    template<typename ObjType, typename FreeFuncType>
    class RefCountedRedlandType : public RedlandType<ObjType, FreeFuncType> {
    public:
        using ThisType = RedlandType<ObjType, FreeFuncType>;
        using ThisType::RedlandType;


//        /**
//         * @brief default constructor. Users would need to populate obj_ and freeFunc_
//         * manually if default constructor is used.
//         * @see RedlandType::setFreeFunc
//         * @see RedlandType::setObj
//         */
//        RefCountedRedlandType() = default;
//
//        /**
//         * @brief generic constructor for ref counted types
//         * @param objType instance of ObjType*, this is the object being ref counted
//         * @param func the function that free's the ref counted type
//         */
//        RefCountedRedlandType(ObjType *objType, std::function<void(ObjType*)> func)
//            : RedlandType<ObjType, FreeFuncType>(objType, func) {
////            incrementUsage();
//        }



        /**
         * @brief copy constructor.
         * @details takes a copy of freeFunc from other. If this RedlandType has
         * a obj_ then it is deleted with the freeFunc. Then the address of
         * the obj_ from other is stored in this->obj_ and the internal reference
         * counter is incremented by 1.
         */
        RefCountedRedlandType(const RefCountedRedlandType &other){
            freeFunc_ = other.freeFunc_;
            if (obj_) {
                freeFunc_(obj_);
                obj_ = nullptr;
            }
            obj_ = other.get();// automatically increments the reference count
        }

        /**
         * @brief copy assignment constructor.
         * @details takes a copy of freeFunc from other if we do not already have one. If this RedlandType has
         * a obj_ then it is deleted with the freeFunc. Then the address of
         * the obj_ from other is stored in this->obj_ and the internal reference
         * counter is incremented by 1.
         */
        RefCountedRedlandType &operator=(const RefCountedRedlandType &other){
            if (*this != other) {
                // this is a weird one since we're treating the method that free's memory
                // as a member variable. It means that we want to free an existing obj_ with a
                // uninitialized freeFunc_. So we copy it across first.
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
         * @brief move constructor.
         * @details takes a copy of freeFunc from other. If this RedlandType has
         * a obj_ then it is deleted with the freeFunc. Then the address of
         * the obj_ from other is stored in this->obj_ but the internal reference
         * counter is not incremented by 1.
         */
        RefCountedRedlandType(RefCountedRedlandType &&other) noexcept{
            // this is a weird one since we're treating the method that free's memory
            // as a member variable. It means that we want to free an existing obj_ with a
            // uninitialized freeFunc_. So we copy it across first.
            freeFunc_ = other.freeFunc_;
            if (obj_) {
                freeFunc_(obj_);
                obj_ = nullptr;
            }
            obj_ = other.getWithoutIncrement();
            other.obj_ = nullptr;
        }

        /**
         * @brief move assignment constructor.
         * @details takes a copy of freeFunc from other if we do not already have one. If this RedlandType has
         * a obj_ then it is deleted with the freeFunc. Then the address of
         * the obj_ from other is stored in this->obj_ and the internal reference
         * counter is not incremented by 1.
         */
        RefCountedRedlandType &operator=(RefCountedRedlandType &&other) noexcept {
            if (*this != other) {
                // this is a weird one since we're treating the method that free's memory
                // as a member variable. It means that we want to free an existing obj_ with a
                // uninitialized freeFunc_. So we copy it across first.
                freeFunc_ = other.freeFunc_;
                if (obj_) {
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
         * @brief use the user supplied freeFunc to delete memory pointed to by obj_
         * Account for reference counting
         */
        void freeObj() override {
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
        ObjType *get() const override {
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

        using RedlandType<ObjType, FreeFuncType>::obj_;
        using RedlandType<ObjType, FreeFuncType>::freeFunc_;
    };

}// namespace redland

#endif//LIBOMEXMETA_REFCOUNTEDREDLANDTYPE_H
