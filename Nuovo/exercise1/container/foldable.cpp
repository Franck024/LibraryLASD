
#include <stdexcept>

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */
// template <typename Data>
// bool AuxFoldExist(const Data& data, const void* val){
//     if (data == *((Data*) val))
//         return true;
//     return false;
// }

// template <typename Data>
// bool FoldableContainer<Data>::Exists(const Data& data) const noexcept{
//     bool exists = false;
//     exists = Fold(&AuxFoldExist<Data>, &data);
//     return exists;
// }

template <typename Data>
bool FoldableContainer<Data>::Exists(const Data& item) const noexcept {
    bool exists = false;

    // Implementazione specifica per verificare l'esistenza dell'elemento 'item' nel contenitore
    Fold([&](const Data& data, void* context) {
        if (data == item) {
            exists = true;
            // Stop folding since the item has been found
            *reinterpret_cast<bool*>(context) = true;
        }
    }, &exists);

    return exists;
}


/* ************************************************************************** */

}
