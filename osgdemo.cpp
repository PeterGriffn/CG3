#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgDB/ReadFile>
#include <osg/MatrixTransform>


class Particle : public osg::MatrixTransform
{
public:
    Particle(osg::Node* child);
    virtual ~Particle() {}

    virtual void traverse(osg::NodeVisitor& nv);

private:
    osg::Vec3d _pos;
    osg::Vec3d _vel;
};


int main(int argc,char** argv)
{
    osg::ArgumentParser arguments(&argc, argv);

    osg::ref_ptr<osg::Group> group = new osg::Group;
    osg::ref_ptr<osg::Node> cow = osgDB::readNodeFile("cow.osg");

    std::vector< osg::ref_ptr<Particle> > particles;
    for (int i = 0; i < 3000; ++i)
    {
        osg::ref_ptr<Particle> particle = new Particle(cow.get());
        group->addChild(particle.get());
        particles.push_back(particle);
    }

    osgViewer::Viewer viewer(arguments);
    viewer.setSceneData(group.get());
    viewer.addEventHandler(new osgViewer::StatsHandler);
    viewer.addEventHandler(new osgViewer::HelpHandler);
    return viewer.run();
}


Particle::Particle(osg::Node *child)
    : _pos(0.0, 0.0, 0.1),
      _vel(0.0, 0.0, 0.1)
{
    addChild(child);
    setNumChildrenRequiringUpdateTraversal(1);
}

void Particle::traverse(osg::NodeVisitor &nv)
{
    if (nv.getVisitorType() == osg::NodeVisitor::UPDATE_VISITOR)
    {
        if (_pos.z() < 0.0 || _pos.z() > 1000.0)
        {
            _pos = osg::Vec3d(0.0, 0.0, 0.0);
            double vx = -1.0 + 2.0 * static_cast<double>(rand()) / RAND_MAX;
            double vy = -1.0 + 2.0 * static_cast<double>(rand()) / RAND_MAX;
            double vz = 8.0 + 2.0 * static_cast<double>(rand()) / RAND_MAX;
            _vel = osg::Vec3d(vx, vy, vz);
        }
        if(_vel.z() < -3.0)
        {
             _vel += osg::Vec3d(0.0, 0.0, 6.0);
        }
        _pos += _vel;
        _vel += osg::Vec3d(0.0, 0.0, -0.1);
        setMatrix(osg::Matrix(1.0, 0, 0, 0,
                              0, 1.0, 0, 0,
                              0, 0, 1.0, 0,
                              _pos.x(), _pos.y(), _pos.z(), 1.0));

    }
   osg::MatrixTransform::traverse(nv);
}
