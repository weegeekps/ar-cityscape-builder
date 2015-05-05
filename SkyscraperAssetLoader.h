//
// Created by Adam Morris on 5/3/15.
//

#pragma once

#include <stdio.h>

#include <osg/Group>
#include <osg/Node>
#include <osg/Geode>
#include <osg/ShapeDrawable>
#include <osg/Material>
#include <unordered_map>
#include "Marker.h"
#include "ARTagNode.h"

class SkyscraperAssetLoader {
private:
    osg::Group* rootNode;
public:
    static osg::Group* createBox(float size, osg::Vec4 color, osg::Vec3 location);

    SkyscraperAssetLoader(osg::Group *rootNode);

    void addAsset(osg::ref_ptr<ARTagNode> arTagNode, osg::Group* asset);
    void addAsset(osg::ref_ptr<ARTagNode> arTagNode, std::string path);
};
