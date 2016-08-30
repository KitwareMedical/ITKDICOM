#ifndef itkDICOMImageIO_h
#define itkDICOMImageIO_h

#include <fstream>
#include <stdio.h>
#include "itkImageIOBase.h"
#include "itkDCMTKFileReader.h"  // DCMTKItem, DCMTKSequence


class DicomImage;

namespace itk
{
/** \class DICOMImageIO
 *
 *  \brief Read DICOM image file format.
 */
class DICOMImageIO : public ImageIOBase
{
public:
  typedef DICOMImageIO              Self;
  typedef ImageIOBase               Superclass;
  typedef SmartPointer< Self >      Pointer;

  itkNewMacro(Self);
  itkTypeMacro(DICOMImageIO, ImageIOBase);

  virtual bool CanReadFile(const char*) ITK_OVERRIDE;

  virtual void ReadImageInformation() ITK_OVERRIDE;

  virtual void Read(void*) ITK_OVERRIDE;

  /*-------- This part of the interfaces deals with writing data. ----- */

  /** Determine the file type. Returns true if this ImageIO can write the
   * file specified. */
  virtual bool CanWriteFile(const char *) ITK_OVERRIDE;

  virtual void WriteImageInformation() ITK_OVERRIDE;

  virtual void Write(const void*) ITK_OVERRIDE;

  DICOMImageIO();
  ~DICOMImageIO();

private:
  ITK_DISALLOW_COPY_AND_ASSIGN(DICOMImageIO);

  void OpenDicomImage();

  /*----- internal helpers --------------------------------------------*/
  bool m_UseJPEGCodec;
  bool m_UseJPLSCodec;
  bool m_UseRLECodec;

  DicomImage* m_DImage;

  bool m_DicomImageSetByUser;

  double      m_RescaleSlope;
  double      m_RescaleIntercept;
  std::string m_LastFileName;
};
} // end namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkDICOMImageIO.hxx"
#endif

#endif // itkDICOMImageIO_h
