# THE LIST OF TOOLS AND THE CORRESPONDING SOURCE FILES
# ======================================================
set(TOOLS_LIST
  my-toy-tool
)

set(my-toy-tool_src
  main.cpp
)

configure_file(
    "${CMAKE_SOURCE_DIR}/cmake/cmake_create_symlink.cmake.in"
    "${CMAKE_BINARY_DIR}/cmake_create_symlink.cmake"
    IMMEDIATE @ONLY)

# CONFIGURE THE TOOL
# ==============================
foreach( tool ${TOOLS_LIST} )
  # Create an executable corresponding to 'tool'
  add_executable(
    ${tool}
    ${${tool}_src}
  )

  # Configure include directories for 'tool'
  target_include_directories(
    ${tool}
    PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/../include"
  )

  # On Darwin (unlike on Linux), undefined symbols in shared objects are not
  # allowed at the end of the link-edit. The tools defined here:
  #  - _are_ shared objects
  #  - reference symbols from LLVM shared libraries, i.e. symbols which are
  #    undefined until those shared objects are loaded in memory (and hence
  #    _undefined_ during static linking)
  # The build will fail with errors like this:
  #    "Undefined symbols for architecture x86_64"
  # with various LLVM symbols being undefined. Since those symbols are later
  # loaded and resolved at runtime, these errors are false positives.
  # This behaviour can be modified via the '-undefined' OS X linker flag as
  # follows.
  target_link_libraries(
    ${tool}
    "$<$<PLATFORM_ID:Darwin>:-undefined dynamic_lookup>"
    clangTooling
  )

  install(
    TARGETS ${tool}
    DESTINATION ${llvm_bindir}
  )

  install(
    CODE "execute_process(COMMAND ${CMAKE_COMMAND} -DSYMLINK_OLD=\"${llvm_bindir}/${tool}\" -DSYMLINK_NEW=${tool} -P ${CMAKE_BINARY_DIR}/cmake_create_symlink.cmake)"
  )
endforeach()