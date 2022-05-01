add_executable(testApp test.c
../src/input.c ../src/token.c
../src/syntax_tree.c
../src/optimise.c
../src/range.c
../src/evaluate.c)

target_include_directories(testApp PRIVATE ${PROJECT_SOURCE_DIR}/inc
)

set_target_properties(testApp PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
