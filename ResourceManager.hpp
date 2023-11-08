#pragma once

#include "Resource.hpp"

class ResourceManager
{
    private:
    Resource* resource;  // wskaźnik do zarządzanego zasobu

public:
    // konstruktor domyślny
    ResourceManager() : resource(new Resource()) {}

    // konstruktor kopiujący
    ResourceManager(const ResourceManager& other) : resource(new Resource(*(other.resource))) {
        ++copies;
        ++live;
    }

    // operator przypisania
    ResourceManager& operator=(const ResourceManager& other) {
        if (this != &other) {
            delete resource;  // zwalniamy obecny zasób
            resource = new Resource(*(other.resource));  // alokujemy i kopiujemy nowy zasób
            ++cp_asgn;
        }
        return *this;
    }

    // konstruktor przenoszący
    ResourceManager(ResourceManager&& other) noexcept : resource(other.resource) {
        other.resource = nullptr;  // zapobiegamy zwolnieniu tego samego zasobu przez obiekt źródłowy
        ++moves;
        ++live;
    }

    // operator przypisania przenoszący
    ResourceManager& operator=(ResourceManager&& other) noexcept {
        if (this != &other) {
            delete resource;  // zwalniamy obecny zasób
            resource = other.resource;  // przenosimy zasób
            other.resource = nullptr;  // zapobiegamy zwolnieniu tego samego zasobu przez obiekt źródłowy
            ++mv_asgn;
        }
        return *this;
    }

    // destruktor
    ~ResourceManager() {
        delete resource;  // zwalniamy zarządzany zasób
        ++destr;
        --live;
    }

    double get() const {
        // metoda zwracająca wynik zasobu
        return resource->get();
    }
};
