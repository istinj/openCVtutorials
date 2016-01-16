FILE(REMOVE_RECURSE
  "CMakeFiles/my_kernel.dir/src/myKernel.cpp.o"
  "../bin/my_kernel.pdb"
  "../bin/my_kernel"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang CXX)
  INCLUDE(CMakeFiles/my_kernel.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
