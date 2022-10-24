// Project UID af1f95f547e44c8ea88730dfb185559d

#include "Matrix.h"
#include "Image_test_helpers.h"
#include "unit_test_framework.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>

using namespace std;


// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Sets various pixels in a 2x2 Image and checks
// that Image_print produces the correct output.
TEST(test_print_basic) {
  Image *img = new Image; // create an Image in dynamic memory

  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};

  Image_init(img, 2, 2);
  Image_set_pixel(img, 0, 0, red);
  Image_set_pixel(img, 0, 1, green);
  Image_set_pixel(img, 1, 0, blue);
  Image_set_pixel(img, 1, 1, white);

  // Capture our output
  ostringstream s;
  Image_print(img, s);

  // Correct output
  ostringstream correct;
  correct << "P3\n2 2\n255\n";
  correct << "255 0 0 0 255 0 \n";
  correct << "0 0 255 255 255 255 \n";
  ASSERT_EQUAL(s.str(), correct.str());

  delete img; // delete the Image
}

TEST(test_image_init){
  Image *img = new Image;
  string inp1 = "P3\n2 2\n255\n255 0 15 13 211 1 \n0 4 55 17 86 111 \n";

  istringstream inp(inp1); 

  Image_init(img, inp);
  ostringstream output;

  Image_print(img, output);
  ASSERT_EQUAL(inp.str() ,output.str());

  delete img;
}

TEST(test_image_set){
  Image *img = new Image;
  ostringstream actual;

  ostringstream expected;
  expected << "P3\n3 3\n255\n";
  expected << "0 0 0 0 0 0 0 0 0";
  expected << "0 0 0 1 5 10 0 0 0";
  expected << "0 0 0 100 1 254 5 17 85";

  Pixel zero;
  zero.r = 0;
  zero.g = 0;
  zero.b = 0;

  Pixel onebyone;
  onebyone.r = 1;
  onebyone.g = 5;
  onebyone.b = 10;

  Pixel twobytwo;
  twobytwo.r = 5;
  twobytwo.g = 17;
  twobytwo.b = 85;

  Pixel onebytwo;
  onebytwo.r = 100;
  onebytwo.r = 1;
  onebytwo.r = 254;

  Image_init(img, 3, 3);
  Image_fill(img, zero);

  Image_set_pixel(img, 1, 1, onebyone);
  Image_set_pixel(img, 2, 2, twobytwo);
  Image_set_pixel(img, 1, 2, onebytwo);

  Image_print(img, actual);

  ASSERT_EQUAL(expected.str(), actual.str());
  delete img;
}

TEST(test_image_width){
  Image *img = new Image;
  Image_init(img, 3, 4);

  int width = Image_width(img);

  ASSERT_EQUAL(width, 3);
  delete img;
}

TEST(test_image_height){
  Image *img = new Image;
  Image_init(img, 3, 4);

  int width = Image_height(img);

  ASSERT_EQUAL(width, 4);
  delete img;
}

TEST(test_image_get_set){
  Image *img = new Image;

  Pixel zero;
  zero.r = 0;
  zero.g = 0;
  zero.b = 0;

  Pixel onebyone;
  onebyone.r = 1;
  onebyone.g = 5;
  onebyone.b = 10;

  Pixel twobytwo;
  twobytwo.r = 5;
  twobytwo.g = 17;
  twobytwo.b = 85;

  Pixel onebytwo;
  onebytwo.r = 100;
  onebytwo.r = 1;
  onebytwo.r = 254;

  Image_init(img, 3, 3);
  Image_fill(img, zero);

  Image_set_pixel(img, 1, 1, onebyone);
  Image_set_pixel(img, 2, 2, twobytwo);
  Image_set_pixel(img, 1, 2, onebytwo);

  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 1, 1), onebyone));
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 2, 2), twobytwo));
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 1, 2), onebytwo));
}

TEST(test_image_fill){
  Image *img = new Image;
  Image_init(img, 4, 4);
  ostringstream actual;
  ostringstream expected;

  Pixel zero;
  zero.r = 0;
  zero.g = 0;
  zero.b = 0;

  Image_fill(img, zero);
  Image_print(img, actual);

  expected << "P3\n4 4\n255\n";
  expected << "0 0 0 0 0 0 0 0 0 0 0 0";
  expected << "0 0 0 0 0 0 0 0 0 0 0 0";
  expected << "0 0 0 0 0 0 0 0 0 0 0 0";
  expected << "0 0 0 0 0 0 0 0 0 0 0 0";

  ASSERT_EQUAL(actual.str(), expected.str());

  delete img;
}

// IMPLEMENT YOUR TEST FUNCTIONS HERE
// You are encouraged to use any functions from Image_test_helpers.h as needed.

// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
