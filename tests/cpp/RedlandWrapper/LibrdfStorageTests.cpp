//
// Created by Ciaran on 5/17/2020.
//
#include "iostream"
#include "redland/LibrdfModel.h"
#include "redland/LibrdfStorage.h"
#include "redland/LibrdfWorld.h"
#include "gtest/gtest.h"
#include <filesystem>


using namespace redland;

class LibrdfStorageTests : public ::testing::Test {

public:
    librdf_world *world = nullptr;
    librdf_statement *statement = nullptr;

    LibrdfStorageTests() {
        world = LibrdfWorld::getWorld();
        statement = librdf_new_statement_from_nodes(
                world,
                librdf_new_node_from_uri_string(world, (const unsigned char *) "http://www.dajobe.org/"),

                librdf_new_node_from_uri_string(world,
                                                (const unsigned char *) "http://purl.org/dc/elements/1.1/creator"),
                librdf_new_node_from_literal(world, (const unsigned char *) "Dave Beckett", NULL, 0));
    }

    ~LibrdfStorageTests() override {
        librdf_free_statement(statement);
        //        librdf_free_world(world);
    }

};


TEST_F(LibrdfStorageTests, TestInstantiateStorage) {
    LibrdfStorage storage1 = LibrdfStorage("memory", "Storage1");
    ASSERT_NE(storage1.getWithoutIncrement(), nullptr);
}

TEST_F(LibrdfStorageTests, TestMoveConstructor) {
    LibrdfStorage storage1;
    LibrdfStorage storage2(std::move(storage1));
    ASSERT_EQ(1, storage2.getUsage());
}

TEST_F(LibrdfStorageTests, TestMoveAssignment) {
    LibrdfStorage storage1;
    LibrdfStorage storage2 = std::move(storage1);
    ASSERT_EQ(1, storage2.getUsage());
}

TEST_F(LibrdfStorageTests, TestCopyConstructor) {
    LibrdfStorage storage1;
    LibrdfStorage storage2(storage1);
    ASSERT_EQ(2, storage2.getUsage());
}

TEST_F(LibrdfStorageTests, TestCopyAssignment) {
    LibrdfStorage storage1;
    LibrdfStorage storage2 = storage1;
    ASSERT_EQ(2, storage2.getUsage());
}


TEST_F(LibrdfStorageTests, TestSQLiteStorage) {
    std::filesystem::path fname = std::filesystem::current_path() += "StorageName.db";
    LibrdfStorage storage = LibrdfStorage("sqlite", fname.string(), "new='yes'");
    LibrdfModel model(storage);
    model.addStatement(statement);
    ASSERT_EQ(1, model.size());
    bool actual = std::filesystem::exists(fname);
    ASSERT_TRUE(actual);
}

TEST_F(LibrdfStorageTests, TestMemoryStorage) {
    std::filesystem::path fname = std::filesystem::current_path() += "StorageName.db";
    LibrdfStorage storage = LibrdfStorage("memory", fname, "new='yes'");
    LibrdfModel model(storage);
    model.addStatement(statement);
    ASSERT_EQ(1, model.size());
    bool actual = std::filesystem::exists(fname);
    ASSERT_TRUE(actual);
}



TEST_F(LibrdfStorageTests, TesthashesMemory) {
    LibrdfStorage storage = LibrdfStorage("hashes", "StorageName", "hash-type='memory'");
    storage.addStatement(statement);
    int actual = storage.size();
    int expected = 1;
    ASSERT_EQ(expected, actual);
}

TEST_F(LibrdfStorageTests, TestfileMemory) {
    std::filesystem::path fname = std::filesystem::current_path() += "StorageName.db";
    LibrdfStorage storage = LibrdfStorage("file", fname);
    LibrdfModel model(storage);
    model.addStatement(statement);
    ASSERT_EQ(1, model.size());
    bool actual = std::filesystem::exists(fname);
    ASSERT_TRUE(actual);
}

//TEST_F(LibrdfStorageTests, TestmysqlMemory) {
//
//    LibrdfStorage storage1 = LibrdfStorage("hashes");
//    storage1.freeObj();
//}
//
//TEST_F(LibrdfStorageTests, TestpostgresqlMemory) {
//    LibrdfStorage storage1 = LibrdfStorage("hashes");
//    storage1.freeObj();
//
//}
//TEST_F(LibrdfStorageTests, TesttstoreMemory) {
//    LibrdfStorage storage1 = LibrdfStorage("hashes");
//    storage1.freeObj();
//
//}

//TEST_F(LibrdfStorageTests, TesturiMemory) {
//    LibrdfStorage storage1 = LibrdfStorage("uri");
//    storage1.freeObj();
//
//}

//TEST_F(LibrdfStorageTests, TestvirtuosoMemory) {
//    LibrdfStorage storage1 = LibrdfStorage("hashes");
//    storage1.freeObj();
//
//}
