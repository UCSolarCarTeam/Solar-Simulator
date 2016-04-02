#pragma once
class ImageData
{
public:
    ImageData();
    int* getWidth();
    int* getHeight();
    int* getNumComponents();
    const unsigned char* getImageData() const;
    void setImageData(unsigned char* data);
    ~ImageData();
private:
    unsigned char* imageData_;
    int width_;
    int height_;
    int numComponents_;
};

