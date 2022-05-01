add_executable(app main.c
                   token.c
                   input.c
                   syntax_tree.c
                   optimise.c
                   range.c
                   evaluate.c)

target_include_directories(app PRIVATE ${PROJECT_SOURCE_DIR}/inc
)

set_target_properties(app PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
