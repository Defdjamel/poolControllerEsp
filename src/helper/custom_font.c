/*******************************************************************************
 * Size: 22 px
 * Bpp: 1
 * Opts: --bpp 1 --size 22 --no-compress --font fontawesome-webfont.woff --range 61530,61461,61459 --format lvgl -o font_info.c
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include <lvgl.h>
#endif

#ifndef FONT_INFO
#define FONT_INFO 1
#endif

#if FONT_INFO

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+F013 "" */
    0x1, 0xf0, 0x0, 0x3e, 0x0, 0x67, 0xcc, 0x1f,
    0xff, 0xc3, 0xff, 0xf8, 0x3f, 0xfe, 0x7, 0xc7,
    0xc7, 0xe0, 0x3f, 0xfc, 0x7, 0xff, 0x80, 0xff,
    0xf0, 0x1f, 0x8f, 0x8f, 0x81, 0xff, 0xf0, 0x7f,
    0xff, 0xf, 0xff, 0xe0, 0xcf, 0x98, 0x1, 0xf0,
    0x0, 0x3e, 0x0,

    /* U+F015 "" */
    0x0, 0xe3, 0x80, 0x1f, 0x38, 0x3, 0xbb, 0x80,
    0x75, 0xf8, 0x1d, 0xf7, 0x83, 0xbf, 0xb8, 0x77,
    0xfd, 0xef, 0xff, 0xf7, 0xff, 0xff, 0xa3, 0xff,
    0xf8, 0x3f, 0xff, 0x83, 0xf1, 0xf8, 0x3f, 0x1f,
    0x83, 0xf1, 0xf8, 0x3f, 0x1f, 0x80,

    /* U+F05A "" */
    0x3, 0xf8, 0x1, 0xff, 0xc0, 0x7c, 0x7c, 0x1f,
    0x8f, 0xc7, 0xf1, 0xfc, 0xff, 0xff, 0xbf, 0x7,
    0xff, 0xe0, 0xff, 0xfc, 0x1f, 0xff, 0xe3, 0xff,
    0xfc, 0x7f, 0xff, 0x8f, 0xff, 0xf1, 0xfe, 0xf8,
    0xf, 0x9f, 0x1, 0xf1, 0xe0, 0x3c, 0x1f, 0xff,
    0x1, 0xff, 0xc0, 0xf, 0xe0, 0x0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 302, .box_w = 19, .box_h = 18, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 43, .adv_w = 327, .box_w = 20, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 81, .adv_w = 302, .box_w = 19, .box_h = 19, .ofs_x = 0, .ofs_y = -2}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_0[] = {
    0x0, 0x2, 0x47
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 61459, .range_length = 72, .glyph_id_start = 1,
        .unicode_list = unicode_list_0, .glyph_id_ofs_list = NULL, .list_length = 3, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif
};



/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t font_info = {
#else
lv_font_t font_info = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 19,          /*The maximum line height required by the font*/
    .base_line = 2,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = 0,
    .underline_thickness = 0,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if FONT_INFO*/
