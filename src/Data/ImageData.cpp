#include "ImageData.h"
#include <stdlib.h>


ImageData::ImageData()
{
}

int* ImageData::getWidth()
{
    return &width_;
}

int* ImageData::getHeight()
{
    return &height_;
}

int* ImageData::getNumComponents()
{
    return &numComponents_;
}

const unsigned char * ImageData::getImageData() const
{
    return imageData_;
}

void ImageData::setImageData(unsigned char * data)
{
    imageData_ = data;
}


ImageData::~ImageData()
{
    free(imageData_); //required as stbi_image_free(imageData) should be called
}
