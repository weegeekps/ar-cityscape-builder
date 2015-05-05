//
// Created by Adam Morris on 5/3/15.
//

#include "SkyscraperAssetLoader.h"
#include "ARTagNode.h"

// Static Methods
osg::Group*SkyscraperAssetLoader::createBox(float size, osg::Vec4 color, osg::Vec3 location) {
    osg::Group* group = new osg::Group();
    osg::Geode* geode = new osg::Geode();

    osg::ShapeDrawable* unitCubeDrawable = new osg::ShapeDrawable(new osg::Box(location, size));

    osg::Material* material = new osg::Material();
    material->setDiffuse(osg::Material::FRONT_AND_BACK, color);

    unitCubeDrawable->getOrCreateStateSet()->setAttributeAndModes(material);
    unitCubeDrawable->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::ON);

    geode->addDrawable(unitCubeDrawable);
    group->addChild(geode);

    return group;
}

// Ctors
SkyscraperAssetLoader::SkyscraperAssetLoader(osg::Group *rootNode) {
    this->rootNode = rootNode;
}

// Public Methods
void SkyscraperAssetLoader::addAsset(osg::ref_ptr<ARTagNode> arTagNode, osg::Group *asset) {
    arTagNode->addChild(asset);
    this->rootNode->addChild(arTagNode);
}

void SkyscraperAssetLoader::addAsset(osg::ref_ptr<ARTagNode> arTagNode, std::string path) {
    osg::Group* asset = (osg::Group*)osgDB::readNodeFile(path);

    if (!asset) {
        std::cerr << "Could not load model at path: " << path << std::endl;
        return;
    }

    this->addAsset(arTagNode, asset);
}
