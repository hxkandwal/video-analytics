//
//  ASMCalculator.hpp
//  EmotionRecognition
//
//  Created by Himanshu Kandwal on 5/9/16.
//  Copyright © 2016 Himanshu Kandwal. All rights reserved.
//

#ifndef ASMCalculator_hpp
#define ASMCalculator_hpp

#include <stdio.h>
#include "svmClassifier.h"

class ASMCalculator {

public:

    void findASMData (SvmClassifier svmclassifier, std::string imageType);
    
};
#endif /* ASMCalculator_hpp */
