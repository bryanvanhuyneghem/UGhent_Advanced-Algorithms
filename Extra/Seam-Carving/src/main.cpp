
#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include "seamcarving.h"

using namespace cv;

int main() {
  Mat image = imread("kasteel.jpg");

  if (image.empty()) {
    std::cerr << "Unable to load image, check if folder contains file!\n";
    exit(EXIT_FAILURE);
  }

  Mat carved_image = reduce_image_with_seam_carving(image, VERTICAL, 100);
  imwrite("result.jpg", carved_image);
  

  return 0;
}
