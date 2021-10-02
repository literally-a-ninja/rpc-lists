cmake_minimum_required(VERSION 3.12)
project(rpc VERSION 1.0)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(rpc_common STATIC src/rpc/list_xdr.c src/util.c)
target_include_directories(rpc_common PUBLIC /usr/include/tirpc)
target_link_libraries(rpc_common -ltirpc)

set(EXECUTABLE_OUTPUT_PATH build)

link_libraries(rpc_common)

add_executable(rpc_cl src/client.c src/rpc/list_clnt.c)
add_executable(rpc_sv src/server.c src/rpc/list_svc.c)

