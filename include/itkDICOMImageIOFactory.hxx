#ifndef itkDICOMImageIOFactory_hxx
#define itkDICOMImageIOFactory_hxx

#include "itkDICOMImageIOFactory.h"
#include "itkDICOMImageIO.h"
#include "itkVersion.h"

namespace itk
{
DICOMImageIOFactory::DICOMImageIOFactory()
{
  this->RegisterOverride( "itkImageIOBase",
                          "itkDICOMImageIO",
                          "DICOM Image IO",
                          1,
                          CreateObjectFunction< DICOMImageIO >::New() );
}

DICOMImageIOFactory::~DICOMImageIOFactory()
{}

const char * DICOMImageIOFactory::GetITKSourceVersion() const
{
  return ITK_SOURCE_VERSION;
}

const char * DICOMImageIOFactory::GetDescription() const
{
  return "DICOM ImageIO Factory, allows the loading of DICOM images into Insight";
}

// Undocumented API used to register during static initialization.
// DO NOT CALL DIRECTLY.

static bool DICOMImageIOFactoryHasBeenRegistered;

void DICOMImageIOFactoryRegister__Private()
{
  if( ! DICOMImageIOFactoryHasBeenRegistered )
    {
    DICOMImageIOFactoryHasBeenRegistered = true;
    DICOMImageIOFactory::RegisterOneFactory();
    }
}

} // end namespace itk

#endif
