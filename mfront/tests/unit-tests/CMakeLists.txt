# a simple macro
macro(test_mfront test_arg)
  add_executable(mfront-${test_arg} EXCLUDE_FROM_ALL ${test_arg}.cxx)
  target_include_directories(mfront-${test_arg}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE ${PROJECT_SOURCE_DIR}/docs/mfront/abaqus/)
  target_link_libraries(mfront-${test_arg}
    TFELMFront TFELMaterial TFELMath
    TFELSystem  TFELGlossary
    TFELUtilities TFELException TFELTests ${TFEL_DL_LIBRARY})
  add_test(NAME mfront-${test_arg} COMMAND mfront-${test_arg})
  add_dependencies(check mfront-${test_arg})
  if((CMAKE_HOST_WIN32) AND (NOT MSYS))
    set_property(TEST mfront-${test_arg}
      PROPERTY DEPENDS "MFrontCastemBehaviours")
    set_property(TEST mfront-${test_arg}
      PROPERTY ENVIRONMENT "PATH=$<TARGET_FILE_DIR:TFELMFront>\;$<TARGET_FILE_DIR:MFrontLogStream>\;$<TARGET_FILE_DIR:TFELMaterial>\;$<TARGET_FILE_DIR:TFELNUMODIS>\;$<TARGET_FILE_DIR:TFELMathParser>\;$<TARGET_FILE_DIR:TFELGlossary>\;$<TARGET_FILE_DIR:TFELSystem>\;$<TARGET_FILE_DIR:TFELUtilities>\;$<TARGET_FILE_DIR:TFELException>\;$<TARGET_FILE_DIR:TFELTests>\;$<TARGET_FILE_DIR:TFELConfig>\;$<TARGET_FILE_DIR:TFELUnicodeSupport>\;$ENV{PATH}")
  endif((CMAKE_HOST_WIN32) AND (NOT MSYS))
endmacro(test_mfront)

macro(test_mfront2 test_arg)
  configure_file("${PROJECT_SOURCE_DIR}/mfront/tests/unit-tests/${test_arg}.cxx.in"
    "${PROJECT_BINARY_DIR}/mfront/tests/unit-tests/${test_arg}.cxx" @ONLY)
  add_executable(mfront-${test_arg} EXCLUDE_FROM_ALL
    "${PROJECT_BINARY_DIR}/mfront/tests/unit-tests/${test_arg}.cxx")
  add_test(NAME mfront-${test_arg} COMMAND mfront-${test_arg})
  add_dependencies(check mfront-${test_arg})
  if((CMAKE_HOST_WIN32) AND (NOT MSYS))
    set_property(TEST mfront-${test_arg}
      PROPERTY DEPENDS "MFrontCastemBehaviours"
      PROPERTY ENVIRONMENT "PATH=$<TARGET_FILE_DIR:TFELMFront>\;$<TARGET_FILE_DIR:MFrontLogStream>\;$<TARGET_FILE_DIR:TFELMaterial>\;$<TARGET_FILE_DIR:TFELNUMODIS>\;$<TARGET_FILE_DIR:TFELMathParser>\;$<TARGET_FILE_DIR:TFELGlossary>\;$<TARGET_FILE_DIR:TFELSystem>\;$<TARGET_FILE_DIR:TFELUtilities>\;$<TARGET_FILE_DIR:TFELException>\;$<TARGET_FILE_DIR:TFELTests>\;$<TARGET_FILE_DIR:TFELConfig>\;$<TARGET_FILE_DIR:TFELUnicodeSupport>\;$ENV{PATH}")
  endif((CMAKE_HOST_WIN32) AND (NOT MSYS))
  target_link_libraries(mfront-${test_arg}
    TFELMFront TFELMaterial TFELMath
    TFELSystem  TFELGlossary
    TFELUtilities TFELException TFELTests)
endmacro(test_mfront2)

macro(test_mfront3 test_arg)
  add_executable(mfront-${test_arg} EXCLUDE_FROM_ALL ${test_arg}.cxx)
  add_test(NAME mfront-${test_arg} COMMAND mfront-${test_arg})
  add_dependencies(check mfront-${test_arg})
  if((CMAKE_HOST_WIN32) AND (NOT MSYS))
    set_property(TEST mfront-${test_arg}
      PROPERTY DEPENDS "MFrontCastemBehaviours"
      PROPERTY ENVIRONMENT "PATH=$<TARGET_FILE_DIR:TFELMFront>\;$<TARGET_FILE_DIR:MFrontLogStream>\;$<TARGET_FILE_DIR:TFELMaterial>\;$<TARGET_FILE_DIR:TFELNUMODIS>\;$<TARGET_FILE_DIR:TFELMathParser>\;$<TARGET_FILE_DIR:TFELGlossary>\;$<TARGET_FILE_DIR:TFELSystem>\;$<TARGET_FILE_DIR:TFELUtilities>\;$<TARGET_FILE_DIR:TFELException>\;$<TARGET_FILE_DIR:TFELTests>\;$<TARGET_FILE_DIR:TFELConfig>\;$<TARGET_FILE_DIR:TFELUnicodeSupport>\;$ENV{PATH}")
  endif((CMAKE_HOST_WIN32) AND (NOT MSYS))
  target_link_libraries(mfront-${test_arg}
    TFELMFront TFELMaterial TFELMath
    TFELSystem  TFELGlossary
    TFELUtilities TFELException TFELTests)
endmacro(test_mfront3)

test_mfront(DSLTest)
test_mfront(ComputeStiffnessTensorTest)
test_mfront2(DSLTest2)
test_mfront2(SwellingTest)
test_mfront(BehaviourDataTest)
test_mfront(SupportedTypesTest)
test_mfront(BehaviourDescriptionTest)
test_mfront(SlipSystemsTest)
test_mfront(BehaviourDescriptionBoundsHandlingTest)
test_mfront3(TargetsDescriptionTest)
test_mfront3(StandardElasticityBrickTest)
test_mfront3(StandardElastoViscoPlasticityBrickTest)
test_mfront3(LocalDataStructureTest)

test_mfront(UMATTest)
test_mfront(VUMATTest_dp)
test_mfront(VUMATTest_sp)

test_mfront(OrthotropicAxesConventionTest)
