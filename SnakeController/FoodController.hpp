#pragma once
#include "SnakeInterface.hpp"
#include "IEventHandler.hpp"
#include "EventT.hpp"
#include "IPort.hpp"

#include <functional>
#include <memory>

class Event;
class IPort;

class FoodController {
public:
    FoodController(IPort& p_foodPort);

    FoodController(FoodController const& p_rhs) = delete;
    FoodController& operator=(FoodController const& p_rhs) = delete;

    void handleFoodInd(std::unique_ptr<Event>);
    void handleFoodResp(std::unique_ptr<Event>);
    void updateFoodPosition(int x, int y, std::function<void()> clearPolicy);
    void sendClearOldFood();
    void sendPlaceNewFood(int x, int y);

    virtual bool isSegmentAtPosition(int x, int y) const  = 0;
    virtual bool isPositionOutsideMap(int x, int y) const  = 0;

protected:
    std::pair<int, int> m_foodPosition;
    //IPort& m_displayPort;
    IPort& m_foodPort;
};