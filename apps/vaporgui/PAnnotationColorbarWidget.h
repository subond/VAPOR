#pragma once

#include "PWidget.h"

class PSection;

//! \class PAnnotationColorbarWidget
//! \brief Widget that provides controls for configuring the colorbar legend.
//! \author Stas Jaroszynski
//!
//! The design is translated from the original implementation.

class PAnnotationColorbarWidget : public PWidget {
    PSection *_pSection;
public:
    PAnnotationColorbarWidget();
protected:
    void updateGUI() const override;
};
