//
// Created by Ciaran on 06/08/2021.
//

#include "librdf.h"
#include "raptor2.h"
#include "rasqal.h"
#include "redland/RedlandAPI.h"
#include "gtest/gtest.h"
#include <functional>

using namespace redland;


typedef struct ref_counted_type_t {
    int usage = 0;
} ref_counted_type;

ref_counted_type *makeRefCountedType() {
    auto *obj = new ref_counted_type();
    obj->usage++;
    return obj;
}

void free_ref_counted_type(ref_counted_type *refCountedType) {
    if (refCountedType) {
        if (refCountedType->usage == 0) {
            return;
        }
        refCountedType->usage--;
        if (refCountedType->usage == 0) {
            delete refCountedType;
            refCountedType = nullptr;
        }
    }
}

using ref_counted_type_free_func = std::function<void(ref_counted_type *)>;


class RefCountedTests : public ::testing::Test {

public:
    RefCountedTests() = default;
};

/**
 * Run these tests with valgrind for comprehensive testing
 */

TEST_F(RefCountedTests, CheckNoMemoryLeakWithTestType) {
    ref_counted_type *refCountedType = makeRefCountedType();
    RefCountedRedlandType<ref_counted_type, ref_counted_type_free_func> refCounted(refCountedType, free_ref_counted_type);
}

TEST_F(RefCountedTests, CheckIncrementWithGetWithTestType) {
    ref_counted_type *refCountedType = makeRefCountedType();
    RefCountedRedlandType<ref_counted_type, ref_counted_type_free_func> refCounted(refCountedType, free_ref_counted_type);
    ref_counted_type *refCountedType2 = refCounted.get();
    ASSERT_EQ(refCountedType, refCountedType2);
    ASSERT_EQ(2, refCountedType->usage);
    // need to call free manually on the second, since it is not managed ny RefCounted
    free_ref_counted_type(refCountedType2);
    ASSERT_EQ(1, refCountedType->usage);
}

TEST_F(RefCountedTests, CheckCopyCtorWithTestType) {
    // allocates new ptr
    ref_counted_type *refCountedType = makeRefCountedType();
    // takes ownership of the ref_counted_type
    RefCountedRedlandType<ref_counted_type, ref_counted_type_free_func> refCounted(refCountedType, free_ref_counted_type);
    // copies and increments the ref count - injecting into redland types
    RefCountedRedlandType<ref_counted_type, ref_counted_type_free_func> refCountedCpy(refCounted);
    ASSERT_EQ(refCounted, refCountedCpy);
    ASSERT_EQ(2, refCountedType->usage);
    int u = 0;
}

TEST_F(RefCountedTests, CheckMoveCtorWithTestType) {
    // allocates new ptr
    ref_counted_type *refCountedType = makeRefCountedType();
    // takes ownership of the ref_counted_type
    RefCountedRedlandType<ref_counted_type, ref_counted_type_free_func> refCounted(refCountedType, free_ref_counted_type);
    RefCountedRedlandType<ref_counted_type, ref_counted_type_free_func> refCountedMv(std::move(refCounted));
    ASSERT_EQ(1, refCountedType->usage);
}


TEST_F(RefCountedTests, CheckCopyAssignCtorWithTestType) {
    // allocates new ptr
    ref_counted_type *refCountedType = makeRefCountedType();
    // takes ownership of the ref_counted_type
    RefCountedRedlandType<ref_counted_type, ref_counted_type_free_func> refCounted(refCountedType, free_ref_counted_type);
    // copies and increments the ref count - injecting into redland types
    RefCountedRedlandType<ref_counted_type, ref_counted_type_free_func> refCountedCpy = refCounted;
    ASSERT_EQ(refCounted, refCountedCpy);
    ASSERT_EQ(2, refCountedType->usage);
}


