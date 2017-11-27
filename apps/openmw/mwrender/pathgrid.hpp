#ifndef GAME_RENDER_MWSCENE_H
#define GAME_RENDER_MWSCENE_H

#include <utility>

#include <vector>
#include <string>
#include <map>

#include <osg/ref_ptr>

namespace ESM
{
    struct Pathgrid;
}

namespace osg
{
    class Group;
    class Geometry;
}

namespace MWWorld
{
    class Ptr;
    class CellStore;
}

namespace MWRender
{
    /// \brief Handles rendering of the AI path grid.
    class Pathgrid
    {
        bool mPathgridEnabled;

        /// Turn pathgrid rendering on/off.
        void togglePathgrid();

        typedef std::vector<const MWWorld::CellStore *> CellList;
        CellList mActiveCells;

        osg::ref_ptr<osg::Group> mRootNode;

        osg::ref_ptr<osg::Group> mPathGridRoot;

        typedef std::map<std::pair<int,int>, osg::ref_ptr<osg::Group> > ExteriorPathgridNodes;
        ExteriorPathgridNodes mExteriorPathgridNodes;
        osg::ref_ptr<osg::Group> mInteriorPathgridNode;

        void enableCellPathgrid(const MWWorld::CellStore *store);
        void disableCellPathgrid(const MWWorld::CellStore *store);

    public:
        Pathgrid(osg::ref_ptr<osg::Group> root);
        ~Pathgrid();

        /// React to given render mode being set.
        /// @param mode render mode (defined in rendermode.hpp)
        bool toggleRenderMode (int mode);

        void addCell(const MWWorld::CellStore* store);
        void removeCell(const MWWorld::CellStore* store);
    };


}

#endif
