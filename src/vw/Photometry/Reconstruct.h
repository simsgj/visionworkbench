// __BEGIN_LICENSE__
// Copyright (C) 2006-2010 United States Government as represented by
// the Administrator of the National Aeronautics and Space Administration.
// All Rights Reserved.
// __END_LICENSE__


/// \file Reconstruct.h

#ifndef __VW_PHOTOMETRY_RECONSTRUCT_H__
#define __VW_PHOTOMETRY_RECONSTRUCT_H__

#define NO_REFL 0
#define LAMBERT 1
#define LUNAR_LAMBERT 2

#include <iostream>
#include <string>
#include <vw/Math/Vector.h>

namespace vw {
namespace photometry {

  typedef struct GlobalParams{
    int reflectanceType;
    int slopeType;
    int exposureInitType;
    int albedoInitType;
    int DEMInitType;
    int shadowInitType;

    float shadowThresh;

    std::string exposureInfoFilename,
      spacecraftPosFilename, sunPosFilename;

    float exposureInitRefValue;
    int exposureInitRefIndex;

    int useWeights;
    int maxNumIter;
    int computeErrors;
    int maxNextOverlappingImages;
    int maxPrevOverlappingImages;
  };

  typedef struct ModelParams {
    float   exposureTime;

    Vector2 cameraParams; //currently not used
    Vector3 sunPosition; //relative to the center of the Moon
    Vector3 spacecraftPosition;//relative to the center of the Moon
    Vector2 rescalingParams; //currently not used

    int *centerLine;
    int *maxDistArray;
    int *centerLineDEM;
    int *maxDistArrayDEM;
    int *horCenterLine;
    int *maxVerDistArray;
    int *horCenterLineDEM;
    int *maxVerDistArrayDEM;

    std::string infoFilename, DEMFilename, meanDEMFilename,
      var2DEMFilename, reliefFilename, shadowFilename,
      errorFilename, inputFilename, outputFilename;

    //Vector2 center2D;
    //float maxDistance;
  };

  // Generic Ostream options for Debugging
  std::ostream& operator<<( std::ostream& os, GlobalParams const& global );
  std::ostream& operator<<( std::ostream& os, ModelParams const& model );

  //generates the normal of a point p1 from the 3D coordinates of p1, p2, p3
  //must be part of shape.cc
  Vector3 computeNormalFrom3DPoints(Vector3 p1, Vector3 p2, Vector3 p3);
  float computeReflectanceFromNormal(Vector3 sunPos, Vector3 xyz, Vector3 normal);

  // Written by Taemin Kim - START
#define DYNAMIC_RANGE  256
#define SIZE_OF_BUFFER (DYNAMIC_RANGE*DYNAMIC_RANGE)
#define SIGNIFICANCE_LEVEL 1.0e-2
#define MIN_WEIGHT 0

  Vector<uint8> load_inverse_weight(char * input_file, int num);
  // Written by Taemin Kim - END

}} // end vw::photometry

#endif//__VW_PHOTOMETRY_RECONSTRUCT_H__