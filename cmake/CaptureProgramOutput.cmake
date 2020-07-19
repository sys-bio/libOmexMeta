# capture_command_output_to_file.cmake
# Arguments: COMMAND and OUTPUTFILE
execute_process(
 COMMAND ${COMMAND}
 OUTPUT_VARIABLE result
)
file(WRITE ${OUTPUTFILE} ${result})
# TODO: Fail if execute_process fails, for example