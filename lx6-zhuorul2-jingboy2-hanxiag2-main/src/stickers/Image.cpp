/**
 * @file Image.cpp
 * 
 * Implementation of class Image.
 */

#include "Image.h"
#include <cmath>
#include <iostream>

using namespace cs225;
using std::fmod;

void Image::lighten() {
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            HSLAPixel & pixel = getPixel(x, y);
            pixel.l += 0.1;
            pixel.l = pixel.l >= 1.0 ? 1.0 : pixel.l;
        }
    }
    return;
}

void Image::lighten(double amount) {
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            HSLAPixel & pixel = getPixel(x, y);
            pixel.l += amount;
            pixel.l = pixel.l >= 1.0 ? 1.0 : pixel.l;
        }
    }
    return;
}

void Image::darken() {
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            HSLAPixel & pixel = getPixel(x, y);
            pixel.l -= 0.1;
            pixel.l = pixel.l <= 0.0 ? 1.0 : pixel.l;
        }
    }
    return;
}

void Image::darken(double amount) {
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            HSLAPixel & pixel = getPixel(x, y);
            pixel.l -= amount;
            pixel.l = pixel.l <= 0.0 ? 0.0 : pixel.l;
        }
    }
    return;
}

void Image::saturate() {
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            HSLAPixel & pixel = getPixel(x, y);
            pixel.s += 0.1;
            pixel.s = pixel.s >= 1.0 ? 1.0 : pixel.s;
        }
    }
    return;
}

void Image::saturate(double amount) {
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            HSLAPixel & pixel = getPixel(x, y);
            pixel.s += amount;
            pixel.s = fmod(pixel.s, 360.0);
            pixel.s = pixel.s >= 1.0 ? 1.0 : pixel.s;
        }
    }
    return;
}

void Image::desaturate() {
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            HSLAPixel & pixel = getPixel(x, y);
            pixel.s -= 0.1;
            pixel.s = pixel.s <= 0.0 ? 1.0 : pixel.s;
        }
    }
    return;
}

void Image::desaturate(double amount) {
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            HSLAPixel & pixel = getPixel(x, y);
            pixel.s -= amount;
            pixel.s = pixel.s <= 0.0 ? 1.0 : pixel.s;
        }
    }
    return;
}

void Image::grayscale() {
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            HSLAPixel & pixel = getPixel(x, y);
            pixel.s = 0;
        }
    }
    return;
}

void Image::rotateColor(double degree) {
    // preprocess degree of rotation
    degree = fmod(degree, 360);
    if (degree < 0) { degree += 360; }
    for (unsigned x = 0; x < width(); x++) {
        for (unsigned y = 0; y < height(); y++) {
            HSLAPixel & pixel = getPixel(x, y);
            pixel.h += degree;
            // prevent excession of domain.
            pixel.h = fmod(pixel.h, 360);
        }
    }
    return;
}

void Image::illinify() {
    const double illini_orange_hue = 11.0;
    const double illini_blue_hue = 216.0;

    for (unsigned int x = 0; x < width(); x++) {
        for (unsigned int y = 0; y < height(); y++) {
            HSLAPixel & pixel = getPixel(x, y);

            if (pixel.h >= 11 && pixel.h <= 216) {
                pixel.h = (illini_blue_hue - pixel.h >= pixel.h - illini_orange_hue) ? illini_orange_hue : illini_blue_hue;
            }
            else if (pixel.h > 216 && pixel.h < 360) {
                pixel.h = (371 - pixel.h > pixel.h - illini_blue_hue) ? illini_blue_hue : illini_orange_hue; // it has to be the number
            }
            else {
                // hue that falls between [0, 11] must be orange.
                pixel.h = illini_orange_hue;
            }
        }
    }
    return;
}

void Image::scale(double factor) {
    // do nothing if factor is one.
    if (factor == 1.0) {
        return;
    }

    // initialize new image.
    Image newImage;
    newImage.resize(round(width() * factor), round(height() * factor));

    // performing nearest interpolation algarithm.
    if (factor > 1) {
        for (unsigned destx = 0; destx < newImage.width(); destx++) {
            for (unsigned desty = 0; desty < newImage.height(); desty++) {
                unsigned srcx = round(destx / factor); unsigned srcy = round(desty / factor);
                // prevent index-out-of-range error.
                if (srcx >= width()) { srcx--; }
                if (srcy >= height()) { srcy-- ;}
                HSLAPixel & pixel_src = getPixel(srcx, srcy);
                HSLAPixel & pixel_dest = newImage.getPixel(destx, desty);
                pixel_dest = pixel_src;
            }
        }
    }
    else if (factor < 1) {
        for (unsigned srcx = 0; srcx < width(); srcx++) {
            for (unsigned srcy = 0; srcy < height(); srcy++) {
                unsigned destx = round(srcx * factor); unsigned desty = round(srcy * factor);
                // prevent index-out-of-range error.
                if (destx >= newImage.width()) { destx--; }
                if (desty >= newImage.height()) { desty--; }
                HSLAPixel & pixel_src = getPixel(srcx, srcy);
                HSLAPixel & pixel_dest = newImage.getPixel(destx, desty);
                pixel_dest = pixel_src;
            }
        }
    }
    *this = newImage;
}

void Image::scale(unsigned w, unsigned h) {
    // do nothing if trying scaling to 1:1.
    if (w == width() && h == height()) {
        return;
    }

    // keep the ratio of original image.
    double original_ratio = (double)width() / (double)height();
    double extended_ratio = (double)w / (double)h;
    if (original_ratio > extended_ratio) { h = round(w / original_ratio); }
    else { w = round(h * original_ratio); }

    Image newImage;
    newImage.resize(w, h);

    // Using bilinear interpolation algarithm.
    for (unsigned x = 0; x < w; x++) {
        for (unsigned y = 0; y < h; y++) {
            // calculate virtual coordinates of source image.
            // margin the center of images.
            double tmpx = (double)x + 0.5 / (double)w * (double)width() - 0.5;
            double tmpy = (double)y + 0.5 / (double)h * (double)height() - 0.5;

            unsigned x0 = round(tmpx);
            unsigned y0 = round(tmpy);

            unsigned x1 = x0 + 1; unsigned y1 = y0 + 1;

            unsigned u = tmpx - x0; unsigned v = tmpy - y0;

            // prevent index-out-of-bound error.
            if (x1 >= width()) {
                x1 = width() - 1;
                x0 = x1 - 1;
            }
            if (y1 >= height()) {
                y1 = height() - 1;
                y0 = y1 - 1;
            }

            // perform interpolation
            HSLAPixel & pixel_dest = newImage.getPixel(x, y);
            unsigned outx = (1-u) * (1-v) * x0 + (1-u)*v * x0 + u*(1-v) * x1 + u*v *x1;
            unsigned outy = (1-u) * (1-v) * y0 + (1-u)*v * y0 + u*(1-v) * y1 + u*v *y1;
            HSLAPixel & pixel_src = getPixel(outx, outy);
            pixel_dest = pixel_src;
        }
    }

    *this = newImage;
    return;
}
