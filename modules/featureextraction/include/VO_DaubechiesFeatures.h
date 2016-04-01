/****************************************************************************************************
*                                                                                                   *
*                   IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.               *
*                                                                                                   *
*   By downloading, copying, installing or using the software you agree to this license.            *
*   If you do not agree to this license, do not download, install, copy or use the software.        *
*                                                                                                   *
*                                   License Agreement                                               *
*                           For Vision Open Statistical Models                                      *
*                                                                                                   *
* Copyright (C):    2006~2014 by JIA Pei, all rights reserved.                                      *
*                                                                                                   *
*                   VOSM is free software under the terms of the GNU Lesser General Public License  *
*                   (GNU LGPL) as published by the Free Software Foundation; either version 3.0 of  *
*                   the License, or (at your option) any later version.                             *
*                   You can use it, modify it, redistribute it, etc; and redistribution and use in  *
*                   source and binary forms, with or without modification, are permitted provided   *
*                   that the following conditions are met:                                          *
*                                                                                                   *
*                   a) Redistribution's of source code must retain this whole paragraph of          *
*                   copyright notice, including this list of conditions and all the following       *
*                   contents in this copyright paragraph.                                           *
*                                                                                                   *
*                   b) Redistribution's in binary form must reproduce this whole paragraph of       *
*                   copyright notice, including this list of conditions and all the following       *
*                   contents in this copyright paragraph, and/or other materials provided with      *
*                   the distribution.                                                               *
*                                                                                                   *
*                   c) The name of the copyright holders may not be used to endorse or promote      *
*                   products derived from this software without specific prior written permission.  *
*                                                                                                   *
*                   Any publications based on this code must cite the following five papers,        *
*                   technic reports and on-line materials.                                          *
*                                                                                                   *
*                   1) P. JIA, 2D Statistical Models, Technical Report of Vision Open Working       *
*                   Group, 2st Edition, Oct 21, 2010.                                               *
*                   http://www.visionopen.com/members/jiapei/publications/pei_sm2dreport2010.pdf    *
*                                                                                                   *
*                   2) P. JIA. Audio-visual based HMI for an Intelligent Wheelchair.                *
*                   PhD thesis, University of Essex, 2010.                                          *
*                   http://www.visionopen.com/members/jiapei/publications/pei_thesischapter34.pdf   *
*                                                                                                   *
*                   3) T. Cootes and C. Taylor. Statistical models of appearance for computer       *
*                   vision. Technical report, Imaging Science and Biomedical Engineering,           *
*                   University of Manchester, March 8 2004.                                         *
*                                                                                                   *
*                   4) I. Matthews and S. Baker. Active appearance models revisited.                *
*                   International Journal of Computer Vision, 60(2):135–164, November 2004.         *
*                                                                                                   *
*                   5) M. B. Stegmann, Active Appearance Models: Theory, Extensions and Cases,      *
*                   http://www2.imm.dtu.dk/~aam/main/, 2000.                                        *
*                                                                                                   *
*                                                                                                   *
* Version:          0.3.4                                                                           *
* Author:           JIA Pei                                                                         *
* Contact:          jp4work@gmail.com                                                               *
* URL:              http://www.visionopen.com                                                       *
* Create Date:      2010-03-08                                                                      *
* Modify Date:      2014-04-15                                                                      *
****************************************************************************************************/


#ifndef _VO_DAUBECHIESFEATURES_H_
#define _VO_DAUBECHIESFEATURES_H_

#include "VO_Features.h"
#include "VO_Daubechies.h"

#define CC_RECTS        "rects"
#define CC_TILTED       "tilted"

//#define HFP_NAME        "daubechiesFeatureParams"


/** 
 * @author    JIA Pei
 * @brief    Daubechies wavelet features.
 */
class VO_DaubechiesFeatures : public VO_Features
{
protected:
    /** which Haar mode is to be used? BASIC, CORE or ALL? */
    unsigned int        m_iMode;

    /** Internal class */
    class Feature
    {
    public:
        Feature();
        Feature( int offset, int x, int y, int _block_w, int _block_h  ); 
        float           filter( const cv::Mat_<float>& iImg );
        void            calc( const cv::Mat_<float>& iImg );
        void            write( cv::FileStorage &fs ) const;

        bool            isFiltering;
        cv::Rect        rect;
        VO_Daubechies   daub;
        cv::Mat_<float> freqs;
    };

    std::vector<Feature>     m_vAllFeatures;

    /** Initialization */
    void                init();

public:
    enum {
        DAUBECHIES4 = 0,
        DAUBECHIES6 = 1,
        DAUBECHIES8 = 2,
        DAUBECHIES10 = 3,
        DAUBECHIES12 = 4,
        DAUBECHIES14 = 5,
        DAUBECHIES16 = 6,
        DAUBECHIES18 = 7,
        DAUBECHIES20 = 8
    };
    
    /** default constructor */
    VO_DaubechiesFeatures ()   {this->m_iFeatureType = DAUBECHIES;}
    
    /** destructor */
    virtual ~VO_DaubechiesFeatures () {this->m_vAllFeatures.clear();}

    /** Generate all features with a specific mode */
    virtual void        VO_GenerateAllFeatureInfo(const cv::Size& size, unsigned int generatingMode = DAUBECHIES4);
    virtual void        VO_GenerateAllFeatures(const cv::Mat& iImg, cv::Point pt = cv::Point(0,0));

    /** Read and write */
    virtual void        ReadFeatures( const cv::FileStorage& fs, cv::Mat_<float>& featureMap );
    virtual void        WriteFeatures( cv::FileStorage& fs, const cv::Mat_<float>& featureMap ) const;
};



/**
* @brief    Daubechies filtering
* @param    iImg        Input    -- input image
 */
inline float VO_DaubechiesFeatures::Feature::filter( const cv::Mat_<float>& iImg )
{
    return 0.0;
}


/**
* @brief    calculate one feature
* @param    iImg        Input    -- input image
 */
inline void VO_DaubechiesFeatures::Feature::calc(const cv::Mat_<float>& iImg)
{
    daub.VO_ForwardTransform(iImg, freqs);
}

#endif        // _VO_DAUBECHIESFEATURES_H_

