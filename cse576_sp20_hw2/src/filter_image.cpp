#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "image.h"

#define M_PI 3.14159265358979323846

// HW1 #2.1
// Image& im: image to L1-normalize
void l1_normalize(Image& im)
  {
  
  // TODO: Normalize each channel
  float s = 0;
  for (int c = 0; c < im.c; c++)
  { 
    s = 0;
    for (int i = c*im.w*im.h; i < (c+1)*im.w*im.h; i++)
    {
      s += im.data[i];
    }
    for (int i = c*im.w*im.h; i < (c+1)*im.w*im.h; i++)
    {
      if(s>0) im.data[i]/=s;
      else im.data[i] = 1.0/im.w/im.h;
    }
    
  }
  
  
  
  }

// HW1 #2.1
// int w: size of filter
// returns the filter Image of size WxW
Image make_box_filter(int w)
  {
  assert(w%2); // w needs to be odd
  
  // TODO: Implement the filter
  Image filter(w, w, 1); 
  for (int i = 0; i < w*w; i++)
  {
    filter.data[i] = 1;
  }
  l1_normalize(filter);  
  return filter;
  }

// HW1 #2.2
// const Image&im: input image
// const Image& filter: filter to convolve with
// bool preserve: whether to preserve number of channels
// returns the convolved image
Image convolve_image(const Image& im, const Image& filter, bool preserve)
  {
  assert(filter.c==1);
  Image ret;
  // This is the case when we need to use the function clamped_pixel(x,y,c).
  // Otherwise you'll have to manually check whether the filter goes out of bounds
  
  // TODO: Make sure you set the sizes of ret properly. Use ret=Image(w,h,c) to reset ret
  // TODO: Do the convolution operator

  float val;
  if (preserve)
  {
    ret = Image(im.w,im.h,im.c);
    for (int x = 0; x < im.w; x++)
    {
      for (int y = 0; y < im.h; y++)
      {
        for (int c = 0; c < im.c; c++)
        {
          val = 0;
          for (int w = 0; w < filter.w; w++)
          {
            for (int h = 0; h < filter.h; h++)
            {
              val += filter(w,h) * im.clamped_pixel(x-filter.w/2+w, y-filter.h/2+h, c);
            }
            
          }
          ret(x,y,c) = val; //<= 1 ? val : 1.0;
        }
        
      }
      
    }
    
  }
  else
  {
    ret = Image(im.w, im.h, 1);
    for (int x = 0; x < im.w; x++)
    {
      for (int y = 0; y < im.h; y++)
      {
        val = 0;
        for (int c = 0; c < im.c; c++)
        {
          for (int w = 0; w < filter.w; w++)
          {
            for (int h = 0; h < filter.h; h++)
            {
              val += filter(w,h) * im.clamped_pixel(x-filter.w/2+w, y-filter.h/2+h, c);
            }
            
          }
        }
        ret(x,y) = val;// <= 1 ? val : 1.0;
      }
      
    }
  }
  // Make sure to return ret and not im. This is just a placeholder
  return ret;
  }

// HW1 #2.3
// returns basic 3x3 high-pass filter
Image make_highpass_filter()
  {
  // TODO: Implement the filter
  Image f(3,3);
  f(0,0) = 0;
  f(0,1) = -1;
  f(0,2) = 0;
  f(1,0) = -1;
  f(1,1) = 4;
  f(1,2) = -1;
  f(2,0) = 0;
  f(2,1) = -1;
  f(2,2) = 0;
  
  return f;
  
  }

// HW1 #2.3
// returns basic 3x3 sharpen filter
Image make_sharpen_filter()
  {
  // TODO: Implement the filter
  Image hp = make_highpass_filter();
  hp(1,1) = 5;
  
  return hp;
  
  }

// HW1 #2.3
// returns basic 3x3 emboss filter
Image make_emboss_filter()
  {
  // TODO: Implement the filter
  Image f(3,3);
  f(0,0) = -2;
  f(0,1) = -1;
  f(0,2) = 0;
  f(1,0) = -1;
  f(1,1) = 1;
  f(1,2) = 1;
  f(2,0) = 0;
  f(2,1) = 1;
  f(2,2) = 2;
  return f;

  
  }

// HW1 #2.4
// float sigma: sigma for the gaussian filter
// returns basic gaussian filter
Image make_gaussian_filter(float sigma)
  {
  // TODO: Implement the filter
  int w = (int)roundf(sigma * 6) + 1;  
  if(w%2==0) w++;
  float sigma_sq = pow(sigma, 2);
  int x,y;
  Image f(w,w);
  for (int i = 0; i < w; i++)
  {
    for (int j = 0; j < w; j++)
    {
      x = pow(i-w/2, 2);
      y = pow(j-w/2, 2);
      f(i,j) = 1.0 / (2 * M_PI * sigma_sq) * exp(-(x+y)/2/sigma_sq);
    }
    
  }
  
  l1_normalize(f);

  return f;
  
  }


