/*
 * A derived Field that properly retrieves a steady field from VAPOR.
 */

#ifndef STEADYVAPORFIELD_H
#define STEADYVAPORFIELD_H

#include "vapor/Field.h"
#include "vapor/Grid.h"

namespace flow
{
class SteadyVAPORField : public Field
{

// Define a few alias
using VGrid = VAPoR::Grid;

public:
    SteadyVAPORField();
   ~SteadyVAPORField();

    //
    // Retrieve velocity or field value
    //
    int  GetVelocity(   float time, const glm::vec3& pos, glm::vec3& vel ) const;
    int  GetScalar  (   float time, const glm::vec3& pos, float& val ) const;
    bool InsideVolume(  float time, const glm::vec3& pos ) const;    
    int  GetExtents(    float time, glm::vec3& minExt, glm::vec3& maxExt ) const;

    //
    // Modifiers
    //
    void UseVelocities( const VGrid* u, const VGrid* v, const VGrid* w );
    void UseScalar (    const VGrid* val );

    // 
    // Since the grids are passed in, SteadyVAPORField does NOT destroy them by default.
    // However, SteadyVAPORField could perform this task if desired.
    //
    void DestroyGrids();

private:
    // 
    // These variables keep the steady grids
    //
    const VGrid* _velocityU;
    const VGrid* _velocityV;
    const VGrid* _velocityW;
    const VGrid* _scalar;
};

};

#endif