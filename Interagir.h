//
// Created by olbnf on 16/04/2025.
//

#ifndef INTERAGIR_H
#define INTERAGIR_H

namespace PokemonGame {

    /**
     * @brief Interface pour les classes qui interagissent avec le joueur.
     * Cette interface définit une méthode d'interaction qui doit être implémentée par toutes les classes qui l'héritent.
     */
    class Interagir {
    public:
        virtual ~Interagir() = default;
        [[nodiscard]] virtual std::string interact() const = 0;
    };

}

#endif //INTERAGIR_H
