/*
 * Fimex
 *
 * (C) Copyright 2011-2019, met.no
 *
 * Project Info:  https://wiki.met.no/fimex/start
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
 * License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301,
 * USA.
 */

/**
  * Used as private/implementation class
  */

#ifndef METGM_GROUP5PTR_H
#define METGM_GROUP5PTR_H

// metgm
//
#include "metgm.h"

// internals
//
#include "MetGmGroup3Ptr.h"
#include "MetGmDimensionsTag.h"

// fimex
//
#include "fimex/CDMReader.h"
#include "fimex/CDMVariable.h"
#include "fimex/SharedArray.h"

#include <memory>

namespace MetNoFimex {

    class MetGmGroup5Ptr {
    public:
        static std::shared_ptr<MetGmGroup5Ptr> createMetGmGroup5PtrForWriting(const CDMReader_p pCdmReader, const CDMVariable* pVariable,
                                                                              const std::shared_ptr<MetGmGroup3Ptr> gp3);

        static std::shared_ptr<MetGmGroup5Ptr> createMetGmGroup5PtrForReading(const std::shared_ptr<MetGmGroup3Ptr> gp3,
                                                                              const std::shared_ptr<MetGmHDTag> hdTag);

        static std::shared_ptr<MetGmGroup5Ptr> createMetGmGroup5PtrForSlicedReading(const std::shared_ptr<MetGmGroup3Ptr> gp3,
                                                                                    const std::shared_ptr<MetGmHDTag> hdTag);

        static std::shared_ptr<MetGmGroup5Ptr> createMetGmGroup5PtrForSlicedWriting(const CDMReader_p pCdmReader, const CDMVariable* pVariable,
                                                                                    const std::shared_ptr<MetGmGroup3Ptr> gp3);

        void sliceToMetGmLayout(shared_array<float>& slice);

        shared_array<float> readDataSlices(size_t pos, size_t numberOfSlices);

        void dumpFimexLayout();
        void dumpMetGmLayout();

        shared_array<float>& data() { return data_; }
        std::string units() {return units_; }

    private:

        void toFimexLayout();
        void slicesToFimexLayout(shared_array<float>& slices, size_t numberOfSlices);

        // reorder z-axis and set fill-values
        void toMetGmLayout();

        explicit MetGmGroup5Ptr(const std::shared_ptr<MetGmGroup3Ptr> gp3, const std::shared_ptr<MetGmHDTag> hdTag, const shared_array<float> data,
                                const std::string fillValue = std::string());

        const std::shared_ptr<MetGmGroup3Ptr> pGp3_;
        const std::shared_ptr<MetGmHDTag> hdTag_;

        long sOffset_;
        long eOffset_;
        shared_array<float> data_;
        std::string                   fillValue_;
        std::string                   units_;
    };

}

#endif // METGM_GROUP5PTR_H
