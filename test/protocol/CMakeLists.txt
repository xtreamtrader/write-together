add_executable(test_serialization_error test_serialization_error.cpp)
target_link_libraries(test_serialization_error protocol)
add_test(NAME serialization_error COMMAND test_serialization_error)

add_executable(test_serialization_signup test_serialization_signup.cpp)
target_link_libraries(test_serialization_signup protocol)
add_test(NAME serialization_signup COMMAND test_serialization_signup)

add_executable(test_serialization_signup_ok test_serialization_signup_ok.cpp)
target_link_libraries(test_serialization_signup_ok protocol)
add_test(NAME serialization_signup_ok COMMAND test_serialization_signup_ok)

add_executable(test_serialization_login test_serialization_login.cpp)
target_link_libraries(test_serialization_login protocol)
add_test(NAME serialization_login COMMAND test_serialization_login)

add_executable(test_serialization_logout test_serialization_logout.cpp)
target_link_libraries(test_serialization_logout protocol)
add_test(NAME serialization_logout COMMAND test_serialization_logout)

add_executable(test_serialization_profile test_serialization_profile.cpp)
target_link_libraries(test_serialization_profile protocol)
add_test(NAME serialization_profile COMMAND test_serialization_profile)

add_executable(test_serialization_profile_ok test_serialization_profile_ok.cpp)
target_link_libraries(test_serialization_profile_ok protocol)
add_test(NAME serialization_profile_ok COMMAND test_serialization_profile_ok)

add_executable(test_serialization_documents test_serialization_documents.cpp)
target_link_libraries(test_serialization_documents protocol)
add_test(NAME serialization_documents COMMAND test_serialization_documents)

add_executable(test_serialization_create test_serialization_create.cpp)
target_link_libraries(test_serialization_create protocol)
add_test(NAME serialization_create COMMAND test_serialization_create)

add_executable(test_serialization_open test_serialization_open.cpp)
target_link_libraries(test_serialization_open protocol)
add_test(NAME serialization_open COMMAND test_serialization_open)

add_executable(test_serialization_close test_serialization_close.cpp)
target_link_libraries(test_serialization_close protocol)
add_test(NAME serialization_close COMMAND test_serialization_close)

add_executable(test_serialization_document test_serialization_document.cpp)
target_link_libraries(test_serialization_document protocol)
add_test(NAME serialization_document COMMAND test_serialization_document)

add_executable(test_serialization_insert test_serialization_insert.cpp)
target_link_libraries(test_serialization_insert protocol crdt)
add_test(NAME serialization_insert COMMAND test_serialization_insert)

add_executable(test_serialization_erase test_serialization_erase.cpp)
target_link_libraries(test_serialization_erase protocol crdt)
add_test(NAME serialization_erase COMMAND test_serialization_erase)

add_executable(test_serialization_cursor test_serialization_cursor.cpp)
target_link_libraries(test_serialization_cursor protocol crdt)
add_test(NAME serialization_cursor COMMAND test_serialization_cursor)

add_executable(test_serialization_format test_serialization_format.cpp)
target_link_libraries(test_serialization_format protocol crdt)
add_test(NAME serialization_format COMMAND test_serialization_format)