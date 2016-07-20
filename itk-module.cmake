set(DOCUMENTATION "Adds support for DICOM IO and anonymization.")

itk_module(DICOM
  DEPENDS
    ITKCommon
    ITKIOImageBase
    ITKDCMTK
    ITKIODCMTK
    ITKZLIB
  TEST_DEPENDS
    ITKTestKernel
  EXCLUDE_FROM_DEFAULT
  DESCRIPTION
    "${DOCUMENTATION}"
)
