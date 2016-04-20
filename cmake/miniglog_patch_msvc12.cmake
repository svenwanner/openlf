cmake_minimum_required(VERSION 2.8)

message("proc ${FILENAME}")

file(READ "${FILENAME}" BUF)
string(REPLACE "// Log severity level constants."
       "#undef ERROR" BUF "${BUF}")
file(WRITE ${FILENAME} "${BUF}")