TEST_F(RefCountedTests, CheckMoveAssignCtorWithTestType) {
    // allocates new ptr
    ref_counted_type *refCountedType = makeRefCountedType();
    // takes ownership of the ref_counted_type
    RefCountedRedlandType<ref_counted_type, ref_counted_type_free_func> refCounted(refCountedType, free_ref_counted_type);
    // copies and increments the ref count - injecting into redland types
    RefCountedRedlandType<ref_counted_type, ref_counted_type_free_func> refCountedMv = std::move(refCounted);
    ASSERT_EQ(1, refCountedType->usage);
}


TEST_F(RefCountedTests, FromDefaultCtr){
    ref_counted_type *refCountedType = makeRefCountedType();

    RefCountedRedlandType<ref_counted_type, ref_counted_type_free_func > refCounted;
    refCounted.setObj(refCountedType);
    refCounted.setFreeFunc(free_ref_counted_type);
    ASSERT_EQ(1, refCounted.getUsage());

}


//TEST_F(LibrdfNodeTests, TestMoveAssignmentOperator) {
//    std::string expected1 = "https://notarealaddress1.com";
//    std::string expected2 = "https://notarealaddress2.com";
//    LibrdfNode node1 = LibrdfNode::fromUriString(expected1);
//    LibrdfNode node2 = LibrdfNode::fromUriString(expected2);
//    node1 = std::move(node2);
//    std::string actual = node1.str();
//    ASSERT_STREQ(expected2.c_str(), actual.c_str());
//}


//
//TEST_F(RefCountedTests, CheckNoMemoryLeakWithLibrdfWorld){
//    librdf_world* world = librdf_new_world();
//    RefCounted<librdf_world, world_free_func> refCounted(world, librdf_free_world);
//}
//
//
//TEST_F(RefCountedTests, CheckNoMemoryLeakWithLibrdfUri){
//    std::string uri_s = "uri string";
//    librdf_uri* uri = librdf_new_uri(LibrdfWorld::getWorld(), (const unsigned char*)uri_s.c_str());
//    RefCounted<librdf_uri , uri_free_func> refCounted(uri, librdf_free_uri);
//}
//
//
//TEST_F(RefCountedTests, CheckNoMemoryLeakWithLibrdfStorage){
//    librdf_storage* storage = librdf_new_storage(LibrdfWorld::getWorld(), "memory", "sstore", nullptr);
//    RefCounted<librdf_storage, storage_free_func> refCounted(storage, librdf_free_storage);
//}
//
//
//TEST_F(RefCountedTests, CheckNoMemoryLeakWithLibrdfSerializer){
//    librdf_serializer* serializer = librdf_new_serializer(LibrdfWorld::getWorld(), "rdfxml", nullptr, nullptr);
//    RefCounted<librdf_serializer, serializer_free_func> refCounted(serializer, librdf_free_serializer);
//}
//
//
//TEST_F(RefCountedTests, CheckNoMemoryLeakWithLibrdfParser){
//    librdf_parser* parser = librdf_new_parser(LibrdfWorld::getWorld(), "rdfxml", nullptr, nullptr);
//    RefCounted<librdf_parser, parser_free_func> refCounted(parser, librdf_free_parser);
//}
//
//
//TEST_F(RefCountedTests, CheckNoMemoryLeakWithLibrdfQuery){
//    librdf_query* query = librdf_new_query(LibrdfWorld::getWorld(), "sparql", nullptr, (const unsigned char*)"query string", nullptr);
//    RefCounted<librdf_query, query_free_func> refCounted(query, librdf_free_query);
//}
//
//TEST_F(RefCountedTests, CheckNoMemoryLeakWithLibrdfNode){
//    librdf_node* node = librdf_new_node(LibrdfWorld::getWorld());
//    RefCounted<librdf_node, node_free_func> refCounted(node, librdf_free_node);
//}
//
//TEST_F(RefCountedTests, CheckIncrementsWithGet){
//    librdf_node* node = librdf_new_node(LibrdfWorld::getWorld());
//    RefCounted<librdf_node, node_free_func> refCounted(node, librdf_free_node);
//    librdf_node* n2 = refCounted.get();
//    ASSERT_EQ(node, n2); // same object
//    ASSERT_EQ(2, refCounted.getUsage());
//}
//