// HW1 #3
// const Image& a: input image
// const Image& b: input image
// returns their sum
Image add_image(const Image& a, const Image& b)
  {
  assert(a.w==b.w && a.h==b.h && a.c==b.c); // assure images are the same size
  
  // TODO: Implement addition
  Image ret(a.w,a.h,a.c);
  
  for (int i = 0; i < ret.size(); i++)
  {
    ret.data[i] = a.data[i] + b.data[i];
  }
  
  
  return ret;
  
  }

// HW1 #3
// const Image& a: input image
// const Image& b: input image
// returns their difference res=a-b
Image sub_image(const Image& a, const Image& b)
  {
  assert(a.w==b.w && a.h==b.h && a.c==b.c); // assure images are the same size
  
  // TODO: Implement subtraction
  
  Image ret(a.w,a.h,a.c);
  for (int i = 0; i < ret.size(); i++)
  {
    ret.data[i] = a.data[i] - b.data[i];
  }
  
  return ret;
  
  }

// HW1 #4.1
// returns basic GX filter
Image make_gx_filter()
  {
  // TODO: Implement the filter
  Image filter(3,3);
  filter.data[0] = -1;
  filter.data[1] = 0;
  filter.data[2] = 1;
  filter.data[3] = -2;
  filter.data[4] = 0;
  filter.data[5] = 2;
  filter.data[6] = -1;
  filter.data[7] = 0;
  filter.data[8] = 1;

  return filter;
  }

// HW1 #4.1
// returns basic GY filter
Image make_gy_filter()
  {
  // TODO: Implement the filter
  Image filter(3,3);
  filter.data[0] = -1;
  filter.data[1] = -2;
  filter.data[2] = -1;
  filter.data[3] = 0;
  filter.data[4] = 0;
  filter.data[5] = 0;
  filter.data[6] = 1;
  filter.data[7] = 2;
  filter.data[8] = 1;
  
  return filter;
  }

// HW1 #4.2
// Image& im: input image
void feature_normalize(Image& im)
  {
  assert(im.w*im.h); // assure we have non-empty image
  
  // TODO: Normalize the features for each channel
  float val_max=im.data[0], val_min=im.data[0];
  for (int i = 0; i < im.size(); i++)
  {
    if(im.data[i] > val_max) val_max=im.data[i];
    if(im.data[i] < val_min) val_min=im.data[i];
  }
  float range = val_max - val_min;
  bool zero = range==0;
  for (int i = 0; i < im.size(); i++)
  {
    if (zero)
    {
      im.data[i] = 0;
    }
    else
    {
      im.data[i] = (im.data[i] - val_min)/range;
    }
    
  }

  
  }


// Normalizes features across all channels
void feature_normalize_total(Image& im)
  {
  assert(im.w*im.h*im.c); // assure we have non-empty image
  
  int nc=im.c;
  im.c=1;im.w*=nc;
  
  feature_normalize(im);
  
  im.w/=nc;im.c=nc;
  
  }


// HW1 #4.3
// Image& im: input image
// return a pair of images of the same size
pair<Image,Image> sobel_image(const Image& im)
  {
  // TODO: Your code here
  Image gx = make_gx_filter();
  Image gy = make_gy_filter();

  Image out_x = convolve_image(im, gx, false);
  Image out_y = convolve_image(im, gy, false);
  
  Image mag(im.w, im.h), theta(im.w, im.h);
  float x,y;
  for (int i = 0; i < mag.size(); i++)
  {
    x = out_x.data[i];
    y = out_y.data[i];
    mag.data[i] = sqrt(pow(x,2) + pow(y,2));
    theta.data[i] = atan2f(y, x);

  }
  
  
  return {mag, theta};
  }


// HW1 #4.4
// const Image& im: input image
// returns the colorized Sobel image of the same size
Image colorize_sobel(const Image& im)
  {
  
  // TODO: Your code here
  Image f = make_gaussian_filter(4);
  Image im2 = convolve_image(im, f, true);

  pair<Image,Image> res = sobel_image(im2);
  Image mag = res.first;
  Image theta = res.second;
  Image ret(im.w,im.h,3);
  feature_normalize(mag);

  for (int i = 0; i < mag.w; i++)
  {
    for (int j = 0; j < mag.h; j++)
    {
      ret(i, j, 0) = theta(i,j) / 2 / M_PI + 0.5;
      ret(i, j, 1) = mag(i,j);
      ret(i, j, 2) = mag(i,j);
    }
    
  }

  hsv_to_rgb(ret);


  return ret;
  }


// HW1 #4.5
// const Image& im: input image
// float sigma1,sigma2: the two sigmas for bilateral filter
// returns the result of applying bilateral filtering to im
Image bilateral_filter(const Image& im, float sigma1, float sigma2)
  {
  Image bf=im;
  
  // TODO: Your bilateral code
  NOT_IMPLEMENTED();
  
  return bf;
  }



// HELPER MEMBER FXNS

void Image::feature_normalize(void) { ::feature_normalize(*this); }
void Image::feature_normalize_total(void) { ::feature_normalize_total(*this); }
void Image::l1_normalize(void) { ::l1_normalize(*this); }

Image operator-(const Image& a, const Image& b) { return sub_image(a,b); }
Image operator+(const Image& a, const Image& b) { return add_image(a,b); }
