#include <cmath>
#include "image.h"

using namespace std;

// HW1 #1
// float x,y: inexact coordinates
// int c: channel
// returns the nearest neibor to pixel (x,y,c)
float Image::pixel_nearest(float x, float y, int c) const
  {
  // Since you are inside class Image you can
  // use the member function pixel(a,b,c)
  
  // TODO: Your code here
  int rx = round(x);
  int ry = round(y);
  //printf("%f,%f\t%d,%d\n", x, y, rx, ry);

  return this->clamped_pixel(rx, ry, c);
  }

// HW1 #1
// float x,y: inexact coordinates
// int c: channel
// returns the bilinearly interpolated pixel (x,y,c)
float Image::pixel_bilinear(float x, float y, int c) const
  {
  // Since you are inside class Image you can
  // use the member function pixel(a,b,c)
  
  
  // TODO: Your code here


  int fx = floor(x);
  int cx = ceil(x);
  int fy = floor(y);
  int cy = ceil(y);

  float a1 = (cx - x) * (y - fy);
  float a2 = (x - fx) * (y - fy);
  float a3 = (cx - x) * (cy - y);
  float a4 = (x - fx) * (cy - y);

  float v1 = this->clamped_pixel(fx, cy, c);
  float v2 = this->clamped_pixel(cx, cy, c);
  float v3 = this->clamped_pixel(fx, fy, c);
  float v4 = this->clamped_pixel(cx, fy, c);

  float val = a1 * v1 + a2 * v2 + a3 * v3 + a4 * v4;
  return val;





//  int fx = floor(x);
//  int cx = ceil(x);
//  int fy = floor(y);
//  int cy = ceil(y);
//
//
//
//  float vffx = (float) (x - fx) * this->clamped_pixel(fx, fy, c);
//  float vfcx = (float) (cx - x) * this->clamped_pixel(cx, fy, c);
//  float vfx  = vffx + vfcx;
//
//  float vcfx = (float) (x - fx) * this->clamped_pixel(fx, cy, c);
//  float vccx = (float) (cx - x) * this->clamped_pixel(cx, cy, c);
//  float vcx = vcfx + vccx;
//
//
//  float vfy = (float) (y - fy) * vfx;
//  float vcy = (float) (cy - y) * vcx;
//
//  float v = vfy + vcy;
//
//  return v;
  }

// HW1 #1
// int w,h: size of new image
// const Image& im: input image
// return new Image of size (w,h,im.c)
Image nearest_resize(const Image& im, int w, int h)
  {
  Image ret(w,h,im.c);

  float scale_x = (float) w / im.w;
  float scale_y = (float) h / im.h;

  for (int c = 0; c < ret.c; c ++) {
      for (int y = 0; y < h; y ++) {
          float sy = -0.5 + (y + 0.5) / scale_y;
          for (int x = 0; x < w; x ++) {
              float sx = -0.5 + (x + 0.5) / scale_x;
              ret(x, y, c) = im.pixel_nearest(sx, sy, c);
          }
      }
  }
  
  return ret;
  }


// HW1 #1
// int w,h: size of new image
// const Image& im: input image
// return new Image of size (w,h,im.c)
Image bilinear_resize(const Image& im, int w, int h)
  {
  
  // TODO: Your code here
  Image ret(w,h,im.c);

  float scale_x = (float) w / im.w;
  float scale_y = (float) h / im.h;

  for (int c = 0; c < ret.c; c ++) {
      for (int y = 0; y < h; y ++) {
          float sy = -0.5 + (float) (y + 0.5) / scale_y;
          for (int x = 0; x < w; x ++) {
              float sx = -0.5 + (float) (x + 0.5) / scale_x;
              ret(x, y, c) = im.pixel_bilinear(sx, sy, c);
          }
      }
  }
  
  return ret;
  }


