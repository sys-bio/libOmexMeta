//
// Created by Ciaran on 09/08/2021.
//

#include "iostream"
#include "redland/LibrdfModel.h"
#include "redland/LibrdfStream.h"
#include "redland/LibrdfWorld.h"
#include "gtest/gtest.h"
#include <filesystem>


using namespace redland;

class LibrdfStreamTests : public ::testing::Test {

public:

    LibrdfStatement statement;
    LibrdfNode subject = LibrdfNode::fromUriString("http://www.dajobe.org/");
    LibrdfNode predicate = LibrdfNode::fromUriString("http://purl.org/dc/elements/1.1/creator");
    LibrdfNode resource = LibrdfNode::fromUriString("http://biscuits.org");

    LibrdfStreamTests() {
        statement.setSubject(subject);
        statement.setPredicate(predicate);
        statement.setResource(resource);
    }

    ~LibrdfStreamTests() override = default;
};

TEST_F(LibrdfStreamTests, TestGetStatement){
    LibrdfStorage storage;
    LibrdfModel model(storage);
    model.addStatement(statement);
    LibrdfStream stream = model.toStream();
    LibrdfStatement statement(stream.getStatement());
    LibrdfNode node = statement.getSubjectNode();
    std::string subject = node.str();
    ASSERT_STREQ("http://www.dajobe.org/", subject.c_str());
}





