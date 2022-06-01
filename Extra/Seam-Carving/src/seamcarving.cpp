
#include "seamcarving.h"

#include <cassert>
#include <cstdio>
#include <list>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <queue>
#include <vector>

#include "graaf.hpp"
#include "kortste-pad.h"

using namespace cv;

#define DEMO

Mat create_energy_image(const Mat& image) {
  Mat energy_image;

  // ruisonderdrukking
  GaussianBlur(image, energy_image, Size(3, 3), 0, 0, BORDER_DEFAULT);

  // omzetting naar grijswaarden
  cvtColor(energy_image, energy_image, COLOR_BGR2GRAY);

  // Scharr berekent de gradient van een image in ofwel de x of de y richting
  Mat dx, dy;
  Scharr(energy_image, dx, CV_16S, 1, 0);
  Scharr(energy_image, dy, CV_16S, 0, 1);

  // We normaliseren beide gradienten naar 8-bit (waardes tussen 0-255)
  convertScaleAbs(dx, dx);
  convertScaleAbs(dy, dy);

  // Waarde voor elke positie wordt voor 50% in x-richting en 50% in y-richting
  // bepaald
  addWeighted(dx, 0.5, dy, 0.5, 0, energy_image);

  return std::move(energy_image);
}

/**
 * @brief Zoekt de naad in een afbeelding
 *
 * @param energy_image een matrix met waarden tussen 0 en 255 met dezelfde
 * dimensies als de originele afbeelding
 * @param direction richting van de naad
 * @return std::vector<int> een lijst van kolomnummers (bij een horizontale
 * naad) of rijnummers (bij een verticale naad) die de coordinaten van de naad
 * aangeeft.
 */
std::vector<int> find_seam(const Mat& energy_image, SeamDirection direction) {
 
  auto geefknoopnr = [&energy_image](int row, int col) {
    assert(row < energy_image.rows);
    assert(col < energy_image.cols);

    return row * energy_image.cols + col;
  };

  auto geefrow = [&energy_image](int knoopnr) {
    return knoopnr / energy_image.cols;
  };

  auto geefcol = [&energy_image](int knoopnr) {
    return knoopnr % energy_image.cols;
  };

  //VUL HIER AAN

}


Mat remove_seam(const Mat& orig_image, SeamDirection direction,
                const std::vector<int>& seam) {
  Range rowRange =
      direction == HORIZONTAL ? Range(0, orig_image.rows - 1) : Range::all();
  Range colRange =
      direction == HORIZONTAL ? Range::all() : Range(0, orig_image.cols - 1);
  Mat reduced_image(orig_image.clone(), rowRange, colRange);

  if (direction == HORIZONTAL) {
    for (int col = 0; col < reduced_image.cols; col++) {
      if (seam[col] == reduced_image.rows) continue;

      orig_image.col(col)
          .rowRange(seam[col] + 1, orig_image.rows)
          .copyTo(
              reduced_image.col(col).rowRange(seam[col], reduced_image.rows));
    }
  } else {
    for (int row = 0; row < reduced_image.rows; row++) {
      if (seam[row] == reduced_image.cols) continue;

      orig_image.row(row)
          .colRange(seam[row] + 1, orig_image.cols)
          .copyTo(
              reduced_image.row(row).colRange(seam[row], reduced_image.cols));
    }
  }

  return reduced_image;
}

Mat reduce_image_with_seam_carving(const Mat& orig_image,
                                   SeamDirection direction) {
  Mat energy_image = create_energy_image(orig_image);

#ifdef DEMO
  imwrite("energy_image.png", energy_image);
#endif

  std::vector<int> seam = find_seam(energy_image, direction);

  assert(seam.size() ==
         (direction == HORIZONTAL ? orig_image.cols : orig_image.rows));

#ifdef DEMO
  // we maken een afbeelding met de seam ingekleurd als zwart
  Mat orig_image_with_seam(orig_image);

  if (direction == HORIZONTAL) {
    for (int col = 0; col < orig_image_with_seam.cols; col++) {
      orig_image_with_seam.at<Vec3b>(seam[col], col) = Vec3b(0, 0, 0);
    }
  } else {
    for (int row = 0; row < orig_image_with_seam.rows; row++) {
      orig_image_with_seam.at<Vec3b>(row, seam[row]) = Vec3b(0, 0, 0);
    }
  }

  imwrite("image_with_seam.jpg", orig_image_with_seam);

#endif

  return remove_seam(orig_image, direction, seam);
};

Mat reduce_image_with_seam_carving(const Mat& orig_image,
                                   SeamDirection direction, int iterations) {
  Mat new_image = orig_image;

  for (int i = 0; i < iterations; i++) {
    new_image = reduce_image_with_seam_carving(new_image, direction);

#ifdef DEMO
    // move image_with_seam.jpg
    std::stringstream with_seam_filename;
    with_seam_filename << "image_with_seam_" << i << ".jpg";
    rename("image_with_seam.jpg", with_seam_filename.str().c_str());

    std::stringstream filename;
    filename << "round" << i << ".jpg";
    imwrite(filename.str(), new_image);
#endif
  }

  return new_image;
}
