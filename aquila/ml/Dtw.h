/**
 * @file Dtw.h
 *
 * An implementation of the Dynamic Time Warping algorithm.
 *
 * This file is part of the Aquila DSP library.
 * Aquila is free software, licensed under the MIT/X11 License. A copy of
 * the license is provided with the library in the LICENSE file.
 *
 * @package Aquila
 * @version 3.0.0-dev
 * @author Zbigniew Siciarz
 * @date 2007-2013
 * @license http://www.opensource.org/licenses/mit-license.php MIT
 * @since 0.5.7
 */

#ifndef DTW_H
#define DTW_H

#include "../global.h"
#include "../functions.h"
#include "DtwPoint.h"
#include <cstddef>
#include <list>
#include <utility>
#include <vector>

namespace Aquila
{
    /**
     * Type of compared data - vectors of features, which themselves are
     * vectors of doubles.
     */
    typedef std::vector<std::vector<double>> DtwDataType;

    /**
     * Type of DTW point array.
     */
    typedef std::vector<std::vector<DtwPoint>> DtwPointsArrayType;

    /**
     * Type of a single point (x, y) on the DTW lowest-cost path.
     */
    typedef std::pair<std::size_t, std::size_t> DtwPathPointType;

    /**
     * Lowest-cost path is a list of points.
     */
    typedef std::list<DtwPathPointType> DtwPathType;

    class AQUILA_EXPORT Dtw
    {
    public:
        /**
         * Type of lowest-cost passes between points.
         */
        enum PassType {Neighbors, Diagonals};

        /**
         * Creates the DTW algorithm wrapper object.
         *
         * @param distanceFunction which function to use for calculating distance
         */
        Dtw(DistanceFunctionType distanceFunction = euclideanDistance,
            PassType passType = Neighbors):
            m_distanceFunction(distanceFunction), m_passType(passType),
            m_points()
        {
        }

        double getDistance(const DtwDataType& from, const DtwDataType& to);

        /**
         * Returns a const reference to the point array.
         *
         * @return DTW points
         */
        const DtwPointsArrayType& getPoints() const
        {
            return m_points;
        }

        /**
         * Returns the final point on the DTW path (in the top right corner).
         *
         * @return a DTW point
         */
        DtwPoint getFinalPoint() const
        {
            return m_points[m_fromSize - 1][m_toSize - 1];
        }

    private:
        /**
         * Distance definition used in DTW (eg. Euclidean, Manhattan etc).
         */
        DistanceFunctionType m_distanceFunction;

        /**
         * Type of passes between points.
         */
        PassType m_passType;

        /**
         * Array of DTW points.
         */
        DtwPointsArrayType m_points;

        /**
         * Coordinates of the top right corner of the points array.
         */
        std::size_t m_fromSize, m_toSize;
    };
}

#endif // DTW_H
