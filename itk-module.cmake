set(DOCUMENTATION "Adds support for DICOM IO and anonymization.")

itk_module(DICOM
  DEPENDS
    ITKCommon
    ITKIODCMTK
  TEST_DEPENDS
    ITKTestKernel
  EXCLUDE_FROM_DEFAULT
  DESCRIPTION
    "${DOCUMENTATION}"
)
