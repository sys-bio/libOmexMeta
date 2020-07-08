//
// Created by Ciaran on 5/17/2020.
//
#include <LibrdfModel.h>
#include "gtest/gtest.h"
#include "World.h"
#include "LibrdfStorage.h"
#include "iostream"
#include <filesystem>


using namespace redland;

class LibrdfStorageTests : public ::testing::Test {

public:
    librdf_world *world = nullptr;
    librdf_statement *statement = nullptr;

    LibrdfStorageTests() {
        world = World::getWorld();
        statement = librdf_new_statement_from_nodes(
                world,
                librdf_new_node_from_uri_string(world, (const unsigned char *) "http://www.dajobe.org/"),

                librdf_new_node_from_uri_string(world,
                                                (const unsigned char *) "http://purl.org/dc/elements/1.1/creator"),
                librdf_new_node_from_literal(world, (const unsigned char *) "Dave Beckett", NULL, 0)
        );

    }

    ~LibrdfStorageTests() override {
        librdf_free_statement(statement);
//        librdf_free_world(world);
    }
};


TEST_F(LibrdfStorageTests, TestInstantiateStorage) {
    redland::LibrdfStorage storage1 = LibrdfStorage("memory", "Storage1");
    ASSERT_NE(storage1.get(), nullptr);
    storage1.freeStorage();
}

TEST_F(LibrdfStorageTests, TestMoveConstructor) {
    redland::LibrdfStorage storage1 = LibrdfStorage();
    // get ptr as int before we move it to compare with storage 2
    auto storage1_int_ptr = reinterpret_cast<std::uintptr_t>(storage1.get());
    redland::LibrdfStorage storage2 = std::move(storage1);
    auto storage2_int_ptr = reinterpret_cast<std::uintptr_t>(storage2.get());
    ASSERT_EQ(storage1_int_ptr, storage2_int_ptr);
    storage2.freeStorage();
}

TEST_F(LibrdfStorageTests, TestMoveAssignment) {
    redland::LibrdfStorage storage1 = LibrdfStorage();
    auto storage1_int_ptr = reinterpret_cast<std::uintptr_t>(storage1.get());
    redland::LibrdfStorage storage2 = LibrdfStorage();
    auto storage2_int_ptr = reinterpret_cast<std::uintptr_t>(storage2.get());
    storage1 = std::move(storage2);
    ASSERT_NE(storage1_int_ptr, storage2_int_ptr);
    storage1.freeStorage();
}


TEST_F(LibrdfStorageTests, TestSQLiteStorage) {
    std::filesystem::path fname = std::filesystem::current_path() += "StorageName.db";
    raptor_world* raptor_world_ptr = librdf_world_get_raptor(world);
    LibrdfStorage storage = LibrdfStorage("sqlite", fname, "new='yes'");
    LibrdfModel model(storage.get());
    model.addStatement(statement);
    raptor_iostream* iostr = raptor_new_iostream_to_file_handle(raptor_world_ptr, stdout);
    librdf_model_write(model.get(), iostr);
    raptor_free_iostream(iostr);
    bool actual = std::filesystem::exists(fname);
    ASSERT_TRUE(actual);
    model.freeModel();
    storage.freeStorage();
}

TEST_F(LibrdfStorageTests, TestPrintAvailableStorages) {
    LibrdfStorage storage = LibrdfStorage();
    storage.printAvailableStorages();
    storage.freeStorage();
}

//TEST_F(LibrdfStorageTests, TestBDBStorage) {
//    const char* fname = "/mnt/d/libOmexMeta/tests/cpp/bdb.db";
//    raptor_world* raptor_world_ptr = librdf_world_get_raptor(world);
//    LibrdfStorage storage = LibrdfStorage("hashes", "bdb", "hash-type='bdb',dir='/mnt/d/libOmexMeta/tests/cpp/'");
//    LibrdfModel model(storage.get());
//    model.addStatement(statement);
//    raptor_iostream* iostr = raptor_new_iostream_to_file_handle(raptor_world_ptr, stdout);
//    librdf_model_write(model.get(), iostr);
//    raptor_free_iostream(iostr);
//    bool actual = std::filesystem::exists(fname);
//    ASSERT_TRUE(actual);
//    model.freeModel();
//    storage.freeStorage();
//}

