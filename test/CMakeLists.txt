itk_module_test()
set(ITKDICOMTests
  itkDICOMAnonymizationImageFilterTest.cpp
)

CreateTestDriver(ITKDICOM ITKIODCMTK "${ITKDICOMTests}")
set_property(TARGET ITKDICOMTestDriver PROPERTY CXX_STANDARD 11)

itk_add_test(NAME itkDICOMAnonymizationImageFilterTest
  COMMAND ITKDICOMTestDriver itkDICOMAnonymizationImageFilterTest
  ${PROJECT_SOURCE_DIR}/data/dicom/53320940.dcm
  ${PROJECT_SOURCE_DIR}/data/dicom/53320940_out.dcm
  ${PROJECT_SOURCE_DIR}/data/dicom/testProfile.txt
)

set_property(TEST itkDICOMAnonymizationImageFilterTest APPEND PROPERTY DEPENDS ITKData)
