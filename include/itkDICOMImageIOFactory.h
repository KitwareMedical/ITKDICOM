#ifndef itkDICOMImageIOFactory_h
#define itkDICOMImageIOFactory_h

#include "itkObjectFactoryBase.h"
#include "itkImageIOBase.h"

namespace itk
{
/** \class DICOMImageIOFactory
 * \brief Create instances of DICOMImageIO objects using an object factory.
 * \ingroup ITKIODICOM
 */
class DICOMImageIOFactory:public ObjectFactoryBase
{
public:
  /** Standard class typedefs. */
  typedef DICOMImageIOFactory        Self;
  typedef ObjectFactoryBase          Superclass;
  typedef SmartPointer< Self >       Pointer;
  typedef SmartPointer< const Self > ConstPointer;

  /** Class methods used to interface with the registered factories. */
  virtual const char * GetITKSourceVersion() const ITK_OVERRIDE;

  virtual const char * GetDescription() const ITK_OVERRIDE;

  /** Method for class instantiation. */
  itkFactorylessNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(DICOMImageIOFactory, ObjectFactoryBase);

  /** Register one factory of this type  */
  static void RegisterOneFactory()
  {
    DICOMImageIOFactory::Pointer dicomFactory = DICOMImageIOFactory::New();

    ObjectFactoryBase::RegisterFactoryInternal(dicomFactory);
  }

protected:
  DICOMImageIOFactory();
  ~DICOMImageIOFactory();

private:
  ITK_DISALLOW_COPY_AND_ASSIGN(DICOMImageIOFactory);
};
} // end namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkDICOMImageIOFactory.hxx"
#endif

#endif
