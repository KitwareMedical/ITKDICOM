itk_module_test()
set(ITKDICOMTests
  itkDICOMAnonymizationImageFilterTest.cxx
)

CreateTestDriver(ITKDICOM ITKIODCMTK "${ITKDICOMTests}")

itk_add_test(NAME itkDICOMAnonymizationImageFilterTest
  COMMAND ITKDICOMTestDriver itkDICOMAnonymizationImageFilterTest
  ${PROJECT_SOURCE_DIR}/data/dicom/53320940.dcm
)

set_property(TEST itkDICOMAnonymizationImageFilterTest APPEND PROPERTY DEPENDS ITKData)
