#include <cstdio>
#include <cstring>
#include <cassert>
#include <cmath>

#include "image.h"

using namespace std;

#define GRAY_R_C 0.299
#define GRAY_G_C 0.587
#define GRAY_B_C 0.114

// HW0 #3
// const Image& im: input image
// return the corresponding grayscale image
Image rgb_to_grayscale(const Image& im)
  {
  assert(im.c == 3); // only accept RGB images
  Image gray(im.w,im.h,1); // create a new grayscale image (note: 1 channel)
  
  // TODO: calculate the pixels of 'gray'

  int gray_size = gray.h * gray.w;

  for (int i = 0; i < gray.h * gray.w; i ++) {
    gray.data[i] = ( (im.data[i] * GRAY_R_C) + (im.data[i + gray_size] * GRAY_G_C) + (im.data[i + 2 * gray_size] * GRAY_B_C) );
  }

  return gray;
  }



// Example function that changes the color of a grayscale image
Image grayscale_to_rgb(const Image& im, float r, float g, float b)
  {
  assert(im.c == 1);
  Image rgb(im.w,im.h,3);
  
  for(int q2=0;q2<im.h;q2++)for(int q1=0;q1<im.w;q1++)
    {
    rgb(q1,q2,0)=r*im(q1,q2);
    rgb(q1,q2,1)=g*im(q1,q2);
    rgb(q1,q2,2)=b*im(q1,q2);
    }
  
  return rgb;
  }




// HW0 #4
// Image& im: input image to be modified in-place
// int c: which channel to shift
// float v: how much to shift
void shift_image(Image& im, int c, float v)
  {
  assert(c>=0 && c<im.c); // needs to be a valid channel
  
  // TODO: shift all the pixels at the specified channel

  for (int i = c * im.h * im.w; i < (c+1) * im.h * im.w; i++) {
    im.data[i] += v;
  } 
 
  return;  
  }

// HW0 #8
// Image& im: input image to be modified in-place
// int c: which channel to scale
// float v: how much to scale
void scale_image(Image& im, int c, float v)
  {
  assert(c>=0 && c<im.c); // needs to be a valid channel
  
  // TODO: scale all the pixels at the specified channel
  

  for (int i = c * im.h * im.w; i < (c+1) * im.h * im.w; i++) {
    im.data[i] *= v;
  } 
 
  return;
  }


// HW0 #5
// Image& im: input image to be modified in-place
void clamp_image(Image& im)
  {
  // TODO: clamp all the pixels in all channel to be between 0 and 1
  
  for (int i = 0; i < im.c * im.h * im.w; i ++) {
    im.data[i] = (im.data[i] < 0) ? 0 : (im.data[i] > 1 ? 1 : im.data[i]);
  }
  
  }

// These might be handy
float max(float a, float b, float c)
  {
  return max({a,b,c});
  }

float min(float a, float b, float c)
  {
  return min({a,b,c});
  }


// HW0 #6
// Image& im: input image to be modified in-place
void rgb_to_hsv(Image& im)
  {
  assert(im.c==3 && "only works for 3-channels images");
  
  // TODO: Convert all pixels from RGB format to HSV format
  
  int im_size = im.h * im.w;

  for (int i = 0; i < im_size; i ++) {
    float R = im.data[i];
    float G = im.data[i + im_size];
    float B = im.data[i + 2 * im_size];

    float V = max (max(R, G), B);
    float m = min (min(R, G), B);

    float C = V - m;

    float S = 0.0;
    if (V)
      S =  C / V;

    float H = 0;
    float Hp = 0;

    if (C) {

      if (V == R) 
        Hp = (G - B) / C;
      else if (V == G) 
        Hp = (B - R) / C + 2;
      else 
        Hp = (R - G) / C + 4;

      H = (Hp < 0) ? (Hp / 6 + 1) : (Hp / 6);

      while (H >= 1)
        H --;
      while (H < 0)
        H ++;
    }


    im.data[i] = H;
    im.data[i + im_size] = S;
    im.data[i + 2 * im_size] = V;
  }

  return;
  
  }

// HW0 #7
// Image& im: input image to be modified in-place
void hsv_to_rgb(Image& im)
  {
  assert(im.c==3 && "only works for 3-channels images");
  
  // TODO: Convert all pixels from HSV format to RGB format
   int im_size = im.h * im.w;

  for (int i = 0; i < im_size; i ++) {
    float H = im.data[i];
    float S = im.data[i + im_size];
    float V = im.data[i + 2 * im_size];

    float C = S * V;

    float X = C * (1 - fabs( fmod((6 * H), 2) - 1));

    float m = V - C;

    float Rp, Gp, Bp;

    if (H >= 0 && H < (float) 1/6) {
      Rp = C;
      Gp = X;
      Bp = 0;
    }

    else if ( H >= (float) 1/6 && H < (float) 2/6) {
      Rp = X;
      Gp = C;
      Bp = 0;
    }

    else if ( H >= (float) 2/6 && H < (float) 3/6) {
      Rp = 0;
      Gp = C;
      Bp = X;
    }

    else if ( H >= (float) 3/6 && H < (float) 4/6) {
      Rp = 0;
      Gp = X;
      Bp = C;
    }

    else if ( H >= (float) 4/6 && H < (float) 5/6) {
      Rp = X;
      Gp = 0;
      Bp = C;
    }

    else {
      Rp = C;
      Gp = 0;
      Bp = X;
    }

 

    float R = Rp + m;
    float G = Gp + m;
    float B = Bp + m;


    im.data[i] = R;
    im.data[i + im_size] = G;
    im.data[i + 2 * im_size] = B;

  }

  return;
  }

// HW0 #9
// Image& im: input image to be modified in-place
void rgb_to_lch(Image& im)
  {
  assert(im.c==3 && "only works for 3-channels images");
  
  // TODO: Convert all pixels from RGB format to LCH format
  
  
  NOT_IMPLEMENTED();
  
  }

// HW0 #9
// Image& im: input image to be modified in-place
void lch_to_rgb(Image& im)
  {
  assert(im.c==3 && "only works for 3-channels images");
  
  // TODO: Convert all pixels from LCH format to RGB format
  
  NOT_IMPLEMENTED();
  
  }



// Implementation of member functions
void Image::clamp(void) { clamp_image(*this); }
void Image::shift(int c, float v) { shift_image(*this,c,v); }
void Image::scale(int c, float v) { scale_image(*this,c,v); }

void Image::HSVtoRGB(void) { hsv_to_rgb(*this); }
void Image::RGBtoHSV(void) { rgb_to_hsv(*this); }
void Image::LCHtoRGB(void) { lch_to_rgb(*this); }
void Image::RGBtoLCH(void) { rgb_to_lch(*this); }
