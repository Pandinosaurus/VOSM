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
* Create Date:      2010-11-04                                                                      *
* Modify Date:      2014-04-17                                                                      *
****************************************************************************************************/

#ifndef __CLASSIFICATIONALGS_H__
#define __CLASSIFICATIONALGS_H__

#include <cstring>
#include <set>
#include "opencv2/core/core.hpp"
#include "opencv/cvaux.h"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include "VO_CVCommon.h"
#include "VO_AdditiveStrongerClassifier.h"




/** 
 * @author		JIA Pei
 * @brief		Classification algorithms.
 */
class CClassificationAlgs
{
protected:
	/** classification method */
	unsigned int				m_iClassificationMethod;

	/** How many classes in total */
	unsigned int 				m_iNbOfCategories;

	/** Decision tree */
    cv::ml::DTrees*					m_CVDtree;

	/** boosting */
    cv::ml::Boost*					m_CVBoost;

	/** random tree */
    cv::ml::RTrees*					m_CVRTrees;

	/** extreme random tree */
    //cv::ml::RTrees 					m_CVERTrees;

	/** SVM */
	cv::ml::SVM*				m_CVSVM;

	/** Initialization */
	void						init(unsigned int mtd);

public:
	enum{NONE = 0, SVM = 1, DecisionTree = 2, Boost = 3, RandomForest = 4, ExtremeRandomForest = 5 };

	/** Constructor */
	CClassificationAlgs(unsigned int mtd=CClassificationAlgs::NONE);

	/** Destructor */
	~CClassificationAlgs();

    /** set configuration for classifier */
    void						SetConfiguration(const std::string& trainedclassifier, unsigned int mtd);

    /** Classifier training */
    void						Training(const cv::Mat_<float>& data, const cv::Mat_<int>& categories);

    /** Do classification */
    int							Classification(	const cv::Mat_<float>& sample);
	
    /** save configuration */
    void						Save(const std::string& fn) const;
	
    /** load configuration */
    void						Load(const std::string& fn);
	
	/** Gets and sets */
	unsigned int				GetClassificationMethod() const {return this->m_iClassificationMethod ;}
};

#endif	// __CLASSIFICATIONALGS_H__
