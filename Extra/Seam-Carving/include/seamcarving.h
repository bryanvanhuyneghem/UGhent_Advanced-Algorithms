#include <opencv2/core.hpp>
#include <vector>

using namespace cv;

enum SeamDirection { VERTICAL, HORIZONTAL };

Mat create_energy_image(const Mat& image);

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
std::vector<int> find_seam(const Mat& energy_image, SeamDirection direction);

Mat remove_seam(const Mat& orig_image, SeamDirection direction,
                const std::vector<int>& seam);

Mat reduce_image_with_seam_carving(const Mat& orig_image,
                                   SeamDirection direction, int iterations);
