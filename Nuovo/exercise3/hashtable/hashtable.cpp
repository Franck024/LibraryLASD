
namespace lasd {

/* ************************************************************************** */

template <typename Data>
ulong Hasable::operator()(const Data& key) const noexcept{
    // Creare un generatore di numeri casuali.
    std::mt19937 generator(std::random_device{}());

    // Mescola i dati in modo casuale.
    std::shuffle(key.begin(), key.end(), generator);

    // Calcola l'hash code basato sui dati mescolati.
    ulong hash = 0;
    for (const auto& element : key) {
      hash ^= std::hash<decltype(element)>()(element);
    }

    return hash;
}

/* ************************************************************************** */

}
