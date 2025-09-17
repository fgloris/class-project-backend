cmake_minimum_required(VERSION 3.22)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_CXX_STANDARD 23)
project(backend)

option(DEBUG "Enable debug mode" OFF)

# Add common directory to include path
include_directories(${CMAKE_SOURCE_DIR})

# use boost 1.89 built from source.
set(BOOST_ROOT "/usr/local")
set(Boost_INCLUDE_DIR "/usr/local/include")
set(Boost_LIBRARY_DIR "/usr/local/lib")

set(PROTO_GEN_DIR "${CMAKE_BINARY_DIR}/generated")
file(MAKE_DIRECTORY ${PROTO_GEN_DIR})

set(user_proto_srcs "${PROTO_GEN_DIR}/user.pb.cc")
set(user_proto_hdrs "${PROTO_GEN_DIR}/user.pb.h")
set(user_grpc_srcs "${PROTO_GEN_DIR}/user.grpc.pb.cc")
set(user_grpc_hdrs "${PROTO_GEN_DIR}/user.grpc.pb.h")

find_program(PROTOBUF_PROTOC protoc)
find_program(GRPC_CPP_PLUGIN_EXECUTABLE grpc_cpp_plugin)
message(STATUS "find protoc: ${PROTOBUF_PROTOC}, gRPC plugin: ${GRPC_CPP_PLUGIN_EXECUTABLE}")

add_custom_command(
  OUTPUT "${user_proto_srcs}" "${user_proto_hdrs}" "${user_grpc_srcs}" "${user_grpc_hdrs}"
  COMMAND ${PROTOBUF_PROTOC}
  ARGS --grpc_out "${PROTO_GEN_DIR}"
  --cpp_out "${PROTO_GEN_DIR}"
  -I "${user_proto_path}"
  --plugin=protoc-gen-grpc="${GRPC_CPP_PLUGIN_EXECUTABLE}"
  "${user_proto}"
  DEPENDS "${user_proto}"
  COMMENT "Generating user proto files..."
)

add_custom_target(proto_gen DEPENDS
  ${user_proto_srcs}
  ${user_proto_hdrs}
  ${user_grpc_srcs}
  ${user_grpc_hdrs}
)

set(PROTO_SRCS 
  ${user_proto_srcs}
  ${user_grpc_srcs}
)
set(PROTO_HDRS 
  ${user_proto_hdrs}
  ${user_grpc_hdrs}
)

file(GLOB_RECURSE COMMON_SOURCES "common/*/*.cpp")

add_subdirectory(third_parties/jwt-cpp)
add_subdirectory(user_service)