//TEST_F(LibrdfStorageTests, TestMemoryStorage) {
//    const char* fname = "/mnt/d/libOmexMeta/tests/cpp/StorageName.db";
//    raptor_world* raptor_world_ptr = librdf_world_get_raptor(world);
//    LibrdfStorage storage = LibrdfStorage("sqlite", fname, "new='yes'");
//    LibrdfModel model(storage.get());
//    model.addStatement(statement);
//    raptor_iostream* iostr = raptor_new_iostream_to_file_handle(raptor_world_ptr, stdout);
//    librdf_model_write(model.get(), iostr);
//    raptor_free_iostream(iostr);
//    bool actual = std::filesystem::exists(fname);
//    ASSERT_TRUE(actual);
//    model.freeModel();
//    storage.freeStorage();
//}


//TEST_F(LibrdfStorageTests, TestMemoryStorage) {
//    std::cout << __FILE__ <<":"<<__LINE__<<std::endl;
//    redland::LibrdfStorage storage = LibrdfStorage("memory", "StorageName", nullptr);
//    std::cout << __FILE__ <<":"<<__LINE__<<std::endl;
//    storage.addStatement(statement);
//    std::cout << __FILE__ <<":"<<__LINE__<<std::endl;
//    librdf_stream *stream = librdf_storage_find_statements(storage.get(), statement);
//    std::cout << __FILE__ <<":"<<__LINE__<<std::endl;
//    librdf_statement *obj = librdf_stream_get_object(stream);
//    std::cout << __FILE__ <<":"<<__LINE__<<std::endl;
//    ASSERT_TRUE(librdf_statement_equals(statement, obj));
//    std::cout << __FILE__ <<":"<<__LINE__<<std::endl;
//    librdf_free_statement(statement);
//    std::cout << __FILE__ <<":"<<__LINE__<<std::endl;
//    librdf_free_statement(obj);
//    std::cout << __FILE__ <<":"<<__LINE__<<std::endl;
//    storage.freeStorage();
//    std::cout << __FILE__ <<":"<<__LINE__<<std::endl;
//}

//TEST_F(LibrdfStorageTests, TesthashesMemory) {
//    redland::LibrdfStorage storage = LibrdfStorage("hashes", "StorageName", nullptr);
//    storage.addStatement(statement);
//    int actual = storage.size();
//    int expected = 1;
//    ASSERT_EQ(expected, actual);
//    storage.freeStorage();
//}
//
//TEST_F(LibrdfStorageTests, TestmemoryMemory) {
//    redland::LibrdfStorage storage1 = LibrdfStorage("memory");
//    storage1.freeStorage();
//
//}
//
//TEST_F(LibrdfStorageTests, TestfileMemory) {
//    redland::LibrdfStorage storage1 = LibrdfStorage("file");
//    storage1.freeStorage();
//
//}

//TEST_F(LibrdfStorageTests, TestmysqlMemory) {
//
//    redland::LibrdfStorage storage1 = LibrdfStorage("hashes");
//    storage1.freeStorage();
//}
//
//TEST_F(LibrdfStorageTests, TestpostgresqlMemory) {
//    redland::LibrdfStorage storage1 = LibrdfStorage("hashes");
//    storage1.freeStorage();
//
//}
//

//TEST_F(LibrdfStorageTests, TestsqliteMemory) {
//    librdf_world *world = librdf_new_world();
//    redland::LibrdfStorage storage1 = LibrdfStorage("sqlite");
//    librdf_statement *statement = librdf_new_statement_from_nodes(world,
//                                                                  librdf_new_node_from_uri_string(world,
//                                                                                                  (const unsigned char *) "https://subject.com"),
//                                                                  librdf_new_node_from_uri_string(world,
//                                                                                                  (const unsigned char *) "https://predicate.com"),
//                                                                  librdf_new_node_from_uri_string(world,
//                                                                                                  (const unsigned char *) "https://resource.com")
//    );
//    storage1.addStatement(statement);
//
//
//    librdf_free_statement(statement);
//    storage1.freeStorage();
//    librdf_free_world(world);
//
//
//}

//TEST_F(LibrdfStorageTests, TesttstoreMemory) {
//    redland::LibrdfStorage storage1 = LibrdfStorage("hashes");
//    storage1.freeStorage();
//
//}

//TEST_F(LibrdfStorageTests, TesturiMemory) {
//    redland::LibrdfStorage storage1 = LibrdfStorage("uri");
//    storage1.freeStorage();
//
//}

//TEST_F(LibrdfStorageTests, TestvirtuosoMemory) {
//    redland::LibrdfStorage storage1 = LibrdfStorage("hashes");
//    storage1.freeStorage();
//
//}














