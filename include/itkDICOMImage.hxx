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

#ifndef itkDICOMImage_hxx
#define itkDICOMImage_hxx

#include "itkDICOMImage.h"

namespace itk
{

template< typename TPixel, unsigned int VImageDimension >
DICOMImage< TPixel, VImageDimension >
::DICOMImage()
{
  m_DICOMMetaData = new MetaDataDictionary;
}

template< typename TPixel, unsigned int VImageDimension >
DICOMImage< TPixel, VImageDimension >
::~DICOMImage()
{
  delete m_DICOMMetaData;
}

template< typename TPixel, unsigned int VImageDimension >
void
DICOMImage< TPixel, VImageDimension >
::PrintSelf(std::ostream & os, Indent indent) const
{
  Superclass::PrintSelf(os, indent);
}

template< typename TPixel, unsigned int VImageDimension >
MetaDataDictionary &
DICOMImage< TPixel, VImageDimension >
::GetDICOMMetaData(void)
{
  return *m_DICOMMetaData;
}

template< typename TPixel, unsigned int VImageDimension >
const MetaDataDictionary &
DICOMImage< TPixel, VImageDimension >
::GetDICOMMetaData(void) const
{
  return *m_DICOMMetaData;
}

template< typename TPixel, unsigned int VImageDimension >
void
DICOMImage< TPixel, VImageDimension >
::SetDICOMMetaData(const MetaDataDictionary & rhs)
{
  *m_DICOMMetaData = rhs;
}

} // end namespace itk

#endif
