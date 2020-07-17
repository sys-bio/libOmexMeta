#include "RedlandWrapper.h"


int main(){
    LibrdfStorage storage;
    LibrdfModel model(storage.get());
    LibrdfStatement statement = LibrdfStatement::fromRawNodePtrs(
            LibrdfNode::fromUriString("https//subject.com").get(),
            LibrdfNode::fromUriString("https//predicate.com").get(),
            LibrdfNode::fromUriString("https//resource.com").get()
    );
    model.addStatement(statement);
    statement.freeStatement();
    model.freeModel();
    storage.freeStorage();
    return 0;
}