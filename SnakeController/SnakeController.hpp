#pragma once

#include <functional>
#include <algorithm>
#include <sstream>
#include <memory>
#include <list>

#include "IEventHandler.hpp"
#include "SnakeInterface.hpp"
#include "FoodController.hpp"
#include "Exceptions.hpp"
#include "EventT.hpp"
#include "IPort.hpp"

class Event;
class IPort;

namespace Snake
{


class Controller : public IEventHandler, public FoodController
{
public:
    Controller(IPort& p_displayPort, IPort& p_scorePort, std::string const& p_config);

    Controller(Controller const& p_rhs) = delete;
    Controller& operator=(Controller const& p_rhs) = delete;

    void receive(std::unique_ptr<Event> e) override;

private:
    IPort& m_scorePort;
    IPort& m_displayPort;

    std::pair<int, int> m_mapDimension;


    struct Segment
    {
        int x;
        int y;
    };

    std::list<Segment> m_segments;
    Direction m_currentDirection;

    void handleTimeoutInd();
    void handleDirectionInd(std::unique_ptr<Event>);
    void handlePauseInd(std::unique_ptr<Event>);

    bool isSegmentAtPosition(int x, int y) const;
    Segment calculateNewHead() const;
    void updateSegmentsIfSuccessfullMove(Segment const& newHead);
    void addHeadSegment(Segment const& newHead);
    void removeTailSegmentIfNotScored(Segment const& newHead);
    void removeTailSegment();

    bool isPositionOutsideMap(int x, int y) const;



    bool m_paused;
};

} // namespace Snake
