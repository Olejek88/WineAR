/*===============================================================================
Copyright (c) 2015-2016 PTC Inc. All Rights Reserved.

Copyright (c) 2014 Qualcomm Connected Experiences, Inc. All Rights Reserved.

Vuforia is a trademark of PTC Inc., registered in the United States and other 
countries.

@file 
    EyewearUserCalibrator.h

@brief
    Header file for EyewearUserCalibrator class.
===============================================================================*/
#ifndef _VUFORIA_EYEWEARUSERCALIBRATOR_H_
#define _VUFORIA_EYEWEARUSERCALIBRATOR_H_

// Include files
#include <Vuforia/NonCopyable.h>
#include <Vuforia/Vuforia.h>
#include <Vuforia/EyeID.h>
#include <Vuforia/EyewearCalibrationReading.h>

namespace Vuforia
{

/// A class for creating custom user calibration procedures for see-through eyewear
/**
 *  - Users of optical see-through eyewear devices need to perform a calibration
 *    to determine how to project an augmentation such that it will appear
 *    registered with the real world.  This calibration is both user and
 *    device specific.  Vuforia provides a default calibration but to obtain
 *    the best possible AR experience the user should calibrate Vuforia for
 *    their own eyes and device.
 *
 *  - If the eyewear device is a stereo then the calibration needs to be
 *    carried out independently on each eye.
 *
 *  - Millimeters must be used as the unit of measurement throughout
 *    calibration.  The calibration image target used should have its size
 *    specified in millimetres when initialising this object.  This size
 *    must match the size specified in the dataset for the target and the
 *    printed size of the target.
 *
 *  - The projection matrix generated by the calibration process includes
 *    OpenGL clip planes which will cause augmentations very close or far
 *    from the user to be clipped.
 */
class VUFORIA_API EyewearUserCalibrator : private NonCopyable
{
public:

    /*
    * The consistency of an eyewear user calibration is a measurement as to how
    * consistent the calibration data supplied to the calibrator is.
    */
    enum CONSISTENCY
    {
        /** there is no consistency data available, for example if only
            calibration data for one eye has been supplied or the calibrator
            has not been initialised */
        NONE = 0,

        /** there is very little consistency and the user has likely not
            understood how to perform the calibration process */
        VERY_BAD = 1,

        /** the consistency is bad and the calibration is unlikely to result in
            a good user experience */
        BAD = 2,

        /** the calibration is likely usable but the user should review the result
            and consider repeating the calibration */
        OK = 3,

        /** the calibration data is consistent and although this is no guarantee
            of a good calibration it is a strong indicator */
        GOOD = 4,

        CONSISTENCY_LEN = 5
    };


    /**
     * Initialises the eyewear calibrator.
     *
     * - This function must be called before any other members of this class.
     *
     *  \param surfaceWidth  The width of the rendering surface that the calibration is running in
     *  \param surfaceHeight  The height of the rendering surface that the calibration is running in 
     *  \param targetWidth  The width of the image target being used in meters
     *  \param targetHeight  The height of the image target being used in meters
     *
     *  \return True if initialisation is successful, false otherwise
     *
     **/
    virtual bool init(size_t surfaceWidth, size_t surfaceHeight,
                      float targetWidth,  float targetHeight) = 0;

    /** 
     * Gets a hint of the minimum size a calibration shape should be drawn
     *
     * - The smaller a calibration shape is drawn the further the user needs to
     *   stand away from a target during calibration.  The minimum size that
     *   can be drawn is device specific and this API provide a hint as to what
     *   minimum scale shape is practical.
     *
     * \return The minimum scale of the shape in the range 0.0 - 1.0
     **/
    virtual float getMinScaleHint() const = 0; 

    /**
     * Gets a hint of the maximum size a calibration shape should be drawn
     *  - Drawing a large calibration shape means the sides of the shape will
     *    near to the sides of the display.  Some eyewear devices have
     *    distortion towards the edge of the display.  This API provides a hint
     *    as to the maximum size a calibration shape should be drawn.
     *
     * \return The maximum scale of the shape in the range 0.0 - 1.0
     **/
    virtual float getMaxScaleHint() const = 0;


    /**
     * Gets the aspect ratio that should be used to draw a calibration shape
     * - Some eyewear devices introduce distortion in the calibration shapes,
     *   for example in the form of horizontal or vertical stretch.  This value
     *   should be used to draw calibration shapes that closely match the
     *   aspect ratio of the real world calibration target.
     *
     * \return The aspect ratio for calibration shapes
     **/
    virtual float getDrawingAspectRatio(int surfaceWidth, int surfaceHeight) const = 0;


    /**
     * Checks whether a device stretches the display to create a stereoscopic effect
     *  - When a device enters 3D it may join the displays together to create one
     *    big display.  If the resolution of the display appears the same then the
     *    display is effectively stretched
     *
     * \return True if the display is stretched, otherwise false
     **/
    virtual bool isStereoStretched() const = 0;

    /**
     * Gets a projection matrix calibrated for eyewear
     *
     *  - Calculates and returns a calibrated projection matrix.
     *  - init must be called before calling this function.
     *  - It is recommended to use getProjectionMatrices instead on stereo devices.
     * 
     * \param readings  An array of calibration readings
     * \param numReadings  The number of readings taken, poseReadings and scales must be this length
     * \param calibrationResult  Output matrix for the calibrated matrix
     *
     * \return  True if the call is successful, otherwise false
     **/
    virtual bool getProjectionMatrix(EyewearCalibrationReading reading[],
        int numReadings, Matrix34F& cameraToEyePose, Matrix34F& eyeProjection) = 0;

    /**
    * Gets projection matrices calibrated for eyewear
    *
    *  - Calculates and returns a calibrated projection matrices.
    *  - init must be called before calling this function.
    *
    * \param leftReading  An array of calibration readings for the left eye
    * \param rightReading  An array of calibration readings for the right eye
    * \param Readings  The number of readings taken, poseReadings and scales must be this length
    * \param calibrationResult  Output matrix for the calibrated matrix
    *
    * \return  True if the call is successful, otherwise false
    **/
    virtual CONSISTENCY getProjectionMatrices(EyewearCalibrationReading leftReading[],
                                              int numLeftReadings,
                                              EyewearCalibrationReading rightReading[],
                                              int numRightReadings,
                                              Matrix34F& leftCameraToEyePose, Matrix34F& leftEyeProjection,
                                              Matrix34F& rightCameraToEyePose, Matrix34F& rightEyeProjection) = 0;
};

} // namespace Vuforia

#endif //_VUFORIA_EYEWEARUSERCALIBRATOR_H_
