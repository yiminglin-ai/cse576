#include <cmath>
#include "image.h"

using namespace std;

// HW1 #1
// float x,y: inexact coordinates
// int c: channel
// returns the nearest neighbor to pixel (x,y,c)
float Image::pixel_nearest(float x, float y, int c) const
  {
  // Since you are inside class Image you can
  // use the member function pixel(a,b,c)
  
  // TODO: Your code here
  return clamped_pixel(rint(x), rint(y), c);
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
  int x_low, x_high, y_low, y_high;
  x_low = floorf(x);
  y_low = floorf(y);
  x_high = ceilf(x);
  y_high = ceilf(y);

  float p0 = x - x_low;
  float p1 = x_high - x;
  float p2 = y - y_low;
  float p3 = y_high - y;

  float v0 = clamped_pixel(x_low, y_low, c);
  float v1 = clamped_pixel(x_high, y_low, c);
  float v2 = clamped_pixel(x_low, y_high, c);
  float v3 = clamped_pixel(x_high, y_high, c);
  
  return p3 * (p0 * v1 + p1 * v0) + p2 * (p0 * v3 + p1 * v2);
  }

// HW1 #1
// int w,h: size of new image
// const Image& im: input image
// return new Image of size (w,h,im.c)
Image nearest_resize(const Image& im, int w, int h)
  {
  Image ret(w,h,im.c);
  
  // TODO: Your code here
  float aw = (float)im.w / (float) w;
  float bw = 0.5 * (aw-1);
  float ah = (float)im.h / (float) h;
  float bh = 0.5 * (ah-1);
  float u,v;

  for (int x = 0; x < w; x++)
  {
    for (int y = 0; y < h; y++)
    {
      // map back to original image
      u = x * aw + bw;
      v = y * ah + bh;
      for (int c = 0; c < im.c; c++)
      {
        ret(x, y, c) = im.pixel_nearest(u,v,c);
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
  
  Image ret(w,h,im.c);
  
  // TODO: Your code here
  float aw = (float)im.w / (float) w;
  float bw = 0.5 * (aw-1);
  float ah = (float)im.h / (float) h;
  float bh = 0.5 * (ah-1);
  float u,v;

  for (int x = 0; x < w; x++)
  {
    for (int y = 0; y < h; y++)
    {
      // map back to original image
      u = x * aw + bw;
      v = y * ah + bh;
      for (int c = 0; c < im.c; c++)
      {
        ret(x, y, c) = im.pixel_bilinear(u,v,c);
      }
      
    }
    
  }
  
  
  
  
  return ret;
  }


