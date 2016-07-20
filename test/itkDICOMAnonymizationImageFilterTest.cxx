/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

#include "itkImageSeriesReader.h"
#include "itkImageFileWriter.h"
#include "itkImageIOBase.h"
#include "itkImageIOFactory.h"
#include "itkDCMTKSeriesFileNames.h"
#include "itkPipelineMonitorImageFilter.h"
#include "itkStreamingImageFilter.h"
#include "itkDICOMImage.h"
#include "itkDICOMImageIO.h"


int itkDICOMAnonymizationImageFilterTest( int argc, char* argv[] )
{
  typedef itk::DICOMImageIO         ImageIOType;
  typedef itk::DCMTKSeriesFileNames SeriesFileNames;

  const char * inputFileName = argv[1];

  ImageIOType::Pointer imageIO = ImageIOType::New();
  imageIO->SetFileName(inputFileName);

  // Determine pixel type, component type, and number of dimensions
  imageIO->ReadImageInformation();

  typedef itk::ImageIOBase::IOPixelType IOPixelType;
  const IOPixelType pixelType = imageIO->GetPixelType();

  std::cout << "Pixel Type is "
            << itk::ImageIOBase::GetPixelTypeAsString( pixelType )
            << std::endl;

  typedef itk::ImageIOBase::IOComponentType IOComponentType;
  const IOComponentType componentType = imageIO->GetComponentType();

  std::cout << "Component Type is "
            << imageIO->GetComponentTypeAsString( componentType )
            << std::endl;

  const unsigned int imageDimension = imageIO->GetNumberOfDimensions();

  std::cout << "Image Dimension is " << imageDimension << std::endl;

  /*unsigned int numberOfDataPieces = 4;

  ImageIOType::Pointer dicomIO = ImageIOType::New();
  SeriesFileNames::Pointer filenameGenerator = SeriesFileNames::New();
  filenameGenerator->SetInputDirectory( argv[1] );

  ReaderType::Pointer reader = ReaderType::New();

  const ReaderType::FileNamesContainer & filenames =
    filenameGenerator->GetInputFileNames();

  std::cout << "Filenames:" << std::endl;

  for (auto & it : filenames)
    {
    std::cout << it << std::endl;
    }

  reader->SetFileNames( filenames );
  reader->SetImageIO( dicomIO );

  typedef itk::PipelineMonitorImageFilter<ImageType> MonitorFilter;
  MonitorFilter::Pointer monitor = MonitorFilter::New();
  monitor->SetInput( reader->GetOutput() );

  typedef itk::StreamingImageFilter<ImageType, ImageType> StreamingFilter;
  StreamingFilter::Pointer streamer = StreamingFilter::New();
  streamer->SetInput( monitor->GetOutput() );
  streamer->SetNumberOfStreamDivisions( numberOfDataPieces );

  try
    {
    //if( forceNoStreaming )
      {
      // no streaming
      reader->UseStreamingOff();
      streamer->Update();
      }
    else
      {
      // stream based on the number of z-slices
      reader->UseStreamingOn();
      reader->UpdateOutputInformation();
      numberOfDataPieces = reader->GetOutput()->GetLargestPossibleRegion().GetSize()[2];
      streamer->SetNumberOfStreamDivisions( numberOfDataPieces );
      streamer->Update();
      }
    }
  catch( itk::ExceptionObject & err )
    {
    std::cerr << "ExceptionObject caught !" << std::endl;
    std::cerr << err << std::endl;
    std::cerr << monitor;
    return EXIT_FAILURE;
    }

  std::cout << "Origin: " << reader->GetOutput()->GetOrigin() << std::endl;
  std::cout << "direction: " << reader->GetOutput()->GetDirection() << std::endl;
  std::cout << "Spacing: " << reader->GetOutput()->GetSpacing() << std::endl;
  //std::cout << "Expected Spacing: " << expectedSpacing << std::endl;*/

  return EXIT_SUCCESS;
}
