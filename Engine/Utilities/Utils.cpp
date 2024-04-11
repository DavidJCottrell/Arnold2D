#include "Utils.h"

Coordinates Utils::normalise(Coordinates coordinates) {
    Coordinates normalisedCoordinates = coordinates;
    double vecMagnitude = sqrt(pow(coordinates.x, 2) + pow(coordinates.y, 2));
    if (vecMagnitude > 0) {
        normalisedCoordinates.x /= (float) vecMagnitude;
        normalisedCoordinates.y /= (float) vecMagnitude;
    }
    return normalisedCoordinates;
}
