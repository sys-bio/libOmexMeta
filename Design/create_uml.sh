if [ $# -eq 0 ]
  then
    outfile="$(pwd)"
  else
    outfile=$1
fi
hpp2plantuml -i ../semsim/*.h -i ../semsim/*/*.h -o KylesDesign.puml
java -jar plantuml.jar -tsvg KylesDesign.puml -o $outfile
