//
// Created by Ciaran on 06/08/2021.
//

#include "gtest/gtest.h"
#include "redland/RedlandAPI.h"
#include "librdf.h"
#include <functional>

using namespace redland;
using namespace redland::_for_tests;

class RefCountedTests : public ::testing::Test {

public:

    RefCountedTests() = default;
};

/**
 * Run some of these tests with valgrind
 */

TEST_F(RefCountedTests, CheckNoMemoryLeakWithTestType){
    ref_counted_type * refCountedType = makeRefCountedType();
    RefCounted<ref_counted_type, ref_counted_type_free_func> refCounted(refCountedType, free_ref_counted_type);
}

TEST_F(RefCountedTests, CheckIncrementWithGetWithTestType){
    ref_counted_type * refCountedType = makeRefCountedType();
    RefCounted<ref_counted_type, ref_counted_type_free_func> refCounted(refCountedType, free_ref_counted_type);
    ref_counted_type * refCountedType2 = refCounted.get();
    ASSERT_EQ(refCountedType, refCountedType2);
    ASSERT_EQ(2, refCountedType->usage);
    // need to call free manually on the second, since it is not managed ny RefCounted
    free_ref_counted_type(refCountedType2);
    ASSERT_EQ(1, refCountedType->usage);
}

TEST_F(RefCountedTests, CheckCopyCtorWithTestType){
    ref_counted_type * refCountedType = makeRefCountedType();
    RefCounted<ref_counted_type, ref_counted_type_free_func> refCounted(refCountedType, free_ref_counted_type);
    RefCounted<ref_counted_type, ref_counted_type_free_func> refCountedCpy(refCounted);
    ASSERT_EQ(refCounted, refCountedCpy);
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

















