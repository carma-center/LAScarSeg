/**
 * Given the blood pool of the left atrium, segment the scar tissue
 */

#include "ScarSegmenterCLP.h"

#include <iostream>
#include <string>

#include "localChanVeseWallSegmenter3D.h"
#include "utilities.hxx"

//itk
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"

int main(int argc, char** argv)
{
  PARSE_ARGS;

  typedef short PixelType;
  typedef CLocalChanVeseWallSegmenter3D< PixelType > segmenter_t;

  typedef itk::Image< PixelType, 3 > ImageType;

  /* read novel image */
  ImageType::Pointer img;
  img = readImage<ImageType>(originalImageFileName.c_str());

  typedef segmenter_t::MaskImageType MaskImageType;
  MaskImageType::Pointer maskEndo, maskWall;

  /* read endo mask */
  maskEndo = readImage<MaskImageType>(endoImageFileName.c_str());


  /* read wall mask */
  maskWall = readImage<MaskImageType>(wallImageFileName.c_str());

  /* find distribution of scar*/
  MaskImageType::Pointer imScar;
  imScar = ScarSegmentation<ImageType, MaskImageType, MaskImageType>(img, maskWall, maskEndo);

  imScar = ResampleImage<MaskImageType, MaskImageType>(imScar, img->GetSpacing());

  writeImage<segmenter_t::MaskImageType>(imScar, segmentedImageFileName.c_str());

  return 0;
}

