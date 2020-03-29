if [ $# -eq 0 ]
  then
    outfile="design.svd"
  else 
    outfile=$1
fi
hpp2plantuml -i ../semsim/*.h -i ../semsim/*/*.h -o KylesDesign.puml
java -jar plantuml.jar -tsvg KylesDesign.puml -o $outfile
