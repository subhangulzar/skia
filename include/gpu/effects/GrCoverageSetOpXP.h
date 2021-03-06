/*
 * Copyright 2014 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef GrCoverageSetOpXP_DEFINED
#define GrCoverageSetOpXP_DEFINED

#include "GrTypes.h"
#include "GrXferProcessor.h"
#include "SkRegion.h"

class GrProcOptInfo;

/**
 * This xfer processor directly blends the the src coverage with the dst using a set operator. It is
 * useful for rendering coverage masks using CSG. It can optionally invert the src coverage before
 * applying the set operator.
 */
class GrCoverageSetOpXPFactory : public GrXPFactory {
public:
    static GrXPFactory* Create(SkRegion::Op regionOp, bool invertCoverage = false);

    bool supportsRGBCoverage(GrColor /*knownColor*/,
                             uint32_t /*knownColorFlags*/) const override {
        return true;
    }

    void getInvariantOutput(const GrProcOptInfo& colorPOI, const GrProcOptInfo& coveragePOI,
                            GrXPFactory::InvariantOutput*) const override;

private:
    GrCoverageSetOpXPFactory(SkRegion::Op regionOp, bool invertCoverage);

    GrXferProcessor* onCreateXferProcessor(const GrCaps& caps,
                                           const GrProcOptInfo& colorPOI,
                                           const GrProcOptInfo& coveragePOI,
                                           const GrDeviceCoordTexture* dstCopy) const override;

    bool willReadDstColor(const GrCaps& /*caps*/,
                          const GrProcOptInfo& /*colorPOI*/,
                          const GrProcOptInfo& /*coveragePOI*/) const override {
        return false;
    }

    bool onIsEqual(const GrXPFactory& xpfBase) const override {
        const GrCoverageSetOpXPFactory& xpf = xpfBase.cast<GrCoverageSetOpXPFactory>();
        return fRegionOp == xpf.fRegionOp;
    }

    GR_DECLARE_XP_FACTORY_TEST;

    SkRegion::Op fRegionOp;
    bool         fInvertCoverage;

    typedef GrXPFactory INHERITED;
};
#endif

