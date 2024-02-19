/*
** EPITECH PROJECT, 2020
** B-YEP-400-MPL-4-1-indiestudio-alec.ferrari
** File description:
** SystemManager.hpp
*/

#pragma once

#include "ECS/types.hpp"
#include "ECS/System.hpp"
#include "lib/Lib.hpp"

namespace ECS
{
    class SystemManager
    {
        public:
            template<typename T>
            std::shared_ptr<T> registerSystem(void)
            {
                TypeId typeName = typeid(T).name();
                if (_systems.find(typeName) != _systems.end())
                    throw lib::Exception("System already registered");

                std::cout << "Making  " << typeName << std::endl;
                auto system = std::make_shared<T>();
                std::cout << "Made  " << typeName << std::endl;
                _systems.insert({typeName, system});
                std::cout << "Inserting  " << typeName << std::endl;
                std::cout << "Registered  " << typeName << std::endl;
                return system;
            }

            template<typename T>
            void setSignature(Signature signature)
            {

                std::cout << "Signing" << std::endl;
                TypeId typeName = typeid(T).name();
                if (_systems.find(typeName) == _systems.end())
                    throw lib::Exception("System isn't registered");

                _signatures.insert({typeName, signature});
            }

            void entityDestroyed(Guid entity);
            void entitySignatureChanged(Guid entity, Signature entitySignature);

        private:
            // The char * is used as a type id (basically a long) as it is system defined and unique.
            // Map from system type string pointer to a signature
            std::unordered_map<TypeId, Signature> _signatures{};

            // Map from system type string pointer to a system pointer
            std::unordered_map<TypeId, std::shared_ptr<System>> _systems{};
    };

} // namespace ECS
