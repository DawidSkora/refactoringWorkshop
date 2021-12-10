#include "FoodController.hpp"

FoodController::FoodController(IPort& p_foodPort) : m_foodPort(p_foodPort)
{}

void FoodController::handleFoodInd(std::unique_ptr<Event> e)
{
    auto receivedFood = payload<FoodInd>(*e);

    updateFoodPosition(receivedFood.x, receivedFood.y, std::bind(&FoodController::sendClearOldFood, this));
}

void FoodController::handleFoodResp(std::unique_ptr<Event> e)
{
    auto requestedFood = payload<FoodResp>(*e);

    updateFoodPosition(requestedFood.x, requestedFood.y, []{});
}

void FoodController::updateFoodPosition(int x, int y, std::function<void()> clearPolicy)
{
        if (isSegmentAtPosition(x, y)) {
            m_foodPort.send(std::make_unique<EventT<FoodReq>>());
            return;
        }

        if (isPositionOutsideMap(x, y)) {
            m_foodPort.send(std::make_unique<EventT<FoodReq>>());
            return;
        }

        clearPolicy();
        sendPlaceNewFood(x, y);
}

void FoodController::sendPlaceNewFood(int x, int y)
{
    m_foodPosition = std::make_pair(x, y);

    DisplayInd placeNewFood;
    placeNewFood.x = x;
    placeNewFood.y = y;
    placeNewFood.value = Cell_FOOD;

    //m_displayPort.send(std::make_unique<EventT<DisplayInd>>(placeNewFood));
}

void FoodController::sendClearOldFood()
{
    DisplayInd clearOldFood;
    clearOldFood.x = m_foodPosition.first;
    clearOldFood.y = m_foodPosition.second;
    clearOldFood.value = Cell_FREE;

    //m_displayPort.send(std::make_unique<EventT<DisplayInd>>(clearOldFood));
}