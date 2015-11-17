// 
// File:   tk2CMSSWFull.h
// Author: ndemaio
//
// Created on August 28, 2009, 5:23 PM
//

/**
 * @file tk2CMSSWFull.h
 * @brief This is the header file for the CMSSW XML translator class
 */

#ifndef _TK2CMSSWFULL_H
#define	_TK2CMSSWFULL_H

#include <tk2CMSSW_datatypes.h>
#include <tk2CMSSW_strings.h>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <pwd.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <Extractor.h>
#include <PixelExtractor.h>

#include <XMLWriter.h>
#include <MaterialTable.h>
#include <MaterialBudget.h>
#include <mainConfigHandler.h>
#include <boost/filesystem/exception.hpp>
#include <boost/filesystem/operations.hpp>

using boost::property_tree::ptree;
/**
 * A shorter alias for the filesystem library namespace
 */
namespace bfs = boost::filesystem;
namespace insur {
    /**
     * @class tk2CMSSWFull
     * @brief This class is the main translator interface for generating XML output for CMSSW from an existing material budget and table.
     *
     * It deals directly with setting up output paths and buffers for output files, while it delegates analysis and XML formatting of the material 
     * budget to an internal instance of <i>Extractor</i> and <i>XMLWriter</i>, respectively. Existing files are not overwritten until analysis
     * and XML formatting have been completed successfully. Should any of them fail, any existing older files are restored; preliminary
     * results for the new files are discarded.
     */
    class tk2CMSSWFull {
        mainConfigHandler& mainConfiguration;
    public:
        tk2CMSSWFull(mainConfigHandler& mch) : mainConfiguration(mch) {}
        virtual ~tk2CMSSWFull() {}
        void translateOuterTracker(MaterialTable& mt, MaterialBudget& mb, std::string outsubdir = "", bool wt = false);
        void translateInnerPixel(MaterialTable& mt, MaterialBudget& mb, std::string outsubdir = "", bool wt = false);
 
    protected:
        CMSSWBundle otdata, pixdata;
        Extractor otex;
        PixelExtractor pex;
        XMLWriter wr;
    private:
        //std::vector<ConfigFile> configFiles_;
        void print(CMSSWBundle data);
        void printPixelXml(const CMSSWBundle& cmsswXmlInfo, mainConfigHandler& mainConfiguration,
                           const std::vector<std::string> barrelRmatpath,
                           const std::vector<std::string> ecapRmatpath,
                           const unsigned int numBarrelLayers,
                           const std::vector<std::pair<unsigned int,unsigned int>> discRingpair,
                           std::string outsubdir);
        void printOuterTrackerXml(const CMSSWBundle& cmsswXmlInfo, mainConfigHandler& mainConfiguration,
                                  std::string outsubdir);

        void writeMaterialSection( ptree& tree, const std::vector<Element>& elements,
                                   const std::vector<Composite>& composites,
                                   const string label, const string nameSpace);
        void writeSolidSection( ptree& tree, const std::vector<ShapeInfo>& shapes, const string label);
        void writeRotationSection( ptree& tree, const string label);
        void writeLogicalPartSection( ptree& tree, const std::vector<LogicalInfo>& logic, const string label);
        void writePosPartSection( ptree& tree, const std::vector<PosInfo>& positions,
                                  const std::vector<AlgoInfo>& algos,const string label);
        void writeStructureTopology( ptree& tree_topo, const std::vector<SpecParInfo>& specs, const string& nameSpace,
                                     std::vector<std::string>& barrel_partselectors,
                                     std::vector<std::string>& endcap_partselectors);
        void writeSens( ptree& tree_sense, const string& nameSpace,
                        const string& barrelDet, const string& endcapDet,
                        std::vector<std::string>& barrel_partselectors,
                        std::vector<std::string>& endcap_partselectors);
        void writeProdCuts( ptree& tree_prodCut, const string& nameSpace,
                       const string& barrelDet, const string& endcapDet,
                       std::vector<std::string>& barrel_partselectors,
                       std::vector<std::string>& endcap_partselectors);
    };
}
#endif	/* _TK2CMSSW_H */

