from semsim import RasqalQuery, RasqalQueryResult
from sys import argv

# if three args passed assume first query is a graph-based query and run
# second query on that

print("**********************************************************")
query1 = RasqalQuery(argv[1], "rdfxml", True);
query_result1 = query1.run(argv[2])
if len(argv) >= 4:
    rdf1 = query_result1.toRDFString("turtle");
print(query_result1.asList())
print("**********************************************************")

if len(argv) >= 4:
    print("\nSecond query\n\n")
    print("**********************************************************")
    query2 = RasqalQuery(rdf1)
    query2.run(argv[3]).toString()
    print("**********************************************************")
