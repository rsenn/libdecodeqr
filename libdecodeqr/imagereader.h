/////////////////////////////////////////////////////////////////////////
//
// imagereader.h --a part of libdecodeqr
//
// Copyright(C) 2007 NISHI Takao <zophos@koka-in.org>
//                   JMA  (Japan Medical Association)
//                   NaCl (Network Applied Communication Laboratory Ltd.)
//
// This is free software with ABSOLUTELY NO WARRANTY.
// You can redistribute and/or modify it under the terms of LGPL.
//
// $Id$
//
#ifndef __QR_IMAGE_READER__
#define __QR_IMAGE_READER__

#ifdef _DEBUG
#include <stdio.h>
#endif

#include <memory.h>
#include "qrerror.h"
#include "container.h"


/////////////////////////////////////////////////////////////////////////
//
// image processing parameters
//
#define DEFAULT_ADAPTIVE_TH_SIZE 25
#define DEFAULT_ADAPTIVE_TH_DELTA 10
#define MIN_AREA 49
#define MIN_AREA_RATIO .65
#define MIN_FERET_RATIO .7
#define FIND_CODE_AREA_POLY_APPROX_TH 50
#define POSTERIZED_TH_LOW 64
#define POSTERIZED_TH_HI 96
#define POSTERIZED_TH_STEP 8

namespace Qr{
    class ImageReader{
    public:
        Qr *qr;
        short status;

    private:
//        void *_img_src_internal;
//        void *_img_src;
//        void *_img_transformed;
//        void *_img_binarized;
//        void *_img_tmp_1c;
//        void *_stor;
//        void *_stor_tmp;
//        void *_seq_finder_pattern;
//        void *_seq_code_area_contour;
//        void _coderegion_vertexes[4];
//        void _finderpattern_boxes[3];
//
    public:
        ImageReader();
        ImageReader(int width,int height,
                                 int depth=0,
                                 int channel=3);
        ~ImageReader();
        
        void *set_image(void *src);
        unsigned char *set_image(unsigned char *buffer,int size);
        void *set_image(int width,int height,
                                         int depth,int channel);
        void release_image();

        void *src_buffer();
        void *transformed_buffer();
        void *binarized_buffer();
        void *tmp_buffer();
        void *coderegion_vertexes();
        void *finderpattern_boxes();

        Qr *decode(int adaptive_th_size=
                                DEFAULT_ADAPTIVE_TH_SIZE,
                                int adaptive_th_delta=
                                DEFAULT_ADAPTIVE_TH_DELTA);
        Qr *decode(void *src,
                                int adaptive_th_size=
                                DEFAULT_ADAPTIVE_TH_SIZE,
                                int adaptive_th_delta=
                                DEFAULT_ADAPTIVE_TH_DELTA);

    private:
        void _init();
        void _alloc_image(int width,int height,
                                       int depth,int channel);

        Qr *_decode(int adaptive_th_size,int adaptive_th_delta);
        
        void *_find_finder_pattern();
        void *_find_code_area_contour(double th);
        void _transform_image();
        void _create_posterized_image(int block_size,
                                                   double delta,
                                                   int low_th,
                                                   int hi_th);
        void *_get_code_matrix();
        int _get_format_info(void *src,int pos=0);
        void *_get_function_patterns();
        void _unmask_code_matrix(void *src,
                                              void *function_patterns);
        int _read_code_word(void *src,void *mask);

        double _get_cell_size();
        void *_get_mask_pattern();

    };

    static int seq_cmp_by_clockwise(const void *_a,
                                    const void *_b,
                                    void *_cog);

    void apaptive_white_leveling(const void* src,void* dst,
                                 double middle_value,int adaptive_method,
                                 int threshold_type,int block_size,
                                 double param1);

}

#endif
