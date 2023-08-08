
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
bool FoldableContainer<Data>::Exists(const Data& data) const noexcept{
    struct ExistsFoldFunctor {
        const Data& targetData;
        bool result = false;

        ExistsFoldFunctor(const Data& data) : targetData(data) {}

        void operator()(const Data& currentData, void*) {
            if (currentData == targetData) {
                result = true;
            }
        }
    };

    ExistsFoldFunctor existsFoldFunctor(data);
    Fold(existsFoldFunctor, nullptr);

    return existsFoldFunctor.result;
}

/* ************************************************************************** */

}
