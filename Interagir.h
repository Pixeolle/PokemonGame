//
// Created by olbnf on 16/04/2025.
//

#ifndef INTERAGIR_H
#define INTERAGIR_H

namespace PokemonGame {

    class Interagir {
    public:
        virtual ~Interagir() = default;
        virtual void interact() const = 0;
    };

}

#endif //INTERAGIR_H
