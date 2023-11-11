#pragma once

#include "Resource.hpp"

class ResourceManager
{
    private:
        Resource* resource;  // wskaźnik do zarządzanego zasobu
    public:
        // konstruktor domyślny
        ResourceManager() : resource(new Resource()) {}

        double get()
        {
            return resource -> get();
        }

    ResourceManager(const ResourceManager& rm)
    {
        cout << "konstruktor kopiujacy"<< endl;
        resource = new Resource(*rm.resource);
    }

    // konstruktor przenoszący
    ResourceManager(ResourceManager&& rm) noexcept
    {
        cout << "konstruktor przenoszący"<< endl;
        resource = new Resource(move(*rm.resource));
    }
    ResourceManager& operator=(const ResourceManager& rm)
    {
        cout << "operator przypisania"<< endl;
        if (this == &rm) {
            return *this;
        }
        delete resource;
        resource = new Resource(*rm.resource);
        return *this;
    }

    ResourceManager& operator=(ResourceManager&& rm) noexcept
    {
        cout << "przenoszący operator przypisania"<< endl;
        if (this == &rm) {
            return *this;
        }

        resource = new Resource(move(*rm.resource));
    }
    ~ResourceManager()
    {
        delete resource;
    }
};
