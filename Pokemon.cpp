

#include <iostream>
#include <stdexcept>

#include "Pokemon.h"

#include "Utils.h"

namespace PokemonGame {


    /**
     * @brief Constructeur de la classe Pokemon.
     * @param name Nom du Pokémon.
     * @param hp Points de vie maximum du Pokémon.
     * @param types Liste des types du Pokémon (1 ou 2 types maximum).
     * @param attackName Nom de l'attaque du Pokémon.
     * @param attackPower Puissance de l'attaque du Pokémon.
     * @throws std::invalid_argument Si les HP sont négatifs ou si le nombre de types est invalide.
     */
    Pokemon::Pokemon(const std::string& name, int hp, const std::vector<Type>& types, const std::string& attackName, int attackPower):
        name_(Utils::String::trimValidateTitle(name, "nom du pokémon")),
        maxHp_(hp),
        hp_(hp),
        types_(types),
        attackName_(Utils::String::trimValidateTitle(attackName, "nom de l'attaque")),
        attackPower_(attackPower)
    {
        if (hp < 0) {
            throw std::invalid_argument("Les HP doivent être positifs.");
        }

        if (types.empty() || types.size() > 2) {
            throw std::invalid_argument("Un pokémon ne peut avoir que 1 ou 2 types.");
        }
    }

    /**
     * @brief Constructeur de copie de la classe Pokemon.
     * @param other Instance de Pokemon à copier.
     */
    Pokemon::Pokemon(const Pokemon& other) :
        name_(other.name_),
        maxHp_(other.maxHp_),
        hp_(other.hp_),
        types_(other.types_),
        attackName_(other.attackName_),
        attackPower_(other.attackPower_)
    {}

    void Pokemon::applyDamage(int damage) {
        hp_ -= std::min(hp_, damage);
    }

    /**
     * @brief Soigne le Pokémon d'un certain montant de points de vie.
     * @param amount Montant de points de vie à soigner.
     */
    void Pokemon::heal(int amount) {
        hp_ += std::min(maxHp_ - hp_, amount);
    }

    void Pokemon::fullHeal() {
        hp_ = maxHp_;
    }

    void Pokemon::displayInfo() const {
        std::cout << name_ << " (" << types_ << ") : " << hp_ << "/" << maxHp_ << "\n";
        std::cout << "   ↳ " << attackName_ << " : " << attackPower_ << std::endl;
    }

    [[nodiscard]] bool Pokemon::isFainted() const {
        return hp_ <= 0;
    }

    /**
     * @brief Interagit avec le Pokémon en affichant un son.
     * @return Une chaîne de caractères représentant le son du Pokémon.
     */
    std::string Pokemon::interact() const {
        std::string sound = name_.substr(0, std::min(name_.length(), static_cast<std::string::size_type>(4)));
        sound += sound;

        return name_ + " : \"" + sound + "...\"";
    }

    std::ostream& operator<<(std::ostream& out, const Pokemon& pokemon) {
        out << pokemon.name_ << " (" << pokemon.types_ << ")";
        return out;
    }

    const std::string& Pokemon::getName() const {
        return name_;
    }

    int Pokemon::getMaxHp() const {
        return maxHp_;
    }

    int Pokemon::getHp() const {
        return hp_;
    }

    /**
     * @brief Récupère les types du Pokémon.
     * @return Référence constante vers le vecteur des types..
     */
    const std::vector<Type>& Pokemon::getTypes() const {
        return types_;
    }

    /**
     * @brief Obtient le nom de l'attaque du Pokémon.
     * @return Référence constante vers le nom de l'attaque.
     */
    const std::string& Pokemon::getAttackName() const {
        return attackName_;
    }

    int Pokemon::getAttackPower() const {
        return attackPower_;
    }

} // PokemonGame