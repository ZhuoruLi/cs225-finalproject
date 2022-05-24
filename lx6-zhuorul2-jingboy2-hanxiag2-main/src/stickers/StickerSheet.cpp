/**
 * @file StickerSheet.cpp
 * Implementation of StickerSheet class.
 */

#include "StickerSheet.h"
#include "../cs225/HSLAPixel.h"

using namespace std;

StickerSheet::StickerSheet( const Image & picture, unsigned max ) {
    _base_picture = picture;
    _max = max;
    ptr_ = new Image;
}

StickerSheet::~StickerSheet() {
    if (ptr_ != NULL) {
        delete ptr_;
    }
}

StickerSheet::StickerSheet( const StickerSheet & other ) {
    _base_picture = other._base_picture;
    _max = other._max;

    // iteratively copy and add all the stickers.
    for (unsigned index = 0; index < other._stickers.size(); index++) {
        Sticker new_sticker(other._stickers.at(index));
        _stickers.push_back(new_sticker);
    }
}

int StickerSheet::addSticker( Image & sticker, unsigned x, unsigned y ) {
    // exceeds maximum number of stickers.
    if ( _stickers.size() == _max ) { return -1; }

    Sticker stk(sticker, x, y);
    _stickers.push_back(stk);
    return _stickers.size() - 1;
}

void StickerSheet::changeMaxStickers( unsigned max ) {
    // If number of current collection of stickers exceeds the new maximum, 
    // discard stickers beyond the bound.
    if ( max < _stickers.size() ) {
        unsigned count = _stickers.size() - max;
        while (count > 0) {
            _stickers.pop_back();
            --count;
        }
    }
    _max = max;
}

Image * StickerSheet::getSticker( unsigned index ) {
    try {
        *ptr_ = _stickers.at(index)._source_image;
        return ptr_;
    }
    catch (const out_of_range & err) {
        cerr << "Trying to access _stickers at index " << index << " which is out of bound." << endl;
        return NULL;
    }
}

const StickerSheet & StickerSheet::operator=( const StickerSheet & other ) {
    _base_picture = other._base_picture;
    _max = other._max;

    _stickers.clear();
    for (unsigned index = 0; index < other._stickers.size(); index++) {
        Sticker new_sticker(other._stickers.at(index));
        _stickers.push_back(new_sticker);
    }

    return *this;
}

void StickerSheet::removeSticker( unsigned index ) {
    // walk to the position of index.
    vector<Sticker>::iterator it = _stickers.begin();
    it += index;
    _stickers.erase(it);
}

Image StickerSheet::render() const {
    // Make a copy of base picture and add stickers to it.
    Image output_img = _base_picture;
    for (unsigned index = 0; index < _stickers.size(); index++) {
        Sticker current_sticker = _stickers.at(index);  // current sticker being processed.
        unsigned stk_w = current_sticker._source_image.width();     // width of sticker
        unsigned stk_h = current_sticker._source_image.height();    // height of sticker

        // expand the base picture to contain oversized or out-of-bound stickers.
        unsigned original_width = output_img.width(); unsigned original_height = output_img.height();
        if ( current_sticker._x + stk_w >= output_img.width() ) {
            output_img.resize( current_sticker._x + stk_w, original_height );
        }
        if ( current_sticker._y + stk_h >= output_img.height() ) {
            output_img.resize( original_width, current_sticker._y + stk_h );
        }

        for (unsigned x = current_sticker._x; x < current_sticker._x + stk_w; x++) {
            for (unsigned y = current_sticker._y; y < current_sticker._y + stk_h; y++) {
                unsigned dx = x - current_sticker._x;  // x coordinate of sticker
                unsigned dy = y - current_sticker._y;  // y coordinate of sticker
                HSLAPixel & pixel_o = output_img.getPixel(x, y);    // pixel on output image
                HSLAPixel & pixel_stk = current_sticker._source_image.getPixel(dx, dy);   // pixel on sticker
                pixel_o = pixel_stk.a == 1 ? pixel_stk : pixel_o;   // Omit transparent pxs of stickers.
            }
        }
    }
    return output_img;
}

bool StickerSheet::translate( unsigned index, unsigned x, unsigned y ) {
    try {
        Sticker & sticker = _stickers.at(index);
        sticker._x = x;
        sticker._y = y;
        return true;
    }
    catch (const out_of_range & err) {
        return false;
    }
}

Sticker::Sticker() {
    _source_image = Image();
    _x = 0;
    _y = 0;
}

Sticker::Sticker( const Image & src_img, unsigned dx, unsigned dy ) {
    _source_image = src_img;
    _x = dx;
    _y = dy;
};

Sticker::Sticker( const Sticker & other ) {
    _source_image = other._source_image;
    _x = other._x;
    _y = other._y;
}