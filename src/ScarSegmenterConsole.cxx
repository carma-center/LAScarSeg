/**
 * Given the blood pool of the left atrium, extract the la-wall
 */
#include <iostream>
#include <string>


#include "localChanVeseWallSegmenter3D.h"
#include "utilities.hxx"


//itk
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"


int main(int argc, char** argv)
{
  if (argc < 4)
    {
      std::cerr<<"Parameters: originalImageFileName interiorMask outputImage\n";
      exit(-1);
    }

  std::string originalImageFileName(argv[1]);
  std::string labelImageFileName(argv[2]);
  std::string segmentedImageFileName(argv[3]);

  unsigned long numiter = 100;

  typedef short PixelType;
  typedef CLocalChanVeseWallSegmenter3D< PixelType > segmenter_t;

  typedef itk::Image< PixelType, 3 > ImageType;

  /* read novel image */
  ImageType::Pointer img, imgSample;
  img = readImage<ImageType>(originalImageFileName.c_str());

  /* read interiro mask */
  typedef segmenter_t::MaskImageType MaskImageType;
  MaskImageType::Pointer mask, maskSample, maskEpi, maskWall;
  mask = readImage<MaskImageType>(labelImageFileName.c_str());

  /* resample images*/
  ImageType::SpacingType spacing;
  spacing = mask->GetSpacing();
  spacing[0] *= 2.0;
  spacing[1] *= 2.0;
  imgSample = ResampleImage<ImageType, ImageType>(img, spacing);
  maskSample = ResampleImage<MaskImageType, MaskImageType>(mask, spacing);

  /* do segmentation */
  segmenter_t cv;
  cv.setImage(imgSample);
  cv.setMask(maskSample);

  cv.setNumIter(numiter);
  cv.setNBHDSize(10, 10, 3);
  cv.doSegmenation();

  maskEpi = cv.getTotalMask();

  /*extract the Wall*/
  maskWall = ExtractXORImage<MaskImageType, MaskImageType, MaskImageType>(maskSample, maskEpi);

  /* find distribution of scar*/
  MaskImageType::Pointer imScar;
  imScar = ScarSegmentation<ImageType, MaskImageType, MaskImageType>(imgSample, maskWall, maskSample);

  writeImage<segmenter_t::MaskImageType>(imScar, segmentedImageFileName.c_str());

  return 0;
}

