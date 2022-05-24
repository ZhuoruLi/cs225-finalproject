/**
 * @file Image.h
 * Contains your declaration of the interface for the Image class.
 */

#pragma once

#include "../cs225/PNG.h"

using namespace cs225;

class Image : public PNG {
public:
    /**
     * Lighten an Image by increasing the luminance of every pixel by 0.1
     */ 
    void lighten();

    /**
     * Lighten an Image by increasing the luminance of every pixel by amount.
     * @param amount of luminance increase.
     */ 
    void lighten(double amount);

    /**
     * Darken an Image by decreasing the luminance of every pixel by 0.1.
     */
    void darken();

    /**
     * Darkens an Image by decreasing the luminance of every pixel by amount.
     * @param amount of luminance decrease.
     */
    void darken(double amount);

    /**
     * Saturates an Image by increasing the saturation of every pixel by 0.1.
     */
    void saturate();

    /**
     * Saturates an Image by increasing the saturation of every pixel by amount.
     * @param amount of saturation increase.
     */
    void saturate(double amount);

    /**
     * Desaturates an Image by decreasing the saturation of every pixel by 0.1.
     */
    void desaturate();

    /**
     * Desaturates an Image by decreasing the saturation of every pixel by amount.
     * @param amount of saturation decrease.
     */
    void desaturate(double amount);

    /**
     * Turns the image grayscale.
     */
    void grayscale();

    /**
     * Rotates the color wheel by degrees.
     * @param degree of color wheel rotated.
     */
    void rotateColor(double degrees);

    /**
     * Illinify the image.
     * Turns every pixel into either illini orange or illini blue.
     */
    void illinify();

    /**
     * Scale the Image by a given factor.
     * @param factor to resize the image.
     */
    void scale(double factor);
    
    /**
     * Scales the image to fit within the size (w x h).
     * @param w width of the image to fit in.
     * @param h height of the image of fit in.
     */
    void scale(unsigned w, unsigned h);
};